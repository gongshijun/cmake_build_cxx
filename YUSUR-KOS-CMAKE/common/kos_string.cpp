/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @LastEditors: Shijun Gong
 * @Date: 2019-03-06 18:06:22
 * @LastEditTime: 2019-03-06 20:19:15
 */
// define common operation for string
#include "kos_string.h"

namespace kos
{
    std::string convert_to_str(const float& num)
    {
        std::ostringstream oss;
        oss << num;
        std::string str(oss.str());
        return str;
    }

    std::string convert_to_str(const int& num)
    {
        std::ostringstream oss;
        oss << num;
        std::string str(oss.str());
        return str;
    }

    std::string convert_to_str(const unsigned long long& num)
    {
        std::ostringstream oss;
        oss << num;
        std::string str(oss.str());
        return str;
    }

	unsigned long str_to_ul_base2(const char* str)
	{
		return strtoul(str, NULL, 2);
	}
} // namespace kos