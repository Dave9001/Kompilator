#ifndef __ASM_TYPES_H__
#define __ASM_TYPES_H__

#include "../basic_types.h"

typedef Cplr_index Asm_index;
typedef Cplr_id Asm_id;
typedef Cplr_val Asm_val;
typedef Cplr_name Asm_name;

typedef enum tag_Asm_instr_e
{
    EMPTY_INSTR,
    GET,
    PUT,
    LOAD,
    STORE,
    LOAD_I,
    STORE_I,
    ADD,
    SUB,
    SHIFT,
    INC, //10th
    DEC,
    JUMP,
    JPOS,
    JZERO,
    JNEG,

/* nowe */
    SHR,
    SHL,
    RESET,
    JODD,

    HALT
}Asm_instr_e;

typedef enum tag_Asm_p0_e
{
    P0_UNRELATED,
    A_IN_P0,
    B_IN_P0,
    C_IN_P0,
    D_IN_P0
}Asm_p0_e;

typedef struct tag_Asm_node_s
{
    struct tag_Asm_node_s *prev_ps;
    struct tag_Asm_node_s *next_ps;
    
    Asm_instr_e asm_instr_e;
    Asm_val instr_arg;
    /*nowe*/
    Asm_val reg_1;
    Asm_val reg_2;

}Asm_node_s;
typedef Asm_node_s *Asm_node_ps;
typedef Asm_node_ps *Asm_node_pps;
typedef Asm_node_s *const Asm_node_cps;
typedef Asm_node_s **const Asm_node_cpps;



#endif /*__ASM_TYPES_H__*/
