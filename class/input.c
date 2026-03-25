// input.c
#include "student.h"
#include <stdio.h>

void input(struct Student stu[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("请输入第%d个学生信息（姓名 年龄 数学 语文）：\n", i+1);
        scanf("%s %d %f %f", stu[i].name, &stu[i].age, &stu[i].math, &stu[i].chinese);
    }
}
