#pragma once

#include <iostream>
#include <boost/make_shared.hpp>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>
#include <libconfig.h++>

namespace hl {

template <typename WorkerProcessorFactory, typename WorkerCloneFactory>
class ThriftServer {
    typedef ::apache::thrift::TProcessor TProcessor;
    typedef ::apache::thrift::TProcessorFactory TProcessorFactory;
    typedef ::apache::thrift::transport::TServerTransport TServerTransport;
    typedef ::apache::thrift::transport::TServerSocket TServerSocket;
    typedef ::apache::thrift::transport::TTransportFactory TTransportFactory;
    typedef ::apache::thrift::transport::TBufferedTransportFactory TBufferedTransportFactory;
    typedef ::apache::thrift::protocol::TProtocolFactory TProtocolFactory;
    typedef ::apache::thrift::protocol::TBinaryProtocolFactory TBinaryProtocolFactory;
    typedef ::apache::thrift::protocol::TCompactProtocolFactory TCompactProtocolFactory;
    typedef ::apache::thrift::server::TSimpleServer TSimpleServer;
    typedef ::apache::thrift::server::TThreadedServer TThreadedServer;
    typedef ::apache::thrift::server::TThreadPoolServer TThreadPoolServer;
    typedef ::apache::thrift::concurrency::ThreadManager ThreadManager;
    typedef ::apache::thrift::concurrency::ThreadFactory ThreadFactory;
    typedef ::apache::thrift::concurrency::PlatformThreadFactory PlatformThreadFactory;

public:
    int init(const libconfig::Setting& setting);
    int run();
    int stop();

    boost::shared_ptr<const ThreadManager> getThreadManager();

private:
    int32_t _serverPort   = 2017;
    int32_t _threadNumber = 30;
    boost::shared_ptr<TThreadPoolServer> _server;
    boost::shared_ptr<ThreadManager> _threadManager;
};

template <typename WorkerProcessorFactory, typename WorkerCloneFactory>
auto ThriftServer<WorkerProcessorFactory, WorkerCloneFactory>::getThreadManager() -> boost::shared_ptr<const ThreadManager> {
    return _threadManager;
}

template <typename WorkerProcessorFactory, typename WorkerCloneFactory>
int ThriftServer<WorkerProcessorFactory, WorkerCloneFactory>::init(const libconfig::Setting& setting) {
    try {
        _serverPort   = setting.lookup("server_port");
        _threadNumber = setting.lookup("thread_number");
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

template <typename WorkerProcessorFactory, typename WorkerCloneFactory>
int ThriftServer<WorkerProcessorFactory, WorkerCloneFactory>::run() {
    _threadManager = ThreadManager::newSimpleThreadManager(_threadNumber);
    _threadManager->threadFactory(boost::make_shared<PlatformThreadFactory>());
    _threadManager->start();

    _server = boost::make_shared<TThreadPoolServer>(
        boost::make_shared<WorkerProcessorFactory>(
            boost::make_shared<WorkerCloneFactory>()
        ),
        boost::make_shared<TServerSocket>(_serverPort),
        boost::make_shared<TBufferedTransportFactory>(),
        boost::make_shared<TCompactProtocolFactory>(),
        _threadManager
    );
    _server->serve();

    return 0;
}

template <typename WorkerProcessorFactory, typename WorkerCloneFactory>
int ThriftServer<WorkerProcessorFactory, WorkerCloneFactory>::stop() {
    _server->stop();
    _threadManager->stop();
    return 0;
}

}

