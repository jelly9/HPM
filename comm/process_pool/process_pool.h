#ifndef __HPM_COMM_PROCESSPOOL_PROCESSPOOL_H__
#define __HPM_COMM_PROCESSPOOL_PROCESSPOOL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NAME_SIZE       32
#define PATH_SIZE       128

/* 返回码 */
enum RETURN{
    FAILED = -1,
    SUCCESS = 0
};

/* 进程信息 */
typedef struct process{
    char name[NAME_SIZE];
    pid_t pid;
    int pipefd[2];
    size_t score;
}process_t;

/* 进程池 */
typedef struct instance{
    /* 程序路径 */
    char prog_name[PATH_SIZE];
    /* 配置文件路径 */
    char conf_name[PATH_SIZE];

    int proc_num;
    int proc_idx;

    /* 进程池数组 */
    process_t *proc;
}instance_t;


int process_pool_init(instance_t *pinst, int proc_num);


#endif
