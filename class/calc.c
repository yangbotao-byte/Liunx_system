// calc.c
#include "student.h"

void calc(struct Student stu[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        stu[i].total = stu[i].math + stu[i].chinese;
        stu[i].avg = stu[i].total / 2;
    }
}
