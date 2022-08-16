#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include "hashmap.h"

long findchr(const char *str, char sep)
{
    long i = 0;
    char ch;
    while ((ch = str[i++]) != '\0') {
        if (ch == sep) {
            return i;
        }
    }
    return -1;
}

int main()
{
    char cmd;
    char *str = malloc(256);
    char *key, *val;
    long idx = -1;
    int hsh = -1;

    hashmap_t map;
    hashmap_init(&map);

    for (;;) {
        printf("> ");
        scanf(" %c %s", &cmd, str);

        if (cmd == 'g') {
            val = hashmap_get(&map, str);
            if (val != NULL) {
                printf("< %s\n", val);
            } else {
                puts("! Not found");
            }
        } else if (cmd == 's') {
            idx = findchr(str, '=');
            if (idx == -1) {
                puts("! Invalid key=value");
            } else {
                key = strndup(str, idx - 1);
                val = strdup(str + idx);
                hsh = hashmap_set(&map, key, val);
                if (hsh == -1) {
                    puts("! Could not set key. Out of memory?");
                } else {
                    printf("! %d\n", hsh);
                }
            }
        } else {
            printf("! Invalid command: %c\n", cmd);
        }
    }

    free(str);

    return 0;
}

#pragma clang diagnostic pop