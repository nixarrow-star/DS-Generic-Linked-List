# 📚 Generic Linked List Library (C)

A lightweight and fully generic singly-linked list implementation in C.  
This library allows you to store **any type of data**, thanks to `void*` pointers and user-provided destroy functions.

---

## ✅ Features

- Store arbitrary data types
- Insert at front, back, or any index
- Access or remove data at a specific index
- Automatic data cleanup with user-defined destroy functions
- Safe and minimal API

---

## 📦 Data Structures

### `struct node`
Represents a single cell of the linked list:

```c
struct node
{
    void *data;                       // Pointer to stored data
    void (*destroy_data)(void *);     // Function used to free the data
    struct node *next;                // Pointer to next element
};
```

✔ Each node owns the data it stores  
✔ When the list is destroyed, `destroy_data(data)` is automatically called

---

### `struct list`
Represents the entire list:

```c
struct list
{
    size_t size;          // Number of elements stored
    struct node *first_node;
};
```

- `size` updates after insert/remove
- `first_node` points to the first element

---

## 🔧 API Documentation

### `struct list *list_init();`
Initializes an empty list.

- On success → returns a valid empty list  
- On failure → returns `NULL`

---

### `struct list *list_insert_front(struct list *list, void *data, void (*destroy_data)(void *));`
Inserts `data` at the front of the list.

- Stores the pointer, does not copy data  
- `destroy_data` will be used later by `list_destroy`

- On success → returns `list`  
- On allocation failure → returns `NULL`

---

### `struct list *list_insert_back(struct list *list, void *data, void (*destroy_data)(void *));`
Inserts `data` at the back of the list.

- On success → returns `list`  
- On allocation failure → returns `NULL`

---

### `struct list *list_insert_at(struct list *list, void *data, void (*destroy_data)(void *), size_t index);`
Inserts `data` at the given index.

- `index == 0` → front  
- `index == list->size` → back

- On success → returns `list`  
- On invalid index or allocation failure → returns `NULL`

---

### `void *list_get_at(struct list *list, size_t index);`
Returns the stored data at index.

- Does **not** remove or modify the list  
- On success → returns the `void*` data  
- On invalid index → returns `NULL`

---

### `void *list_pop_at(struct list *list, size_t index);`
Removes the node at `index` and returns its data pointer.

- The node is freed  
- `destroy_data` is **NOT** called → the caller must free the returned data

- On success → returns the data pointer  
- On invalid index → returns `NULL`

---

### `void list_destroy(struct list *list);`
Destroys the whole list:

- Frees every node  
- Calls each stored `destroy_data(data)` before freeing the node

⚠ **WARNING:**  
> The list automatically destroys all stored data.  
> Only call this when you no longer need the data.

---

## ✅ Example Usage

```c
void free_int(void *n)
{
    free(n);
}

int main()
{
    struct list *l = list_init();
    if (!l) return 1;

    int *x = malloc(sizeof(int));
    *x = 42;

    list_insert_back(l, x, free_int);

    int *val = list_get_at(l, 0);
    printf("Value: %d
", *val);

    list_destroy(l);
}
```

---

## ✅ License

Free to use and modify in any project.
