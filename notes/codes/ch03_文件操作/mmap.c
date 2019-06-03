// 实验：使用 mmap 函数

/*
	mmap 函数
	mmap （内存映射）作用是建立一段可以被两个或更多程序读写的内存。
*/

/*
	#include <sys/mman.h>

	void *mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);

	创建一个指向一段内存区域的指针，这个内存区域可以与 fildes 所表示的文件关联。
	addr 参数用来请求使用某个特定的内存地址，如果取零，就自动分配。
	len 是可以访问的数据量。
	
	prot 是访问权限，可以是：
	- PROT_READ 允许读该内存段
	- PROT_WRITE 允许写该内存段
	- PROT_EXEC 允许执行该内存段
	- PROT_NONE 该内存段不能被访问

	flags 控制程序对内存段的改变造成的影响
	- MAP_PRIVATE 内存段是私有的，对它的修改只对本进程有效
	- MAP_SHARED 把该内存段的修改保存到磁盘文件中
	- MAP_FIXED 该内存段必须位于 addr 指定的地址中
 */

/*
	#include <sys/mman.h>

	int msync(void *addr, size_t len, int flags);

	把该内存段的某个部分或整段中的修改写回到被映射的文件中（或从被映射的文件中读出）。

	addr 和 len 确定了修改的内存段。
	flags 控制执行修改的具体方式：
	- MS_ASYNC 采取异步写
	- MS_SYNC 采取同步写
	- MS_INVALIDATE 从文件中读回数据
 */

/*
	#include <sys/mman.h>

	int munmap(void *addr, size_t len);

	释放掉内存段。
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct {
	int integer;
	char string[24];
} RECORD;

#define NRECORDS (100)

int main()
{
	RECORD record, *mapped;
	int i, f;
	FILE *fp;

	fp = fopen("records.dat", "w+");
	for (i = 0; i<NRECORDS; i++) {
		record.integer = i;
		sprintf(record.string, "RECORD-%d", i);
		fwrite(&record, sizeof(record), 1, fp);
	}
	fclose(fp);

	// 修改第43条记录
	fp = fopen("records.dat", "r+");
	fseek(fp, 43 * sizeof(record), SEEK_SET);
	fread(&record, sizeof(record), 1, fp);

	record.integer = 143;
	sprintf(record.string, "RECORD-%d", record.integer);

	fseek(fp, 43 * sizeof(record), SEEK_SET);
	fwrite(&record, sizeof(record), 1, fp);
	fclose(fp);

	// 把这些记录影射到内存中，然后访问第43条记录，修改其值
	f = open("records.dat", O_RDWR);
	mapped = (RECORD*)mmap(0, NRECORDS * sizeof(record), PROT_READ|PROT_WRITE, MAP_SHARED, f, 0);
	mapped[43].integer = 243;
	sprintf(mapped[43].string, "RECORD-%d", mapped[43].integer);

	msync((void*)mapped, NRECORDS * sizeof(record), MS_ASYNC);
	munmap((void*)mapped, NRECORDS * sizeof(record));
	close(f);

	exit(0);
}
