#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H
#include <stddef.h>
#include <stdlib.h>

struct node
{
    void *data;
    void (*destroy_data)(void *);
    struct node *next;
};

struct list
{
    size_t size;
    struct node *first_node;
};

struct list *list_init();
struct list *list_insert_front(struct list *list, void *data, void (*destroy_data)(void *));
struct list *list_insert_back(struct list *list, void *data, void (*destroy_data)(void *));
struct list *list_insert_at(struct list *list, void *data, void (*destroy_data)(void *), size_t index);
void *list_get_at(struct list *list, size_t index);
void *list_pop_at(struct list *list, size_t index);
void list_destroy(struct list *list);

#endif /* GENERIC_LIST_H */