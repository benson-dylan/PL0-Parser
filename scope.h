#ifndef _SCOPE_H
#define _SCOPE_H
#include "id_attrs.h"

typedef struct ident_map {
    char *name;
    id_attrs attrs; 
} ident_map;

typedef struct node {
    struct ident_map pair;
    struct node *next;
} node;

#endif