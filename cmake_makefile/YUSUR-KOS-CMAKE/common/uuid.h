/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @LastEditors: Shijun Gong
 * @Date: 2019-03-06 10:48:46
 * @LastEditTime: 2019-03-12 15:58:10
 */
 // Universally Unique Identifier
 // the method to generate uuid (bit_len), the uuid can be recycle
 // and minimize search time
#ifndef KOS_COMMON_UUID_H_
#define KOS_COMMON_UUID_H_

#include <bitset>
#include <cmath>
// #include <cstddef> std::byte in vs2017 not supported, so use unsigned char
#include <memory>
// #include <vector>

namespace kos
{
	// max_level: default equals to 10
	// level_len: default ceil(max_len / max_level)
	// max_len: maximum supported, max_level * level_len = max_len
	// the UUID >= 1, if return id equals zero, it represent failure.
	class UUID
	{
	private:
		unsigned long max_level_;
		unsigned long level_len_;
		uint64_t max_len_;
		// base id, all future ids is added on this basis
		// default is zero
		uint64_t base_id_;
		unsigned char** id_set_;
		unsigned long* level_used_count_;

	public:
		UUID() = delete;
		UUID(const uint64_t& max_len, const unsigned long &max_level = 10,
			const uint64_t& base_id = 0);
		UUID(UUID const& other) = default;
		UUID& operator = (UUID const& other) = default;

		~UUID();

		bool set_base_id(const uint64_t& base_id);
		// get a id, if return id == 0, represent failure
		uint64_t get_id();

		// release id
		bool release_id(const uint64_t& id)
		{
			return change_status(id - 1, '0');
		}

		// hand saaign a id
		bool occupy_id(const uint64_t& id)
		{
			return change_status(id - 1, '1');
		}

		bool release_all();

	private:
		// based three point the level is able to use.
		bool level_enable(const unsigned long & level_index);
		// {
		//    return level_arr[0] == '0' ? true: level_arr[level_len_ / 2] == 
		//        '0' ? true : level_arr[level_len_ - 1] == '0' ? true : false;
		// }

		// getting a useable level
		// if return zero, represent failure.
		unsigned long get_level();
		// {
		//    if (id_set_ == nullptr) return 0;
		//    for (unsigned long i = 1; i < max_level_ + 1; ++i)
		//    {
		//        if (id_set_[i] == nullptr || level_enable(id_set_[i]))
		//            return i;
		//    }
		//    return 0;
		// }

		// change the status in id_set_
		bool change_status(uint64_t id, const char& status);
		// {
		//    id = id - base_id_;
		//    unsigned long level = ceil(id / level_len_);
		//    unsigned long index = id % level_len_;
		//    if (level > max_level_) return false;
		//    id_set_[level] = init_level(level);
		//    id_set_[level][index] = status;
		//    return true;
		// }

		// init a level
		unsigned char* init_level(const unsigned long& level_index);
		// {
		//    if (id_set_[level_index] == nullptr)
		//    {
		//        id_set_[level_index] = (unsigned char*)malloc(level_len_ * sizeof(unsigned char));
		//        for (unsigned long i = 0; i < level_len_ ; ++i)
		//            id_set_[level_index][i] = '0';
		//    }
		//    return id_set_[level_index];
		// }

		void level_used_inc(const unsigned long& level_index);

		void level_used_dec(const unsigned long& level_index);
	};
} // namespace kos

#endif // KOS_COMMON_UUID_H_