#include"mysql.h"
#include<iostream>
#include"user.h"
#include"group.h"
#include"groupuser.h"
#include"friendmodel.h"
#include"groupmodel.h"
#include"usermodel.h"
#include"offlinemessagemodel.h"
#include<map>
#include<vector>
#include<string>
using namespace ChatRoom;
using namespace std;
// 定义ANSI转义码的颜色
const std::string RED = "\033[31m";      // 红色
const std::string GREEN = "\033[32m";    // 绿色
const std::string YELLOW = "\033[33m";   // 黄色
const std::string BLUE = "\033[34m";     // 蓝色
const std::string YRED = "\033[35m";     // 洋红色
const std::string QING = "\033[36m";     // 青色
const std::string WHITE = "\033[37m";     // 白色
const std::string RESET = "\033[0m";     // 重置颜色
enum Managetype{
    QUERY = 1,
    ADD,
    DELETE,
    UPDATE,
    STATISTIC   //统计
};
void print_menu(){
    cout << "============欢迎来带东软校友通数据管理系统=================" << endl;
    cout << WHITE <<"请选择您的操作:"<< RESET <<endl;
    cout << YELLOW <<"1.信息查询" << RESET << endl;
    cout << YELLOW <<"2.信息添加" << RESET << endl;
    cout << YELLOW <<"3.信息删除" << RESET << endl;
    cout << YELLOW <<"4.信息更新" << RESET << endl;
    cout << YELLOW <<"5.信息统计" << RESET << endl;
    cout << "=========================================================" << endl;
    cout << BLUE <<"请输入:"<<RESET;
};
void UserDataManage(){
    UserModel userModel;
    print_menu();
    int choice = 0;
    cin >> choice;
    switch(choice){
        case QUERY:
        {
            cout << WHITE <<"请输入待查询的用户信息(用户名,输入all为查询全部):"<< RESET <<endl;
            string name;
            cin>>name;
            cout<<YELLOW<<"查询结果为:"<<RESET<<endl;
            vector<User> vec;
            vec = userModel.query(name);
            if(!vec.empty()){
                for(auto& user:vec){
                    if(user.getId() != -1){
                        cout<<GREEN<<"user id:"<<user.getId()<<" ";
                        cout<<GREEN<<"user name:"<<user.getName()<<" ";
                        cout<<GREEN<<"user State:"<<user.getState()<<RESET<<endl;
                    }else{
                        cout<<RED<<"用户未找到,请检查!"<<RESET<<endl;
                    }
                }
            }else{
                cout<<RED<<"用户未找到,请检查！"<<RESET<<endl;
            }
        }
        break;
        case ADD:
        {
            string name,password;
            cout<<YELLOW<<"应输入用户名:"<<endl;
            cin>>name;
            cout<<"请输入用户密码:"<<RESET<<endl;
            cin>>password;
            User user;
            user.setName(name);
            user.setPwd(password);
            bool res = userModel.insert(user);
            if(res){
                cout<<GREEN<<"用户插入成功！"<<RESET<<endl;
            }else{
                cout<<RED<<"用户插入失败!"<<RESET<<endl;
            }    
        }
        break;
        case DELETE:
        {
            int user_id = 0;
            cout<<YELLOW<<"请输入待删除的用户id:"<<RESET<<endl;
            cin>>user_id;  
            bool res = userModel.deleteUser(user_id);
            if(res){
                cout<<GREEN<<"用户删除成功"<<RESET<<endl;
            }else{
                cout<<RED<<"用户删除失败!"<<RESET<<endl;
            }    
        }
        break;
        case UPDATE:
        {
            int user_id = 0,chioce = 0;
            string info;
            bool res;
            User user;
            cout<<YELLOW<<"请输入待更新的用户id:"<<endl;
            cin>>user_id;
            user.setId(user_id);
            cin.get();
            cout<<WHITE<<"请选择您要更新的内容:"<<RESET<<endl;
            cout << YELLOW <<"1.更新用户名" << RESET << endl;
            cout << YELLOW <<"2.更新状态" << RESET << endl;
            cin>>chioce;
            cin.get(); //吸收换行符
            if(1 == chioce){
                cout<<WHITE<<"请输入新的用户名:"<<RESET<<endl;
                cin>>info;
                user.setName(info);
                res = userModel.updateName(user);
            }
            else if(2 == chioce){
                cout<<WHITE<<"请输入新的用户状态:"<<RESET<<endl;
                cin>>info;
                user.setState(info);
                res = userModel.updateState(user);
            }else{
                cout<<RED<<"输入有误"<<endl;
                break;
            }
            if(res){
                cout<<GREEN<<"信息更新成功"<<RESET<<endl;
            }else{
                cout<<RED<<"信息更细失败!"<<RESET<<endl;
            }    
        }
        break;
        case STATISTIC:
        {
            int count = userModel.userCount();
            if(count == -1){
                cout<<RED<<"查询出错"<<RESET<<endl;
            }else{
                cout<<GREEN<<"当前系统用户数量为:"<<count<<RESET<<endl;
            }
        }
        break;
        default:
        cout<<RED<<"输入有误！"<<RESET<<endl;
        break;
    }

}
void FriendDataManage(){
      FriendModel friendModel;
    int choice;

    while(true) {
        // 清屏
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        // 菜单界面
        cout << "============ 好友关系管理 ============" << endl;
        cout << WHITE << "请选择操作类型:" << RESET << endl;
        cout << YELLOW << "1.查询好友列表" << RESET << endl;
        cout << YELLOW << "2.添加好友关系" << RESET << endl;
        cout << YELLOW << "3.删除好友关系" << RESET << endl;
        cout << YELLOW << "4.统计好友数量" << RESET << endl;
        cout << YELLOW << "5.返回主菜单" << RESET << endl;
        cout << "=====================================" << endl;
        cout << BLUE << "请输入选择: " << RESET;

        // 输入处理
        if(!(cin >> choice)) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << RED << "输入错误，请重新选择！" << RESET << endl;
            continue;
        }

        switch(choice) {
            case 1: { // 查询好友列表
                int userid;
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) {
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << RED << "无效的用户ID！" << RESET << endl;
                    break;
                }

                vector<User> friends = friendModel.query(userid);
                if(!friends.empty()) {
                    cout << GREEN << "\n====== 好友列表 ======" << RESET << endl;
                    cout << "用户ID\t用户名\t\t状态" << endl;
                    for(auto& user : friends) {
                        cout << user.getId() << "\t" 
                             << user.getName() << "\t\t"
                             << user.getState() << endl;
                    }
                } else {
                    cout << RED << "未找到好友或用户不存在" << RESET << endl;
                }
                break;
            }

            case 2: { // 添加好友
                int userid, friendid;
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) goto add_error;
                cout << YELLOW << "请输入好友ID: " << RESET;
                if(!(cin >> friendid)) goto add_error;

                if(userid == friendid) {
                    cout << RED << "不能添加自己为好友！" << RESET << endl;
                    break;
                }

                friendModel.insert(userid, friendid);
                cout << GREEN << "已执行添加操作" << RESET << endl;
                break;

                add_error:
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << RED << "输入错误，请检查ID格式！" << RESET << endl;
                break;
            }

            case 3: { // 删除好友
                int userid, friendid;
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) goto del_error;
                cout << YELLOW << "请输入要删除的好友ID: " << RESET;
                if(!(cin >> friendid)) goto del_error;

                friendModel.remove(userid, friendid);
                cout << GREEN << "已执行删除操作" << RESET << endl;
                break;

                del_error:
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << RED << "输入错误，请检查ID格式！" << RESET << endl;
                break;
            }

            case 4: { // 统计好友
                int userid;
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) {
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cout << RED << "无效的用户ID！" << RESET << endl;
                    break;
                }

                int count = friendModel.count(userid);
                cout << GREEN << "好友总数: " << count << RESET << endl;
                break;
            }

            case 5: // 返回主菜单
                return;

            default:
                cout << RED << "无效的选项！" << RESET << endl;
                break;
        }

        // 通用暂停控制
        cout << YELLOW << "\n按回车键继续..." << RESET;
        cin.ignore();
        cin.get();
    }
}

void GroupDataManage(){
      GroupModel groupModel;
    int choice;

    while(true) {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        cout << "============ 群组管理 ============" << endl;
        cout << WHITE << "请选择操作类型:" << RESET << endl;
        cout << YELLOW << "1.创建群组" << RESET << endl;
        cout << YELLOW << "2.加入群组" << RESET << endl;
        cout << YELLOW << "3.查询所在群组" << RESET << endl;
        cout << YELLOW << "4.查询群组成员" << RESET << endl;
        cout << YELLOW << "5.返回主菜单" << RESET << endl;
        cout << "=================================" << endl;
        cout << BLUE << "请输入:" << RESET;

        if(!(cin >> choice)){
            cin.clear();
            cin.ignore(1024, '\n');
            cout << RED << "输入错误！" << RESET << endl;
            continue;
        }

        switch(choice) {
            case 1: { // 创建群组
                string name, desc;
                cout << YELLOW << "请输入群组名称: " << RESET;
                cin >> name;
                cout << YELLOW << "请输入群组描述: " << RESET;
                cin.ignore();
                getline(cin, desc);

                Group group(-1, name, desc);
                if(groupModel.createGroup(group)) {
                    cout << GREEN << "创建成功，群组ID: " << group.getId() << RESET << endl;
                } else {
                    cout << RED << "创建失败" << RESET << endl;
                }
                break;
            }

            case 2: { // 加入群组
                int userid, groupid;
                string role = "normal";
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) break;
                cout << YELLOW << "请输入群组ID: " << RESET;
                if(!(cin >> groupid)) break;
                
                groupModel.addGroup(userid, groupid, role);
                cout << GREEN << "已加入群组" << RESET << endl;
                break;
            }

            case 3: { // 查询所在群组
                  int userid;
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) break;

                vector<Group> groups = groupModel.queryGroups(userid);
                if(!groups.empty()) {
                    cout << GREEN << "====== 所在群组 ======" << RESET << endl;
                    // 修改为使用非const引用
                    for(auto& group : groups) {  // 去掉了const
                        cout << "群组ID: " << group.getId() 
                             << "\t名称: " << group.getName()
                             << "\t描述: " << group.getDesc() << endl;
                    }
                } else {
                    cout << RED << "未加入任何群组" << RESET << endl;
                }
                break;
            }
            

            case 4: { // 查询群组成员
                int userid, groupid;
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) break;
                cout << YELLOW << "请输入群组ID: " << RESET;
                if(!(cin >> groupid)) break;

                vector<int> members = groupModel.queryGroupUsers(userid, groupid);
                if(!members.empty()) {
                    cout << GREEN << "====== 群组成员 ======" << RESET << endl;
                    for(int memberid : members) {
                        cout << "成员ID: " << memberid << endl;
                    }
                } else {
                    cout << RED << "无其他成员" << RESET << endl;
                }
                break;
            }

            case 5:
                return;

            default:
                cout << RED << "无效选项！" << RESET << endl;
                break;
        }

        cout << YELLOW << "\n按回车继续..." << RESET;
        // 使用简化缓冲区清理
        cin.ignore(1024, '\n'); 
        cin.get();
    }
}
void OfflineDataManage(){
      OfflineMsgModel offlineModel;
    int choice;

    while(true) {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        cout << "============ 离线消息管理 ============" << endl;
        cout << WHITE << "请选择操作类型:" << RESET << endl;
        cout << YELLOW << "1.查询离线消息" << RESET << endl;
        cout << YELLOW << "2.删除离线消息" << RESET << endl;
        cout << YELLOW << "3.统计消息数量" << RESET << endl;
        cout << YELLOW << "4.返回主菜单" << RESET << endl;
        cout << "====================================" << endl;
        cout << BLUE << "请输入:" << RESET;

        if(!(cin >> choice)){
            cin.clear();
            cin.ignore(1024, '\n');
            cout << RED << "输入错误！" << RESET << endl;
            continue;
        }

        switch(choice) {
            case 1: { // 查询消息
                int userid;
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) break;

                vector<string> msgs = offlineModel.query(userid);
                if(!msgs.empty()) {
                    cout << GREEN << "====== 离线消息 ======" << RESET << endl;
                    for(size_t i=0; i<msgs.size(); ++i) {
                        cout << i+1 << ". " << msgs[i] << endl;
                    }
                } else {
                    cout << RED << "无离线消息" << RESET << endl;
                }
                break;
            }

            case 2: { // 删除消息（关键修改点）
                int userid;
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) break;

                // 直接调用void方法，不获取返回值
                offlineModel.remove(userid);
                cout << GREEN << "已执行删除操作" << RESET << endl;
                break;
            }

            case 3: { // 统计消息
                int userid;
                cout << YELLOW << "请输入用户ID: " << RESET;
                if(!(cin >> userid)) break;

                int count = offlineModel.count(userid);
                if(count >= 0) {
                    cout << GREEN << "未读消息数: " << count << RESET << endl;
                } else {
                    cout << RED << "统计失败" << RESET << endl;
                }
                break;
            }

            case 4:
                return;

            default:
                cout << RED << "无效选项！" << RESET << endl;
                break;
        }

        cout << YELLOW << "\n按回车继续..." << RESET;
        cin.ignore(1024, '\n');
        cin.get();
    }
}
int main(){
    int choice = 0;
    while(1){
        // 显示首页面菜单、查询、插入、删除、更新
        cout << "===========欢迎来到东软校友通数据管理系统===============" << endl;
        cout << WHITE <<"请选择您的操作："<< RESET <<endl;
        cout << YELLOW <<"1.用户信息管理" << RESET << endl;
        cout << YELLOW <<"2.好友信息管理" << RESET << endl;
        cout << YELLOW <<"3.群组信息管理" << RESET << endl;
        cout << YELLOW <<"4.离线信息管理" << RESET << endl;
        cout << "=====================================================" << endl;
        cout << BLUE <<"请输入:"<<RESET;
        cin >>choice;
        if(-1 == choice){
            cout<<YELLOW<<"退出系统"<<RESET<<endl;
            break;
        }
        cin.get();// 读掉缓冲区的回车
        switch(choice)
        {
            case 1: //用户数据管理
                UserDataManage();
                break;
            case 2: //好友数据管理
                FriendDataManage();
                break;
            case 3: //群组数据管理
                GroupDataManage();
                break;
            case 4: //离线消息管理
                OfflineDataManage();
                break;
            default:
                cout<<RED<<"input error"<<RESET<<endl;
                cin.clear();  //异常输入时,cin会输出错误标记，通过clear将其清除
                cin.ignore(100,'\n'); //清空缓冲区
                break;
        }
        
    }
    return 0;
}
