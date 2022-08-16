#include <stdio.h>
#include "hashmap.h"

int main()
{

    hashmap_t map;
    hashmap_init(&map);
    hashmap_set(&map, "hello!!!", "world");

    char *text = hashmap_get(&map, "hello!!!");
    if (text) {
        puts(text);
    } else {
        puts("<Invalid>");
    }

    return 0;
}
