
;--- another struct alignment test

	.386
	.model flat

;--- a Win32 sample

KEY_EVENT_RECORD struct
bKeyDown			DWORD	?
wRepeatCount		WORD	?
wVirtualKeyCode		WORD	?
wVirtualScanCode	WORD	?
union uChar
UnicodeChar			WORD	?
AsciiChar			BYTE	?
ends
dwControlKeyState	DWORD	?
KEY_EVENT_RECORD ends

COORD struct
X	SWORD	?
Y	SWORD	?
COORD ends

MOUSE_EVENT_RECORD struct
dwMousePosition		COORD	<>
dwButtonState		DWORD	?
dwControlKeyState	DWORD	?
dwEventFlags		DWORD	?
MOUSE_EVENT_RECORD ends

WINDOW_BUFFER_SIZE_RECORD struct
dwSize	COORD	<>
WINDOW_BUFFER_SIZE_RECORD ends

MENU_EVENT_RECORD struct
dwCommandId	DWORD	?
MENU_EVENT_RECORD ends

FOCUS_EVENT_RECORD struct
bSetFocus	DWORD	?
FOCUS_EVENT_RECORD ends

INPUT_RECORD struct 4
EventType	WORD	?
union Event
KeyEvent	KEY_EVENT_RECORD	<>
MouseEvent	MOUSE_EVENT_RECORD	<>
WindowBufferSizeEvent	WINDOW_BUFFER_SIZE_RECORD	<>
MenuEvent	MENU_EVENT_RECORD	<>
FocusEvent	FOCUS_EVENT_RECORD	<>
ends
INPUT_RECORD ends

	.data

	INPUT_RECORD <1,<<2>>>
	db -1

	END
