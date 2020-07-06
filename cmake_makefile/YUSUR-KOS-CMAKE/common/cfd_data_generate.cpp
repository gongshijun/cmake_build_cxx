/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @Date: 2018-11-07 10:54:46
 * @LastEditTime: 2019-03-07 15:42:58
 * @LastEditors: Shijun Gong
 */
#include "cfd_data_generate.h"

#include <stdio.h>
#include <stdlib.h>

namespace kos
{
	bool gen_iv_data(unsigned int*& data_p, const unsigned long& length)
	{
		// if (length == 0)
		 // {
		 //	KOS_COUT_INFO << "Error: Data genarate failed. length = " << length;
		 //	return false;
		 // }
		// KOS_ASSERT(length != 0);

		unsigned int i = 0;

		float a = RAND_MAX;
		float b;
		float gap = 255.0;

		for (; i < length; i++)
		{
			b = rand();
			data_p[i] = b / a * gap;
		}
		return true;
	}

	// bool gen_fv_data(float*& data_p, const unsigned long& length)
	// {
		// if (length == 0)
		// {
		//	KOS_COUT_INFO << "Error: Data genarate failed. length = " << length;
		//	return false;
		// }
		// KOS_ASSERT(length != 0);

		// unsigned int i = 0;
		//float *data = (float*)malloc(sizeof(float)*length);

		// float a = RAND_MAX;
		// float b;
		// float gap = 255.0;

		// for (; i < length; i++)
		// {
			// b = rand();
			// data_p[i] = b / a * gap;
		// }
		// return true;
	// }

	bool gen_fv_data(float*& data_p, const unsigned long& length)
	{
		// KOS_ASSERT(length != 0);

		unsigned int i = 0;
		//float *data = (float*)malloc(sizeof(float)*length);

		float a = RAND_MAX;
		float b;
		float gap = 255.0;

		for (; i < length; i++)
		{
			b = rand();
			data_p[i] = b / a * gap;
		}
		return true;
	}

	bool gen_fm_data(float**& data_p, const unsigned int& raw, const unsigned int& col)
	{

		// KOS_ASSERT(length != 0);

		unsigned int i = 0;

		for (; i < raw; i++)
		{
			gen_fv_data(data_p[i], col);
		}
		return true;
	}

} // namespace KOS