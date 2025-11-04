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

- 只能使用`lf`占位符读取 double 类型的变量的输入

- 定义结构体

  ```c
  typedef struct  { // 定义结构体
      double a; // 变量类型以及变量名
      double b;
      double c;
  } Parameter ; // 结构体名称
  ```

- 定义函数

  ```c
  返回值 函数名(参数列表){
     
  }
  ```

- 参数列表传递指针参数

  ```c
  // 传递指针参数
  void calculation(Parameter *param){
  }
  ```

- goto 语句

  ```c
  start:
  scanf("%d",&choice);
  if(choice == 1){
      continue;
  }else if(choice == 2){
      break;
  }else{
      printf("输入错误，请重新输入!\t1、继续 2、退出\n");
      goto start; // 直接跳转到上面定义的 start 上
  }
  ```

  

