#include <stdio.h>

int main() {
    printf("华氏温度与摄氏温度对照表\n");
    printf("C 摄氏温度\tF 华氏温度\n");
    printf("计算公式： C = (F-32)(5/9)\n");
    printf("======================================\n");

    double input;
    while (1) {
        printf("请输入华氏温度：\n");
        scanf("%lf", &input);
        if(input > 300){
            printf("温度过高，无法计算\n");
            break;
        }
        printf("华氏温度为：%0.2f\t", input);
        printf("摄氏温度为：%0.2f\n", (input - 32) * 5 / 9);
        printf("======================================\n");
    }

    return 0;
}
