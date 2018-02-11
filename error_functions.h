/**
 *
 * @copyright:
 * @file: error_functions.h
 * @since: 2018-02-10
 * @author: czq | 7160844@qq.com
 * @description:
 *     常见错误处理函数的声明 
 * @usage:
 * @others:
 * @TODO:
 * @Revision History:
 * Date            Rel Ver.        Notes
 * 2018-02-10        1.0             开始创建
 *
 **/
#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void errMsg(const char *format, ...);

#ifdef __GNUC__

/* This macro stops 'gcc -Wall' complaining that "control reaches */
/*     end of non-void function" if we use the following functions to */
/*     terminate main() or some other non-void function. */

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

void errExit(const char *format, ...) NORETURN;
void err_exit(const char *format, ...) NORETURN;
void errExitEN(int errnum, const char *format, ...) NORETURN;
void fatal(const char *format, ...) NORETURN;
void usageErr(const char *format, ...) NORETURN;
void cmdLineErr(const char *format, ...) NORETURN;
#endif    /*ERROR_FUNCTIONS_H*/
