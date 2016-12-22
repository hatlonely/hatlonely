//
//  tutorial_client.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/24.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  thrift框架：https://github.com/apache/thrift/tree/master/tutorial
//  生成gen-cpp: thrift -r --gen cpp tutorial.thrift
//

#include <iostream>

#include <boost/make_shared.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen-cpp/Calculator.h"

namespace thrift_tutorial_client {

int main(int argc, const char *argv[]) {
    typedef ::apache::thrift::transport::TTransport TTransport;
    typedef ::apache::thrift::transport::TSocket TSocket;
    typedef ::apache::thrift::protocol::TProtocol TProtocol;
    typedef ::apache::thrift::transport::TBufferedTransport TBufferedTransport;
    typedef ::apache::thrift::protocol::TBinaryProtocol TBinaryProtocol;
    typedef ::apache::thrift::TException TException;
    boost::shared_ptr<TTransport> socket    = boost::make_shared<TSocket>("127.0.0.1", 9090);
    boost::shared_ptr<TTransport> transport = boost::make_shared<TBufferedTransport>(socket);
    boost::shared_ptr<TProtocol> protocol   = boost::make_shared<TBinaryProtocol>(transport);
    tutorial::CalculatorClient client(protocol);
    
    try {
        transport->open();
        {
            client.ping();
            std::cout << "ping()" << std::endl;
        } {
            std::cout << "1 + 1" << client.add(1, 1) << std::endl;
        } {
            tutorial::Work work;
            work.op = tutorial::Operation::DIVIDE;
            work.num1 = 1;
            work.num2 = 0;
            try {
                client.calculate(666666, work);
            } catch (tutorial::InvalidOperation &io) {
                std::cout << io.why << std::endl;
            }
        } {
            tutorial::Work work;
            work.op = tutorial::Operation::SUBTRACT;
            work.num1 = 15;
            work.num2 = 10;
            try {
                std::cout << "15 - 10 = " << client.calculate(666666, work) << std::endl;
            } catch (tutorial::InvalidOperation &io) {
                std::cout << io.why << std::endl;
            }
        } {
            shared::SharedStruct ss;
            client.getStruct(ss, 666666);
            std::cout << "receive log: " << ss << std::endl;
        }
        transport->close();
    } catch (TException &tx) {
        std::cout << tx.what() << std::endl;
    }
    
    return 0;
}

}
