#ifndef __CPLR_TYPES_H__
#define __CPLR_TYPES_H__

#include "../basic_types.h"
#include "../ct/Ct_types.h"
#include "../ram/Ram_types.h"


#define INIT_INFO(listHead, regs)\
    {\
        .pid_listHead_cpps = listHead,\
        .last_ct_node_ps = NULL,\
        .ct_head_ps = NULL,\
        .cplr_state_e = CPLR_BEGIN,\
        .current_cmd_s = {},\
        .ram_head_ps = NULL,\
        .pc = VAL_ZERO,\
        .registers_cps = regs\
    }

typedef Cplr_id Cplr_register_id;
typedef const Cplr_register_id Cplr_register_id_c;

typedef enum tag_Cplr_state_e
{
    CPLR_DECLARE,
    CPLR_BEGIN,
    CPLR_END,
}Cplr_state_e;

typedef enum tag_Cplr_registers_e
{
    a='a',
    b='b',
    c='c',
    d='d',
    e='e',
    f='f',
    uninitialized='?'
}Cplr_registers_e;
typedef const Cplr_registers_e Cplr_registers_ce;

typedef struct tag_Cplr_registers_s
{
    Cplr_registers_e reg_a;
    Cplr_registers_e reg_b;
    Cplr_registers_e reg_c;
    Cplr_registers_e reg_d;
    Cplr_registers_e reg_e;
    Cplr_registers_e reg_f;

    Pid_node_s pid_reg_a_s;
    Pid_node_s pid_reg_b_s;
    Pid_node_s pid_reg_c_s;
    Pid_node_s pid_reg_d_s;
    Pid_node_s pid_reg_e_s;
    Pid_node_s pid_reg_f_s;

    bool in_use_reg_a;
    bool in_use_reg_b;
    bool in_use_reg_c;
    bool in_use_reg_d;
    bool in_use_reg_e;
    bool in_use_reg_f;
}Cplr_registers_s;
typedef Cplr_registers_s *const Cplr_registers_cps;


typedef struct tag_Cplr_info_s
{
    Pid_node_cpps pid_listHead_cpps;
    Cplr_state_e cplr_state_e;
    
    Ct_node_ps last_ct_node_ps;
    Ct_node_ps ct_head_ps;
    Cmd_command_s current_cmd_s;

    struct tag_Ram_node_s* ram_head_ps;
    Cplr_registers_cps registers_cps;

    Cplr_val pc;
	FILE* outputFile;
}Cplr_info_s;
typedef Cplr_info_s *const Cplr_info_cps;
typedef Cplr_info_s const *const Cplr_info_cpcs;



typedef struct tag_Cplr_ramids_s
{
    Ram_id id_dest;
    Ram_id id_dest_in;
    Ram_id id_A;
    Ram_id id_A_in;
    Ram_id id_B;
    Ram_id id_B_in;
}Cplr_ramids_s;



#endif /*__CPLR_TYPES_H__*/
