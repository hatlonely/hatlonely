//
//  mysql_connector_c.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/23.
//  Copyright © 2015年 hatlonely. All rights reserved.
//

#include <mysql.h>
#include <iostream>

namespace mysql_connector_c {

int main(int argc, const char *argv[]) {
    MYSQL mysql_connection;
    // 初始化连接
    mysql_init(&mysql_connection);
    // 连接数据库
    if (mysql_real_connect(&mysql_connection, "localhost", "username",
                           "passwd", "employees", 3306, NULL, 0) == nullptr) {
        std::cout << "connect failed." << std::endl;
        return -1;
    }
    
    // 执行sql
    if (mysql_query(&mysql_connection, "SELECT * FROM employees LIMIT 4") != 0) {
        std::cout << "mysql_query failed" << std::endl;
        return -1;
    }
    
    // 保存执行结果
    MYSQL_RES* result = mysql_store_result(&mysql_connection);
    // 获取结果的行数
    uint64_t num_rows = mysql_num_rows(result);
    // 获取结果的列数
    uint32_t num_fields = mysql_num_fields(result);
    // 获取返回几个的列名
    MYSQL_FIELD* fields = mysql_fetch_fields(result);
    for (uint32_t i = 0; i < num_fields; i++) {
        std::cout << fields[i].name << ": " << fields[i].type << ", ";
    }
    std::cout << std::endl;
    for (uint64_t i = 0; i < num_rows; i++) {
        // 获取一行，并且指针移向下一行
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row == nullptr) {
            std::cout << "mysql_fetch_row failed" << std::endl;
            break;
        }
        for (uint32_t j = 0; j < num_fields; j++) {
            std::cout << row[j] << ", ";
        }
        std::cout << std::endl;
    }
    // 释放结果
    mysql_free_result(result);
    
    // 断开链接
    mysql_close(&mysql_connection);
    
    return 0;
}
    
}
