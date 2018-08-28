ROOTPATH=/home/ubuntu/HPM
LOG_INCLUDE=$(ROOTPATH)/comm/log
MYSQL_INCLUDE=$(ROOTPATH)/3th/sql/include 
MYSQL_LIB=$(ROOTPATH)/3th/sql/lib

.PHONY:all
all: sql_tools

sql_tools:sql_client.o sql_api.o
	g++ -o $@ $^ -L$(MYSQL_LIB) -lmysqlclient

%.o:%.cpp
	g++ -c $< $(FLAGS) -I$(MYSQL_INCLUDE) -I$(LOG_INCLUDE)

.PHONY:clean
clean:
	rm -f sql_tools *.o
