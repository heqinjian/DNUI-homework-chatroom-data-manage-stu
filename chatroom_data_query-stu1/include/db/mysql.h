#pragma once
#include<string>
#include<mysql/mysql.h>
//处理数据库操作类
namespace ChatRoom{
    class MySQL{
        private:
        MYSQL* _conn;  //数据库连接
        public:
        MySQL();
        ~MySQL();
        //连接数据库
        bool Connect();
        //查询数据
        MYSQL_RES* Query(std::string sql);
        //更新数据
        bool Update(std::string sql);
        //删除数据
        bool Delete(std::string sql);
        //获取连接
        MYSQL* GetConnection();
    };    
}
