#include <stdbool.h>
#include "lib/minunit.h"
#include "hashmap.h"

hashmap_t map;

void test_setup(void)
{
}

void test_teardown(void)
{
}

MU_TEST(test_init)
{
    map.keys[0] = "asa";
    hashmap_init(&map);
    int found_string = false;
    for (int i = 0; i < map.max_keys; i++) {
        if (map.keys[i] != NULL) {
            found_string = true;
            break;
        }
    }

    mu_check(!found_string);
}

MU_TEST(test_set_get)
{
    mu_check(hashmap_set(&map, "foo", "bar"));
    mu_assert_string_eq("bar", hashmap_get(&map, "foo")); // NOLINT(bugprone-suspicious-string-compare)
}

MU_TEST_SUITE(test_suite)
{
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_init);
    MU_RUN_TEST(test_set_get);
}

int main(int argc, char *argv[])
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
