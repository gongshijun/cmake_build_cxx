/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @LastEditors: Shijun Gong
 * @Date: 2019-03-06 18:06:10
 * @LastEditTime: 2019-03-06 20:18:56
 */
// define some common operation for string
#ifndef KOS_STRING_H_
#define KOS_STRING_H_

#include <string>
#include <sstream>

namespace kos
{
    std::string convert_to_str(const float& num);
    std::string convert_to_str(const int& num);
    std::string convert_to_str(const unsigned long long& num);
	unsigned long str_to_ul_base2(const char* str);
} // namespace kos

#endif // KOS_STRING_H_