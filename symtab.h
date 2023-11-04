#ifndef _SYMTAB_H
#define _SYMTAB_H
#include <stdbool.h>
#include "scope.h"
#include "id_use.h"

#define MAX_NESTING 100;

typedef struct stack_node {
    struct scope_node *head;
    struct stack_node *next;
} stack_node;

extern void symtab_initialize();

extern bool symtab_empty();

// Is the symbol table itself full?
extern bool symtab_full();

// Return a pointer to a new, empty stack node
extern stack_node *create_stack_node();

// Return the number of scopes
// currently in the symbol table.
extern unsigned int symtab_size();

// Return the current scope's
// count of variables declared
extern unsigned int symtab_scope_loc_count();

// Return the current scope's size
// (the number of declared ids).
// extern unsigned int symtab_scope_size();

// Is name declared?
// (this looks back through all scopes)
extern bool symtab_declared(const char *name);

// Is name declared in the current scope?
// (this only looks in the current scope)
extern bool symtab_declared_in_current_scope(const char *name);

// Requires: attrs != NULL &&
// !symtab_declared_in_current_scope(name)
// Add an association from the given name
// to the given attributes
extern void symtab_insert(const char *name, id_attrs *attrs);

// Push new scope to the top of the stack
// Requires: !symtab_full()
extern void symtab_enter_scope();

// Pop scope at top of stack and destroy it
// Requires: !symtab_empty()
extern void symtab_leave_scope();

// If name is declared, return
// an id_use pointer for it, otherwise
// return NULL if name isn't declared
extern id_use *symtab_lookup(const char *name);

#endif