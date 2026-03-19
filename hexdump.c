#include <stdio.h>

int main() {
	char c;
	while((c = getchar()) != EOF) {
		printf("%02x ", c);	// 至少输出2位十六进制数，如果不足2位则左侧用0补齐
	}
	printf("\n");
}
