
#ifndef _MSC_VER
	# define __in
	# define _In_
	# define _Out_
#endif

#define STD_OUTPUT_HANDLE   ((DWORD)-11)
typedef void *HANDLE;

typedef short SHORT;
typedef unsigned short      WORD;

typedef struct _COORD {
    SHORT X;
    SHORT Y;
} COORD, *PCOORD;

typedef struct _SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
} SMALL_RECT, *PSMALL_RECT;

typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
    COORD dwSize;
    COORD dwCursorPosition;
    WORD  wAttributes;
    SMALL_RECT srWindow;
    COORD dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO, *PCONSOLE_SCREEN_BUFFER_INFO;

#define DECLSPEC_IMPORT __declspec(dllimport)
#define WINBASEAPI DECLSPEC_IMPORT

typedef unsigned long       DWORD;
typedef int                 BOOL;

#ifdef _WIN64

#define WINAPI __fastcall

#else

#define WINAPI __stdcall

#endif

WINBASEAPI
HANDLE
WINAPI
GetStdHandle(
    __in DWORD nStdHandle
    );

WINBASEAPI
BOOL
WINAPI
GetConsoleScreenBufferInfo(
    _In_ HANDLE hConsoleOutput,
    _Out_ PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo
    );

WINBASEAPI
BOOL
WINAPI
SetConsoleTextAttribute(
    _In_ HANDLE hConsoleOutput,
    _In_ WORD wAttributes
    );