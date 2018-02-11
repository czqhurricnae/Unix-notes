/**
 *
 * @copyright:
 * @file: tlpi_hdr.h
 * @since: 2018-02-10
 * @author: czq | 7160844@qq.com
 * @description:
 *     大多数程序实例所使用的头文件 
 * @usage:
 * @others:
 * @TODO:
 * @Revision History:
 * Date            Rel Ver.        Notes
 * 2018-02-10        1.0             开始创建
 *
 **/
#ifndef TLPI_HDR_H
#define TLPI_HDR_H      /* Prevent accidental double inclusion */

#include <sys/types.h>  /* Type definition used by many programs */
#include <stdio.h>      /* Standard I/O functions */  
#include <stdlib.h>     /* Prototype of commonly used library fucntions, */
                        /* plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */

#include "get_num.h"    /* Declares our functions for handling numeric */
                        /* arguments (getInt(), getLong()) */

#include "error_functions.h"  /* Declares our error-handling functions */

typedef enum {FALSE, TRUE} Boolean;

#define min(m, n) ((m) < (n) ? (m) : (n))
#define max(m, n) ((m) < (n) ? (m) : (n))

#endif    /*TLPI_HDR_H*/
