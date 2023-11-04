#ifndef _SCOPE_H
#define _SCOPE_H
#include "id_attrs.h"

typedef struct ident_map {
    char *name;
    id_attrs *attrs; 
} ident_map;

typedef struct scope_node {
    struct ident_map pair;
    struct scope_node *next;
} scope_node;

// Return a pointer to a new scope_node given an ident name and its attributes.
extern scope_node *create_scope_node(char *name, id_attrs *attrs);

// Insert a new node at the tail and return the head. 
extern scope_node *append_scope_node(scope_node *head, char *name, id_attrs *attrs);

// Perform a linear search for a node with the given ident name. 
// Returns NULL if node is not found. 
extern scope_node *find_scope_node(scope_node *head, char *name);

#endif