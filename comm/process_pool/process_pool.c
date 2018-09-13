#include "process_pool.h"
#include "ilog.h"

/* 处理信号 */
static void sigHandler (  ){

}

int process_pool_init ( instance_t *pinst, int proc_num ){

    int ret = FAILED;
    int status = 0;

    if  (  NULL == pinst || proc_num <= 0  ) {
        HPMError ( "pinst or proc_num is NULL,pinst: %p, proc_num: %d\n", pinst, proc_num );
        goto _E1;
    }

    sigHandler (  );

    pinst->proc_idx = 0;
    pinst->proc_num = 0;

    pinst->proc =  ( process_t * )malloc ( sizeof ( process_t )* ( proc_num+1 ) );
    if  (  !pinst->proc  ) {
        HPMError ( "malloc failed\n" );
        goto _E1;
    }

    /* fork新进程 0号为Master进程*/
    int idx = 1;
    for  (  ; idx <= proc_num+1; ++idx   ) {

        ret = pipe ( pinst->proc[idx].pipefd );
        if  (  SUCCESS != ret  ) {
            HPMError ( "make pipe falied\n" );
            goto _E2;
        }

        HPMDebug ( "Setup worker# %d\n", idx );

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
            HPMDebug ( "child process: %d\n", pinst->proc[idx].pid );
            close ( pinst->proc[idx].pipefd[1] );
            pinst->proc_idx = idx;
            // ret = __worker ( pinst );
            goto _E2;
        }
    }

    //ret = __master ( pinst );
    
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

_E1:
    return 0;
}

int main (  ){
    instance_t *pi =  ( instance_t* )malloc ( sizeof ( instance_t ) );
    process_pool_init ( pi, 10 );

    return 0;
}
