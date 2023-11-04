#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "scope.h"

// Return a pointer to a new node given an ident name and its attributes.
extern node *create_node(char *name, id_attrs *attrs)
{
    node *ret = (node *)malloc(sizeof(node));
    if (ret == NULL)
        bail_with_error("Node creation failed in scope module!");

    ident_map new_map;
    new_map.name = name;
    new_map.attrs = attrs;
    ret->pair = new_map;
    ret->next = NULL;

    return ret;
}

// Insert a new node at the tail and return the head. 
extern node *append_node(node *head, char *name, id_attrs *attrs)
{
    // Create first node if list is empty
    if (head == NULL)
        return create_node(name, attrs);

    node *iterator = head;
    while (iterator->next != NULL)
        iterator = iterator->next;

    iterator->next = create_node(name, attrs);
    return head;
}

// Perform a linear search for a node with the given ident name. 
// Returns NULL if node is not found. 
extern node *find_node(node *head, char *name)
{
    node *iterator = head;
    while(iterator != NULL)
    {
        if(strcmp(name, iterator->pair.name) == 0)
            return iterator;
        iterator = iterator->next;
    }
    return NULL; 
}