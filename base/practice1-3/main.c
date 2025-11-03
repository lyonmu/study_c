#include <stdio.h>

int main() {
  printf("华氏温度与摄氏温度对照表\n");
  printf("华氏温度(F)  摄氏温度(C)\n");
  printf("C = (5/9) * (F - 32)\n");
  printf("========================\n");
  for (int f = 300; f >= 0; f -= 20) {
    int c = (f - 32) * 5 / 9;
    printf("%d\t%d\n", f, c);
    printf("========================\n");
  }
  return 0;
}