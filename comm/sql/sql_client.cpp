#include "sql_api.h"
#include "ilog.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void showUsage(char *program)
{
    printf("\t\nUsage: %s [-i <config>] [-o <option>]\n\n", program);
    exit(0);
}
int main(int argc, char*argv[])
{
//    if(argc <= 1){
//        showUsage(argv[0]);
//        exit(0);
//    }

    const char *config = "./test.conf";
    const char *option = "select";

    // 解析命令行参数
    char ch;
    while((ch = getopt(argc, argv, "i:o:c:h")) != EOF){
        switch(ch){
        case 'i':
            config = optarg;
            break;
        case 'o':
            option = optarg;
            break;
        case '?':
        case 'h':
        default:
            showUsage(argv[0]);
            exit(1);
        }
    }
    if(config == NULL){
        showUsage(argv[0]);
        exit(2);
    }

    char ip[32] = {0};
    int  port = 3306;
    char user[32] = {0};
    char passwd[32] = {0};
    char database[32] = {0};

    // 读取配置文件
    FILE *fp = fopen(config, "r");
    if(fp == NULL){
        HPMError("open config file failed: %s\n", config);
        exit(3);
    }
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
            strncpy(passwd, line+7, 2);
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
    strcpy(passwd, getpass("Password:"));

    HPMDebug("%s\n", ip);
    HPMDebug("%d\n", port);
    HPMDebug("%s\n", user);
    HPMDebug("%s\n", passwd);
    HPMDebug("%s\n", database);

    //sqlApi mydb(ip, port, user, passwd, database);
    sqlApi mydb("127.0.0.1", 3306, "root", "m9", "httpd");
    mydb.connect();
    if(strcmp(option, "insert") == 0){
        mydb.insert("LM", "wman", "18", "study", "SUST");
    }
    if(strcmp(option, "select") == 0){
        mydb.select();
    }

    return 0;
}

