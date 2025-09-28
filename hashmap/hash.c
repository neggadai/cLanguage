#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

unsigned int hash_djb2(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}


void init(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i].used = 0;
        map->table[i].key = NULL;
    }
}

void insert(HashMap* map, const char* key, int value) {
    unsigned int index = hash_djb2(key);
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
    unsigned int index = hash_djb2(key);
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
    unsigned int index = hash_djb2(key);
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

void copy_map(HashMap* src, HashMap* dest) {
    init(dest);
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (src->table[i].used) {
            dest->table[i].key = strdup(src->table[i].key);
            dest->table[i].value = src->table[i].value;
            dest->table[i].used = 1;
        }
    }
}

