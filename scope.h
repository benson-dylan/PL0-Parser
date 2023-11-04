#ifndef _SCOPE_H
#define _SCOPE_H
#include "id_attrs.h"

typedef struct ident_map {
    char *name;
    id_attrs *attrs; 
} ident_map;

typedef struct node {
    struct ident_map pair;
    struct node *next;
} node;

// Return a pointer to a new node given an ident name and its attributes.
extern node *create_node(char *name, id_attrs *attrs);

// Insert a new node at the tail and return the head. 
extern node *append_node(node *head, char *name, id_attrs *attrs);

// Perform a linear search for a node with the given ident name. 
// Returns NULL if node is not found. 
extern node *find_node(node *head, char *name);

#endif