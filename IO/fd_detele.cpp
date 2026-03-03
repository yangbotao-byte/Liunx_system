#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    const char *filename = argv[1];

    // 1. 打开两次文件：fd1只读（负责读），fd2读写（负责写）
    int fd1 = open(filename, O_RDONLY);  // 对应图中“文件描述符4 → r”
    if (fd1 == -1) {
        perror("open fd1");
        exit(EXIT_FAILURE);
    }
    int fd2 = open(filename, O_RDWR);    // 对应图中“文件描述符5 → r+”
    if (fd2 == -1) {
        perror("open fd2");
        close(fd1);
        exit(EXIT_FAILURE);
    }

    // 2. 遍历文件，找到第10行和第11行的字节偏移（关键：行号不等于偏移，需逐行找）
    off_t line_offsets[12];  // 记录前11行的起始偏移
    int current_line = 0;
    char c; // 检查是否存在换行符
    line_offsets[0] = 0;  // 第1行从0字节开始

    while (read(fd1, &c, 1) > 0) {
        if (c == '\n') {
            current_line++;
            if (current_line < 12) {
                // 记录下一行的起始偏移
                line_offsets[current_line] = lseek(fd1, 0, SEEK_CUR);
            }
            if (current_line >= 11) break;  // 找到第11行偏移后停止
        }
    }

    // 检查文件是否至少有10行
    if (current_line < 10) {
        fprintf(stderr, "Error: File has less than 10 lines\n");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // 第10行的起始偏移：line_offsets[9]，结束偏移：line_offsets[10]
    off_t line10_start = line_offsets[9];
    off_t line11_start = line_offsets[10];
    off_t line10_len = line11_start - line10_start;  // 第10行的字节长度

    // 3. 获取文件总大小，用于后续截断
    struct stat st;
    if (fstat(fd1, &st) == -1) {
        perror("fstat");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }
    off_t file_size = st.st_size;

    // 4. 定位：fd1到第11行开始读，fd2到第10行开始写（对应图中lseek操作）
    if (lseek(fd1, line11_start, SEEK_SET) == -1) {
        perror("lseek fd1");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }
    if (lseek(fd2, line10_start, SEEK_SET) == -1) {
        perror("lseek fd2");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // 5. 循环读取第11行及以后内容，覆盖写入到第10行位置
    char buf[4096];  // 用缓冲区提高效率
    ssize_t n_read;
    while ((n_read = read(fd1, buf, sizeof(buf))) > 0) {
        if (write(fd2, buf, n_read) != n_read) {
            perror("write");
            close(fd1);
            close(fd2);
            exit(EXIT_FAILURE);
        }
    }
    if (n_read == -1) {
        perror("read");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // 6. 截断文件：删除第10行后，文件长度减少line10_len字节
    off_t new_size = file_size - line10_len;
    if (ftruncate(fd2, new_size) == -1) {
        perror("ftruncate");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // 7. 关闭文件描述符
    close(fd1);
    close(fd2);

    printf("第10行删除成功（双文件描述符方式）\n");
    return 0;
}