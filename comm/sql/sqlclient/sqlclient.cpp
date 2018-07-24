#include "sqlapi.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

void showUsage(char *program)
{
    printf("\t\nUsage: %s [-f <config>] [-o <option>] [-c <mysql command>]\n", program);
    exit(0);
}
int main(int argc, char*argv[])
{
    if(argc != 7)
    {
        showUsage(argv[0]);
    }

    const char *config = NULL;
    const char *option = NULL;
    const char *command = NULL;

    // 解析命令行参数
    for(int i = 1; i < argc-1; ++i)
    {
        if(strcmp(argv[i], "-f") == 0)
            config = argv[i+1];
        else if(strcmp(argv[i], "-o") == 0)
            option = argv[i+1];
        else if(strcmp(argv[i], "-c") == 0)
            command = argv[i+1];
    }

    char ip[32] = {0};
    int  port = 3306;
    char user[32] = {0};
    char passwd[32] = {0};
    char database[32] = "httpd";

    /* 读取配置文件
     * ip: xxx.xxx.xxx.xxx
     * port: xxxx
     * */
    FILE *fp = fopen(config, "r");
    char *line = NULL;
    size_t len = 0;
    while(getline(&line, &len, fp) > 0)
    {
        if(strncmp(line, "ip:", 3) == 0){
            strcpy(ip, line+3);
            size_t len = strlen(ip);
            if(ip[len-1] == '\n')
                ip[len-1] = '\0';
        }
        else if(strncmp(line, "port:", 5) == 0){
            port = atoi(line+5);
        }
        else if(strncmp(line, "user:", 5) == 0){
            strcpy(user, line+5);
            size_t len = strlen(user);
            if(user[len-1] == '\n')
                user[len-1] = '\0';
        }
        else if(strncmp(line, "passwd:", 7) == 0){
            strcpy(passwd, line+7);
            size_t len = strlen(ip);
            if(passwd[len-1] == '\n')
                passwd[len-1] = '\0';
        }
        else if(strncmp(line, "database:", 9) == 0){
            strcpy(database, line+9);
            size_t len = strlen(ip);
            if(database[len-1] == '\n')
                database[len-1] = '\0';
        }
    }
    fclose(fp);

    // 输入登录用户名,密码,和数据库名
    printf("User: ");
    scanf("%s", user);
    fflush(stdin);
    strcpy(passwd, getpass("Password: "));
    printf("Database: ");
    scanf("%s", database);
    fflush(stdin);

    sqlApi mydb(ip, port, user, passwd, database);
    mydb.connect();
    if(strcmp(option, "insert") == 0){
        mydb.insert("LM", "wman", "18", "study", "SUST");
    }
    if(strcmp(option, "select") == 0){
        mydb.select();
    }

    return 0;
}

