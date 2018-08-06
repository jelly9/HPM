#ifndef __HPM_COMM_LOG_ILOG_H__
#define __HPM_COMM_LOG_ILOG_H__

#include <stdio.h>
#include <time.h>

#define DEBUG_LOG_OPEN 1
#define ERROR_LOG_OPEN 1

#if DEBUG_LOG_OPEN
// 打印日志到标准输出中 
#define HPMDebug(format, ...) \
    do{ \
        time_t t = time(0); \
        struct tm ptm; \
        memset(&ptm, 0, sizeof(ptm)); \
        localtime_r(&t, &ptm); \
        fprintf(stdout, "\033[32m[DEBUG][%4d-%02d-%02d %02d:%02d:%02d][%s:%s:%d]\033[0m:" format, \
               ptm.tm_year + 1900, ptm.tm_mon + 1, ptm.tm_mday, ptm.tm_hour, \
               ptm.tm_min, ptm.tm_sec, __FILE__, __FUNCTION__ , __LINE__, ##__VA_ARGS__); \
        fflush(stdout); \
    }while(0)
#else 
#define LogDebug(format, ...)
#endif

#if ERROR_LOG_OPEN
// 打印日志到标准输出中 
#define HPMError(format, ...) \
    do{ \
        time_t t = time(0); \
        struct tm ptm; \
        memset(&ptm, 0, sizeof(ptm)); \
        localtime_r(&t, &ptm); \
        fprintf(stdout, "\033[31m[ERROR][%4d-%02d-%02d %02d:%02d:%02d][%s:%s:%d]\033[0m:" format, \
               ptm.tm_year + 1900, ptm.tm_mon + 1, ptm.tm_mday, ptm.tm_hour, \
               ptm.tm_min, ptm.tm_sec, __FILE__, __FUNCTION__ , __LINE__, ##__VA_ARGS__); \
        fflush(stdout); \
    }while(0)
#else 
#define HPMError(format, ...)
#endif



#endif
