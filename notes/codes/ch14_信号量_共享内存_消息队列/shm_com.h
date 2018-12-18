// 实验：共享内存

// 此文件是共享内存实验所用的公共文件

#ifndef __SHM_COM_H__
#define __SHM_COM_H__

#define TEXT_SZ 2048

struct shared_use_st {
	int wrtten_by_you;
	char some_text[TEXT_SZ];
};

#endif //__SHM_COM_H__
