#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 输出指定长度的缓冲区字符数组，如果 size = 0，则不输出.
 * @param buf 	缓冲区指针
 * @param size 	缓冲区长度
 */
void print_init_content(unsigned char *buf, size_t size) {
	if (!size) {
		return;
	}
	printf("|");
	for(int i = 0; i < size; ++i) {
		unsigned char c = buf[i];
		if (c < 0x20 || c > 0x7E) {
			printf(".");
			continue;
		}
		printf("%c", c);
	}
	printf("|\n");
}

int main() {
	int c;									// 存储当前正在处理的字节.
	int mem_addr = 0;						// 记录处理的字节在输入流的相对地址.
	unsigned char *buf = (unsigned char*) calloc(0x10, sizeof(char));	// 记录每行原始字符串的缓冲区.
	// 将输入逐字节处理.
	while((c = getchar()) != EOF) {
		// 当前字符的索引如果是 16 倍数，那么输出当前的相对内存地址.
		if (mem_addr % 0x10 == 0x0) {
			printf("%08x ", mem_addr);
		}
		// 解码出原始字符，放在缓冲区中.
		buf[mem_addr % 0x10] = (unsigned char) c;
		printf("%02x ", c);	// 至少输出2位十六进制数，如果不足2位则左侧用0补齐.

		// 每行第 8 个字符后面多输出一个空格.
		if ((mem_addr + 9) % 0x10 == 0) {
			printf(" ");
		}

		mem_addr++;

		// 下一个字符的索引如果是 16 的倍数，那么换行.
		if (mem_addr % 16 == 0x0) {
			// 执行完这里代表一行结束了，buf 的 16个元素会被逐个替换为新一行的字符内容.
			print_init_content(buf, strlen(buf));
		}
	}
	
	// mem_addr 比当前已处理的字符索引大 1, 故 mem_addr % 16 表示该行当前已经处理的字符串数量.
	unsigned int padding = (0x10 - (mem_addr % 16)) * 3 + ((mem_addr % 16) >= 8 ? 0 : 1);
	// padding == 0x10 * 3 + 1 表示 while 循环已经完全输出了，不需要再填充了.
	if (padding != 0x10 * 3 + 1) {
		printf("%*s",  padding, " ");	// 使用 space 填充.
	}
	// 打印原始字符串.
	print_init_content(buf, mem_addr % 16);
	printf("%08x ", mem_addr);
	printf("\n");
}
