ROOTPATH=/home/jellyxiao/HPM
LOG_INCLUDE=$(ROOTPATH)/comm/log

tools:process_pool.c
	gcc -o $@ $^ -I$(LOG_INCLUDE)

.PHONY:clean
clean:
	rm -f tools

.PHONY:debug
debug:
	echo $(LOG_INCLUDE)
