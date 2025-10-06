#pragma once
#define TABLE_SIZE 10

typedef struct {
    char* key;
    int value;
    int used;
} Entry;

typedef struct {
    Entry table[TABLE_SIZE];
} HashMap;

unsigned int hash_djb2(const char* key);
void init(HashMap* map);
void insert(HashMap* map, const char* key, int value);
int* get(HashMap* map, const char* key);
void remove_key(HashMap* map, const char* key);
void free_map(HashMap* map);
void copy_map(HashMap* src, HashMap* dest);
