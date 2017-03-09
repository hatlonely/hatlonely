#pragma once

#include <boost/make_shared.hpp>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>
#include <leveldb/db.h>
#include <libconfig.h++>
#include <LeveldbCppThrift.h>

namespace hl {

class LeveldbCppThriftHandler : virtual public LeveldbCppThriftIf {
    typedef ::apache::thrift::transport::TSocket TSocket;
public:
    LeveldbCppThriftHandler(boost::shared_ptr<TSocket> sock);
    void levelPut(const std::string& key, const std::string& value);
    void levelGet(std::string& value, const std::string& key);
    void levelDel(const std::string& key);
private:
    boost::shared_ptr<TSocket> _socket;
};
    
class LeveldbCppThriftFactory : public LeveldbCppThriftIfFactory {
public:
    static leveldb::DB** db;
    static int dbnum;
    static int init(const libconfig::Setting& setting);
    virtual ~LeveldbCppThriftFactory();
    virtual LeveldbCppThriftIf* getHandler(const ::apache::thrift::TConnectionInfo& connectionInfo);
    virtual void releaseHandler(LeveldbCppThriftIf* handler);
};

}
