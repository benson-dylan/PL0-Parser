#ifndef _SCOPE_CHECK_H
#define _SCOPE_CHECK_H
#include "ast.h"
#include "symtab.h"

// Build the symbol table for prog
// and check for duplicate declarations
// or uses of undeclared identifiers
extern void scope_check_program(block_t prog);

extern void scope_check_constDecls(const_decls_t cds);

extern void scope_check_const_idents(const_def_t *cd);

// build the symbol table
// and check the declarations in vds
extern void scope_check_varDecls(var_decls_t vds);

// Add declarations for the names in vd,
// reporting duplicate declarations
extern void scope_check_varDecl(var_decl_t vd);

// Add declarations for the names in ids
// to current scope as type vt
// reporting any duplicate declarations
extern void scope_check_idents(idents_t ids, id_kind vt);

// Add declaration for id
// to current scope as type vt
// reporting if it's a duplicate declaration
extern void scope_check_declare_ident(ident_t *id, id_kind vt);

#endif 