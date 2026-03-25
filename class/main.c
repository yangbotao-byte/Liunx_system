// main.c
#include "student.h"
#include <stdio.h>

int main() {
    int n;
    struct Student stu[N];

    printf("请输入学生人数：");
    scanf("%d", &n);

    input(stu, n);   // 输入
    calc(stu, n);   // 计算
    output(stu, n); // 输出

    return 0;
}
