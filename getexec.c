//   dual licensed under the WTFPL v2 and MIT licenses
//   without any warranty.
//   by Gregory Pakosz (@gpakosz)
// https://github.com/gpakosz/whereami

#include <stdlib.h>

#if !defined(GEX_MALLOC)
#define GEX_MALLOC(size) malloc(size)
#endif

#if !defined(GEX_FREE)
#define GEX_FREE(p) free(p)
#endif

#if !defined(GEX_REALLOC)
#define GEX_REALLOC(p, size) realloc(p, size)
#endif

#if defined(_WIN32)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#if defined(_MSC_VER)
#pragma warning(push, 3)
#endif
#include <windows.h>
#include <intrin.h>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#elif defined(__linux__) || defined(__CYGWIN__) || defined(__sun) || defined(GEX_USE_PROC_SELF_EXE)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__linux__)
#include <linux/limits.h>
#else
#include <limits.h>
#endif
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>
#include <unistd.h>

#if !defined(GEX_PROC_SELF_EXE)
#if defined(__sun)
#define GEX_PROC_SELF_EXE "/proc/self/path/a.out"
#else
#define GEX_PROC_SELF_EXE "/proc/self/exe"
#endif
#endif

#if !defined(GEX_PROC_SELF_MAPS_RETRY)
#define GEX_PROC_SELF_MAPS_RETRY 5
#endif

#if !defined(GEX_PROC_SELF_MAPS)
#if defined(__sun)
#define GEX_PROC_SELF_MAPS "/proc/self/map"
#else
#define GEX_PROC_SELF_MAPS "/proc/self/maps"
#endif
#endif

#if defined(__ANDROID__) || defined(ANDROID)
#include <fcntl.h>
#include <sys/mman.h>
//#include <unistd.h>
#endif

#elif defined(__APPLE__)

#define _DARWIN_BETTER_REALPATH
#include <mach-o/dyld.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#elif defined(__QNXNTO__)

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#if !defined(GEX_PROC_SELF_EXE)
#define GEX_PROC_SELF_EXE "/proc/self/exefile"
#endif

#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__)

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <dlfcn.h>

#else

#error unsupported platform

#endif

#include "basedefs.h"

#if defined(uasm_MSVC_COMPATIBLE_COMPILER)
#define GEX_RETURN_ADDRESS() _ReturnAddress()
#elif defined(uasm_GCC_COMPATIBLE_COMPILER)
#define GEX_RETURN_ADDRESS() __builtin_extract_return_addr(__builtin_return_address(0))
#else
#error unsupported compiler
#endif

#ifdef __cplusplus
extern "C" {
#endif

uasm_PACK_PUSH_STACK

#if defined(_WIN32)

static int getModulePath_(HMODULE module, char* out, int capacity, int* dirname_length)
{
  wchar_t buffer1[MAX_PATH];
  wchar_t buffer2[MAX_PATH];
  wchar_t* path = NULL;
  int length = -1;

  for (;;)
  {
    DWORD size;
    int length_, length__;

    size = GetModuleFileNameW(module, buffer1, sizeof(buffer1) / sizeof(buffer1[0]));

    if (size == 0)
      break;
    else if (size == (DWORD)(sizeof(buffer1) / sizeof(buffer1[0])))
    {
      DWORD size_ = size;
      do
      {
        wchar_t* path_;

        path_ = (wchar_t*)GEX_REALLOC(path, sizeof(wchar_t) * size_ * 2);
        if (!path_)
          break;
        size_ *= 2;
        path = path_;
        size = GetModuleFileNameW(module, path, size_);
      }
      while (size == size_);

      if (size == size_)
        break;
    }
    else
      path = buffer1;

    if (!_wfullpath(buffer2, path, MAX_PATH))
      break;
    length_ = (int)wcslen(buffer2);
    length__ = WideCharToMultiByte(CP_UTF8, 0, buffer2, length_ , out, capacity, NULL, NULL);

    if (length__ == 0)
      length__ = WideCharToMultiByte(CP_UTF8, 0, buffer2, length_, NULL, 0, NULL, NULL);
    if (length__ == 0)
      break;

    if (length__ <= capacity && dirname_length)
    {
      int i;

      for (i = length__ - 1; i >= 0; --i)
      {
        if (out[i] == '\\')
        {
          *dirname_length = i;
          break;
        }
      }
    }

    length = length__;

    break;
  }

  if (path != buffer1)
    GEX_FREE(path);

  return length;
}

int getExecutablePath(char* out, int capacity, int* dirname_length)
{
  return getModulePath_(NULL, out, capacity, dirname_length);
}

int getModulePath(char* out, int capacity, int* dirname_length)
{
  HMODULE module;
  int length = -1;

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4054)
#endif
  if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)GEX_RETURN_ADDRESS(), &module))
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
  {
    length = getModulePath_(module, out, capacity, dirname_length);
  }

  return length;
}

#elif defined(__linux__) || defined(__CYGWIN__) || defined(__sun) || defined(GEX_USE_PROC_SELF_EXE)

int getExecutablePath(char* out, int capacity, int* dirname_length)
{
  char buffer[PATH_MAX];
  char* resolved = NULL;
  int length = -1;

  for (;;)
  {
    resolved = realpath(GEX_PROC_SELF_EXE, buffer);
    if (!resolved)
      break;

    length = (int)strlen(resolved);
    if (length <= capacity)
    {
      memcpy(out, resolved, length);

      if (dirname_length)
      {
        int i;

        for (i = length - 1; i >= 0; --i)
        {
          if (out[i] == '/')
          {
            *dirname_length = i;
            break;
          }
        }
      }
    }

    break;
  }

  return length;
}

int getModulePath(char* out, int capacity, int* dirname_length)
{
  int length = -1;
  FILE* maps = NULL;

  for (int r = 0; r < GEX_PROC_SELF_MAPS_RETRY; ++r)
  {
    maps = fopen(GEX_PROC_SELF_MAPS, "r");
    if (!maps)
      break;

    for (;;)
    {
      char buffer[PATH_MAX < 1024 ? 1024 : PATH_MAX];
      uint64_t low, high;
      char perms[5];
      uint64_t offset;
      uint32_t major, minor;
      char path[PATH_MAX];
      uint32_t inode;

      if (!fgets(buffer, sizeof(buffer), maps))
        break;

      if (sscanf(buffer, "%" PRIx64 "-%" PRIx64 " %s %" PRIx64 " %x:%x %u %s\n", &low, &high, perms, &offset, &major, &minor, &inode, path) == 8)
      {
        uint64_t addr = (uintptr_t)GEX_RETURN_ADDRESS();
        if (low <= addr && addr <= high)
        {
          char* resolved;

          resolved = realpath(path, buffer);
          if (!resolved)
            break;

          length = (int)strlen(resolved);
#if defined(__ANDROID__) || defined(ANDROID)
          if (length > 4
              &&buffer[length - 1] == 'k'
              &&buffer[length - 2] == 'p'
              &&buffer[length - 3] == 'a'
              &&buffer[length - 4] == '.')
          {
            int fd = open(path, O_RDONLY);
            if (fd == -1)
            {
              length = -1; // retry
              break;
            }

            char* begin = (char*)mmap(0, offset, PROT_READ, MAP_SHARED, fd, 0);
            if (begin == MAP_FAILED)
            {
              close(fd);
              length = -1; // retry
              break;
            }

            char* p = begin + offset - 30; // minimum size of local file header
            while (p >= begin) // scan backwards
            {
              if (*((uint32_t*)p) == 0x04034b50UL) // local file header signature found
              {
                uint16_t length_ = *((uint16_t*)(p + 26));

                if (length + 2 + length_ < (int)sizeof(buffer))
                {
                  memcpy(&buffer[length], "!/", 2);
                  memcpy(&buffer[length + 2], p + 30, length_);
                  length += 2 + length_;
                }

                break;
              }

              --p;
            }

            munmap(begin, offset);
            close(fd);
          }
#endif
          if (length <= capacity)
          {
            memcpy(out, resolved, length);

            if (dirname_length)
            {
              int i;

              for (i = length - 1; i >= 0; --i)
              {
                if (out[i] == '/')
                {
                  *dirname_length = i;
                  break;
                }
              }
            }
          }

          break;
        }
      }
    }

    fclose(maps);
    maps = NULL;

    if (length != -1)
      break;
  }

  if (maps)
    fclose(maps);

  return length;
}

#elif defined(__APPLE__)

int getExecutablePath(char* out, int capacity, int* dirname_length)
{
  char buffer1[PATH_MAX];
  char buffer2[PATH_MAX];
  char* path = buffer1;
  char* resolved = NULL;
  int length = -1;

  for (;;)
  {
    uint32_t size = (uint32_t)sizeof(buffer1);
    if (_NSGetExecutablePath(path, &size) == -1)
    {
      path = (char*)GEX_MALLOC(size);
      if (!_NSGetExecutablePath(path, &size))
        break;
    }

    resolved = realpath(path, buffer2);
    if (!resolved)
      break;

    length = (int)strlen(resolved);
    if (length <= capacity)
    {
      memcpy(out, resolved, length);

      if (dirname_length)
      {
        int i;

        for (i = length - 1; i >= 0; --i)
        {
          if (out[i] == '/')
          {
            *dirname_length = i;
            break;
          }
        }
      }
    }

    break;
  }

  if (path != buffer1)
    GEX_FREE(path);

  return length;
}

int getModulePath(char* out, int capacity, int* dirname_length)
{
  char buffer[PATH_MAX];
  char* resolved = NULL;
  int length = -1;

  for(;;)
  {
    Dl_info info;

    if (dladdr(GEX_RETURN_ADDRESS(), &info))
    {
      resolved = realpath(info.dli_fname, buffer);
      if (!resolved)
        break;

      length = (int)strlen(resolved);
      if (length <= capacity)
      {
        memcpy(out, resolved, length);

        if (dirname_length)
        {
          int i;

          for (i = length - 1; i >= 0; --i)
          {
            if (out[i] == '/')
            {
              *dirname_length = i;
              break;
            }
          }
        }
      }
    }

    break;
  }

  return length;
}

#elif defined(__QNXNTO__)

int getExecutablePath(char* out, int capacity, int* dirname_length)
{
  char buffer1[PATH_MAX];
  char buffer2[PATH_MAX];
  char* resolved = NULL;
  FILE* self_exe = NULL;
  int length = -1;

  for (;;)
  {
    self_exe = fopen(GEX_PROC_SELF_EXE, "r");
    if (!self_exe)
      break;

    if (!fgets(buffer1, sizeof(buffer1), self_exe))
      break;

    resolved = realpath(buffer1, buffer2);
    if (!resolved)
      break;

    length = (int)strlen(resolved);
    if (length <= capacity)
    {
      memcpy(out, resolved, length);

      if (dirname_length)
      {
        int i;

        for (i = length - 1; i >= 0; --i)
        {
          if (out[i] == '/')
          {
            *dirname_length = i;
            break;
          }
        }
      }
    }

    break;
  }

  fclose(self_exe);

  return length;
}

int getModulePath(char* out, int capacity, int* dirname_length)
{
  char buffer[PATH_MAX];
  char* resolved = NULL;
  int length = -1;

  for(;;)
  {
    Dl_info info;

    if (dladdr(GEX_RETURN_ADDRESS(), &info))
    {
      resolved = realpath(info.dli_fname, buffer);
      if (!resolved)
        break;

      length = (int)strlen(resolved);
      if (length <= capacity)
      {
        memcpy(out, resolved, length);

        if (dirname_length)
        {
          int i;

          for (i = length - 1; i >= 0; --i)
          {
            if (out[i] == '/')
            {
              *dirname_length = i;
              break;
            }
          }
        }
      }
    }

    break;
  }

  return length;
}

#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__)

int getExecutablePath(char* out, int capacity, int* dirname_length)
{
  char buffer1[PATH_MAX];
  char buffer2[PATH_MAX];
  char* path = buffer1;
  char* resolved = NULL;
  int length = -1;

  for (;;)
  {
#if defined(__NetBSD__)
    int mib[4] = { CTL_KERN, KERN_PROC_ARGS, -1, KERN_PROC_PATHNAME };
#else
    int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };
#endif
    size_t size = sizeof(buffer1);

    if (sysctl(mib, (u_int)(sizeof(mib) / sizeof(mib[0])), path, &size, NULL, 0) != 0)
        break;

    resolved = realpath(path, buffer2);
    if (!resolved)
      break;

    length = (int)strlen(resolved);
    if (length <= capacity)
    {
      memcpy(out, resolved, length);

      if (dirname_length)
      {
        int i;

        for (i = length - 1; i >= 0; --i)
        {
          if (out[i] == '/')
          {
            *dirname_length = i;
            break;
          }
        }
      }
    }

    break;
  }

  if (path != buffer1)
    GEX_FREE(path);

  return length;
}

int getModulePath(char* out, int capacity, int* dirname_length)
{
  char buffer[PATH_MAX];
  char* resolved = NULL;
  int length = -1;

  for(;;)
  {
    Dl_info info;

    if (dladdr(GEX_RETURN_ADDRESS(), &info))
    {
      resolved = realpath(info.dli_fname, buffer);
      if (!resolved)
        break;

      length = (int)strlen(resolved);
      if (length <= capacity)
      {
        memcpy(out, resolved, length);

        if (dirname_length)
        {
          int i;

          for (i = length - 1; i >= 0; --i)
          {
            if (out[i] == '/')
            {
              *dirname_length = i;
              break;
            }
          }
        }
      }
    }

    break;
  }

  return length;
}

#else

#error unsupported platform

#endif

uasm_PACK_PUSH_STACK

#ifdef __cplusplus
}
#endif
