#ifndef __ASM_FUNCTIONS_H__
#define __ASM_FUNCTIONS_H__

#include "Asm_types.h"
#include "../ct/Ct_types.h"
#include "../cplr/Cplr_types.h"

extern void Asm_DeleteCode(
    Ct_node_ps node_ps
);
/*extern Asm_node_ps Asm_NumberGenerator(
    Cplr_info_cps info_cps,
    Cplr_val number,
    Ct_node_cps ct_node_cps
);*/

extern Asm_node_ps Asm_NumberGenerator_nowy(
    Cplr_info_cps info_cps,
    Cplr_val number,
    Ct_node_cps ct_node_cps,
    const Cplr_registers_e reg_to_use
);

extern void Asm_ASSIGN(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_IF(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ELSE(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ENDIF(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_WHILE(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_DO(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ENDWHILE(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ENDDO(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_FOR(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ENDFOR(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern Asm_node_ps Asm_READ(
    Asm_val D
);
extern void Asm_WRITE(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern Asm_node_ps Asm_PLUS(
    //Asm_val D,
    Asm_val A,
    Asm_val B
);
extern Asm_node_ps Asm_PLUS_nowy(
    Asm_val reg_A,
    Asm_val reg_B
);
extern Asm_node_ps Asm_MINUS(
    Asm_val D,
    Asm_val A,
    Asm_val B
);
extern Asm_node_ps Asm_MINUS_nowy(
    Asm_val reg_A,
    Asm_val reg_B
);
extern Asm_node_ps Asm_TIMES(
    Asm_val pD,
    Asm_val pA,
    Asm_val A,
    Asm_val pB,
    Asm_val B,
    Cplr_info_cps info_cps,
    Ct_node_cps ct_cps
);
extern Asm_node_ps Asm_TIMES_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C,
    Asm_val reg_D
);
extern Asm_node_ps Asm_TIMESWithoutSwapAndOneCheck_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C,
    Asm_val reg_D
);
extern Asm_node_ps Asm_DIV(
    Asm_val D,
    Asm_val A,
    Asm_val B,
    Asm_val pA,
    Asm_val pB
);
extern Asm_node_ps Asm_MOD(
    Asm_val D,
    Asm_val A,
    Asm_val B,
    Asm_val pA,
    Asm_val pB
);
extern Asm_node_ps Asm_MOD_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C,
    Asm_val reg_E,
    Asm_val reg_tA
);
extern Asm_node_ps Asm_GEQ(
    Asm_val B,
    Asm_val C
);

extern Asm_node_ps Asm_GEQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
);


extern Asm_node_ps Asm_LEQ(
    Asm_val B,
    Asm_val C
);

extern Asm_node_ps Asm_LEQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
);

extern Asm_node_ps Asm_LE(
    Asm_val B,
    Asm_val C
);
extern Asm_node_ps Asm_LE_nowy(
    Asm_val reg_A,
    Asm_val reg_B
);
extern Asm_node_ps Asm_GE(
    Asm_val B,
    Asm_val C
);

extern Asm_node_ps Asm_GE_nowy(
    Asm_val reg_A,
    Asm_val reg_B
);

extern Asm_node_ps Asm_EQ(
    Asm_val B,
    Asm_val C
);
extern Asm_node_ps Asm_EQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
);
extern Asm_node_ps Asm_NEQ(
    Asm_val B,
    Asm_val C
);
extern Asm_node_ps Asm_NEQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
);

extern void Asm_AppendCode(
    Asm_node_cpps asm_head_cpps,
    Asm_node_ps asm_code_ps
);
extern void Asm_Print(
    Asm_node_ps asm_ps
);
extern void Asm_PrintList(
    Asm_node_ps asm_head_ps
);
/*nowy extern void Asm_Alloc_1_m1(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps
);*/
extern Asm_node_ps Asm_LastAsmNode(
    Ct_node_ps ct_node_ps
);
extern Asm_index Asm_CodeLen(
    Ct_node_ps ct_from_ps,
    Ct_node_ps ct_to_ps
);
extern Asm_node_ps Asm_FindLastSTOREinList_nowy(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_cps
);
extern Asm_val Asm_NumberOfinstrAfterGiven_nowy(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_cps,
    Asm_node_ps asm_ps
);


#endif /*__ASM_FUNCTIONS_H__*/
