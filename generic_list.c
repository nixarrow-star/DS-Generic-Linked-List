#include "generic_list.h"

//Init the list
struct list *list_init()
{
    struct list *list = calloc(1, sizeof(struct list));
    return list;
}

//Insert from the front of the list
struct list *list_insert_front(struct list *list, void *data, void (*destroy_data)(void *))
{
    if(list == NULL)
    {
        return NULL;
    }

    //Node creation
    struct node *node_to_insert = calloc(1, sizeof(struct node));
    if(!node_to_insert)
        return NULL;
    node_to_insert->data = data;
    node_to_insert->destroy_data = destroy_data;
    node_to_insert->next = list->first_node;
    
    //Update list
    list->size++;
    list->first_node = node_to_insert;

    return list;
}

//Insert from the back of the list 
struct list *list_insert_back(struct list *list, void *data, void (*destroy_data)(void *))
{
    if(list == NULL)
    {
        return NULL;
    }

    //If empty list
    if(list->size == 0)
    {
        return list_insert_back(list, data, destroy_data);
    }

    //Go to the place to insert
    struct node *cur_node = list->first_node;
    while(cur_node->next != NULL)
    {
        cur_node = cur_node->next;
    }

    //Node creation
    struct node *node_to_insert = calloc(1, sizeof(struct node));
    if(!node_to_insert)
        return NULL;
    node_to_insert->data = data;
    node_to_insert->destroy_data = destroy_data;
    node_to_insert->next = NULL;

    //Update list
    cur_node->next = node_to_insert;
    list->size++;

    return list;
}

struct list *list_insert_at(struct list *list, void *data, void (*destroy_data)(void *), size_t index)
{
    if(list == NULL)
    {
        return NULL;
    }

    //If insert from the front
    if(index == 0)
    {
        return list_insert_front(list, data, destroy_data);
    }

    //If insert from the back
    if(index == list->size)
    {
        return list_insert_back(list, data, destroy_data);
    }

    //If invalid index
    if(index > list->size)
    {
        return NULL;
    }

    //Node creation
    struct node *node_to_insert = calloc(1, sizeof(struct node));
    if(!node_to_insert)
        return NULL;
    node_to_insert->data = data;
    node_to_insert->destroy_data = destroy_data;

    //Go to the place to insert
    struct node *cur_node = list->first_node;
    while(index-1 > 0)
    {
        cur_node=cur_node->next;
        index--;
    }
    
    //Update list
    struct node *cur_next = cur_node->next;
    cur_node->next = node_to_insert;
    node_to_insert->next = cur_next;
    list->size++;

    return list;
}

//Get the data at the index index
void *list_get_at(struct list *list, size_t index)
{
    if(list == NULL)
    {
        return NULL;
    }

    //If invalid index
    if(index >= list->size)
    {
        return NULL;
    }

    //Go to the node to get
    struct node *cur_node = list->first_node;
    while(index > 0)
    {
        cur_node = cur_node->next;
        index--;
    }

    return cur_node->data;
}