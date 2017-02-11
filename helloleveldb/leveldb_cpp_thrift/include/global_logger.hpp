#pragma once

#include <string>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/loggingmacros.h>

#ifndef PRINT
#ifndef DEBUG
#define PRINT(info) do {} while(0)
#else
#define PRINT(info) LOG4CPLUS_DEBUG(::hl::GlobalLogger::getInstance().printLogger, info)
#endif
#endif

#ifndef INFO
#define INFO(info) LOG4CPLUS_INFO(::hl::GlobalLogger::getInstance().infoLogger, info)
#endif

#ifndef WARN
#define WARN(info) LOG4CPLUS_WARN(::hl::GlobalLogger::getInstance().warnLogger, info)
#endif

#ifndef FATAL
#define FATAL(info) LOG4CPLUS_FATAL(::hl::GlobalLogger::getInstance().warnLogger, info)
#endif

namespace hl {
    
class GlobalLogger {
public:
    log4cplus::Logger infoLogger;
    log4cplus::Logger warnLogger;
    log4cplus::Logger printLogger;
    
    static int init(const std::string& logini) {
        log4cplus::PropertyConfigurator config(logini);
        config.configure();
        
        if (log4cplus::Logger::exists("info")) {
            log4cplus::Logger logger = log4cplus::Logger::getInstance("info");
            getInstance().infoLogger = logger;
        }
        
        if (log4cplus::Logger::exists("warn")) {
            log4cplus::Logger logger = log4cplus::Logger::getInstance("warn");
            getInstance().warnLogger = logger;
        }
        
        if (log4cplus::Logger::exists("print")) {
            log4cplus::Logger logger = log4cplus::Logger::getInstance("print");
            getInstance().printLogger = logger;
        }
        
        return 0;
    }

    static GlobalLogger& getInstance() {
        static GlobalLogger instance;
        return instance;
    }
    
private:
    GlobalLogger() = default;
    GlobalLogger(const GlobalLogger&) = delete;
    GlobalLogger(GlobalLogger&&) = delete;
    GlobalLogger& operator =(const GlobalLogger&) = delete;
    GlobalLogger& operator =(GlobalLogger&&) = delete;
    ~GlobalLogger() = default;
};
    
}
