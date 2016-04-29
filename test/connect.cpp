#include <iostream>
#include <cstring>
#include <unordered_map>
#include "configfile.h"
#include "configitem.h"
#include "mysqlopt.h"
#include "slide_window.h"
#include "stropt.h"

extern "C" {
#include "unp.h"
}

using namespace configlib; 
using namespace std;
using namespace SlideWindow;

int main(int argc, char *argv[])
{	

    //初始化，连接数据库
    Mysql *mysql = new Mysql();/*{{{*/

    Mysql_conf *mysql_conf = new Mysql_conf();
    snprintf(mysql_conf->ip, 80, "127.0.0.1");
    snprintf(mysql_conf->user_name, 80, "root");
    snprintf(mysql_conf->password, 80, "cba654321");
    snprintf(mysql_conf->db_name, 80, "Test");
    mysql_conf->port = 3306;

    if(mysql->init(mysql_conf)){
        cout<<"init error"<<endl;
        return 1;
    }

    //数据库操作
    char str[2000];
    char sql[sql_maxlen];/*{{{*/

    //while(scanf("%s", str) != EOF) {
    while(fgets(str, 1000, stdin)) {
        vector<string> vet;
        explode(str, vet);
        //printf("%s\n", str);
        snprintf(sql, sql_maxlen, "insert into blacklist set ukey = '%s', ip = '%s', type = '%s', status = '%s', create_time = %s, update_time = %s, expire_time = %s", vet[0].c_str(), vet[1].c_str(), vet[2].c_str(), vet[3].c_str(), vet[4].c_str(), vet[5].c_str(), vet[6].c_str());
        mysql->insert(sql);
        printf("%s\n", sql);
    }

    return 0;
}
