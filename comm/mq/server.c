#include <stdio.h>
#include "common.h"

int main()
{
    int msg_id = CreateMsg();
    printf("Create a MQ! msg_id = %d\n", msg_id);

    char rcvBuf[1024];
    while(1){
        RecvMsg(msg_id, CLIENT_TYPE, rcvBuf);
        printf("Cli say: %s\n", rcvBuf);
        fflush(stdout);
        SendMsg(msg_id, SERVER_TYPE, rcvBuf);
    }

    return 0;
}
