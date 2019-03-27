/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @Date: 2018-12-24 14:24:44
 * @LastEditTime: 2019-03-05 15:44:26
 * @LastEditors: Shijun Gong
 */
#ifndef KOS_ENV_PARSE_PERF_CONF_H_
#define KOS_ENV_PARSE_PERF_CONF_H_

#include <vector>

namespace kos
{
extern std::vector<const char*> cfd_xml_name;
extern std::vector<unsigned int> cfd_xml_value;

extern unsigned long cfd_xml_data_length;
extern unsigned long long cfd_xml_data_addr;

unsigned int cfd_parse_xml(const char* file_name);
void cfd_parse_xml_perf_free();
} // namespace kos

#endif  // KOS_ENV_PARSE_PERF_CONF_H_