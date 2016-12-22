//
//  protobuf.cpp
//  HelloC
//
//  Created by hatlonely on 15/12/23.
//  Copyright © 2015年 hatlonely. All rights reserved.
//
//  protobuf: https://github.com/google/protobuf/tree/master/examples
//  由proto文件生成源文件：protoc --cpp_out=. -I. address_book.proto

#include <iostream>
#include <fstream>
#include "address_book.pb.h"

namespace protobuf_protobuf {

int main(int argc, const char *argv[]) {
    char *buff = new char[1024];
    int length = 0;
    {
        tutorial::AddressBook address_book;
        {
            tutorial::Person *person = address_book.add_person();
            person->set_name("hatlonely");
            person->set_id(123456);
            person->set_email("hatlonely@gmail.com");
            {
                tutorial::Person::PhoneNumber *phone = person->add_phone();
                phone->set_number("138xxxx5740");
                phone->set_type(tutorial::Person::MOBILE);
            } {
                tutorial::Person::PhoneNumber *phone = person->add_phone();
                phone->set_number("131xxxx6528");
                phone->set_type(tutorial::Person::HOME);
            }
        } {
            tutorial::Person *person = address_book.add_person();
            person->set_name("playjokes");
            person->set_id(654321);
            person->set_email("playjokes@gmail.com");
            {
                tutorial::Person::PhoneNumber *phone = person->add_phone();
                phone->set_number("158xxxx1234");
                phone->set_type(tutorial::Person::MOBILE);
            } {
                tutorial::Person::PhoneNumber *phone = person->add_phone();
                phone->set_number("137xxxx5678");
                phone->set_type(tutorial::Person::HOME);
            }
        }
        
        std::ofstream fout("./address_book.dt");
        if (!address_book.SerializeToOstream(&fout)) {
            std::cerr << "serialize to ostream failed." << std::endl;
        }
        if (!address_book.SerializeToArray(buff, 1024)) {
            std::cerr << "serialize to array failed." << std::endl;
        }
        length = address_book.GetCachedSize();
    }
    
    {
        tutorial::AddressBook address_book;
        if (!address_book.ParseFromArray(buff, length)) {
            std::cerr << "parse from array failed." << std::endl;
        }
        for (int i = 0; i < address_book.person_size(); i++) {
            const tutorial::Person &person = address_book.person(i);
            std::cout << "id: " << person.id() << std::endl;
            std::cout << "name: " << person.name() << std::endl;
            std::cout << "email: " << person.email() << std::endl;
            for (int j = 0; j < person.phone_size(); j++) {
                const tutorial::Person::PhoneNumber &phone = person.phone(j);
                switch (phone.type()) {
                    case tutorial::Person::HOME: {
                        std::cout << "HOME phone #" << phone.number() << std::endl;
                        break;
                    }
                    case tutorial::Person::WORK: {
                        std::cout << "WORK phone #" << phone.number() << std::endl;
                        break;
                    }
                    case tutorial::Person::MOBILE: {
                        std::cout << "MOBILE phone #" << phone.number() << std::endl;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
            std::cout << std::endl;
        }
    }
    
    return 0;
}
    
}