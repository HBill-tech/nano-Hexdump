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
* 利用 echo 通过管道输入
```bash
echo "hello" | ./hexdump
```

* 将文件内容通过管道输入
```bash
cat hexdump.c | ./hexdump
```