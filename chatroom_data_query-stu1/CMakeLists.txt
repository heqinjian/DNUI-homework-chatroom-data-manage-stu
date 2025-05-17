cmake_minimum_required(VERSION 3.0)
project(chatroom)
# 配置编译选项
set(CMAKE_CXX_FLAG ${CMKAE_CXX_FLAGS} -g -std=c++11 )
# 配置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/db)
include_directories(${PROJECT_SOURCE_DIR}/include/model)
# 连接库目录
link_directories(/usr/lib64/mysql)
# 源文件目录 
add_subdirectory(src)



