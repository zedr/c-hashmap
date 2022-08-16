#include <string.h>
#include <malloc.h>
#include "hashmap.h"

unsigned short hash(const char *key)
{
    unsigned short acc = 0;
    char ch;

    for (int i = 0;; i++) {
        ch = key[i];
        if (ch == '\0') {
            break;
        } else {
            acc += ch;
        }
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
    struct key *k, *tmp;

    for (int i = 0; i < map->max_keys; i++) {
        if ((k = map->keys[i])) {
            while (k) {
                tmp = k->next;
                free(k->name);
                free(k->val);
                free(k);
                k = tmp;
            }
            map->keys[i] = NULL;
        }
    }
}

int hashmap_set(hashmap_t *map, char *key, char *val)
{
    unsigned short hsh = hash(key);
    char *tmp_val = strdup(val);
    struct key *tmp_key, *k;

    if (tmp_val) {
        tmp_key = (map->keys)[hsh];
        if (tmp_key == NULL) {
            (map->keys)[hsh] = malloc(sizeof *tmp_key);
            (map->keys)[hsh]->name = strdup(key);
            (map->keys)[hsh]->val = tmp_val;
            (map->keys)[hsh]->next = NULL;
        } else {
            for (;;) {
                if (tmp_key->next == NULL) {
                    tmp_key->next = malloc(sizeof *tmp_key);
                    tmp_key->next->name = strdup(key);
                    tmp_key->next->val = tmp_val;
                    tmp_key->next->next = NULL;
                    break;
                } else {
                    tmp_key = tmp_key->next;
                }
            }
        };

        return (int) hsh;
    } else {
        return -1;
    }
}

char *hashmap_get(hashmap_t *map, char *key)
{
    int hsh = hash(key);
    struct key *tmp_key;

    tmp_key = (map->keys)[hsh];
    if (tmp_key == NULL) {
        return NULL;
    } else {
        for (;;) {
            if (strcmp(tmp_key->name, key) == 0) {
                return tmp_key->val;
            } else {
                tmp_key = tmp_key->next;
                if (tmp_key == NULL) {
                    return NULL;
                }
            }
        }
    }
}
