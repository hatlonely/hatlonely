//
//  hiredis.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/22.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  redis API for c/c++
//  github: https://github.com/redis/hiredis
//
//  install for mac deveplement `brew install hiredis`
//

#include <iostream>
#include <sstream>
#include <cassert>
#include <hiredis/hiredis.h>

namespace hiredis_hiredis {

int main(int argc, const char *argv[]) {
    const char *host = (argc > 1) ? argv[1] : "127.0.0.1";
    int port = (argc > 2) ? atoi(argv[2]) : 6379;
    struct timeval timeout = { 1, 500000 };
    redisContext *context = redisConnectWithTimeout(host, port, timeout);
    if (context == nullptr) {
        std::cout << "alloc redisContext failed." << std::endl;
        return -1;
    }
    if (context->err) {
        std::cout << "connection error: [" << context->errstr << "]" << std::endl;
    }

    {
        // PING
        redisReply *reply = (redisReply *)redisCommand(context, "PING");
        if (reply == nullptr) {
            std::cout << context->errstr << std::endl;
            return -1;
        }
        if (reply->type == REDIS_REPLY_STATUS) {
            std::cout << "PING: " << reply->str << std::endl;
        }
        freeReplyObject(reply);
    } {
        // SET <key> <vlaue>
        redisReply *reply = (redisReply *)redisCommand(context, "SET %s %s", "foo", "hello world");
        if (reply == nullptr) {
            std::cout << context->errstr << std::endl;
            return -1;
        }
        if (reply->type == REDIS_REPLY_STATUS) {
            std::cout << "SET: " << reply->str << std::endl;
        }
        freeReplyObject(reply);
    } {
        // SET <key> <value> binary api
        redisReply *reply = (redisReply *)redisCommand(context, "SET %b %b", "bar", (size_t)3, "hello", (size_t)5);
        if (reply == nullptr) {
            std::cout << context->errstr << std::endl;
            return -1;
        }
        if (reply->type == REDIS_REPLY_STATUS) {
            std::cout << "SET (binary API): " << reply->str << std::endl;
        }
        freeReplyObject(reply);
    } {
        // GET <key>
        redisReply *reply = (redisReply *)redisCommand(context, "GET %s", "foo");
        if (reply == nullptr) {
            std::cout << context->errstr << std::endl;
            return -1;
        }
        if (reply->type == REDIS_REPLY_STRING) {
            std::cout << "GET: " << reply->str << std::endl;
        }
        freeReplyObject(reply);
    } {
        for (size_t i = 0; i < 2; i++) {
            // INCR <counter>
            redisReply *reply = (redisReply *)redisCommand(context, "INCR %s", "counter");
            if (reply == nullptr) {
                std::cout << context->errstr << std::endl;
                return -1;
            }
            if (reply->type == REDIS_REPLY_INTEGER) {
                std::cout << "INC: " << reply->integer << std::endl;
            }
            freeReplyObject(reply);
        }
    } {
        {
            // DEL <list>
            redisReply *reply = (redisReply *)redisCommand(context, "DEL mylist");
            if (reply == nullptr) {
                std::cout << context->errstr << std::endl;
                return -1;
            }
            freeReplyObject(reply);
        } {
            for (size_t i = 0; i < 10; i++) {
                // LPUSH <list> <value>
                redisReply *reply = (redisReply *)redisCommand(context, "LPUSH mylist element-%u", i);
                if (reply == nullptr) {
                    std::cout << context->errstr << std::endl;
                    return -1;
                }
                if (reply->type == REDIS_REPLY_INTEGER) {
                    std::cout << "LPUSH: " << reply->integer << std::endl;
                }
                freeReplyObject(reply);
            }
        } {
            // LRANGE <list> <startindex> <endindex>
            redisReply *reply = (redisReply *)redisCommand(context, "LRANGE mylist 0 -1");
            if (reply == nullptr) {
                std::cout << context->errstr << std::endl;
                return -1;
            }
            if (reply->type == REDIS_REPLY_ARRAY) {
                for (size_t i = 0; i < reply->elements; i++) {
                    std::cout << i << ") " << reply->element[i]->str << std::endl;
                }
            }
        } {
            // pipeline
            // pipeline可以实现批量操作，将多条命令打成一个包，大大减少网络开销，提高性能
            redisReply *reply = nullptr;
            redisAppendCommand(context, "SET %s %s", "key1", "value1");
            redisAppendCommand(context, "SET %s %s", "key2", "value2");
            redisAppendCommand(context, "SET %s %s", "key3", "value3");
            for (size_t i = 0; i < 2; i++) {
                if (redisGetReply(context, (void **)&reply) != REDIS_OK) {
                    break;
                }
                if (reply->type == REDIS_REPLY_STATUS) {
                    std::cout << "SET: " << reply->str << std::endl;
                }
                freeReplyObject(reply);
            }
            
            redisAppendCommand(context, "GET %s", "key1");
            redisAppendCommand(context, "GET %s", "key2");
            redisAppendCommand(context, "GET %s", "key3");
            for (size_t i = 0; i < 4; i++) {
                if (redisGetReply(context, (void **)&reply) != REDIS_OK) {
                    break;
                }
                if (reply->type == REDIS_REPLY_STRING) {
                    std::cout << "GET: " << reply->str << std::endl;
                }
                freeReplyObject(reply);
            }
        } {
            // mget
            std::stringstream ss;
            ss << "MGET";
            for (int i = 0; i < 4; i++) {
                ss << " " << "key" << i;
            }
            std::cout << ss.str() << std::endl;
            redisReply *reply = (redisReply *)redisCommand(context, ss.str().c_str());
            if (reply == nullptr) {
                std::cout << context->errstr << std::endl;
                return -1;
            }
            if (reply->type == REDIS_REPLY_ARRAY) {
                for (size_t i = 0; i < reply->elements; i++) {
                    if (reply->element[i]->str == nullptr) {
                        std::cout << i << ") " << "nil" << std::endl;
                    } else {
                        std::cout << i << ") " << reply->element[i]->str << std::endl;
                    }
                }
            }
        }
        
        redisFree(context);
    }
    
    return 0;
}

}