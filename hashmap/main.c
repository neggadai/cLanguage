#include <stdio.h>
#include "hash.h"

int main() {
    HashMap map;
    init(&map);

    insert(&map, "baobab", 10);
    insert(&map, "banana", 20);
    insert(&map, "los", 30);

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (map.table[i].used)
            printf("[%d] %s = %d\n", i, map.table[i].key, map.table[i].value);
    }

    int* val = get(&map, "banana");
    if (val) printf("banana => %d\n", *val);
    
    remove_key(&map, "banana");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (map.table[i].used)
            printf("[%d] %s = %d\n", i, map.table[i].key, map.table[i].value);
    }

    HashMap copy;
    copy_map(&map, &copy);
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (copy.table[i].used)
            printf("[%d] %s = %d\n", i, copy.table[i].key, copy.table[i].value);
    }

    return 0;
}

