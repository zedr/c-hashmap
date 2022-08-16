#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "hashmap.h"

int hash(char *key)
{
    unsigned short acc = 0;
    char ch;

    while ((ch = *key++) != EOF) {
        acc += ch;
    }

    return acc;
}

void hashmap_init(hashmap_t *map)
{
    map->max_keys = USHRT_MAX;
    for (int i = 0; i < USHRT_MAX; i++) {
        map->keys[i] = NULL;
    }
}

void hashmap_free(hashmap_t *map)
{
    for (int i = 0; i< map->max_keys; i++) {
        free(map->keys[i]);
        map->keys[i] = NULL;
    }
}

char *hashmap_set(hashmap_t *map, char *key, char *val)
{
    int hsh = hash(key);
    char *tmp = strdup(val);
    if (tmp) {
        (map->keys)[hsh] = tmp;
        return tmp;
    } else {
        return NULL;
    }
}

char *hashmap_get(hashmap_t *map, char *key)
{
    return (map->keys)[hash(key)];
}
