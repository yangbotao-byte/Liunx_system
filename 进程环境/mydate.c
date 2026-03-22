// #include<stdio.h>
// #include<stdlib.h>
// #include<time.h>
// #include<unistd.h>
// #include<string.h>
// #include<getopt.h>

// #define SIZE 1024

// int main(int argc, char **argv){

//     int ch = 0;
//     time_t tm_pos;
//     FILE* fp = stdout;
//     char buff[SIZE];
//     struct tm *tm_message;
//     char fmstr[SIZE];

//     fmstr[0] = '\0';

//     time(&tm_pos);
//     tm_message = localtime(&tm_pos);


//     while(1){
//         ch = getopt(argc, argv, "-H:MSy:md");
//         if(ch < 0)
//             break;

//         switch(ch){
//             case '1':
//             printf("enter\n");
//                     fp = fopen(argv[optind - 1], "w");
//                     if(fp == stdout){
//                         perror("fopen()");
//                         printf("1");
//                         fp = stdout;
//                     }
//                 break;
//             case 'H':
//                 if(strcmp(optarg, "12") == 0)
//                     strncat(fmstr, "%I(%P) ", SIZE);
//                 else if(strcmp(optarg, "24") == 0)
//                     strncat(fmstr, "%H ", SIZE);
//                 else
//                     fprintf(stderr, "value erro");
//                 break;
//             case 'M':
//                 strncat(fmstr, "%M ", SIZE);
//                 break;
//             case 'S':
//                 strncat(fmstr, "%S ", SIZE);
//                 break;
//             case 'y':
//                 if(strcmp(optarg, "2") == 0)
//                     strncat(fmstr, "%y ", SIZE);
//                 else if(strcmp(optarg, "4") == 0)
//                     strncat(fmstr, "%Y ", SIZE);
//                 else
//                     break;
//                 break;
//             case 'm':
//                 strncat(fmstr, "%m ", SIZE);
//                 break;
//             case 'd':
//                 strncat(fmstr, "%d ", SIZE);
//                 break;
//             default:
//                 break;
//         }
//     }

//     strncat(fmstr, "\n", SIZE);
//     strftime(buff, SIZE, fmstr, tm_message);
//     fputs(buff, fp);

//     if(fp != stdout)
//         fclose(fp);

//     exit(0);
// }




#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<getopt.h>

#define SIZE 1024

int main(int argc, char **argv){

    int ch = 0;
    time_t tm_pos;
    FILE* fp = stdout;
    char buff[SIZE];
    struct tm *tm_message;
    char fmstr[SIZE];
    int count = 0;

    fmstr[0] = '\0';

    time(&tm_pos);
    tm_message = localtime(&tm_pos);

    while(1){
        // 保留你确认过的开头 '-'，非选项参数会触发 case '1'
        ch = getopt(argc, argv, "-H:MSy:md");
        // count++;
        if(ch < 0){
            // printf("1111\n");
            // printf("%d\n",count);
            break;
        }

        switch(ch){
            case 1:
                printf("enter\n"); // 测试用，可删除
                // 1. 打开文件
                fp = fopen(argv[optind - 1], "w");
                // 2. 正确判断：是否打开失败（只有失败才返回 NULL）
                if(fp == NULL){
                    perror("fopen() failed"); // 打印真实错误原因
                    fp = stdout; // 失败则回退到标准输出
                }
                break;

            case 'H':
                if(strcmp(optarg, "12") == 0)
                    strncat(fmstr, "%I(%P) ", SIZE);
                else if(strcmp(optarg, "24") == 0)
                    strncat(fmstr, "%H ", SIZE);
                else
                    fprintf(stderr, "value erro");
                break;

            case 'M':
                strncat(fmstr, "%M ", SIZE);
                break;

            case 'S':
                strncat(fmstr, "%S ", SIZE);
                break;

            case 'y':
                if(strcmp(optarg, "2") == 0)
                    strncat(fmstr, "%y ", SIZE);
                else if(strcmp(optarg, "4") == 0)
                    strncat(fmstr, "%Y ", SIZE);
                // 修正：这里原来有两个 break，删掉一个！
                break;

            case 'm':
                strncat(fmstr, "%m ", SIZE);
                break;

            case 'd':
                strncat(fmstr, "%d ", SIZE);
                break;

            default:
                break;
        }
    }

    strncat(fmstr, "\n", SIZE);
    strftime(buff, SIZE, fmstr, tm_message);
    fputs(buff, fp);

    if(fp != stdout)
        fclose(fp);

    exit(0);
}