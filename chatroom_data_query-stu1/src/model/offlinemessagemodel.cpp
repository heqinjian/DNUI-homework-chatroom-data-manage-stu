#include "offlinemessagemodel.h"
#include <mysql/mysql.h>
#include "mysql.h"
#include <iostream>

namespace ChatRoom {
// 存储用户的离线消息
void OfflineMsgModel::insert(int userid, string msg)
{
    // 组装 SQL 语句
    char sql[1024] = {0};
    // 防止 SQL 注入，对特殊字符进行转义
    MYSQL *conn;
    MySQL mysql;
    if (mysql.Connect())
    {
        conn = mysql.GetConnection();
        char escapedMsg[2048];
        mysql_real_escape_string(conn, escapedMsg, msg.c_str(), msg.length());
        sprintf(sql, "INSERT INTO OfflineMessage (userid, message) VALUES (%d, '%s')", userid, escapedMsg);

        if (mysql.Update(sql) != 0)
        {
            std::cerr << "Failed to insert offline message for user " << userid << ". Error: " << mysql_error(conn) << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to connect to database when inserting offline message for user " << userid << std::endl;
    }
}

// 删除用户的离线消息
void OfflineMsgModel::remove(int userid)
{
    // 组装 SQL 语句
    char sql[1024] = {0};
    sprintf(sql, "DELETE FROM OfflineMessage WHERE userid = %d", userid);

    MySQL mysql;
    if (mysql.Connect())
    {
        if (mysql.Update(sql) != 0)
        {
            MYSQL *conn = mysql.GetConnection();
            std::cerr << "Failed to remove offline messages for user " << userid << ". Error: " << mysql_error(conn) << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to connect to database when removing offline messages for user " << userid << std::endl;
    }
}

// 查询用户的离线消息
std::vector<std::string> OfflineMsgModel::query(int userid)
{
    // 组装 SQL 语句
    char sql[1024] = {0};
    sprintf(sql, "SELECT message FROM OfflineMessage WHERE userid = %d", userid);

    std::vector<std::string> vec;
    MySQL mysql;
    if (mysql.Connect())
    {
        MYSQL_RES *res = mysql.Query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                vec.push_back(row[0]);
            }
            mysql_free_result(res);
        }
        else
        {
            MYSQL *conn = mysql.GetConnection();
            std::cerr << "Failed to query offline messages for user " << userid << ". Error: " << mysql_error(conn) << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to connect to database when querying offline messages for user " << userid << std::endl;
    }
    return vec;
}

// 统计离线消息
int OfflineMsgModel::count(int userid)
{
    // 组装 SQL 语句
    char sql[1024] = {0};
    sprintf(sql, "SELECT COUNT(*) FROM OfflineMessage WHERE userid = %d", userid);

    int count = 0;
    MySQL mysql;
    if (mysql.Connect())
    {
        MYSQL_RES *res = mysql.Query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                count = atoi(row[0]);
            }
            mysql_free_result(res);
        }
        else
        {
            MYSQL *conn = mysql.GetConnection();
            std::cerr << "Failed to count offline messages for user " << userid << ". Error: " << mysql_error(conn) << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to connect to database when counting offline messages for user " << userid << std::endl;
    }
    return count;
}
}    