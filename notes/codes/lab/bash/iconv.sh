#! /bin/bash

# iconv 可以转换文件编码格式
# 通常 windows 下文件是 gbk 编码， Linux 下文件是 utf8 编码

# iconv -f GB2312 -t utf8 filename
# 将文件 filename 从 GB2312 编码格式转换成 utf8 编码格式，输出到标准输出中去
test1()
{
    cat some_gbk_words
    iconv -f GB2312 -t utf8 some_gbk_words
}

# 加 -o outfile 表示将输出放到新文件中去，新文件可以和旧文件重名，从而完成对旧文件编码的修改
test2()
{
    cp some_gbk_words some_gbk_words.bak
    
    cat some_gbk_words.bak
    iconv -f GB2312 -t utf8 some_gbk_words.bak -o some_gbk_words.bak
    cat some_gbk_words.bak
}

#test1
test2