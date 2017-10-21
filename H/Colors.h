#ifndef _COLORS_
#define _COLORS_

/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#define WIN_BLUE 1
#define WIN_GREEN 2
#define WIN_CYAN 3
#define WIN_RED 4
#define WIN_PINK 5
#define WIN_YELLOW 6
#define WIN_WHITE 7
#define WIN_GREY 8
#define WIN_LTBLUE 9
#define WIN_LTGREEN 10
#define WIN_LTCYAN 11
#define WIN_LTRED 12
#define WIN_LTPINK 13
#define WIN_LTYELLOW 14
#define WIN_LTWHITE 15

#endif  /* _COLORS_ */