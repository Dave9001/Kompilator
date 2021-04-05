#ifndef __RAM_TYPES_H__
#define __RAM_TYPES_H__

#include "../basic_types.h"
#include "../pid/Pid_types.h"
#include "../ct/Ct_types.h"


#define INDEX_ZERO (Cplr_val)0
#define RAM_NUMB_OF_REGISTERS (Cplr_val)8

typedef Cplr_val Ram_id;

typedef enum tag_Ram_type_e
{
    RAM_UNRELATED,
    RAM_NUMBER,
    RAM_PID,
    RAM_ARRAY,
    RAM_REGISTER
}Ram_type_e;

typedef struct tag_Ram_node_s
{
    struct tag_Ram_node_s* next_ps;
    struct tag_Ram_node_s* prev_ps;

    Ct_node_ps ct_branch_head_ps;

    Ram_id id;
    Ram_id array_upper_lim;

    Ram_type_e type_e;
    Pid_node_ps pid_ps;
}Ram_node_s;
typedef Ram_node_s * Ram_node_ps;
typedef Ram_node_s const Ram_node_cs;
typedef Ram_node_s *const Ram_node_cps;
typedef Ram_node_s **const Ram_node_cpps;

typedef struct tag_Ram_addresses_s
{
    Ram_id adr_pid_1;
    Ram_id adr_pid_2;
    Ram_id adr_pid_3;

    Ram_id adr_idx_1;
    Ram_id adr_idx_2;
    Ram_id adr_idx_3;
}Ram_addresses_s;




#endif /*__RAM_TYPES_H__*/
