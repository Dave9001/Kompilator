#ifndef __PID_FUNCTIONS_H__
#define __PID_FUNCTIONS_H__

#include "Pid_types.h"
#include "../cplr/Cplr_types.h"

extern void Pid_AddToList(
    Pid_node_cpps listHead_cpps,
    Pid_node_s pid_s
);
extern void Pid_DelByPtr(
    Cplr_info_cps info_cps,
    //Pid_node_pps listHead_cpps,
    Pid_node_ps pid_to_del_ps
);
extern void Pid_DelByName(
    Cplr_info_cps info_cps,
    //Pid_node_cpps listHead_cpps,
    Pid_name_c name_c
);
extern Pid_node_ps Pid_FindByName(
    Pid_node_cpps listHead_cpps,
    Pid_name_c name_c
);
extern void Pid_DelList(
    Cplr_info_cps info_cps
);
extern Pid_decRes_e Pid_AddToList_Variable(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
);
extern void Pid_AddToList_Number(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
);
extern void Pid_AddToList_Iterator(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
);
extern void Pid_AddArray_LowerLim(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
);
extern Pid_decRes_e Pid_AddArray_UpperLim(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
);
extern void Pid_UpdateToArray(
    Cplr_info_cps info_cps
);




#endif /*__PID_FUNCTIONS_H__*/
