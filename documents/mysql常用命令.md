# mysql常用命令

## mysql 安装

1 安装和启动

``` sh
# 安装
sudo yum install mariadb mariadb-server

# 启动
sudo systemctl start mariadb

# 开机启动
sudo systemctl enable mariadb
```

2. 修改root密码

``` sh
# 第一次设置密码
sudo mysqladmin -u root password 123456

# 修改密码
sudo mysqladmin -u root -p password 123456
```

3. 创建用户

``` sql
CREATE USER 'hatlonely'@'192.168.0.%' IDENTIFIED BY '123456';
CREATE USER 'hatlonely'@'localhost' IDENTIFIED BY '123456';
CREATE DATABASE IF NOT EXISTS hatlonely DEFAULT CHARSET utf8 COLLATE utf8_general_ci;
GRANT ALL PRIVILEGES ON hatlonely.* TO 'hatlonely'@'192.168.0.%';
GRANT ALL PRIVILEGES ON hatlonely.* TO 'hatlonely'@'localhost';
```

## 用户管理

1. 创建用户

    ```sql
    CREATE USER 'user'@'host' IDENTIFIED BY 'passwd'
    ```

2. 赋予用户权限

    ```sql
    GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,DROP ON database.table TO user@'host' IDENTIFIED BY 'passwd'
    ```

3. 修改用户密码

    ```sql
    MYSQLADMIN -uuser -ppasswd PASSWORD newpasswd
    ```

4. 删除用户

    ```sql
    DROP USER user
    ```

5. 取消授权用户

    ```sql
    REVOKE privilege ON database.table FROM 'user'@'host'
    ```

6. 查看授权

    ```sql
    SHOW GRANTS FOR 'user'@'host'
    ```

## 数据库表操作

1. 显示数据库

    ```sql
    SHOW DATABASES;
    ```

2. 进入数据库

    ```sql
    USE database;
    ```

3. 显示表

    ```
    SHOW TABLES;
    ```

4. 查看表结构

    ```sql
    DESCRIBE table;
    ```

5. 创建数据库

    ```sql
    CREATE DATEBASES database;
    ```

6. 创建表

    ```sql
    CREATE TABLE table (
        `wordid` bigint(20) unsigned NOT NULL,
        `md64` bigint(20) unsigned NOT NULL,
        `keyword` char(64) NOT NULL,
        PRIMARY KEY (`wordid`),
        KEY `idx_md64` (`md64`),
        KEY `idx_keyword` (`keyword`)
    ) ENGINE=InnoDB DEFAULT CHARSET=gbk
    ```

7. 插入

    ```sql
    INSERT INTO table (`wordid`, `md64`, `keyword`) VALUES (wordid, md64, keyword)
    ```

8. 导入文件

    ```sql
    LOAD DATA INFILE 'file' INTO TABLE table;
    ```

9. 删除

    ```sql
    DELETE FROM table WHERE 1=1
    ```

10. 更新

    ```sql
    UPDATE table SET column='value' WHERE condition
    ```

11. 删除数据库

    ```sql
    DROP DATABASE database
    ```

12. 修改表的存储引擎

    ```sql
    ALTER TABLE table ENGINE=engine;
    ```

13. 删除字段

    ```sql
    ALTER TABLE table DROP column;
    ```

14. 修改表名

    ```sql
    ALTER TABLE table RENAME TO new_table;
    ```

15. 修改字段名

    ```sql
    ALTER TABLE table CHANGE column new_column data_type;
    ```

