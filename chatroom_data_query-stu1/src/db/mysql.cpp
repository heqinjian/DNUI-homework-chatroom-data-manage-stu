#include "mysql.h"
#include "const.h"
using namespace ChatRoom;
MySQL::MySQL(){
    //初始化一个mysql连接，传空，创建一个。非空，初始化传入的
    _conn = mysql_init(nullptr);
}
MySQL::~MySQL(){
    if(_conn != nullptr){
        //关闭连接
        mysql_close(_conn);
    }
}
//连接数据库
bool  MySQL::Connect(){
    MYSQL *p = mysql_real_connect(_conn, server.c_str(),user.c_str(),
                                 password.c_str(),dbname.c_str(),3306,nullptr,0);
    if(p != nullptr){
        //设置字符集，否则中文会乱码
        mysql_query(_conn, "set names gbk");
        return true;
    }else{
        return false;
    }
}
//查询数据
MYSQL_RES*  MySQL::Query(std::string sql){
    //执行失败，返回非零值
    if(mysql_query(_conn,sql.c_str())){
        return nullptr;
    }else{
        return mysql_use_result(_conn);
    }
}
//更新数据
bool  MySQL::Update(std::string sql){
    if(mysql_query(_conn,sql.c_str())){
        return false;
    }else{
        return true;
    }
}
//删除数据
bool  MySQL::Delete(std::string sql){
    if(mysql_query(_conn,sql.c_str())){
        return false;
    }else{
        return true;
    }
}
//获取连接
MYSQL*  MySQL::GetConnection(){
    return _conn;
}