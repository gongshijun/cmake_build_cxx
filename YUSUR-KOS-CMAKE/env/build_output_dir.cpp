/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @Date: 2018-11-07 10:55:49
 * @LastEditTime: 2019-03-05 15:47:26
 * @LastEditors: Shijun Gong
 */
#include "build_output_dir.h"

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#elif _LINUX
#include <stdarg.h>
#include <sys/stat.h>
#endif

#ifdef _WIN32
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#elif _LINUX
#define ACCESS access
#define MKDIR(a) mkdir((a), 0755)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace kos
{
unsigned int cfd_creat_dir(const char *pDir)
{
    int i = 0;
    int ret = 0;
    int len = 0;
    char* cpDir = NULL;
    
    if (pDir == NULL)
    {
        return 0;
    }
    //solve the pDir is a const string.
    cpDir = _strdup(pDir);
    len = strlen(cpDir);
    for (i = 0; i < len; i++)
    {
        if (cpDir[i] == '\\' || cpDir[i] == '/')
        {
            cpDir[i] = '\0';
            ret = ACCESS(cpDir, 0);
            if (ret != 0)
            {
                ret = MKDIR(cpDir);
                if (ret != 0)
                {
                    return 0;
                }
            }
            cpDir[i] = '/';
        }
    }
	ret = ACCESS(cpDir, 0);
	if (ret != 0)
	{
		ret = MKDIR(cpDir);
		if (ret != 0)
		{
			ret = 0;
		}
		else
		{
			ret = 1;
		}
	}
	else
	{
		ret = 1;
	}
    free(cpDir);
    return ret;
}

unsigned int cfd_build_output_dir()
{
    if (!cfd_creat_dir(OUTPUT_DATA_DIR))
    {
        printf("  Create Output Data Dir failed. %s\n", OUTPUT_DATA_DIR);
        return 0;
    }
    if (!cfd_creat_dir(OUTPUT_RESULT_DIR))
    {
        printf("  Create Output Result Dir failed. %s\n", OUTPUT_RESULT_DIR);
        return 0;
    }
    return 1;
}
} // namespace kos