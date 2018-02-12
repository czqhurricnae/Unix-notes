/**
 *
 * @copyright:
 * @file: get_num.h
 * @since: 2018-02-11
 * @author: czq | 7160844@qq.com
 * @description:
 *     get_num.c的头文件 
 * @usage:
 * @others:
 * @TODO:
 * @Revision History:
 * Date            Rel Ver.        Notes
 * 2018-02-11        1.0             开始创建
 *
 **/
#ifndef GET_NUM_H
#define GET_NUM_H

#define GN_NONNEG 01        /* Value must be >= 1 */
#define GN_GT_0 02          /* Value must be > 0 */

#define GN_ANY_BASE 0100    /* By default, intergers are decimal */
#define GN_BASE_8 0200      /* Case use any base - like strtol(3) */
#define GN_BASE_16 0400     /* Value is expressed in octal */

long getLong(const char *arg, int flags, const char *name);
int getInt(const char *arg, int flags, const char *name);
#endif                      /*GET_NUM_H*/
