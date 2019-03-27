/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @LastEditors: Shijun Gong
 * @Date: 2019-03-25 10:04:06
 * @LastEditTime: 2019-03-26 20:53:13
 */
#ifndef KOS_CONF_KOS_CONF_H_
#define KOS_CONF_KOS_CONF_H_

namespace kos {
// the configured options and setting for kos
#cmakedefine  KOS_VERSION_MAJOR @KOS_VERSION_MAJOR@
#cmakedefine  KOS_VERSION_MINOR @KOS_VERSION_MINOR@
#cmakedefine  KOS_VERSION_PATCH @KOS_VERSION_PATCH@

// Enable KOS debug
#cmakedefine  KOS_DEBUG_ENABLE
// Enable KOS Log System
// #cmakedefine KOS_LOG_ENABLE
#cmakedefine  KOS_RIGHT_STR "@KOS_HELLO_STR@"

// configuration file
#cmakedefine YCC_KERNEL_CONF_PATH "@YCC_KERNEL_CONF_PATH@"

// kos log configuration file
#cmakedefine KOS_LOG_CONF_FILE_PATH "@KOS_LOG_CONF_FILE_PATH@"

} // namespace kos
#endif // KOS_CONF_KOS_CONF_H_
