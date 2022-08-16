#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-suspicious-string-compare"

#include <stdbool.h>
#include <malloc.h>
#include "lib/minunit.h"
#include "hashmap.h"

hashmap_t map;

void test_setup(void)
{
    hashmap_init(&map);
}

void test_teardown(void)
{
    hashmap_free(&map);
}

MU_TEST(test_init)
{
    struct key *k = malloc(sizeof(struct key));
    map.keys[0] = k;
    map.keys[0]->name = "foo";
    map.keys[0]->val = "bar";
    map.keys[0]->next = NULL;

    hashmap_init(&map);

    int found_string = false;
    for (int i = 0; i < map.max_keys; i++) {
        if (map.keys[i] != NULL) {
            found_string = true;
            break;
        }
    }

    free(k);
    mu_check(!found_string);

}

MU_TEST(test_set_get)
{
    mu_check(hashmap_set(&map, "foo", "bar"));
    mu_assert_string_eq("bar", hashmap_get(&map, "foo"));
}

MU_TEST(test_free)
{
    int hsh = hash("foo");
    hashmap_set(&map, "foo", "bar");
    hashmap_set(&map, "bar", "foo");
    hashmap_set(&map, "rab", "oof");
    hashmap_free(&map);
    mu_check(map.keys[hsh] == NULL);
}

MU_TEST(test_collision)
{
    hashmap_set(&map, "ofo", "bra");
    hashmap_set(&map, "foo", "bar");
    hashmap_set(&map, "oof", "rab");
    char *val = hashmap_get(&map, "foo");
    mu_assert_string_eq("bar", val);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_init);
    MU_RUN_TEST(test_set_get);
    MU_RUN_TEST(test_free);
    MU_RUN_TEST(test_collision);
}

int main(int argc, char *argv[])
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}

#pragma clang diagnostic pop