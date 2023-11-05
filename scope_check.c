#include <stdlib.h>
#include <stdio.h>
#include "scope_check.h"
#include "scope.h"
#include "ast.h"
#include "symtab.h"
#include "utilities.h"

void scope_check_program(block_t prog)
{
    symtab_enter_scope(); // push
    scope_check_constDecls(prog.const_decls);
    scope_check_varDecls(prog.var_decls);
    scope_check_stmts(prog.stmt);
    symtab_leave_scope(); // pop
}

extern void scope_check_constDecls(const_decls_t cds)
{
    const_decl_t *cdp = cds.const_decls;
    while (cdp != NULL)
    {
        scope_check_const_idents(cdp->const_defs.const_defs);
        cdp = cdp->next;
    }
}

extern void scope_check_const_idents(const_def_t *cd)
{
    const_def_t *cdp = cd;
    while (cdp != NULL)
    {
        scope_check_declare_ident(&(cdp->ident), constant_idk);
        cdp = cdp->next;
    }
}

extern void scope_check_varDecls(var_decls_t vds)
{
    var_decl_t *vdp = vds.var_decls;
    while (vdp != NULL)
    {
        scope_check_varDecl(*vdp);
        vdp = vdp->next;
    }
}

extern void scope_check_varDecl(var_decl_t vd)
{
    scope_check_idents(vd.idents, variable_idk);
}

extern void scope_check_idents(idents_t ids, id_kind vt)
{
    ident_t *idp = ids.idents;
    while (idp != NULL)
    {
        scope_check_declare_ident(idp, vt);
        idp = idp->next;
    }
}

extern void scope_check_declare_ident(ident_t *id, id_kind vt)
{
    id_use *ident_query = symtab_lookup(id->name);
    if(ident_query != NULL)
    {
        if (ident_query->attrs->kind == constant_idk)
            bail_with_prog_error(*(id->file_loc), "%s \"%s\" is already declared as a constant", vt == constant_idk ? "constant" : "variable", id->name);   
        else 
            bail_with_prog_error(*(id->file_loc), "%s \"%s\" is already declared as a variable", vt == constant_idk ? "constant" : "variable", id->name);
    } 
    else 
    {
        int ofst_cnt = symtab_scope_loc_count();
        id_attrs *attrs = create_id_attrs(*(id->file_loc), vt, ofst_cnt);
        symtab_insert(id->name, attrs);
    }
}

extern void scope_check_stmts(stmt_t stmt)
{
    stmt_t *stp = &stmt;
    while (stp != NULL)
    {
        scope_check_stmt(*stp);
        stp = stp->next;
    }
}

extern void scope_check_stmt(stmt_t stmt)
{
    switch (stmt.stmt_kind)
    {
        case assign_stmt:
            scope_check_assignStmt(stmt.data.assign_stmt);
            break;
        case call_stmt:
            scope_check_callStmt(stmt.data.call_stmt);
            break;
        case begin_stmt:
            scope_check_beginStmt(stmt.data.begin_stmt);
            break;
        case if_stmt:
            scope_check_ifStmt(stmt.data.if_stmt);
            break;
        case while_stmt:
            scope_check_whileStmt(stmt.data.while_stmt);
            break;
        case read_stmt:
            scope_check_readStmt(stmt.data.read_stmt);
            break;
        case write_stmt:
            scope_check_writeStmt(stmt.data.write_stmt);
            break;
        case skip_stmt:
            scope_check_skipStmt(stmt.data.skip_stmt);
            break;
        default:
            bail_with_error("Invalid statement kind in scope_check_stmt!");
            break;
    }
}

extern void scope_check_assignStmt(assign_stmt_t stmt)
extern void scope_check_callStmt(call_stmt_t stmt);
extern void scope_check_beginStmt(begin_stmt_t stmt);
extern void scope_check_ifStmt(if_stmt_t stmt);
extern void scope_check_whileStmt(while_stmt_t stmt);
extern void scope_check_readStmt(read_stmt_t stmt);
extern void scope_check_writeStmt(write_stmt_t stmt);
extern void scope_check_skipStmt(skip_stmt_t stmt);
