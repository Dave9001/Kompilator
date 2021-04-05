#ifndef __CMD_FUNCTIONS_H__
#define __CMD_FUNCTIONS_H__

#include "Cmd_types.h"
#include "../cplr/Cplr_types.h"

extern Cmd_pidAction_e Cmd_AddPid(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c
);
extern Cmd_pidAction_e Cmd_AddPidNotArray_nowy(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c
);
extern Cmd_pidAction_e Cmd_AddPidArray(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c
);
extern Cmd_pidAction_e Cmd_AddPidArray_nowy(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c
);
extern Cmd_pidAction_e Cmd_AddArray(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c,
    Pid_name_c index_name_c
);
extern Cmd_pidAction_e Cmd_AddArray_nowy(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c,
    Pid_name_c index_name_c
);
extern void Cmd_AddType(
    Cplr_info_cps info_cps,
    Cmd_type_ce cmd_type_ce
);
extern void Cmd_AddNumber(
    Cplr_info_cps info_cps,
    Pid_name_c number_name_c
);
extern void Cmd_AddExpr(
    Cplr_info_cps info_cps,
    Cmd_exprType_ce expr_type_ce
);
extern void Cmd_AddCond(
    Cplr_info_cps info_cps,
    Cmd_condType_ce cond_type_ce
);
extern void Cmd_Clear(
    Cplr_info_cps info_cps
);
extern Cmd_command_s Cmd_Clean(void);
extern void Cmd_UpdateLastCt(
    Cplr_info_cps info_cps
);
extern bool Cmd_IsExpressionLike(
    Cmd_type_e type_e
);
extern bool Cmd_UninitializedAssign_nowy(
    Cplr_info_cps info_cps
);
extern bool Cmd_UninitializedCondition_nowy(
    Cplr_info_cps info_cps
);
extern bool Cmd_UninitializedWRITE_nowy(
    Cplr_info_cps info_cps
);
extern void Cmd_InitializedPid_nowy(
    Cplr_info_cps info_cps
);

#endif/*__CMD_FUNCTIONS_H__*/
