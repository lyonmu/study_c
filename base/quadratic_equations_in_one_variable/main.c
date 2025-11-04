#include <stdio.h>
#include <math.h>

// 输出一元二次方程的解、可以重复输出
//  1、编写一个函数输出一元二次方程的解
//     a、函数接受一个 struct 的指针
//     b、计算根号下 b*b - 4*a*c是否大于等于0
//     c、如果大于等于0，计算两个根并输出
//     d、如果小于0，输出无解
//  2、main 函数循环调用，增加确认退出标志

typedef struct  {
    double a;
    double b;
    double c;
}Parameter ;

void   calculation(Parameter *param){
    if (param->a == 0){
        printf("一元二次方程中 a 不能等于零 \n");
        return;
    }
    if ((param->b*param->b) - (4*param->a*param->c) > 0) {
        printf("该一元二次方程有两个解 x1 = %0.2f,x2 = %0.2f\n",(-param->b + sqrt((param->b*param->b) - (4*param->a*param->c)))/(2*param->a),(-param->b - sqrt((param->b*param->b) - (4*param->a*param->c)))/(2*param->a));
    }else if((param->b*param->b) - (4*param->a*param->c) == 0){
        printf("该一元二次方程有一个解 x = %0.2f\n",(-param->b)/(2*param->a));
    }else if((param->b*param->b) - (4*param->a*param->c) < 0){
        printf("该一元二次方程无解\n");
    }
}


int main(){
    int choice = 1;
    while (choice != 2) {
        Parameter param;
        printf("请输入一元二次方程的系数 a,b,c:\n");
        scanf("%lf %lf %lf",&param.a,&param.b,&param.c);
        calculation(&param);
        printf("是否继续？1、继续 2、退出\n");
        start:
        scanf("%d",&choice);
        if(choice == 1){
            continue;
        }else if(choice == 2){
            break;
        }else{
            printf("输入错误，请重新输入!\t1、继续 2、退出\n");
            goto start;
        }
    }

    return 0;
}
