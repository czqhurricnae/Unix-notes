/**
 *
 * @copyright:
 * @file: error_functions.c
 * @since: 2018-02-11
 * @author: czq | 7160844@qq.com
 * @description:
 *     为所有程序所使用的错误处理函数 
 * @usage:
 * @others:
 * @TODO:
 * @Revision History:
 * Date            Rel Ver.        Notes
 * 2018-02-11        1.0             开始创建
 *
 **/
#include <stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc"         /* Defines ename and MAX_ENAME */

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif
static void
terminate(Boolean useExit3)
{
    char *s;

    /* Dump core if EF_DUMPCORE environment variable is defined and */
    /* is a nonempty string; otherwise call exit(3) or _exit(2), */
    /* depending on the value of 'useExit3'. */

    s = getenv("EF_DUMPCORE");

    if (s != NULL && *s != '\0')
    {
        abort();
    }
    else if (useExit3)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        _exit(EXIT_FAILURE);
    }
}

static void
outputError(Boolean useErr, int err, Boolean flushStdout,
    const char *format, va_list ap)
{
   #define BUF_SIZE 500
   char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];
   vsnprintf(userMsg, BUF_SIZE, format, ap);

   if (useErr)
   {
      snprintf(errText, BUF_SIZE, " [%s %s]",
              (err > 0 & err <= MAX_ENAME) ?
              ename[err]: "?UNKNOWN?", strerror(err));
   }
   else
   {
       snprintf(errText, BUF_SIZE, ":");
   }

   snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);

   if (flushStdout)
   {
       fflush(stdout);        /* Flush any pending stdout */
   }
   fputs(buf, stderr);
   fflush(stderr);
}

/**
 * Function: errMsg
 * Description:
 *    在标准错误设备上打印消息, 除了将一个终止换行符自动追加到输出字符,
 *    该函数的参数列表与printf()所用相同.
 *    该函数会打印与当前errno值相对应的错误文本, 包括错误名以及有strerror()
 *    返回的错误描述, 外加由参数列表指定的格式化输出.
 * Calls:
 * Called By:
 * Input:
 * Output:
 * Return:
 * Table Accessed:
 * Table Updated:
 * Others:
 **/
void errMsg(const char *format, ...)
{
    va_list argList;
    int savedErrno;

    savedErrno = errno;        /* In case we change it here */

    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    errno = savedErrno;
}

/**
 * Function: errExit
 * Description:
 *    会以如下两种方式之一来终止程序:
 *    1. 调用exit()退出
 *    2. 若环境变量EF_DUMPCORE定义为非空字符串, 则调用abort()退出
 *    同时生成核心转储(core dump)文件, 供调试器使用
 * Calls:
 * Called By:
 * Input:
 * Output:
 * Return:
 * Table Accessed:
 * Table Updated:
 * Others:
 **/
void errExit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}

/**
 * Function: err_exit()
 * Description:
 *    类似于errExit(), 但存在两方面的差异:
 *    1. 打印错误消息前, err_exit()不会刷新标准输出
 *    2. err_exit()终止进程使用的是_exit(), 而非exit(), 这一退出方式,
 *    略去了对stdio缓冲区的刷新以及对退出处理程序(exit_handler)的调用.
 * Calls:
 * Called By:
 * Input:
 * Output:
 * Return:
 * Table Accessed:
 * Table Updated:
 * Others:
 **/
void err_exit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, FALSE, format, argList);
    va_end(argList);

    terminate(FALSE);
}
