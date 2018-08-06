#ifndef __HPM_comm_include_DELAYRUN_H__
#define __HPM_comm_include_DELAYRUN_H__

void func(int i){
    (void)i;
}

#define DELAY_CALL(f, ...) \
    do{ \
        f(##__VA_ARGS__); \
    }while(0)


DELAY_CALL(func, 10);

#endif
