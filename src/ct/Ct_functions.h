#ifndef __CT_FUNCTIONS_H__
#define __CT_FUNCTIONS_H__

#include "Ct_types.h"
#include "../pid/Pid_types.h"
#include "../cplr/Cplr_types.h"


extern void Ct_AddNode(
    Cplr_info_cps cplr_info_cps
);
extern bool Ct_IterNotEmbeded(
    Ct_node_ps last_ct_node_ps,
    Pid_node_ps pid_ps
);
extern bool Ct_IterNotInScope(
    Ct_node_cps last_ct_node_cps,
    Pid_node_ps iter_pid_ps
);
extern void Ct_CalcPidOccurr(
    Cplr_info_cps cplr_info_cps
);
extern Ct_node_ps Ct_Head(
    Cplr_info_cps cplr_info_cps 
);
extern void Ct_DeleteNode(
    Cplr_info_cps cplr_info_cps,
    Ct_node_ps node_ps
);
extern void Ct_LastNodeToNULL(
    Cplr_info_cps cplr_info_cps
);
extern Ct_node_ps Ct_NextNode(
    Ct_node_ps node_ps
);
extern Ct_node_ps Ct_NextCmdNode(
    Ct_node_ps node_ps
);
extern Ct_node_ps Ct_HeadOfBranch(
    Ct_node_cps node_cps
);
extern bool Ct_NodeIsBranch(
    Ct_node_cps node_cps
);
extern bool Ct_NodeIsEndOfBranch(
    Ct_node_cps last_node_cps
);

#endif /*__CT_FUNCTIONS_H__*/
