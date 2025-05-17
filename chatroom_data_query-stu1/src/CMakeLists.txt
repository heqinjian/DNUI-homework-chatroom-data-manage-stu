aux_source_directory(./ SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
# 生成可执行文件
add_executable(ChatRoomManage ${SRC_LIST} ${DB_LIST} ${MODEL_LIST})
# 连接库
target_link_libraries(ChatRoomManage mysqlclient)
