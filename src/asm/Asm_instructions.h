#ifndef __ASM_INSTRUCTIONS_H__
#define __ASM_INSTRUCTIONS_H__

#include "Asm_types.h"
#include "../ct/Ct_types.h"
#include "../cplr/Cplr_types.h"


extern void Asm_GET(
    Asm_node_cpps asm_head_cpps
);
extern void Asm_GET_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_PUT(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_PUT_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_LOAD(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_LOAD_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_LOAD_I(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_STORE(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_STORE_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_STORE_I(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_ADD(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_ADD_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SUB(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SUB_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
/*extern void Asm_INC(
    Asm_node_cpps asm_head_cpps
);*/
extern void Asm_DEC(
    Asm_node_cpps asm_head_cpps
);
extern void Asm_DEC_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SHIFT(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JUMP(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JUMP_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JPOS(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JODD_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JZERO(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JZERO_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JNEG(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_HALT(
    Asm_node_cpps asm_head_cpps
);

extern void Asm_INC_nowy(
    Cplr_register_id_c register_id,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_RESET_nowy(
    Cplr_registers_e register_id,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SHL_nowy(
    Cplr_register_id_c register_id,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SHR_nowy(
    Cplr_register_id_c register_id,
    Asm_node_cpps asm_head_cpps
);

/*
extern Asm_node_ps Asm_EQ(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_EQ_0_C(void);
extern Asm_node_ps Asm_EQ_B_0(void);

extern Asm_node_ps Asm_NEQ(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_NEQ_0_C(void);
extern Asm_node_ps Asm_NEQ_B_0(void);

extern Asm_node_ps Asm_GE(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_GE_0_C(void);
extern Asm_node_ps Asm_GE_B_0(void);

extern Asm_node_ps Asm_LE(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_LE_0_C(void);
extern Asm_node_ps Asm_LE_B_0(void);

extern Asm_node_ps Asm_LEQ(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_LEQ_0_C(void);
extern Asm_node_ps Asm_LEQ_B_0(void);

extern Asm_node_ps Asm_GEQ(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_GEQ_0_C(void);
extern Asm_node_ps Asm_GEQ_B_0(void);
*/

#endif /*__ASM_INSTRUCTIONS_H__*/