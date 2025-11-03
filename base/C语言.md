# hello world

```c
// 导入头文件
#include <stdio.h>

// 主函数
int main() {
  // 打印hello world
  printf("hello world!\n");
  return 0;
}
```

- 编译命令

```shell
# 创建目录并使用 gcc 命令编译源文件
mkdir bin && gcc -o bin/main main.c
```