#ifndef __CPLR_FUNCTIONS_H__
#define __CPLR_FUNCTIONS_H__

#include "Cplr_types.h"




/********************************************************************
 * 
 *  -----------------------EXTERN DECLARATIONS-----------------------
 * 
 ********************************************************************/
extern bool Cplr_InSection_End(
    Cplr_info_s const info_cs
);
extern bool Cplr_InSection_Declare(
    Cplr_info_s const info_cs
);
extern bool Cplr_InSection_Begin(
    Cplr_info_s const info_cs
);
extern void Cplr_PrintRam(
    Cplr_info_cps info_cps
);


extern void Cplr_SetCplrState_Declare(
    Cplr_info_cps info_cps
);
extern void Cplr_SetCplrState_Begin(
    Cplr_info_cps info_cps
);
extern void Cplr_SetCplrState_End(
    Cplr_info_cps info_cps
);

extern void Cplr_AddCodeTreeNode(
    Cplr_info_cps cplr_info_cps ,
   Cmd_command_cs command_s
);


extern void Cplr_PrintDecorator(
    Cplr_name title
);
extern void Cplr_PrintPids(
    Cplr_info_cps info_cps
);
extern void Cplr_PrintWholeCt(
    Cplr_info_cps info_cps
);


extern void Cplr_AsmReader(
    Cplr_info_cps info_cps
);
extern void Cplr_AsmReader_nowy(
    Cplr_info_cps info_cps
);

extern void Cplr_TESTWRITE(
    Cplr_info_cps info_cps
);

/*extern void Cplr_AllocArrays(
    Cplr_info_cps info_cps
);*/

extern void Cplr_AllocArrays_nowy(
    Cplr_info_cps info_cps
);

extern void Cplr_CodeGenerator(
    Cplr_info_cps info_cps
);
extern void Cplr_AllocPids(
    Cplr_info_cps info_cps
);

#endif /*__CPLR_FUNCTIONS_H__*/
