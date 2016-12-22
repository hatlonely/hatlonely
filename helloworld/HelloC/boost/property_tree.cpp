//
//  property_tree.cpp
//  HelloC
//
//  Created by hatlonely on 16/1/1.
//  Copyright © 2016年 hatlonely. All rights reserved.
//
//  property_tree 属性树，适合用作配置文件，或者json和xml解析
//

#include <sstream>
#include <vector>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace boost_property_tree {

int main(int argc, const char *argv[]) {
    {
        // 创建 property_tree 对象
        // {"name": "hatlonely", "age": 24, "skill": ["java", "c++"], "email": "hatlonely@gmail.com"}
        boost::property_tree::ptree pt;
        pt.put("name", "hatlonely");
        pt.put("age", 24);
        pt.put("email", "hatlonely@gmail.com");
        {
            boost::property_tree::ptree child;
            child.push_back(boost::property_tree::ptree::value_type("", boost::property_tree::ptree("c++")));
            child.push_back(boost::property_tree::ptree::value_type("", boost::property_tree::ptree("java")));
            pt.add_child("skill", child);
        }
        boost::property_tree::write_json(std::cout, pt);
    } {
        // 由 json 创建 property_tree 对象
        std::stringstream ss;
        ss << "{\"name\": \"hatlonely\", \"age\": 24, \"skill\": [\"java\", \"c++\"], \"email\": \"hatlonely@gmail.com\"}";
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        boost::property_tree::write_json(std::cout, pt);
        boost::property_tree::write_json(std::cout, pt, false);
        
        // 获取 property_tree 对象的属性
        std::cout << pt.get<std::string>("name") << std::endl;
        std::cout << pt.get<int>("age") << std::endl;

        auto its = pt.get_child("skill").equal_range("");
        for (auto it = its.first; it != its.second; ++it) {
            std::cout << it->second.data() << std::endl;
        }
    } {
        // 创建 property_tree 对象
        // <name>hatlonely</name>
        // <age>24</age>
        // <email>hatlonely@gmail.com</email>
        // <skills><skill>c++</skill><skill>java</skill></skills>
        boost::property_tree::ptree pt;
        pt.put("name", "hatlonely");
        pt.put("age", 24);
        pt.put("email", "hatlonely@gmail.com");
        pt.add("skills.skill", "c++");
        pt.add("skills.skill", "java");
        boost::property_tree::write_xml(std::cout, pt);
        std::cout << std::endl;
    } {
        // 由 xml 创建 property_tree 对象
        std::stringstream ss;
        ss << "<name>hatlonely</name>"
           << "<age>24</age>"
           << "<email>hatlonely@gmail.com</email>"
           << "<skills><skill>c++</skill><skill>java</skill></skills>";
        boost::property_tree::ptree pt;
        boost::property_tree::read_xml(ss, pt);
        // 获取 property_tree 对象的属性
        auto its = pt.get_child("skills").equal_range("skill");
        for (auto it = its.first; it != its.second; ++it) {
            std::cout << it->second.data() << std::endl;
        }
    }

    return 0;
}

}