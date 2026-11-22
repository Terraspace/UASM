/* Read linked CodeView/PDB locations with Microsoft DIA, then verify actual
 * bytes in a debugged child at its INT 3 checkpoints. No VS UI automation or
 * COM registration is required. See codeview_locations.cmd. */
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <cvconst.h>
#include <dbghelp.h>
#include <dia2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static HANDLE process;
static CONTEXT ctx;
static unsigned checks, failures, stops, seen;
static DWORD64 regvalue(ULONG r) {
  switch (r) {
  case 328:
    return ctx.Rax;
  case 329:
    return ctx.Rbx;
  case 330:
    return ctx.Rcx;
  case 331:
    return ctx.Rdx;
  case 332:
    return ctx.Rsi;
  case 333:
    return ctx.Rdi;
  case 334:
    return ctx.Rbp;
  case 335:
    return ctx.Rsp;
  case 336:
    return ctx.R8;
  case 337:
    return ctx.R9;
  case 338:
    return ctx.R10;
  case 339:
    return ctx.R11;
  case 340:
    return ctx.R12;
  case 341:
    return ctx.R13;
  case 342:
    return ctx.R14;
  case 343:
    return ctx.R15;
  }
  return 0;
}
static BOOL CALLBACK symbol(PSYMBOL_INFO s, ULONG bytes, void *unused) {
  unsigned char got[32] = {0}, want[32] = {0};
  SIZE_T done;
  unsigned n = 8;
  uint64_t bits = 0;
  int pointer = 0;
  if (strncmp(s->Name, "arg_", 4) && strncmp(s->Name, "local_", 6))
    return TRUE;
  seen++;
  if (!strcmp(s->Name, "arg_i"))
    bits = 0x1122334455667788ULL;
  else if (!strcmp(s->Name, "arg_d"))
    bits = 0x400a000000000000ULL;
  else if (!strcmp(s->Name, "arg_f")) {
    bits = 0x3fc00000;
    n = 4;
  } else if (!strcmp(s->Name, "arg_tail"))
    bits = 0x55667788;
  else if (!strcmp(s->Name, "arg_last"))
    bits = 99;
  else if (!strcmp(s->Name, "local_i"))
    bits = 42;
  else if (!strcmp(s->Name, "local_d"))
    bits = 0x401a000000000000ULL;
  else if (strstr(s->Name, "ptr"))
    pointer = 1;
  else if (strstr(s->Name, "vec")) {
    float v[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    n = strstr(s->Name, "256") ? 32 : 16;
    memcpy(want, v, n);
  } else if (!strcmp(s->Name, "arg_big")) {
    uint64_t v[3] = {123, 0x401a000000000000ULL, 77};
    n = 20;
    memcpy(want, v, n);
  } else if (!strcmp(s->Name, "arg_hfa")) {
    float v[2] = {5, 6};
    if (s->Flags & SYMFLAG_REGISTER) {
      n = 4;
      memcpy(want, ((char *)v) + (unsigned)s->Value, 4);
    } else
      memcpy(want, v, 8);
  } else
    return TRUE;
  if (bits)
    memcpy(want, &bits, n);
  unsigned read_size = (s->Flags & 0x80000000) ? 8 : n;
  if (s->Flags & SYMFLAG_REGREL) {
    DWORD64 at = regvalue(s->Register) + (int64_t)s->Address;
    if (!ReadProcessMemory(process, (void *)at, got, read_size, &done)) {
      printf("READ FAIL %s reg%lu off%lld err%lu\n", s->Name, s->Register,
             (int64_t)s->Address, GetLastError());
      failures++;
      return TRUE;
    }
  } else if (s->Flags & SYMFLAG_REGISTER) {
    if (s->Register >= 154 && s->Register <= 161)
      memcpy(got, (&ctx.Xmm0) + (s->Register - 154), n);
    else {
      uint64_t v = regvalue(s->Register);
      memcpy(got, &v, n);
    }
  } else {
    printf("LOCATION %s flags%lx reg%lu address%llx\n", s->Name, s->Flags,
           s->Register, s->Address);
    failures++;
    return TRUE;
  }
  if (s->Flags & 0x80000000) {
    uint64_t address;
    memcpy(&address, got, 8);
    if (!ReadProcessMemory(process, (void *)address, got, n, &done)) {
      failures++;
      return TRUE;
    }
  }
  if (pointer) {
    uint64_t address;
    memcpy(&address, got, 8);
    bits = 0;
    ReadProcessMemory(process, (void *)address, &bits, 8, &done);
    if (bits == 123) {
      checks++;
      return TRUE;
    }
  } else if (!memcmp(got, want, n)) {
    checks++;
    return TRUE;
  }
  printf("FAIL %s flags%lx reg%lu off%lld got", s->Name, s->Flags, s->Register,
         (int64_t)s->Address);
  for (unsigned i = 0; i < n; i++)
    printf("%02x", got[i]);
  printf("\n");
  failures++;
  return TRUE;
}

int main(int argc, char **argv) {
  STARTUPINFOA si = {sizeof(si)};
  PROCESS_INFORMATION pi = {0};
  DEBUG_EVENT ev;
  BOOL active = TRUE;
  char cmd[MAX_PATH + 8];
  IDiaDataSource *source = NULL;
  IDiaSession *session = NULL;
  IClassFactory *factory = NULL;
  wchar_t pdb[MAX_PATH];
  if (argc < 4 || argc > 6)
    return 2;
  unsigned expected_stops = argc >= 5 ? (unsigned)atoi(argv[4]) : 9;
  unsigned expected_checks = argc == 6 ? (unsigned)atoi(argv[5]) : 76;
  CoInitialize(NULL);
  HMODULE dll = LoadLibraryA(argv[3]);
  if (!dll) {
    printf("DIA DLL error %lu\n", GetLastError());
    return 2;
  }
  typedef HRESULT(WINAPI * getclass)(REFCLSID, REFIID, LPVOID *);
  getclass get = (getclass)GetProcAddress(dll, "DllGetClassObject");
  HRESULT hr = get(__uuidof(DiaSource), IID_IClassFactory, (void **)&factory);
  if (SUCCEEDED(hr))
    hr = factory->CreateInstance(NULL, __uuidof(IDiaDataSource),
                                 (void **)&source);
  MultiByteToWideChar(CP_ACP, 0, argv[2], -1, pdb, MAX_PATH);
  if (SUCCEEDED(hr))
    hr = source->loadDataFromPdb(pdb);
  if (SUCCEEDED(hr))
    hr = source->openSession(&session);
  if (FAILED(hr)) {
    printf("DIA load %lx\n", hr);
    return 2;
  }
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
  snprintf(cmd, sizeof(cmd), "\"%s\"", argv[1]);
  if (!CreateProcessA(NULL, cmd, NULL, NULL, FALSE,
                      DEBUG_ONLY_THIS_PROCESS | CREATE_NO_WINDOW, NULL, NULL,
                      &si, &pi))
    return 2;
  process = pi.hProcess;
  while (active && WaitForDebugEvent(&ev, 15000)) {
    DWORD status = DBG_CONTINUE;
    if (ev.dwDebugEventCode == CREATE_PROCESS_DEBUG_EVENT) {
      session->put_loadAddress((ULONGLONG)ev.u.CreateProcessInfo.lpBaseOfImage);
      if (ev.u.CreateProcessInfo.hFile)
        CloseHandle(ev.u.CreateProcessInfo.hFile);
    } else if (ev.dwDebugEventCode == LOAD_DLL_DEBUG_EVENT) {
      if (ev.u.LoadDll.hFile)
        CloseHandle(ev.u.LoadDll.hFile);
    } else if (ev.dwDebugEventCode == EXCEPTION_DEBUG_EVENT) {
      if (ev.u.Exception.ExceptionRecord.ExceptionCode ==
          EXCEPTION_BREAKPOINT) {
        ctx.ContextFlags = CONTEXT_ALL;
        GetThreadContext(pi.hThread, &ctx);
        IDiaSymbol *fn = NULL;
        if (session->findSymbolByVA(
                (ULONGLONG)ev.u.Exception.ExceptionRecord.ExceptionAddress,
                SymTagFunction, &fn) == S_OK) {
          BSTR name = NULL;
          fn->get_name(&name);
          printf("STOP %ls\n", name);
          SysFreeString(name);
          stops++;
          seen = 0;
          IDiaEnumSymbols *locals = NULL;
          if (session->findChildrenExByVA(
                  fn, SymTagData, NULL, nsNone,
                  (ULONGLONG)ev.u.Exception.ExceptionRecord.ExceptionAddress,
                  &locals) == S_OK) {
            IDiaSymbol *local;
            ULONG fetched;
            while (locals->Next(1, &local, &fetched) == S_OK) {
              char storage[sizeof(SYMBOL_INFO) + MAX_SYM_NAME] = {0};
              PSYMBOL_INFO record = (PSYMBOL_INFO)storage;
              DWORD location = 0, reg = 0;
              LONG offset = 0;
              local->get_name(&name);
              WideCharToMultiByte(CP_ACP, 0, name, -1, record->Name,
                                  MAX_SYM_NAME, NULL, NULL);
              SysFreeString(name);
              local->get_locationType(&location);
              local->get_registerId(&reg);
              local->get_offset(&offset);
              DWORD member = 0;
              local->get_offsetInUdt(&member);
              record->Value = member;
              record->Register = reg;
              record->Address = (int64_t)offset;
              if (location == LocIsRegRel)
                record->Flags = SYMFLAG_REGREL;
              else if (location == LocIsEnregistered)
                record->Flags = SYMFLAG_REGISTER;
              IDiaSymbol *type = NULL;
              BOOL reference = FALSE;
              if (local->get_type(&type) == S_OK) {
                type->get_reference(&reference);
                type->Release();
              }
              if (reference)
                record->Flags |= 0x80000000;
              symbol(record, 0, NULL);
              local->Release();
            }
            locals->Release();
          }
          if (!seen) {
            printf("NO LOCALS\n");
            failures++;
          }
          fn->Release();
        }
      } else {
        printf("exception %lx\n", ev.u.Exception.ExceptionRecord.ExceptionCode);
        failures++;
        status = DBG_EXCEPTION_NOT_HANDLED;
      }
    } else if (ev.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) {
      active = FALSE;
      if (ev.u.ExitProcess.dwExitCode)
        failures++;
    }
    ContinueDebugEvent(ev.dwProcessId, ev.dwThreadId, status);
  }
  session->Release();
  source->Release();
  factory->Release();
  CoUninitialize();
  CloseHandle(pi.hThread);
  CloseHandle(pi.hProcess);
  printf("CodeView live locations: %u stops, %u checks, %u failures\n", stops,
         checks, failures);
  return failures || stops != expected_stops || checks != expected_checks;
}
