/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @LastEditors: Shijun Gong
 * @Date: 2019-03-25 15:04:37
 * @LastEditTime: 2019-03-27 10:46:02
 */
#include "env/kos_env.h"

void main()
{
    using namespace kos;
    // init log system
    init_el_conf();

    KOS_COUT_INFO << "Test Log System: Hello World!";
}
