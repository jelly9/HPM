ROOTPATH=$(shell pwd)
MYSQL_INCLUDE=$(ROOTPATH)/lib/include
MYSQL_LIB=$(ROOTPATH)/lib/lib
FLAGS=#-D_DEBUG_

.PHONY:all
all: sql_tools

sql_tools:sqlclient.o sqlapi.o
	g++ -o $@ $^ -L$(MYSQL_LIB) -lmysqlclient

%.o:%.cpp
	g++ -c $< $(FLAGS) -I$(MYSQL_INCLUDE)

.PHONY:clean
clean:
	rm -f sql_tools *.o

#export LD_LIBRARY_PATH=/home/ubuntu/code/sqlsvr/sqlclient/lib/lib
