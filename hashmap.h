#ifndef HASHMAP_HASHMAP_H
#define HASHMAP_HASHMAP_H

#include <limits.h>

struct key {
    char *name;
    char *val;
    struct key *next;
};

typedef struct {
    unsigned short max_keys;
    struct key *keys[USHRT_MAX];
} hashmap_t;

unsigned short hash(const char *key);

void hashmap_init(hashmap_t *map);

void hashmap_free(hashmap_t *map);

int hashmap_set(hashmap_t *map, char *key, char *val);

char *hashmap_get(hashmap_t *map, char *key);

#endif //HASHMAP_HASHMAP_H
