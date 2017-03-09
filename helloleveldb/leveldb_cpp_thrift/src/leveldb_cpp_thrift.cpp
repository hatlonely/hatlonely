#include "leveldb_cpp_thrift.h"
#include <iostream>
#include "global_logger.hpp"

namespace hl {

LeveldbCppThriftHandler::LeveldbCppThriftHandler(boost::shared_ptr<TSocket> socket) : _socket(socket) {}

void LeveldbCppThriftHandler::levelPut(const std::string& key, const std::string& value) {
    int dbindex = std::hash<std::string>{}(key) % LeveldbCppThriftFactory::dbnum;
    auto status = LeveldbCppThriftFactory::db[dbindex]->Put(leveldb::WriteOptions(), key, value);
    if (!status.ok()) {
        LeveldbCppThriftException LeveldbCppThriftException;
        LeveldbCppThriftException.message = status.ToString();
        WARN("Put key[" << key << "], value[" << value << "] failed. status[" << status.ToString() << "]");
        throw LeveldbCppThriftException;
    }
    INFO("\tPut\t" << key << "\t" << value);
}

void LeveldbCppThriftHandler::levelGet(std::string& value, const std::string& key) {
    int dbindex = std::hash<std::string>{}(key) % LeveldbCppThriftFactory::dbnum;
    auto status = LeveldbCppThriftFactory::db[dbindex]->Get(leveldb::ReadOptions(), key, &value);
    if (!status.ok()) {
        LeveldbCppThriftException LeveldbCppThriftException;
        LeveldbCppThriftException.message = status.ToString();
        INFO("Get key[" << key << "], value[" << value << "] failed. status[" << status.ToString() << "]");
        throw LeveldbCppThriftException;
    }
    INFO("\tGet\t" << key << "\t" << value);
}
    
void LeveldbCppThriftHandler::levelDel(const std::string& key) {
    int dbindex = std::hash<std::string>{}(key) % LeveldbCppThriftFactory::dbnum;
    auto status = LeveldbCppThriftFactory::db[dbindex]->Delete(leveldb::WriteOptions(), key);
    if (!status.ok()) {
        LeveldbCppThriftException LeveldbCppThriftException;
        LeveldbCppThriftException.message = status.ToString();
        INFO("Del key[" << key << "] failed. status[" << status.ToString() << "]");
        throw LeveldbCppThriftException;
    }
    INFO("\tDel\t" << key << "\t" << "");
}
    
leveldb::DB** LeveldbCppThriftFactory::db = nullptr;
int LeveldbCppThriftFactory::dbnum = 0;

int LeveldbCppThriftFactory::init(const libconfig::Setting& setting) {
    leveldb::Options options;
    options.create_if_missing = true;
    std::string dbpath = setting["dbpath"].c_str();
    dbnum = setting["dbnum"];
    if (dbnum <= 0) {
        WARN("dbnum[" << dbnum << "] <= 0");
        return -1;
    }
    db = new leveldb::DB*[dbnum];
    for (int i = 0; i < dbnum; i++) {
        leveldb::Status status = leveldb::DB::Open(options, dbpath + "/" + std::to_string(i), db + i);
        if (!status.ok()) {
            WARN(status.ToString());
            return -1;
        }
    }
    
    return 0;
}
    
LeveldbCppThriftIf* LeveldbCppThriftFactory::getHandler(const ::apache::thrift::TConnectionInfo& connectionInfo) {
    typedef ::apache::thrift::transport::TSocket TSocket;
    boost::shared_ptr<TSocket> sock = boost::dynamic_pointer_cast<TSocket>(connectionInfo.transport);
    return new LeveldbCppThriftHandler(sock);
}

void LeveldbCppThriftFactory::releaseHandler(LeveldbCppThriftIf* handler) {
    delete handler;
}
    
LeveldbCppThriftFactory::~LeveldbCppThriftFactory() {}

}
