#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "symtab.h"
#include "utilities.h"
#include "scope.h"

// Head node of the symtab (i.e. top of stack)
static stack_node *symtab;

static unsigned int size;

// initialize the symbol table
extern void symtab_initialize()
{
    size = 0;
    symtab = NULL;

}

extern bool symtab_empty()
{
    return size == 0;
}

// Is the symbol table itself full?
extern bool symtab_full()
{
    return size >= MAX_NESTING;
}
// Return a pointer to a new, empty stack node
extern stack_node *create_stack_node()
{
    stack_node *ret = (stack_node *)malloc(sizeof(stack_node));
    if (ret == NULL)
        bail_with_error("stack_node creation failed in symtab module!");

    ret->head = NULL;
    ret->next = NULL;
    return ret;
}

// Push new scope to the top of the stack
extern void symtab_enter_scope(stack_node *new_scope)
{
    if (symtab_empty())
    {
        symtab = create_stack_node();
        size++;
        return;
    }

    stack_node *new_scope = create_stack_node();
    new_scope->next = symtab;
    symtab = new_scope;
    size++;
}

void symtab_leave_scope()
{
    if (symtab_empty())
        return;
        
    stack_node *temp = symtab;
    symtab = symtab->next;
    scope_destroy(temp->head);
    free(temp);
    size--;
}

extern unsigned int symtab_size()
{
    return size;
}

bool declared_in_current_scope(char* name)
{
    if (symtab == NULL | symtab->head == NULL)
        return false;

    scope_node *curr = symtab->head;

    while (curr != NULL)
    {
        if (strcmp(curr.name, name) == 0)
            return true;
        else
            curr = curr.next;
    }
    
    return false;
}

extern void symtab_insert(const char *name, id_attrs *attrs)
{
    symtab.head = append_scope_node(symtab.head, name, attrs);
}

 
