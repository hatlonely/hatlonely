//
//  tutorial_server.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/23.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  thrift框架：https://github.com/apache/thrift/tree/master/tutorial
//  生成gen-cpp: thrift -r --gen cpp tutorial.thrift
//

#include <iostream>
#include <sstream>

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

#include "gen-cpp/Calculator.h"

namespace thrift_tutorial_server {

class CalculatorHandler : public tutorial::CalculatorIf {
public:
    CalculatorHandler() {}
    void ping() {
        std::cout << "ping()" << std::endl;
    }
    
    int32_t add(const int32_t n1, const int32_t n2) {
        return n1 + n2;
    }
    
    int32_t calculate(const int32_t logid, const tutorial::Work &work) {
        std::cout << "calculate()" << std::endl;
        int32_t val = 0;
        
        switch (work.op) {
            case tutorial::Operation::ADD: {
                val = work.num1 + work.num2;
                break;
            }
            case tutorial::Operation::SUBTRACT: {
                val = work.num1 - work.num2;
                break;
            }
            case tutorial::Operation::MULTIPLY: {
                val = work.num1 * work.num2;
                break;
            }
            case tutorial::Operation::DIVIDE: {
                if (work.num2 == 0) {
                    tutorial::InvalidOperation io;
                    io.whatOp = work.op;
                    io.why = "Cannot divide by 0";
                    throw io;
                }
                val = work.num1 / work.num2;
                break;
            }
            default: {
                tutorial::InvalidOperation io;
                io.whatOp = work.op;
                io.why = "Invalid operation";
                throw io;
                break;
            }
        }
        
        shared::SharedStruct ss;
        ss.key = logid;
        ss.value = std::to_string(val);
        
        log[logid] = ss;
        
        return val;
    }
    
    void getStruct(shared::SharedStruct &result, const int32_t logid) {
        std::cout << "getStruct" << std::endl;
        result = log[logid];
    }
    
    void zip() {
        std::cout << "zip()" << std::endl;
    }
protected:
    std::map<int32_t, shared::SharedStruct> log;
};

class CalculatorCloneFactory : public tutorial::CalculatorIfFactory {
public:
    virtual ~CalculatorCloneFactory() {}
    virtual tutorial::CalculatorIf *getHandler(const ::apache::thrift::TConnectionInfo& connInfo){
        typedef ::apache::thrift::transport::TSocket TSocket;
        boost::shared_ptr<TSocket> sock = boost::dynamic_pointer_cast<TSocket>(connInfo.transport);
        std::cout << "Incoming connection" << std::endl;
        std::cout << "\tSocketInfo: "  << sock->getSocketInfo() << std::endl;
        std::cout << "\tPeerHost: "    << sock->getPeerHost() << std::endl;
        std::cout << "\tPeerAddress: " << sock->getPeerAddress() << std::endl;
        std::cout << "\tPeerPort: "    << sock->getPeerPort() << std::endl;
        return new CalculatorHandler;
    }
    virtual void releaseHandler(::shared::SharedServiceIf *handler) {
        delete handler;
    }
};

int main(int argc, const char *argv[]) {
    typedef ::apache::thrift::TProcessor TProcessor;
    typedef ::apache::thrift::TProcessorFactory TProcessorFactory;
    typedef ::apache::thrift::transport::TServerTransport TServerTransport;
    typedef ::apache::thrift::transport::TServerSocket TServerSocket;
    typedef ::apache::thrift::transport::TTransportFactory TTransportFactory;
    typedef ::apache::thrift::transport::TBufferedTransportFactory TBufferedTransportFactory;
    typedef ::apache::thrift::protocol::TProtocolFactory TProtocolFactory;
    typedef ::apache::thrift::protocol::TBinaryProtocolFactory TBinaryProtocolFactory;
    typedef ::apache::thrift::server::TSimpleServer TSimpleServer;
    typedef ::apache::thrift::server::TThreadedServer TThreadedServer;
    typedef ::apache::thrift::server::TThreadPoolServer TThreadPoolServer;
    typedef ::apache::thrift::concurrency::ThreadManager ThreadManager;
    typedef ::apache::thrift::concurrency::ThreadFactory ThreadFactory;
    typedef ::apache::thrift::concurrency::PlatformThreadFactory PlatformThreadFactory;
#if 0
    {
        boost::shared_ptr<CalculatorHandler> handler           = boost::make_shared<CalculatorHandler>();
        boost::shared_ptr<TProcessor> processor                = boost::make_shared<tutorial::CalculatorProcessor>(handler);
        boost::shared_ptr<TServerTransport> server_transport   = boost::make_shared<TServerSocket>(9090);
        boost::shared_ptr<TTransportFactory> transport_factory = boost::make_shared<TBufferedTransportFactory>();
        boost::shared_ptr<TProtocolFactory> protocol_factory   = boost::make_shared<TBinaryProtocolFactory>();
        TSimpleServer server(processor, server_transport, transport_factory, protocol_factory);
        server.serve();
    }
#elif 0
    {
        boost::shared_ptr<CalculatorHandler> handler           = boost::make_shared<CalculatorHandler>();
        boost::shared_ptr<TProcessor> processor                = boost::make_shared<tutorial::CalculatorProcessor>(handler);
        boost::shared_ptr<TServerTransport> server_transport   = boost::make_shared<TServerSocket>(9090);
        boost::shared_ptr<TTransportFactory> transport_factory = boost::make_shared<TBufferedTransportFactory>();
        boost::shared_ptr<TProtocolFactory> protocol_factory   = boost::make_shared<TBinaryProtocolFactory>();
        TThreadedServer server(processor, server_transport, transport_factory, protocol_factory);
        server.serve();
    }
#elif 0
    {
        boost::shared_ptr<tutorial::CalculatorIfFactory> if_factory = boost::make_shared<CalculatorCloneFactory>();
        boost::shared_ptr<TProcessorFactory> processor              = boost::make_shared<tutorial::CalculatorProcessorFactory>(if_factory);
        boost::shared_ptr<TServerTransport> server_transport        = boost::make_shared<TServerSocket>(9090);
        boost::shared_ptr<TTransportFactory> transport_factory      = boost::make_shared<TBufferedTransportFactory>();
        boost::shared_ptr<TProtocolFactory> protocol_factory        = boost::make_shared<TBinaryProtocolFactory>();
        TThreadedServer server(processor, server_transport, transport_factory, protocol_factory);
        server.serve();
    }
#elif 1
    {
        const int worker_count = 10;
        boost::shared_ptr<ThreadManager> thread_manager = ThreadManager::newSimpleThreadManager(worker_count);
        boost::shared_ptr<ThreadFactory> thread_factory = boost::make_shared<PlatformThreadFactory>();
        thread_manager->threadFactory(thread_factory);
        thread_manager->start();

        boost::shared_ptr<tutorial::CalculatorIfFactory> if_factory = boost::make_shared<CalculatorCloneFactory>();
        boost::shared_ptr<TProcessorFactory> processor              = boost::make_shared<tutorial::CalculatorProcessorFactory>(if_factory);
        boost::shared_ptr<TServerTransport> server_transport        = boost::make_shared<TServerSocket>(9090);
        boost::shared_ptr<TTransportFactory> transport_factory      = boost::make_shared<TBufferedTransportFactory>();
        boost::shared_ptr<TProtocolFactory> protocol_factory        = boost::make_shared<TBinaryProtocolFactory>();
        TThreadPoolServer server(processor, server_transport, transport_factory, protocol_factory, thread_manager);
        server.serve();
    }
#endif
    return 0;
}

}