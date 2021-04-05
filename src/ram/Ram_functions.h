#ifndef __RAM_FUNCTIONS_H__
#define __RAM_FUNCTIONS_H__

#include "Ram_types.h"
#include "../cplr/Cplr_types.h"


extern Ram_id Ram_Alloc(
    Cplr_info_cps info_cps,
    Cplr_index size
);
extern void Ram_DelList(
    Cplr_info_cps info_cps
);
extern Ram_node_ps Ram_FindByName(
    Ram_node_cps listHead_cps,
    Pid_name_c name_c
);
extern Ram_node_ps Ram_FindByPid(
    Ram_node_cps listHead_cps,
    Pid_node_cps pid_cps
);
extern void Ram_Init(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_alloc_cps,
    Pid_node_cps pid_cps
);
extern void Ram_DelAllAllocInBranch(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_branch_head_cps
);
extern void Ram_CreateRegisters(
    Cplr_info_cps info_cps
);
extern void Ram_DelByPtr(
    Cplr_info_cps info_cps,
    Ram_node_ps ram_to_del_ps
);
/*extern void Ram_AllocArrays(
    Cplr_info_cps info_cps
);*/
extern Ram_id Ram_Adr(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_cps,
    Ct_node_cps ct_node_cps
);
extern Ram_addresses_s Ram_RetAdr(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_cps
);
extern Ram_id Ram_ArraySize(
    Pid_val lower_lim,
    Pid_val upper_lim
);
extern void Ram_DelById(
    Cplr_info_cps info_cps,
    Ram_id ram_to_del
);
extern Ram_id Ram_RetIdOfZero(
    Cplr_info_cps info_cps,
    Pid_node_cps array_ps
);

#endif /*__RAM_FUNCTIONS_H__*/
