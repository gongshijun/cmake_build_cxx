/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @Date: 2018-12-24 16:03:16
 * @LastEditTime: 2019-03-05 15:45:06
 * @LastEditors: Shijun Gong
 */
#ifndef KOS_ENV_BUILD_OUTPUT_DIR_H_
#define KOS_ENV_BUILD_OUTPUT_DIR_H_

namespace kos
{
#define OUTPUT_DATA_DIR "output\\data"
#define OUTPUT_RESULT_DIR "output\\result"

//Ability to create multiple directories
//Linux or Window is OK.
unsigned int cfd_creat_dir(const char *pDir);

unsigned int cfd_build_output_dir();
} // namespace kos

#endif  //KOS_ENV_BUILD_OUTPUT_DIR_H_