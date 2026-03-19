# 复现hexdump

hexdump 是一个在 Linux/Unix 系统中常用的命令行工具，用于以十六进制形式查看文件内容. 它对于分析二进制文件、检查数据格式、调试程序等场景非常有用.

## 使用说明

### 下载

```bash
git clone https://gitcode.com/huanghaoqi/hexdump.git
cd hexdump
```

### 编译

```bash
gcc hexdump.c -o hexdump
``` 

### 运行
#### 利用 echo 通过管道输入
1.无命令行参数
```bash
echo "hello world! have a good day" | ./hexdump 
```
输出为
```bash
00000000 6865 6c6c 6f20 776f 726c 6421 2068 6176 
00000010 6520 6120 676f 6f64 2064 6179 
0000001d
```
2.有 -C 参数 (不区分大小写)
```bash
echo "hello world! have a good day" | ./hexdump -C
```
输出为
```
00000000 68 65 6c 6c 6f 20 77 6f  72 6c 64 21 20 68 61 76  |hello world! hav|
00000010 65 20 61 20 67 6f 6f 64  20 64 61 79 0a           |e a good day.|
0000001d
```

#### 将文件内容通过管道输入
1.无命令行参数
```bash
cat hexdump.c | ./hexdump
```
输出为
```bash
00000000 2369 6e63 6c75 6465 203c 7374 6469 6f2e 
00000010 683e 0a23 696e 636c 7564 6520 3c73 7464 
                        ...
00000c80 2030 3b0a 7d0a 
00000c86
```

2.有 -C 参数
```bash
cat hexdump.c | ./hexdump -C
```
输出为
```bash
00000000 23 69 6e 63 6c 75 64 65  20 3c 73 74 64 69 6f 2e  |#include <stdio.|
00000010 68 3e 0a 23 69 6e 63 6c  75 64 65 20 3c 73 74 64  |h>.#include <std|
                                    ...
00000c70 74 28 31 29 3b 0a 09 7d  0a 09 72 65 74 75 72 6e  |t(1);..}..return|
00000c80 20 30 3b 0a 7d 0a                                 | 0;.}.|
00000c86
```
