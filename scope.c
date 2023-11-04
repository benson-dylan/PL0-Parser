#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "scope.h"

// Return a pointer to a new scope_node given an ident name and its attributes.
extern scope_node *create_scope_node(char *name, id_attrs *attrs)
{
    scope_node *ret = (scope_node *)malloc(sizeof(scope_node));
    if (ret == NULL)
        bail_with_error("scope_node creation failed in scope module!");

    ident_map new_map;
    new_map.name = name;
    new_map.attrs = attrs;
    ret->pair = new_map;
    ret->next = NULL;

    return ret;
}

// Insert a new node at the tail and return the head. 
extern scope_node *append_scope_node(scope_node *head, char *name, id_attrs *attrs)
{
    // Create first node if list is empty
    if (head == NULL)
        return create_scope_node(name, attrs);

    scope_node *iterator = head;
    while (iterator->next != NULL)
        iterator = iterator->next;

    iterator->next = create_scope_node(name, attrs);
    return head;
}

// Perform a linear search for a node with the given ident name. 
// Returns NULL if node is not found. 
extern scope_node *find_scope_node(scope_node *head, char *name)
{
    scope_node *iterator = head;
    while(iterator != NULL)
    {
        if(strcmp(name, iterator->pair.name) == 0)
            return iterator;
        iterator = iterator->next;
    }
    return NULL; 
}
// Free all nodes in the scope data structure
extern void scope_destroy(scope_node *head)
{
    scope_node *iterator = head;
    while(iterator != NULL)
    {
        scope_node *temp = iterator;
        iterator = iterator->next;
        free(temp->pair.attrs);
        free(temp);
    }
}