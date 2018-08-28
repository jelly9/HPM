#include <stdio.h>
#include "common.h"

int main()
{
    int msg_id = GetMsg();
    printf("Get a MQ! msg_id = %d\n",  msg_id);

    char rcvBuf[1024];
    char sndBuf[1024];
    while(1){
        printf("Cli Enter: ");
        fflush(stdout);
        size_t size = read(0, sndBuf, 1023);
        sndBuf[size-1] = 0;
        SendMsg(msg_id, CLIENT_TYPE, sndBuf);
        RecvMsg(msg_id, SERVER_TYPE, rcvBuf);
        printf("Svr Echo: %s\n", rcvBuf);
    }

    return 0;
}
