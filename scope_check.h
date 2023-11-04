#ifndef _SCOPE_CHECK_H
#define _SCOPE_CHECK_H
#include "scope.h"
#include "symtab.h"

// Build the symbol table for prog
// and check for duplicate declarations
// or uses of undeclared identifiers
extern void scope_check_program(program_t prog);

// build the symbol table
// and check the declarations in vds
extern void scope_check_varDecls(var_decls_t vds);

// Add declarations for the names in vd,
// reporting duplicate declarations
extern void scope_check_varDecl(var_decl_t vd);

// Add declarations for the names in ids
// to current scope as type vt
// reporting any duplicate declarations
extern void scope_check_idents(idents_t ids, var_type_e vt);

// Add declaration for id
// to current scope as type vt
// reporting if it's a duplicate declaration
void scope_check_declare_ident(dent_t id, var_type_e vt);

#endif 