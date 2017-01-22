#include <iostream>
#include <string>
#include <sstream>
#include <gflags/gflags.h>
#include <gflags/gflags_declare.h>
#include <LeveldbCppThrift.h>
#include "global_logger.hpp"
#include "leveldb_cpp_thrift.h"
#include "thrift_server.hpp"

hl::ThriftServer<hl::LeveldbCppThriftProcessorFactory, hl::LeveldbCppThriftFactory> leveldbCppHttpServer;

void signalTerminal(int) {
    leveldbCppHttpServer.stop();
};

std::string VersionString() {
    std::stringstream ss;
    ss << "version " << TAG_VERSION << std::endl;
    ss << "BUILD_TIME: [" << __DATE__ << " " << __TIME__ << "]";
#ifdef DEBUG
    ss << "DEBUG_MODE: TRUE";
#endif
#ifdef GPROF
    ss << "GPROF_MODE: TRUE";
#endif
    return ss.str();
}

std::string UsageMessage() {
    return "usage: leveldb_cpp_thrift [-h] [-v]";
}

DEFINE_bool(h, false, "show usage message");
DEFINE_bool(v, false, "show version string");

int main(int argc, char *argv[]) {
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTERM, signalTerminal);
    signal(SIGINT, signalTerminal);
    
    google::SetVersionString(VersionString());
    google::SetUsageMessage(UsageMessage());
    google::ParseCommandLineFlags(&argc, &argv, false);
    if (fLB::FLAGS_h) {
        std::cout << UsageMessage() << std::endl;
        return 0;
    }
    if (fLB::FLAGS_v) {
        std::cout << VersionString() << std::endl;
        return 0;
    }
    google::HandleCommandLineHelpFlags();

    try {
        libconfig::Config config;
        config.readFile("./conf/leveldb_cpp_thrift.conf");
        
        if (hl::GlobalLogger::init(config.lookup("log4cplus").c_str())) {
            WARN("GlobalLogger init failed.");
            return -1;
        }
        
        if (hl::LeveldbCppThriftFactory::init(config.lookup("leveldb")) != 0) {
            WARN("LeveldbCppThriftFactory init failed.");
            return -1;
        }
        
        if (leveldbCppHttpServer.init(config.lookup("server")) != 0) {
            WARN("LeveldbCppHttpServer init failed.");
            return -1;
        }
        
        INFO("LeveldbCppHttpServer init ok");
        
        if (leveldbCppHttpServer.run() != 0) {
            WARN("LeveldbCppHttpServer run failed.");
            return -1;
        }
    } catch (const libconfig::ParseException &e) {
        std::cout << e.what() << " [" << e.getFile() << ":" << e.getLine() << "] " << e.getError() << std::endl;
        return -1;
    } catch (const libconfig::SettingException &e) {
        std::cout << e.what() << " [" << e.getPath() << "] " << std::endl;
        return -1;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
