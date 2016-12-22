//
//  log4cplus.cpp
//  HelloC
//
//  Created by hatlonely on 16/3/27.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <cstdlib>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/loggingmacros.h>

namespace log4cplus_log4cplus {
    
int main(int argc, const char *argv[]) {
    log4cplus::PropertyConfigurator config(LOG4CPLUS_C_STR_TO_TSTRING("/Users/hatlonely/hatlonely/"
        "git_workspace/helloworld/HelloC/HelloC/log4cplus/log4cplus.properties"));
    config.configure();
    
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_C_STR_TO_TSTRING("console"));
    LOG4CPLUS_TRACE(logger, "this is a trace log");
    LOG4CPLUS_INFO(logger, "this is a info log");
    LOG4CPLUS_WARN(logger, "this is a warn log");
    LOG4CPLUS_ERROR(logger, "this is a error log");
    LOG4CPLUS_FATAL(logger, "this is a fatal log");
    
    return 0;
}
    
}
