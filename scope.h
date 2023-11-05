#ifndef _SCOPE_H
#define _SCOPE_H
#include "id_attrs.h"

typedef struct scope_node {
    const char *name;
    id_attrs *attrs; 
    struct scope_node *next;
} scope_node;

// Return a pointer to a new scope_node given an ident name and its attributes.
extern scope_node *create_scope_node(const char *name, id_attrs *attrs);

// Insert a new node at head.
extern scope_node *append_scope_node(scope_node *head, const char *name, id_attrs *attrs);

// Perform a linear search for a node with the given ident name. 
// Returns NULL if node is not found. 
extern scope_node *find_scope_node(scope_node *head, const char *name);

// Free all nodes in the scope data structure
extern void scope_destroy(scope_node *head);

#endif