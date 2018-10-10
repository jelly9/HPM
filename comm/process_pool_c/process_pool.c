#include "process_pool.h"

#define __offset(pinst) \
    ((pinst)->proc[(pinst)->proc_idx]) 
#define __round_robin(pinst, roll) \
    ((pinst)->proc[((roll) % (pinst)->proc_num) + 1].pipefd[1])

/* 处理信号 */
static void __sig_handler (  ){

}

static void __sig_quit (  ) {

} 

static int __master( instance_t *pinst ) {
    int ret = 0;
    int fd = 0;
    int ix = 0;
    int roll = 0;
    char c = 0;

    HPMDebug("Master%u setup\n", pinst->proc_idx);

    for ( g_enable = 1; g_enable; ) {
        fd = __round_robin ( pinst, ++roll );
        //c = 'A' + roll % 3; 
        read(0, &c, 1);
        ret = write(fd, &c, 1);
        if ( ret <= 0 ) {
            return FAILED;
        }
        HPMDebug("Master%u send command: %c\n", pinst->proc_idx, c);
        sleep(1);
    }
    
    for ( ix = 1; ix <= pinst->proc_num; ++ix ) {
        c = 'Q';
        write( __round_robin(pinst, ++roll), &c, 1 );
    }
}

static int __worker( instance_t *pinst ) {
    int fd = __offset ( pinst ).pipefd[0];
    int ix = 0;
    ssize_t rd_size = FAILED;
    char buff[1024] = {0};

    HPMDebug("Worker%u setup\n", pinst->proc_idx);
    for ( g_enable = 1; g_enable; ) {
        rd_size = read( fd, buff, sizeof(buff) );
        if ( rd_size < 0 ) {
            if ( errno == EAGAIN || errno == EINTR ) {
                continue;
            }
            HPMError("read failed\n");
            return FAILED;
        }
        for ( ix = 0; ix < rd_size; ++ix ) {
            switch ( buff[ix] ) {
            case 'A':
            case 'B':
            case 'C':
                __offset(pinst).score += buff[ix];
                HPMDebug("Worker%u recv command: %c, score: %d\n",
                         pinst->proc_idx, buff[ix], __offset(pinst).score);
                break;
            case 'Q':
                HPMDebug("Quit\n");
                g_enable = 0;
                break;

            default:
                break;
            }
        }
    }
    HPMDebug("Worker%u shutdown\n", pinst->proc_idx);
    return SUCCESS;
} 

int process_pool_init ( instance_t *pinst, int proc_num ){

    int ret = FAILED;
    int status = 0;

    if  (  NULL == pinst || proc_num <= 0  ) {
        HPMError ( "pinst or proc_num is NULL,pinst: %p, proc_num: %d\n", pinst, proc_num );
        goto _E1;
    }

    __sig_handler (  );

    pinst->proc_idx = 0;
    pinst->proc_num = proc_num;

    pinst->proc =  ( process_t * )malloc ( sizeof ( process_t )* ( proc_num+1 ) );
    if  (  !pinst->proc  ) {
        HPMError ( "malloc failed\n" );
        goto _E1;
    }

    /* fork新进程 0号为Master进程*/
    int idx = 1;
    for  (  ; idx <= proc_num; ++idx   ) {

        ret = pipe ( pinst->proc[idx].pipefd );
        if  (  SUCCESS != ret  ) {
            HPMError ( "make pipe falied\n" );
            goto _E2;
        }

        pinst->proc[idx].pid = fork (  );
        if  (  pinst->proc[idx].pid < 0  ) {
            HPMError ( "fork failed: %d\n", idx );
            goto _E2;
        } else if  (  pinst->proc[idx].pid == 0  ) {
            /* father */
            //CLOSE_FD ( pinst->proc[idx].pipefd[0] );
            close ( pinst->proc[idx].pipefd[0] );
            continue;
        } else {
            /* child */
            HPMDebug ( "child init: %d\n", pinst->proc[idx].pid );
            close ( pinst->proc[idx].pipefd[1] );
            pinst->proc_idx = idx;
            //ret = __worker ( pinst );
            ret =  pinst->handler ( pinst );
            goto _E2;
        }
    }

    ret = __master ( pinst );
    
    /* 回收子进程 */
    for  (  idx = 1; idx <= proc_num; ++ idx  ) {
        waitpid ( pinst->proc[idx].pid, &status, WNOHANG );
    }

_E2:
    for  (  idx = 1; idx <= pinst->proc_num; ++idx  ) {
        close ( pinst->proc[idx].pipefd[0] );
        close ( pinst->proc[idx].pipefd[1] );
    }

    free ( pinst->proc );
    pinst->proc = NULL;

_E1:
    return 0;
}

int main ( int argc, char *argv[] ){
    instance_t *pi =  ( instance_t* )malloc ( sizeof ( instance_t ) );
    //pi->handler = (int(*)(void*))__worker;
    pi->handler = __worker;
    process_pool_init ( pi, 10 );

    return 0;
}
