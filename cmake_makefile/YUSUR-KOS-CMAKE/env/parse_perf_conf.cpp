/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @Date: 2018-11-07 10:56:04
 * @LastEditTime: 2019-03-05 15:48:11
 * @LastEditors: Shijun Gong
 */
#include "parse_perf_conf.h"

#include <stdio.h>

#include "third_party/tinyxml2.h"

using namespace tinyxml2;

namespace kos
{
std::vector<const char*> cfd_xml_name;
std::vector<unsigned int> cfd_xml_value;

unsigned long cfd_xml_data_length = 0;
unsigned long long cfd_xml_data_addr = 0;

unsigned int cfd_parse_xml(const char* file_name)
{
    XMLDocument doc;
    doc.LoadFile(file_name);
    if (doc.ErrorID())
    {
        printf("  Load XML File %s Failed.\n", file_name);
        return 0;
    }

    XMLElement* root_elem = doc.RootElement();

    XMLElement* prop_elem = root_elem->FirstChildElement("property");
    cfd_xml_data_length = atol(prop_elem->FirstChildElement("value")->GetText());
    prop_elem = prop_elem->NextSiblingElement("property");
    cfd_xml_data_addr = atoll(prop_elem->FirstChildElement("value")->GetText());
    prop_elem = prop_elem->NextSiblingElement("property");

    while (prop_elem != NULL)
    {
        cfd_xml_name.push_back((const char*)_strdup(prop_elem->FirstChildElement("name")->GetText()));
        cfd_xml_value.push_back(atoi(prop_elem->FirstChildElement("value")->GetText()));
        prop_elem = prop_elem->NextSiblingElement("property");
    }
    return 1;
}

void cfd_parse_xml_perf_free()
{
    cfd_xml_value.clear();
	for (int i = 0; i < std::size(cfd_xml_name); i++)
	{
		free((char*)cfd_xml_name[i]);
	}
	cfd_xml_name.clear();
}
}
