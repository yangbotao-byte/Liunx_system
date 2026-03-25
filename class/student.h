// student.h
#ifndef STUDENT_H
#define STUDENT_H

#define N 50  // 最大学生数

// 学生结构体
struct Student {
    char name[20];
    int age;
    float math;
    float chinese;
    float total;
    float avg;
};

// 函数声明
void input(struct Student stu[], int n);
void calc(struct Student stu[], int n);
void output(struct Student stu[], int n);

#endif
