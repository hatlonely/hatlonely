//
//  glog.cpp
//  HelloC
//
//  Created by hatlonely on 16/2/25.
//  Copyright © 2016年 hatlonely. All rights reserved.
//
//  线程安全日志库
//  官网: http://google-glog.googlecode.com/svn/trunk/doc/glog.html
//  github: git@github.com:google/glog.git
//

#include <iostream>
#include <cassert>
#include <glog/logging.h>
#include <glog/raw_logging.h>

namespace glog_glog {
    
int main(int argc, const char *argv[]) {
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::INFO, "log.");    // 设置INFO日志文件
    google::SetStderrLogging(google::INFO);     // 同时输出到屏幕
    fLB::FLAGS_colorlogtostderr = true;         // 设置颜色
    fLI::FLAGS_v = 3;                           // 自定义日志文件级别
    LOG(INFO) << "内置日志";
    VLOG(3) << "自定义日志";
    DLOG(ERROR) << "DEBUG 日志";
    DVLOG(3) << "DEBUG 自定义日志";
    SYSLOG(WARNING) << "系统日志";
    PLOG(WARNING) << "perror 风格日志";
    RAW_LOG(INFO, "底层日志");
    google::ShutdownGoogleLogging();
    return 0;
}
    
}