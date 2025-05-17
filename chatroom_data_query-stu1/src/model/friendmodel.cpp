#include "friendmodel.h"
#include <mysql/mysql.h>
#include "mysql.h"
#include <iostream>

namespace ChatRoom {
// 添加好友关系
void FriendModel::insert(int userid, int friendid)
{
    char sql[1024] = {0};
    sprintf(sql, "INSERT INTO Friend (userid, friendid) VALUES (%d, %d)", userid, friendid);

    MySQL mysql;
    if (mysql.Connect())
    {
        if (mysql.Update(sql) != 0)
        {
            MYSQL* conn = mysql.GetConnection();
            std::cerr << "Failed to insert friend relationship. Error: " << mysql_error(conn) << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to connect to database when inserting friend relationship." << std::endl;
    }
}

// 返回用户好友列表
vector<User> FriendModel::query(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "SELECT u.id, u.name, u.state FROM User u JOIN Friend f ON u.id = f.friendid WHERE f.userid = %d", userid);

    vector<User> friends;
    MySQL mysql;
    if (mysql.Connect())
    {
        MYSQL_RES* res = mysql.Query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                friends.push_back(user);
            }
            mysql_free_result(res);
        }
        else
        {
            MYSQL* conn = mysql.GetConnection();
            std::cerr << "Failed to query friend list. Error: " << mysql_error(conn) << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to connect to database when querying friend list." << std::endl;
    }
    return friends;
}

// 删除好友
void FriendModel::remove(int userid, int friendid)
{
    char sql[1024] = {0};
    sprintf(sql, "DELETE FROM Friend WHERE userid = %d AND friendid = %d", userid, friendid);

    MySQL mysql;
    if (mysql.Connect())
    {
        if (mysql.Update(sql) != 0)
        {
            MYSQL* conn = mysql.GetConnection();
            std::cerr << "Failed to remove friend. Error: " << mysql_error(conn) << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to connect to database when removing friend." << std::endl;
    }
}

// 统计好友个数
int FriendModel::count(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "SELECT COUNT(*) FROM Friend WHERE userid = %d", userid);

    int count = 0;
    MySQL mysql;
    if (mysql.Connect())
    {
        MYSQL_RES* res = mysql.Query(sql);
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
            MYSQL* conn = mysql.GetConnection();
            std::cerr << "Failed to count friends. Error: " << mysql_error(conn) << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to connect to database when counting friends." << std::endl;
    }
    return count;
}    