#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 100

typedef int (*get_hash_t)(const char*);

struct hash_node {
    const char *key;
    struct hash_node *next;
};

int get_hash(const char *str) {
    // simple hash
    int hash = 0;
    while (*str) {
        hash = (hash * 31 + *str) % HASH_TABLE_SIZE;
        str++;
    }
    return hash;
}

int ncollisions(const char **str, get_hash_t hash_func) {
    int collisions = 0;
    struct hash_node *hash_table[HASH_TABLE_SIZE] = {NULL};

    for (int i = 0; str[i] != NULL; i++) {
        int hash = hash_func(str[i]);
        struct hash_node *top = hash_table[hash];
        while (top != NULL) {
            if (strcmp(top->key, str[i]) == 0) {
                collisions++;
                break;
            }
            top = top->next;
        }
        // insert new node
        struct hash_node* new_node = malloc(sizeof(struct hash_node));
        if (new_node == NULL)
            exit(EXIT_FAILURE);

        new_node->key = str[i];
        new_node->next = hash_table[hash];
        hash_table[hash] = new_node;
    }

    return collisions;
}

int main() {
    const char *strings[] = {"hello", "world", "foo", "bar", "hello", "baz", "hello", "bar", NULL};
    int collisions = ncollisions(strings, get_hash);
    printf("Number of collisions: %d\n", collisions);
    return 0;
}
