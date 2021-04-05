#ifndef __CT_TYPES_H__
#define __CT_TYPES_H__

#include "../basic_types.h"
#include "../cmd/Cmd_types.h"
#include "../asm/Asm_types.h"

typedef struct tag_Ct_node_s
{
    struct tag_Ct_node_s *branch_ps;
    struct tag_Ct_node_s *next_ps;
    struct tag_Ct_node_s *prev_ps;

    Cmd_command_s command_s;
    bool  is_branch;

    Asm_node_ps asm_code_head_ps;
    Cplr_val asm_code_length;
}Ct_node_s;
typedef Ct_node_s *Ct_node_ps;
typedef Ct_node_s const *Ct_node_pcs;
typedef Ct_node_ps *Ct_node_pps;
typedef Ct_node_s *const Ct_node_cps;


#endif /*__CT_TYPES_H__*/
