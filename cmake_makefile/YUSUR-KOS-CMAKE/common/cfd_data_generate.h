/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @Date: 2018-12-24 14:24:39
 * @LastEditTime: 2019-03-07 15:41:55
 * @LastEditors: Shijun Gong
 */
#ifndef KOS_COMMON_DATA_GENERATE_H_
#define KOS_COMMON_DATA_GENERATE_H_

 /* rand genarate data. Data Format Convention: The data is unsigned. */
namespace kos
{

	// genarate Vector data: data type int. [0, 255].
	bool gen_iv_data(unsigned int*& data_p, const unsigned long& length);

	// genarate Vector data: data type float. [0, 255].
	bool gen_fv_data(float*& data_p, const unsigned long& length);

	// genarate Vector data: data type float. [0, 255].
	// bool gen_fv_data(float*& data_p, const unsigned long& length);

	// genarate Matrix data: data type float. [0, 255].
	bool gen_fm_data(float**& data_p, const unsigned int& raw, const unsigned int& col);

} // namespace kos

#endif  // KOS_COMMON_DATA_GENERATE_H_