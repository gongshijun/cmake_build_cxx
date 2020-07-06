/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @LastEditors: Shijun Gong
 * @Date: 2019-03-06 16:49:34
 * @LastEditTime: 2019-03-06 16:50:24
 */

#include "uuid.h"

#include <iostream>

#include "uuid.h"

namespace kos
{
	void uuid_test()
	{
		UUID uuid_a(100);
		uint64_t id_a;

		id_a = uuid_a.get_id();
		std::cout << "Get a ID:\n";
		std::cout << id_a << std::endl;

		id_a = uuid_a.get_id();
		std::cout << "Get a ID:\n";
		std::cout << id_a << std::endl;

		id_a = uuid_a.occupy_id(3);
		std::cout << "Occupy a ID:\n";
		std::cout << 3 << std::endl;

		id_a = uuid_a.get_id();
		std::cout << "Get a ID:\n";
		std::cout << id_a << std::endl;

		id_a = uuid_a.release_id(3);
		std::cout << "Free a ID:\n";
		std::cout << 3 << std::endl;

		id_a = uuid_a.get_id();
		std::cout << "Get a ID:\n";
		std::cout << id_a << std::endl;

		UUID uuid_b(100);

		uuid_b.set_base_id(10);

		uint64_t id_b = uuid_b.get_id();
		std::cout << "Get a ID:\n";
		std::cout << id_b << std::endl;

	}
} // namespace kos
