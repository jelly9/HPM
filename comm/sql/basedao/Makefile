ROOTPATH=/home/ubuntu/HPM
MYSQL_INCLUDE=$(ROOTPATH)/3th/include/sql 
LOG_INCLUDE=$(ROOTPATH)/comm/log
MYSQL_LIB=$(ROOTPATH)/3th/lib/sql
FLAGS=#-D_DEBUG_

.PHONY:all
all: sql_tools

sql_tools:sqlClient.o sqlApi.o
	g++ -o $@ $^ -L$(MYSQL_LIB) -lmysqlclient

%.o:%.cpp
	g++ -c $< $(FLAGS) -I$(MYSQL_INCLUDE) -I$(LOG_INCLUDE)

.PHONY:clean
clean:
	rm -f sql_tools *.o

#export LD_LIBRARY_PATH=/home/ubuntu/code/sqlsvr/sqlclient/lib/lib
