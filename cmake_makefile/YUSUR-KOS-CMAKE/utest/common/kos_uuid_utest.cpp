/*
 * @Description: Copyright(c) All rights reserved.
 * @Company: YUSUR
 * @Author: Shijun Gong
 * @LastEditors: Shijun Gong
 * @Date: 2019-03-25 15:09:14
 * @LastEditTime: 2019-03-25 18:55:41
 */
#include "test.h"

#include "common/uuid.h"

 // each run one WHEN in one GIVEN and SCENARIO is a entry
SCENARIO("uuid unit test", "[uuid]")
{
	using namespace kos;
	UUID uuid_a(100);
	uint64_t id_a = 0;

	REQUIRE(id_a == 0);
	GIVEN("Init 100 id, the base is 0")
	{
		WHEN("first time, obtain an id")
		{
			id_a = uuid_a.get_id();

			THEN("The value of id_a change")
			{
				REQUIRE(id_a == 1);
			}
		}
	}

	GIVEN("Init 100 id, the base is 10")
	{
		UUID uuid_b(100);
		uuid_b.set_base_id(10);
		uint64_t id_b;

		WHEN("first time, obtain an id")
		{
			id_b = uuid_b.get_id();

			THEN("The value of id_a change")
			{
				REQUIRE(id_b == 11);
			}
		}
	}
}

// each run one SECTION in one TEST_CASE and TEST_CASE is a entry
TEST_CASE("uuid unit test one", "[uuid]")
{
	using namespace kos;
	UUID uuid_a(100);
	uint64_t id_a = 0;

	REQUIRE(id_a == 0);

	SECTION("obtain an id, record the value")
	{
		THEN("first time, obtain an id. ")
		{
			id_a = uuid_a.get_id();
			REQUIRE(id_a == 1);
		}
	}

	UUID uuid_b(100);
	uuid_b.set_base_id(10);
	uint64_t id_b;

	SECTION("first time, obtain an id")
	{
		id_b = uuid_b.get_id();

		THEN("The value of id_a change")
		{
			REQUIRE(id_b == 11);
		}
	}
}

// Sections can be nested to an arbitrary depth
TEST_CASE("uuid unit test all", "[uuid]")
{
	using namespace kos;
	UUID uuid_a(100);
	uint64_t id_a = 0;

	REQUIRE(id_a == 0);

	SECTION("obtain an id, record the value")
	{

		id_a = uuid_a.get_id();
		REQUIRE(id_a == 1);

		id_a = uuid_a.get_id();
		REQUIRE(id_a == 2);

		id_a = uuid_a.occupy_id(3);
		id_a = uuid_a.get_id();
		REQUIRE(id_a == 4);

		id_a = uuid_a.release_id(3);
		id_a = uuid_a.get_id();
		REQUIRE(id_a == 3);
	}

	UUID uuid_b(100);
	uuid_b.set_base_id(10);
	uint64_t id_b;

	SECTION("first time, obtain an id")
	{
		id_b = uuid_b.get_id();

		THEN("The value of id_a change")
		{
			REQUIRE(id_b == 11);
		}
	}
}