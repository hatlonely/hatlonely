//
//  asio_server.cpp
//  HelloC
//
//  Created by hatlonely on 16/2/11.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <thread>
#include <boost/asio.hpp>

namespace boost_asio_asio_server {
    
int main(int argc, const char *argv[]) {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 6666);
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
    while (true) {
        boost::asio::ip::tcp::socket socket(io_service);
        acceptor.accept(socket);
        std::thread([](boost::asio::ip::tcp::socket socket) {
            boost::system::error_code error_code;
            char data[] = "hello asio";
            boost::asio::write(socket, boost::asio::buffer(data, sizeof(data) / sizeof(data[0])));
        }, std::move(socket)).detach();
    }
    
    return 0;
}
    
}