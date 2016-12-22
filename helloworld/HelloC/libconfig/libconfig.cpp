//
//  libconfig.cpp
//  HelloC
//
//  Created by hatlonely on 16/3/27.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <libconfig.h++>
#include <iostream>

namespace libconfig_libconfig {
    
int main(int argc, const char *argv[]) {
    {
        libconfig::Config config;
        try {
            config.readFile("/Users/hatlonely/hatlonely/git_workspace/"
                            "helloworld/HelloC/HelloC/libconfig/example.cfg");
        } catch (const libconfig::FileIOException &e) {
            std::cout << e.what() << std::endl;
            return -1;
        } catch (const libconfig::ParseException &e) {
            std::cout << e.what() << " [" << e.getFile() << ":" << e.getLine() << "] ";
            std::cout << e.getError() << std::endl;
            return -1;
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            return -1;
        }
        
        try {
            std::string name = config.lookup("name");
            // const libconfig::Setting &books = config.getRoot()["inventory"]["books"];
            const libconfig::Setting &books = config.lookup("inventory.books");
            
            // lookup获取配置项的值，key不存在时抛出异常
            for (int i = 0; i < books.getLength(); i++) {
                const libconfig::Setting &book = books[i];
                std::string title  = book.lookup("title");
                std::string author = book.lookup("author");
                double price       = book.lookup("price");
                int qty            = book.lookup("qty");
            }
            // lookupValue获取配置项的值，key不存在时返回false
            for (int i = 0; i < books.getLength(); i++) {
                std::string title;
                std::string author;
                double price = 0.0;
                int qty = 0;
                
                const libconfig::Setting &book = books[i];
                if (!book.lookupValue("title", title) || !book.lookupValue("author", author) ||
                    !book.lookupValue("price", price) || !book.lookupValue("qty", qty)) {
                    continue;
                }
                
                std::cout << title << std::endl;
            }
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            return -1;
        }
    }
    
    return 0;
}
    
}