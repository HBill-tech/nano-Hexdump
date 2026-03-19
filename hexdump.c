#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 输出指定长度的缓冲区字符数组，如果 size = 0，则不输出.
 * @param buf 	缓冲区指针
 * @param size 	缓冲区长度
 */
void print_init_content(unsigned char* buf, size_t size) {
	if (!size) {
		return;
	}
	printf(" |");
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

void shell_c_param_output() {
	int c;									// 存储当前正在处理的字节.
	int mem_addr = 0;						// 记录处理的字节在输入流的相对地址.
	unsigned char *buf = (unsigned char*) calloc(0x10, sizeof(unsigned char));	// 记录每行原始字符串的缓冲区.
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
		if ((mem_addr + 9) % 0x10 == 0x0) {
			printf(" ");
		}

		mem_addr++;

		// 下一个字符的索引如果是 16 的倍数，那么换行.
		if (mem_addr % 0x10 == 0x0) {
			// 执行完这里代表一行结束了，buf 的 16个元素会被逐个替换为新一行的字符内容.
			print_init_content(buf, strlen(buf));
		}
	}
	
	// mem_addr 比当前已处理的字符索引大 1, 故 mem_addr % 16 表示该行当前已经处理的字符串数量.
	unsigned int padding = (0x10 - (mem_addr % 0x10)) * 3 + ((mem_addr % 0x10) >= 8 ? 0 : 1);
	// padding == 0x10 * 3 + 1 表示 while 循环已经完全输出了，不需要再填充了.
	if (padding != 0x10 * 3 + 1) {
		printf("%*s",  padding, " ");	// 使用 space 填充.
	}
	// 打印原始字符串.
	print_init_content(buf, mem_addr % 0x10);
	printf("%08x\n", mem_addr);
	free(buf);
}

void no_shell_param_output() {
	int c;
	int* buf = (int*) calloc(0x02, sizeof(int));	// 用来存储一个四位 16 进制数字
	int mem_addr = 0;
	while ((c = getchar()) != EOF) {
		// 当前字符的索引如果是 16 倍数，那么输出当前的相对内存地址.
		if (mem_addr % 0x10 == 0x0) {
			printf("%08x ", mem_addr);
		}
		buf[mem_addr % 0x02] = c;
		if ((mem_addr + 1) % 0x02 == 0) {
			// %02x 至少输出2位十六进制数，如果不足2位则左侧用0补齐.
			printf("%02x%02x ", buf[0], buf[1]);	
		}

		mem_addr++;

		// 下一个字符的索引如果是 16 的倍数，那么换行.
		if(mem_addr % 0x10 == 0) {
			printf("\n");
		}
	}
	// 如果最后一行恰好输出一整行，那么不要换行，否则多出一行空行.
	if (mem_addr % 0x10 != 0) {
		printf("\n");
	}
	printf("%08x\n", mem_addr);
	free(buf);
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		no_shell_param_output();
	}
	else if (argc == 2 && (strcmp(argv[1], "-C") == 0 || strcmp(argv[1], "-c") == 0)) {
		shell_c_param_output();
	} else {
		fprintf(stderr, "invaid options in command!\n");
		exit(1);
	}
	return 0;
}
