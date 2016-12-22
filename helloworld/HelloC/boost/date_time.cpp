//
//  date_time.cpp
//  HelloC
//
//  Created by hatlonely on 16/2/9.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>
#include <boost/date_time.hpp>

namespace boost_date_time {

int main(int argc, const char *argv[]) {
    {
        // 日期创建
        boost::gregorian::date date1(boost::gregorian::from_string("2016-2-9"));
        boost::gregorian::date date2(boost::gregorian::from_simple_string("2016-2-9"));
        boost::gregorian::date date3(boost::gregorian::from_simple_string("2016-Feb-9"));
        boost::gregorian::date date4(boost::gregorian::from_undelimited_string("20160209"));
        boost::gregorian::date date5(boost::gregorian::date_from_iso_string("20160209"));
        boost::gregorian::date date6(2016, 2, 9);
        boost::gregorian::date date7(2016, boost::gregorian::Feb, 9);
        std::cout << "date1: " << date1 << std::endl;
        std::cout << "date2: " << date2 << std::endl;
        std::cout << "date3: " << date3 << std::endl;
        std::cout << "date4: " << date4 << std::endl;
        std::cout << "date5: " << date5 << std::endl;
        std::cout << "date6: " << date6 << std::endl;
        std::cout << "date7: " << date7 << std::endl;
    } {
        // 当前日期
        boost::gregorian::date today(boost::gregorian::day_clock::local_day());
        std::cout << "today: " << today << std::endl;
    } {
        // 日期运算
        boost::gregorian::date today(boost::gregorian::day_clock::local_day());
        boost::gregorian::date date1 = today + boost::gregorian::days(100);
        std::cout << "today: " << date1 << std::endl;
        std::cout << "duration: " << (date1 - today).days() << std::endl;
        std::cout << "date1 > today: " << (date1 > today) << std::endl;
    } {
        // 日期字符串
        boost::gregorian::date today(boost::gregorian::day_clock::local_day());
        std::cout << "today: " << boost::gregorian::to_iso_string(today) << std::endl;
        std::cout << "today: " << boost::gregorian::to_iso_extended_string(today) << std::endl;
    } {
        // 日期属性
        boost::gregorian::date today(boost::gregorian::day_clock::local_day());
        std::cout << "year: " << today.year() << std::endl;
        std::cout << "month: " << today.month() << std::endl;               // Jan, Feb
        std::cout << "month: " << today.month().as_number() << std::endl;   // month of year 1-12
        std::cout << "day: " << today.day() << std::endl;                   // day of month 1-31
        std::cout << "day of year: " << today.day_of_year() << std::endl;   // day of year  1-366
        std::cout << "day of week: " << today.day_of_week() << std::endl;   // Mon, Tue
        std::cout << "day of week: " << today.day_of_week().as_number() << std::endl;   // 1-7
        std::cout << "week number: " << today.week_number() << std::endl;   // 1-53
        std::cout << "day number: " << today.day_number() << std::endl;     // total day
        std::cout << "end of month: " << today.end_of_month() << std::endl; // 2016-Feb-29
    } {
        // 日期循环
        boost::gregorian::date t1(boost::gregorian::from_simple_string("2016-2-9"));
        boost::gregorian::date t2(boost::gregorian::from_simple_string("2016-3-9"));
        for (boost::gregorian::date d = t1; d != t2; d += boost::gregorian::days(1)) {
            std::cout << d << std::endl;
        }
    } {
        // ptime
        boost::posix_time::ptime t1(boost::gregorian::date(2016, 2, 9), boost::posix_time::hours(18));
        boost::posix_time::ptime t2(boost::gregorian::date(2016, 2, 9), boost::posix_time::time_duration(19, 1, 1, 0));
        auto d = t2 - t1;
        std::cout << d.total_seconds() << std::endl;
    }
    
    return 0;
}
    
}
