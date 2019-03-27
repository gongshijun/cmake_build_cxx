/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @LastEditors: Shijun Gong
 * @Date: 2019-03-06 16:36:55
 * @LastEditTime: 2019-03-12 15:56:11
 */
#include "uuid.h"

namespace kos
{
	UUID::UUID(const uint64_t& max_len, const unsigned long &max_level,
		const uint64_t& base_id) :
		max_len_(max_len), max_level_(max_level), base_id_(base_id)
	{
		level_len_ = ceil(max_len / max_level);
		id_set_ = (unsigned char**)malloc(max_level * sizeof(unsigned char*));
		for (unsigned long i = 0; i < max_level; ++i)
			id_set_[i] = nullptr;
		level_used_count_ = (unsigned long*)malloc(level_len_ * sizeof(unsigned long));
	}

	bool UUID::set_base_id(const uint64_t& base_id)
	{
		if (base_id_ == base_id)
		{
			return true;
		}
		// if the id_set_ is used, can not set the base_id_
		if (id_set_ != nullptr)
		{
			unsigned long i, j;
			for (i = 0; i < max_level_; ++i)
			{
				if (id_set_[i] == nullptr) continue;
				for (j = 0; j < level_len_; ++j)
				{
					if (id_set_[i][j] == '1')
					{
						return false;
					}
				}
			}
		}
		base_id_ = base_id;
		return true;
	}

	uint64_t UUID::get_id()
	{
		unsigned long useable_level = get_level();
		if (useable_level == 0)
		{
			return 0;
		}
		useable_level = useable_level - 1;
		id_set_[useable_level] = init_level(useable_level);
		unsigned long i = 0;
		for (i = 0; i < level_len_; ++i)
		{
			if (id_set_[useable_level][i] == '1')
				continue;
			id_set_[useable_level][i] = '1';
			level_used_inc(useable_level);
			return base_id_ + (useable_level) * level_len_ + i + 1;
		}
		return 0;
	}

	UUID::~UUID()
	{
		if (id_set_)
		{
			for (unsigned long i = 0; i < max_level_; ++i)
				if (id_set_[i]) free(id_set_[i]);
			free(id_set_);
		}
		if (level_used_count_) free(level_used_count_);
	}

	bool UUID::release_all()
	{
		if (id_set_)
		{
			for (unsigned long i = 0; i < max_level_; ++i)
				if (id_set_[i]) free(id_set_[i]);
			free(id_set_);
		}
		if (level_used_count_) free(level_used_count_);
		id_set_ = (unsigned char**)malloc(max_level_ * sizeof(unsigned char*));
		for (unsigned long i = 0; i < max_level_; ++i)
			id_set_[i] = nullptr;
		level_used_count_ = (unsigned long*)malloc(level_len_ * sizeof(unsigned long));
		return true;
	}

	bool UUID::level_enable(const unsigned long & level_index)
	{
		
		return level_used_count_[level_index] == level_len_ ? false : true;
	}

	unsigned long UUID::get_level()
	{
		if (id_set_ == nullptr) return 0;
		for (unsigned long i = 1; i < max_level_ + 1; ++i)
		{
			if (id_set_[i - 1] == nullptr || level_enable(i - 1))
				return i;
		}
		return 0;
	}

	bool UUID::change_status(uint64_t id, const char& status)
	{
		id = id - base_id_;
		unsigned long level = ceil(id / level_len_);
		unsigned long index = id % level_len_;
		if (level > max_level_) return false;
		id_set_[level] = init_level(level);
		id_set_[level][index] = status;
		if (status) level_used_inc(level);
		else level_used_dec(level);
		return true;
	}

	unsigned char* UUID::init_level(const unsigned long& level_index)
	{
		if (id_set_[level_index] == nullptr)
		{
			id_set_[level_index] = (unsigned char*)malloc(level_len_ * sizeof(unsigned char));
			for (unsigned long i = 0; i < level_len_; ++i)
				id_set_[level_index][i] = '0';
		}
		return id_set_[level_index];
	}

	void UUID::level_used_inc(const unsigned long& level_index)
	{
		level_used_count_[level_index] += 1;
	}

	void UUID::level_used_dec(const unsigned long& level_index)
	{
		level_used_count_[level_index] -= 1;
	}


} // namespace kos