/*
 * 从书本中整理的一些实用案例
 */

#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>

namespace utility
{

/*
 * 根据标记截取字符串，存入一个vector里面
 * 内部使用strtok
 */
void ParseParam(const char *str, std::vector<std::string> &result, const char *delim);

/* 拷贝文件
 * 源文件必须存在，否则失败并输出错误信息，目标文件会自动创建（并截断）
 * 成功返回true
 */
bool CopyFile(const char *src_file, const char *dest_file);

/*
 * 替换进程映像，出错直接终止进程
 */
void Execute(const char *cmd);

}
#endif
