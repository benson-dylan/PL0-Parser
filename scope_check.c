#include "scope_check.h"
#include "ast.h"
#include "symtab.h"

stack_node *scope;

void scope_check_program(program_t prog)
{
    symtab_enter_scope(); // push
    symtab_enter_scope(scope);
    scope_check_constDecls(prog.const_decls);
    scope_check_varDecls(prog.var_decls);
    scope_check_stmt(prog.stmt);
    symtab_leave_scope(); // pop
}

