# redis命令参考

## key

```bash
DEL key [key ...]               # delete key
DUMP key                        # key.serialize()
EXISTS key                      # is_exists(key)

EXPIRE key seconds              # key.live_for(seconds)
PEXPIRE key milliseconds        # key.live_for(seconds, milliseconds)
EXPIREAT key timestamp          # key.live_until(timestamp)     // timestamp为(unix timestamp)
PEXPIREAT key milliseconds-timestamp    # key.live_until(milliseconds-timestamp)
TTL key                         # key.ttl()
PTTL key                        # key.pttl()

KEYS pattern                    # find(pattern)     // 查找符合pattern的key
MIGRATE host port key destination-db timeout [COPY] [REPLACE]   # 将当前key传到目标机器上并删除当前key
MOVE key db                     # 将当前数据库的key移动到给定的数据库db当中
OBJECT subcommand [arguments [arguments]]   # OBJECT命令允许从内部察看给定key的Redis对象
PERSIST key                     # key.love_forever()
TYPE key                        # key.type()
SCAN cursor [MATCH pattern] [COUNT count]   # http://redisdoc.com/key/scan.html
```

## 字符串

```bash
SET key value [EX seconds] [PX milliseconds] [NX|XX]    # key = value, key.live_for(seconds, milliseconds)
GET key                         # key

MSET key value [key value]      # key1 = value1, key2 = vlaue2
MGET key [key]                  # key1, key2

SETEX key seconds value         # key.ttl(seconds)
PSETEX key milliseconds value   # key.ttl(0, millseconds)
SETNX key value                 # if (!key) key = value
MSETNX key value [key value]    # if (!key1 && !key2) {key1 = value1; key2 = vlaue2}

SETRANGE key offset value       # key = key.substring(0, offset + 1) + value
GETRANGE key start end          # key.substring(start, end + 1)

STRLEN key                      # key.length
APPEND key value                # key.append(value)

INCR key                        # key += 1
INCRBY key increment            # key += increment
INCRBYFLOAT key increment       # key += increment

SETBIT key offset value         # key.setbit(offset, value)
GETBIT key offset               # key.getbit(offset)
BITOP operation destkey key [key ...]   # destkey] = operation(key1, key2...)   // operation的值(AND OR NOT XOR)
BITCOUNT key [start] [end]      # key.bitcount(start, end)     // 计算1的数目
```

## hash

```bash
HSET key field value            # key[field] = value
HGET key field                  # key[field]
HSETNX key field value          # if (!key[field]) key[field] = value

HMSET key field value [field value ...]     # key[field1] = value1, key[field2] = value2
HMGET key field [field ...]                 # key[field1], key[field2]
HGETALL key                     # key
HEXISTS key field               # key.contains(field)

HKEYS key                       # key.keys()
HVALS key                       # key.vals()
HLEN key                        # key.size()

HINCRBY key field increment     # key[field] += increment
HINCRBYFLOAT key field increment    # key[field] += increment
HSCAN key cursor [MATCH pattern] [COUNT count]
```

## list

```bash
LSET key index value            # key[index] = value
LINDEX key index                # key[index]
LRANGE key start stop           # key[start: stop]      // LRANGE key 0 -1 查看所有元素

LLEN key                        # key.length
LINSERT key BEFORE|AFTER pivot value        # if (key.contains(pivot)) key.insert(key.indexof(pivot), value)
LREM key count value            # while (count--) key.remove(value)

LPUSH key value [value ...]     # key.push_front(value1); key.push_front(value2)
RPUSH key value [value ...]     # key.push_back(value1); key.push_back(value2)
LPUSHX key value                # if (key) key.push_front(value)
RPUSHX key value                # if (key) key.push_back(value)
LPOP key                        # key.pop_back()
RPOP key                        # key.pop_back()

RPOPLPUSH source destination    # desination.push_front(source.pop_back())  // 原子操作

BLPOP key [key ...] timeout     # key.pop_front(timeout)    // 为空时阻塞
BRPOP key [key ...] timeout     # key.pop_back(timeout)     // 为空时阻塞
BRPOPLPUSH source destination timeout   # desination.push_front(source.pop_back())  // source为空时阻塞
```

## set

```bash
SADD key member [member ...]    # key.add(member)
SREM key member [member ...]    # key.del(member)
SPOP key                        # key.del(random)       // 随机删除
SCARD key                       # key.size()
SMEMBERS key                    # key.members()
SISMEMBER key member            # key.contains(member)
SRANDMEMBER key [count]         # 返回count绝对值个随机元素，count > 0不重复，count < 0可重复

SDIFF key [key ...]             # diff(key1, key2, ...)      // 差集
SINTER key [key ...]            # inter(key1, key2, ...)     // 交集
SUNION key [key ...]            # union(key1, key2, ...)     // 并集

SDIFFSTORE destination key [key ...]    # destination = diff(key1, key2, ...)
SINTERSTORE destination key [key ...]   # destination = inter(key1, key2, ...)
SUNIONSTORE destination key [key ...]   # destination = union(key1, key2, ...)

SSCAN key cursor [MATCH pattern] [COUNT count]
```

## SortedSet

```bash
ZADD key score member [[score member] [score member] ...]   # key.add(score, member)
ZCARD key                       # key.size()
ZCOUNT key min max              # key.score_in(min, max).size()
ZLEXCOUNT key min max           # 按字典顺序返回个数

ZRANGE key start stop [WITHSCORES]      # key.score_in(min, max)
ZREVRANGE key start stop [WITHSCORES]   # key.score_in(max, min)
ZRANGEBYSCORE key min max [WITHSCORES] [LIMIT offset count]
ZREVRANGEBYSCORE key max min [WITHSCORES] [LIMIT offset count]
ZRANGEBYLEX key min max [LIMIT offset count]    # 字典顺序排序

ZRANK key member                # key.rank(member)          // 排名，从0开始
ZREVRANK key member             # key.reverse_rank(member)  // 倒排
ZREM key member [member ...]    # key.remove(member)
ZREMRANGEBYRANK key start stop  # key.remove_rank(start, stop)
ZREMRANGEBYSCORE key min max    # key.remove_score(min, max)
ZREMRANGEBYLEX key min max      # 按字典顺序删除

ZSCORE key member               # key[member].score
ZINCRBY key increment member    # key[member].score += increment

ZUNIONSTORE destination numkeys key [key ...] [WEIGHTS weight [weight ...]] [AGGREGATE SUM|MIN|MAX]
ZINTERSTORE destination numkeys key [key ...] [WEIGHTS weight [weight ...]] [AGGREGATE SUM|MIN|MAX]

ZSCAN key cursor [MATCH pattern] [COUNT count]
```

## HypeLogLog

```bash
PFADD key element [element ...]     # 将任意数量的元素添加到指定的 HyperLogLog 里面
PFCOUNT key [key ...]
PFMERGE destkey sourcekey [sourcekey ...]
```

## Geo

```bash
GEOADD key longitude latitude member [longitude latitude member ...]
GEOPOS key member [member ...]
GEODIST key member1 member2 [unit]
GEORADIUS key longitude latitude radius m|km|ft|mi [WITHCOORD] [WITHDIST] [WITHHASH] [ASC|DESC] [COUNT count]
GEORADIUSBYMEMBER key member radius m|km|ft|mi [WITHCOORD] [WITHDIST] [WITHHASH] [ASC|DESC] [COUNT count]
GEOHASH key member [member ...]
```

## Pub/Sub

```bash
PSUBSCRIBE pattern [pattern ...]
PUBLISH channel message
PUBSUB <subcommand> [argument [argument ...]]
PUNSUBSCRIBE [pattern [pattern ...]]
SUBSCRIBE channel [channel ...]
UNSUBSCRIBE [channel [channel ...]]
```

## Transaction

```bash
DISCARD
EXEC
MULTI
UNWATCH
WATCH key [key ...]
```

## Script

```bash
EVAL script numkeys key [key ...] arg [arg ...]
EVALSHA sha1 numkeys key [key ...] arg [arg ...]
SCRIPT EXISTS script [script ...]
SCRIPT FLUSH
SCRIPT KILL
SCRIPT LOAD script
```

## Connection

```bash
AUTH password
ECHO message
PING
QUIT
SELECT index
```

## server

```bash
BGREWRITEAOF            # 执行AOF重写
SAVE                    # 执行一个同步保存操作
BGSAVE                  # 后台执行快照
CLIENT SETNAME name     # 设置连接名字
CLIENT GETNAME          # 返回连接名字
CLIENT KILL ip:port     # 关闭客户端
CLIENT LIST             # 返回所有连接到服务器的客户端信息和统计数据
CONFIG GET parameter    # 获取配置参数
CONFIG RESETSTAT        # 重置统计参数
CONFIG REWRITE          # 命令对启动Redis服务器时所指定的redis.conf文件进行改写
CONFIG SET parameter value  # 动态地调整Redis服务器的配置(configuration)而无须重启
DBSIZE                  # 返回当前数据库的 key 的数量
DEBUG OBJECT key        # 是一个调试命令，它不应被客户端所使用

DEBUG SEGFAULT          # 执行一个不合法的内存访问从而让 Redis 崩溃，仅在开发时用于 BUG 模拟
FLUSHALL                # 清空整个Redis服务器的数据(删除所有数据库的所有 key )
FLUSHDB                 # 清空当前数据库中的所有key
INFO [section]          # 返回关于Redis服务器的各种信息和统计数值

LASTSAVE                # 返回最近一次Redis成功将数据保存到磁盘上的时间，以UNIX时间戳格式表示
MONITOR                 # 实时打印出Redis服务器接收到的命令，调试用
PSYNC <MASTER_RUN_ID> <OFFSET>  # 用于复制功能(replication)的内部命令
SHUTDOWN                # 保证服务器正常关闭而不丢失任何数据
SLAVEOF host port       # 用于在Redis运行时动态地修改复制(replication)功能的行为
SLOWLOG subcommand [argument]   # Slow log是Redis用来记录查询执行时间的日志系统
SYNC                    # 用于复制功能(replication)的内部命令
TIME                    # 返回当前服务器时间
```

## 参考

- [redis中文网](http://www.redis.net.cn/)
