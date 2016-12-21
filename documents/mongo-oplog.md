# mongo oplog

## MongoDB oplog

1. oplog是mongo中local中的一张表，这个表中记录了所有对mongo表的操作，这个表是固定大小，达到最大大小时，最新的记录会覆盖最旧的记录
2. MongoDB oplog 是mongo local数据库中的一张表，存在replication set集群的各个replication中的local.oplog.rs，但是在master slave集群中只存在master中local.oplog.$main，但是在slave中没有对应的oplog
3. Master slave集群中，slave可以以--mater参数启动，这样启动可以看到oplog表，但此时的oplog表中并没有来自master同步过来的oplog数据，其他表的数据可以正常同步
4. MongoDB 中的每一条操作都会记为一条oplog，每条oplog都用时间戳+递增的数来确保唯一，这个唯一的标志在replication set集群中将是唯一的。
5. MongoDB的oplog中，所有的update操作都只包含了操作的_id和操作的字段，并不包含整个对象，delete操作也只包含delete的_id
6. 操作对象有多个时，会触发条oplog，每条oplog只包含一个对象

## MongoDB oplog格式

ts: 8字节的时间戳，由4字节unix timestamp + 4字节自增计数表示
op: 1字节的操作类型，例如i表示insert，d表示delete
ns: 操作所在的namespace
o: 操作所对应的document,即当前操作的内容
o2: 在执行更新操作时的条件，仅限于update时才有该属性

op字段含义:
> "i": insert
> "u": update
> "d": delete
> "c": db cmd
> "n": no op,即空操作，其会定期执行以确保时效性
 
## 单机--master启动MongoDB观察oplog格式

    $ mkdir -p ~/hatlonely/mongo_workspace/master
    $ mongod --dbpath ~/hatlonely/mongo_workspace/master --master --port 27017
    $ mongo --port 27017
 
执行如下命令

    use test
    db.table.insert({"message": "hello"})
    db.table.insert({"message": "world"})
    db.table.update({"message": "hello"}, {"$set": {"message": "hi"}})
    db.table.remove({"message": "hi"})
    use local
    db.oplog.$main.find({"op": {"$ne": "n"}})
 
得到如下输出

    {
        "ts": Timestamp(1459870869, 1),
        "op": "c",
        "ns": "test.$cmd",
        "o": {
            "create": "table"
        }
    } {
        "ts": Timestamp(1459870869, 2),
        "op": "i",
        "ns": "test.table",
        "o": {
            "_id": ObjectId("5703dc9527a3d0ba4e1cf226"),
            "message": "hello"
        }
    } {
        "ts": Timestamp(1459870869, 3),
        "op": "i",
        "ns": "test.table",
        "o": {
            "_id": ObjectId("5703dc9527a3d0ba4e1cf227"),
            "message": "world"
        }
    } {
        "ts": Timestamp(1459870869, 4),
        "op": "u",
        "ns": "test.table",
        "o2": {
            "_id": ObjectId("5703dc9527a3d0ba4e1cf226")
        },
        "o": {
            "_id": ObjectId("5703dc9527a3d0ba4e1cf226"),
            "$set" : { "message" : "hi" }
        }
    } {
        "ts": Timestamp(1459870871, 1),
        "op": "d",
        "ns": "test.table",
        "b": true,
        "o": {
            "_id": ObjectId("5703dc9527a3d0ba4e1cf226")
        }
    }

## MongoDB master slave 集群搭建

    $ mkdir -p ~/hatlonely/mongo_workspace/master
    $ mkdir -p ~/hatlonely/mongo_workspace/slave1
    $ mkdir -p ~/hatlonely/mongo_workspace/slave2
    $ mongod --dbpath ~/hatlonely/mongo_workspace/master --master --port 27017
    $ mongod --dbpath ~/hatlonely/mongo_workspace/slave1 --slave --source localhost:27017 --port 27018
    $ mongod --dbpath ~/hatlonely/mongo_workspace/slave2 --slave --source localhost:27017 --port 27018
    $ mongo --port 27017
    $ mongo --port 27018
    $ mongo --port 27019
 
## MongoDB replication set 集群搭建

    $ mkdir -p ~/hatlonely/mongo_workspace/master
    $ mkdir -p ~/hatlonely/mongo_workspace/slave1
    $ mkdir -p ~/hatlonely/mongo_workspace/slave2
    $ mongod --port 27017 --dbpath ~/hatlonely/mongo_workspace/master --replSet hatlonely
    $ mongod --port 27018 --dbpath ~/hatlonely/mongo_workspace/slave1 --replSet hatlonely
    $ mongod --port 27019 --dbpath ~/hatlonely/mongo_workspace/slave2 --replSet hatlonely
     
    $ mongo --port 27017
 
执行

    config = {
        _id: 'hatlonely',
        members: [
            {_id: 0, host: 'localhost:27017'},
            {_id: 1, host: 'localhost:27018'},
            {_id: 2, host: 'localhost:27019', arbiterOnly:true}
        ]
    }
     
    rs.initiate(config);

