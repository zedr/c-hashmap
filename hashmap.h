#ifndef HASHMAP_HASHMAP_H
#define HASHMAP_HASHMAP_H

#include <limits.h>

typedef struct {
    unsigned short max_keys;
    char *keys[USHRT_MAX];
} hashmap_t;

int hash(char *key);

void hashmap_init(hashmap_t *map);

char *hashmap_set(hashmap_t *map, char *key, char *val);

char *hashmap_get(hashmap_t *map, char *key);

#endif //HASHMAP_HASHMAP_H
