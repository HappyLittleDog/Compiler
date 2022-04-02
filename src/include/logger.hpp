#pragma once
#include <stdio.h>

#define LOG_INFO(fmt, args...) ({printf("\033[0m\033[1;34m[INFO] \033[0m"); printf(fmt, ##args); printf("\n"); })
#define LOG_ERROR(fmt, args...) ({printf("\033[0m\033[1;31m[ERROR] \033[0m"); printf(fmt, ##args); printf("\n"); })

#ifdef DEBUGMODE
#define LOG_DEBUG(fmt, args...) ({printf("\033[0m\033[1;33m[DEBUG] \033[0m"); printf(fmt, ##args); printf("\n"); })
#else
#define LOG_DEBUG(...) ((void)0)
#endif