#ifndef __PID_TYPES_H__
#define __PID_TYPES_H__

#include "../basic_types.h"

typedef Cplr_index Pid_index;
typedef Cplr_id Pid_id;
typedef Cplr_val Pid_val;
typedef Cplr_name Pid_name;
typedef Pid_name const Pid_name_c;


typedef enum tag_Pid_varStatus_e
{
    STATUS_INITIALIZED,
    STATUS_UNINITIALIZED,
    STATUS_VALUE_KNOWN,
}Pid_varStatus_e;

typedef struct tag_Pid_arrayElement_s
{
    Pid_val value;
    Pid_varStatus_e status_e;
}Pid_arrayElement_s;

typedef struct tag_Pid_array_data_s
{
    Pid_arrayElement_s *array_a;
    Pid_val lower_lim; // uzywane do tablicy (leftBound:rightBound)
    Pid_val upper_lim;
    Pid_varStatus_e status_e;
    Pid_val memory_address;
}Pid_array_data_s;

typedef enum tag_Pid_type_e
{
    TYPE_VARIABLE,
    TYPE_ARRAY,
    TYPE_NUMBER,
    TYPE_ITERATOR
}Pid_type_e;

typedef enum tag_Pid_declareRes_e
{
    DOUBLE_DECLARATION,
    CORRECT_DECLARATION,
    LOWER_LIM_BIGGER
}Pid_decRes_e;

typedef struct tag_Pid_node_s
{
    struct tag_Pid_node_s *prev_ps;
    struct tag_Pid_node_s *next_ps;

    struct tag_Cplr_cTreeNode_s *iter_declaration_ps;

    Pid_array_data_s array_data_s;

    Pid_val occurrences;
    Pid_name name_p;
    Pid_val value;
    Pid_val ram_address;
    Pid_type_e type_e;
    Pid_varStatus_e status_e;
}Pid_node_s;
typedef Pid_node_s * Pid_node_ps;
typedef Pid_node_ps * Pid_node_pps;
typedef Pid_node_s *const Pid_node_cps;
typedef Pid_node_s **const Pid_node_cpps;


#endif /*__PID_TYPES_H__*/
