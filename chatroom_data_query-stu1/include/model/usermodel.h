#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.h"
#include<vector>
namespace ChatRoom{
// User表的数据操作类
class UserModel {
public:
    // User表的增加方法
    bool insert(User &user);

    // 根据用户号码查询用户信息
    vector<User> query(int id);
    
    // 根据用户号码查询用户信息
    vector<User> query(string name);

    // 更新用户的状态信息
    bool updateState(User user);

    // 更新用户的状态信息
    bool updateName(User user);

     // 删除用户信息
    bool deleteUser(int id);
    // 统计用户数量
    int userCount();
    // 重置用户的状态信息
    void resetState();
};
}
#endif
