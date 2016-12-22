//
//  crc.cpp
//  HelloC
//
//  Created by hatlonely on 16/1/10.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cassert>
#include <boost/crc.hpp>

namespace boost_crc {

int main(int argc, const char *argv[]) {
    {
        // "123456789"
        uint8_t const data[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
        size_t len = sizeof(data) / sizeof(data[0]);
        uint16_t const expected = 0x29B1;
        
        // 使用crc_basic构造ccitt校验码
        boost::crc_basic<16> crc_ccitt1(0x1021, 0xFFFF, 0, false, false);
        crc_ccitt1.process_bytes(data, len);
        assert(crc_ccitt1.checksum() == expected);
        
        // 使用crc_optimal构造ccitt校验码
        boost::crc_optimal<16, 0x1021, 0xFFFF, 0, false, false> crc_ccitt2;
        crc_ccitt2 = std::for_each(data, data + len, crc_ccitt2);
        assert(crc_ccitt2() == expected);
        
        // 直接使用crc_ccitt_type
        boost::crc_ccitt_type crc_ccitt3;
        crc_ccitt3.process_bytes(data, len);
        assert(crc_ccitt3.checksum() == expected);
    } {
        std::string data = "123456789";
        uint16_t const expected = 0x29B1;
        boost::crc_ccitt_type crc_ccitt;
        crc_ccitt.process_bytes(data.c_str(), data.length());
        assert(crc_ccitt.checksum() == expected);
    }
    
    return 0;
}
    
}