#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

unsigned int hash_ascii(const char* key) {
    unsigned int sum = 0;
    while (*key) sum += (unsigned char)(*key++);
    return sum % TABLE_SIZE;
}

void init(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i].used = 0;
        map->table[i].key = NULL;
    }
}

void insert(HashMap* map, const char* key, int value) {
    unsigned int index = hash_ascii(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int pos = (index + i) % TABLE_SIZE;
        if (!map->table[pos].used || strcmp(map->table[pos].key, key) == 0) {
            if (!map->table[pos].used) {
                map->table[pos].key = strdup(key);
                map->table[pos].used = 1;
            }
            map->table[pos].value = value;
            return;
        }
    }
}

int* get(HashMap* map, const char* key) {
    unsigned int index = hash_ascii(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int pos = (index + i) % TABLE_SIZE;
        if (map->table[pos].used) {
            if (strcmp(map->table[pos].key, key) == 0) {
                return &map->table[pos].value;
            }
        } else {
            return NULL;
        }
    }
    return NULL;
}
void remove_key(HashMap* map, const char* key) {
    unsigned int index = hash_ascii(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int pos = (index + i) % TABLE_SIZE;
        if (map->table[pos].used && strcmp(map->table[pos].key, key) == 0) {
            free(map->table[pos].key);
            map->table[pos].key = NULL;
            map->table[pos].used = 0;
            return;
        }
    }
}
