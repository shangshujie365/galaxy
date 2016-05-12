/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file galaxy_util.h
 * @author zhoumeiting(zhoumeiting@baidu.com)
 * @date 2016/05/12 18:57:06
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef BAIDU_GALAXY_CLIENT_UTIL_H
#define BAIDU_GALAXY_CLIENT_UTIL_H

#include "sdk/galaxy_sdk.h"

namespace baidu {
namespace galaxy {
namespace client {

int BuildJobFromConfig(const std::string& conf, ::baidu::galaxy::sdk::JobDescription* job);

} //end namespace client
} //end namespace galaxy
} //end namespace baidu

#endif  // GALAXY_UTIL_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
