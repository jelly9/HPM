#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

#define PATHNAME "."
#define PROJ_ID 0x88

struct msgbuf_t{
    long int mtype;
    char mtext[1024];
};

int CreateMsg();
int GetMsg();
int DestroyMag();
int SendMsg(int msg_id, int type, char *msg);
int RecvMsg(int msg_id, int type, char *out);

#endif
