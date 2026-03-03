#include <stdio.h>   // 修复头文件拼写错误
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    const char* filename = "1.txt";

    // 修复：只读模式打开文件，指针判断用NULL
    FILE* fp = fopen(filename, "r");
    if(fp == NULL){  // 修复：指针不能和0比较，用NULL
        perror("fopen()");
        exit(1);
    }

    // 用动态数组存储每行文本
    char** lines = NULL;
    size_t current_line = 0;       // 当前已读取的行数（即总行数）
    size_t capacity = 100;         // 修复：变量名统一为capacity
    lines = malloc(capacity * sizeof(char*));
    if(lines == NULL){
        perror("内存分配失败");
        fclose(fp);
        exit(1);
    }

    char buff[1024];  // 临时存储每行内容
    // 读到文件尾
    while(fgets(buff, sizeof(buff), fp) != NULL){
        //计算行长度（+1为'\0'预留空间）
        size_t len = strlen(buff) + 1;
        char* line = malloc(len);
        if (!line) {
            perror("内存分配失败");
            // 清理已分配内存
            for (size_t i = 0; i < current_line; i++) free(lines[i]);
            free(lines);
            fclose(fp);
            return 1;
        }
        //新增字符串复制，把buff里的内容存入line
        strcpy(line, buff);

        // 数组扩容（行数超过容量时翻倍）
        if (current_line >= capacity) {
            capacity *= 2;
            char** new_lines = realloc(lines, capacity * sizeof(char*));
            if (!new_lines) {
                perror("数组扩容失败");
                free(line);
                for (size_t i = 0; i < current_line; i++) free(lines[i]);
                free(lines);
                fclose(fp);
                return 1;
            }
            lines = new_lines;
        }

        lines[current_line++] = line;  // 存入数组
    }

    fclose(fp);  // 读取完成，关闭原文件

    // 2. 检查是否有第10行（修复：num_lines → current_line）
    if (current_line < 10) {
        printf("文件行数不足10行，无需删除\n");
        // 清理内存
        for (size_t i = 0; i < current_line; i++) free(lines[i]);
        free(lines);
        return 0;
    }

    // 3. 写入临时文件（跳过第10行，索引9）
    const char* tmp_filename = "test.tmp";
    FILE* tmp_fp = fopen(tmp_filename, "w");
    if (!tmp_fp) {
        perror("创建临时文件失败");
        for (size_t i = 0; i < current_line; i++) free(lines[i]);
        free(lines);
        return 1;
    }

    for (size_t i = 0; i < current_line; i++) {
        if (i != 9) {  // 跳过第10行
            fputs(lines[i], tmp_fp);
        }
    }
    fclose(tmp_fp);

    // 4. 用临时文件替换原文件（原子操作）
    if (rename(tmp_filename, filename) != 0) {
        perror("替换文件失败");
        remove(tmp_filename);  // 删除临时文件
        for (size_t i = 0; i < current_line; i++) free(lines[i]);
        free(lines);
        return 1;
    }

    // 5. 清理内存
    for (size_t i = 0; i < current_line; i++) free(lines[i]);
    free(lines);

    printf("第10行删除成功\n");
    return 0;
}