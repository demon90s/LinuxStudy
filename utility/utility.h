/*
 * 从书本中整理的一些实用案例
 */

#ifndef UTILITY_H
#define UTILITY_H

/* 拷贝文件
 * 源文件必须存在，否则失败并输出错误信息，目标文件会自动创建（并截断）
 * 成功返回0，失败返回1
 */
int copy_file(const char *src_file, const char *dest_file);

#endif
