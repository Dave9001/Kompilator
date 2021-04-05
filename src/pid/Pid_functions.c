#include "Pid_functions.h"
#include "../ram/Ram_functions.h"


/********************************************************************
 * 
 *  ----------------------------DEFINES----------------------------
 * 
 ********************************************************************/


#define INNIT_PID(\
    pid, \
    prev_p, next_p, iter_declaration_ps, array_data_s, \
    name_p, value, type_e, ram_address, status_e\
)\
    do{\
        pid.prev_ps = prev_ps;\
        pid.next_ps = next_ps;\
        pid.iter_declaration_ps = iter_declaration_ps;\
        \
        pid.array_data_s = array_data_s;\
        \
        pid.occurrences = VAL_ZERO;\
        pid.name_p = name_p;\
        pid.value  = value;\
        pid.ram_address = ram_address;\
        pid.type_e   = type_e;\
        pid.status_e = status_e;\
    }while(FALSE)

#define DECLRE_PID_DEFAULT_VARIABLE(\
    pid,\
    name_p\
) \
    do {\
        pid.prev_p = NULL;\
        pid.next_p = NULL;\
        pid.iter_declaration_ps = NULL;\
        \
        pid.array_data_s = {.array_a = NULL};\
        \
        pid.occurrences = VAL_ZERO;\
        pid.name_p = name_p;\
        pid.value  = (Pid_val)0L;\
        pid.ram_address = 0;\
        pid.type_e   = PID_TYPE_VARIABLE;\
        pid.status_e = PID_STATUS_UNINITIALIZED;\
    }while(FALSE)

#define PID_TYPE(pid) (pid->type_e) // deafault pids are stored as pointers
#define PIDSTRUCT_TYPE(pid) (pid.type_e)
#define RAM_ADDRESS(pid) (pid->ram_address)
#define VALUE(pid) (pid->value)
#define ARRAY_RANGE(array_data, low, hi)\
    do{\
        low = array_data.low_lim;\
        hi  = array_data.hight_lim;\
    }while(FALSE)
//#define ARRAY_ADDRESS(array_data) (array_data.memory_address)

#define INIT_ARRAY_DEFAULT()\
    {\
        .array_a = NULL,\
        .lower_lim = VAL_ZERO,\
        .upper_lim = VAL_ZERO,\
        .status_e = STATUS_UNINITIALIZED,\
        .memory_address = VAL_ZERO\
    }

#define INIT_CT_NODE(\
    ct_node,\
    command_s,\
    is_branch_e\
)\


/********************************************************************
 * 
 *  -----------------------EXTERN DECLARATIONS-----------------------
 * 
 ********************************************************************/

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

/********************************************************************
 * 
 *  -----------------------STATIC DECLARATIONS-----------------------
 * 
 ********************************************************************/


static void Pid_InsertAsLast(
    Pid_node_cpps listHead_cpps,
    Pid_node_cps pid_cps
);
static void Pid_InitVariable(
    Pid_node_cps pid_cps,
    Pid_name_c name_c
);
static void Pid_InitNumber(
    Pid_node_cps pid_cps,
    Pid_name_c name_c
);
static void Pid_InitIterator(
    Pid_node_cps pid_cps,
    Pid_name_c name_c
);
static Pid_node_ps Pid_LastNode(
    Cplr_info_cpcs info_cpcs
);


/********************************************************************
 * 
 *  -----------------------EXTERN DEFINITIONS-----------------------
 * 
 ********************************************************************/



extern void Pid_AddToList(
    Pid_node_cpps listHead_cpps,
    Pid_node_s pid_s
)
{
    Pid_node_s *pid_to_add_ps = malloc(sizeof(*pid_to_add_ps));
    if(NULL == pid_to_add_ps)
    {
        ERROR_PRINT("malloc failed");
    }

    Pid_InsertAsLast(listHead_cpps, pid_to_add_ps);

    pid_to_add_ps->iter_declaration_ps = pid_s.iter_declaration_ps;
    pid_to_add_ps->array_data_s = pid_s.array_data_s;

    pid_to_add_ps->occurrences = pid_s.occurrences;
    pid_to_add_ps->name_p      = strdup(pid_s.name_p);
    pid_to_add_ps->value       = pid_s.value;
    pid_to_add_ps->ram_address = pid_s.ram_address;
    pid_to_add_ps->type_e      = pid_s.type_e;
    pid_to_add_ps->status_e    = pid_s.status_e;
}

extern void Pid_DelByPtr(
    Cplr_info_cps info_cps,
    //Pid_node_pps listHead_cpps,
    Pid_node_ps pid_to_del_ps
)
{
    Pid_node_pps listHead_cpps = info_cps->pid_listHead_cpps;

    if(pid_to_del_ps != NULL && *listHead_cpps != NULL)
    {
        if(pid_to_del_ps == *listHead_cpps)
        {
            *listHead_cpps = pid_to_del_ps->next_ps;
        }

        if(pid_to_del_ps->prev_ps != NULL)
        {
            pid_to_del_ps->prev_ps->next_ps = pid_to_del_ps->next_ps;
        }

        if(pid_to_del_ps->next_ps != NULL)
        {
            pid_to_del_ps->next_ps->prev_ps = pid_to_del_ps->prev_ps;
        }

        pid_to_del_ps->prev_ps = NULL;
        pid_to_del_ps->next_ps = NULL;

        if(pid_to_del_ps->type_e == TYPE_ARRAY)
        {
            if(pid_to_del_ps->array_data_s.array_a != NULL)
            {
                free(pid_to_del_ps->array_data_s.array_a);
            }
        }
        else if(pid_to_del_ps->type_e == TYPE_ITERATOR)
        {
            pid_to_del_ps->iter_declaration_ps = NULL;
        }

        Ram_node_cps ram_ps = Ram_FindByPid(info_cps->ram_head_ps, pid_to_del_ps);
        if(NULL != ram_ps)
        {
            ram_ps->pid_ps = NULL;
            Ram_DelByPtr(info_cps, ram_ps);
        }

        free(pid_to_del_ps->name_p);
        free(pid_to_del_ps);
    }
}

extern void Pid_DelByName(
    Cplr_info_cps info_cps,
    //Pid_node_cpps listHead_cpps,
    Pid_name_c name_c
)
{
    Pid_node_cpps listHead_cpps = info_cps->pid_listHead_cpps;

    if(NULL == *listHead_cpps)
    {
        return;
    }
    
    Pid_name current_pid_name;
    Pid_node_s *pid_to_del_ps = *listHead_cpps;
    int namesUnequal = 1;
    while(namesUnequal != 0)
    {
        current_pid_name = pid_to_del_ps->name_p;
        namesUnequal = strcmp(name_c, current_pid_name);

        if(NULL == pid_to_del_ps)
        {
            ERROR_PRINT("Deleting pidentifier failed");
        }

        if(0 != namesUnequal)
        {
            pid_to_del_ps = pid_to_del_ps->next_ps;
        }

        if(NULL == pid_to_del_ps)
        {
            break;
        }
    }

    if(pid_to_del_ps != NULL)
    {
       Pid_DelByPtr(info_cps, pid_to_del_ps);
    }
}

extern Pid_node_ps Pid_FindByName(
    Pid_node_cpps listHead_cpps,
    Pid_name_c name_c
)
{
    if(NULL == listHead_cpps || NULL == name_c)
    {
        return NULL;
    }

    if(NULL == *listHead_cpps)
    {
        return NULL;
    }

    Pid_name current_pid_name;
    Pid_node_s *current_pid_ps = *listHead_cpps;

    current_pid_name = current_pid_ps->name_p;
    int namesUnequal = strcmp(name_c, current_pid_name);
    while(namesUnequal != 0)
    {
        current_pid_ps = current_pid_ps->next_ps;

        if(NULL == current_pid_ps)
        {
            break;
        }

        current_pid_name = current_pid_ps->name_p;
        namesUnequal = strcmp(name_c, current_pid_name);
    }

    return current_pid_ps;
}

extern void Pid_DelList(
    Cplr_info_cps info_cps
)
{
    Pid_node_cpps listHead_cpps = info_cps->pid_listHead_cpps;

    while(*listHead_cpps != NULL)
    {
        Pid_DelByPtr(info_cps, *listHead_cpps);
    }
}

extern Pid_decRes_e Pid_AddToList_Variable(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
)
{    
    Pid_node_cpps pid_head_cpps = info_cps->pid_listHead_cpps;
    Pid_node_ps pid_ps = Pid_FindByName(pid_head_cpps, name_c);

    if(NULL == pid_ps)
    {
        Pid_node_s pid_tmp_s = {};
        Pid_InitVariable(&pid_tmp_s, name_c);
        Pid_AddToList(info_cps->pid_listHead_cpps, pid_tmp_s);
    }
    else
    {
        return DOUBLE_DECLARATION;
    }
    
    return CORRECT_DECLARATION;
}

extern void Pid_AddToList_Number(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
)
{
    Pid_node_cpps pid_head_cpps = info_cps->pid_listHead_cpps;
    Pid_node_ps pid_ps = Pid_FindByName(pid_head_cpps, name_c);

    if(NULL == pid_ps)
    {
        Pid_node_s pid_tmp_s = {};
        Pid_InitNumber(&pid_tmp_s, name_c);
        Pid_AddToList(info_cps->pid_listHead_cpps, pid_tmp_s);
    }
}

extern void Pid_AddToList_Iterator(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
)
{
    Pid_node_s pid_tmp_s = {};
    Pid_InitIterator(&pid_tmp_s, name_c);
    Pid_AddToList(info_cps->pid_listHead_cpps, pid_tmp_s);
}

extern void Pid_AddArray_LowerLim(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
)
{
    Pid_node_ps last_node_ps = Pid_LastNode(info_cps);
    if(NULL == last_node_ps)
    {
        ERROR_PRINT("array not found");
    }

    if(TYPE_ARRAY != last_node_ps->type_e)
    {
        ERROR_PRINT("array not found");
    }

    last_node_ps->array_data_s.lower_lim = atoll(name_c);
}

extern Pid_decRes_e Pid_AddArray_UpperLim(
    Cplr_info_cps info_cps,
    Pid_name_c name_c
)
{
    Pid_node_ps last_node_ps = Pid_LastNode(info_cps);
    if(NULL == last_node_ps)
    {
        ERROR_PRINT("array not found");
    }

    if(TYPE_ARRAY != last_node_ps->type_e)
    {
        ERROR_PRINT("array not found");
    }

    last_node_ps->array_data_s.upper_lim = atoll(name_c);
    Cplr_val upper = last_node_ps->array_data_s.upper_lim;
    Cplr_val lower = last_node_ps->array_data_s.lower_lim;
    if(lower > upper)
    {
        return LOWER_LIM_BIGGER;
    }

    return CORRECT_DECLARATION;
}

extern void Pid_UpdateToArray(
    Cplr_info_cps info_cps
)
{
    Pid_node_ps last_node_ps = Pid_LastNode(info_cps);
    if(NULL == last_node_ps)
    {
        ERROR_PRINT("array not found");
    }

    last_node_ps->type_e = TYPE_ARRAY;
}


/********************************************************************
 * 
 *  -----------------------STATIC DEFINITIONS-----------------------
 * 
 ********************************************************************/


static void Pid_InsertAsLast(
    Pid_node_s ** listHead_cpps,
    Pid_node_cps pid_cps
)
{
    if(NULL == *listHead_cpps)
    {
        pid_cps->prev_ps = NULL;
        pid_cps->next_ps = NULL;
        *listHead_cpps = pid_cps;
    }
    else
    {
        Pid_node_s *tmp_ps = *listHead_cpps;
        while(tmp_ps->next_ps != NULL)
        {
            tmp_ps = tmp_ps->next_ps;
        }

        tmp_ps->next_ps = pid_cps;
        pid_cps->prev_ps = tmp_ps;
        pid_cps->next_ps = NULL;
    }
}

static void Pid_InitVariable(
    Pid_node_cps pid_cps,
    Pid_name_c name_c
)
{
    Pid_array_data_s array_s = INIT_ARRAY_DEFAULT();

    pid_cps->prev_ps = NULL;
    pid_cps->next_ps= NULL;
    pid_cps->iter_declaration_ps = NULL;

    pid_cps->array_data_s = array_s;

    pid_cps->name_p = name_c;
    pid_cps->value  = VAL_ZERO;
    pid_cps->occurrences = VAL_ZERO;
    pid_cps->ram_address = VAL_ZERO;
    pid_cps->type_e   = TYPE_VARIABLE;
    pid_cps->status_e = STATUS_UNINITIALIZED;

}

static void Pid_InitNumber(
    Pid_node_cps pid_cps,
    Pid_name_c name_c
)
{
    Pid_array_data_s array_s = INIT_ARRAY_DEFAULT();

    pid_cps->prev_ps = NULL;
    pid_cps->next_ps= NULL;
    pid_cps->iter_declaration_ps = NULL;

    pid_cps->array_data_s = array_s;

    pid_cps->name_p = name_c;
    pid_cps->occurrences = VAL_ZERO;
    pid_cps->value  = atoll(name_c);
    pid_cps->ram_address = 0;
    pid_cps->type_e   = TYPE_NUMBER;
    pid_cps->status_e = STATUS_UNINITIALIZED;
}

static void Pid_InitIterator(
    Pid_node_cps pid_cps,
    Pid_name_c name_c
)
{
    Pid_array_data_s array_s = INIT_ARRAY_DEFAULT();

    pid_cps->prev_ps = NULL;
    pid_cps->next_ps= NULL;
    pid_cps->iter_declaration_ps = NULL;

    pid_cps->array_data_s = array_s;

    pid_cps->name_p = name_c;
    pid_cps->occurrences = VAL_ZERO;
    pid_cps->value  = (Pid_val)0L;
    pid_cps->ram_address = 0;
    pid_cps->type_e   = TYPE_ITERATOR;
    pid_cps->status_e = STATUS_UNINITIALIZED;
}

static Pid_node_ps Pid_LastNode(
    Cplr_info_cpcs info_cpcs
)
{
    Pid_node_ps tmp_ps = *info_cpcs->pid_listHead_cpps;
    if(NULL == tmp_ps)
    {
        return NULL;
    }

    while(NULL != tmp_ps->next_ps)
    {
        tmp_ps = tmp_ps->next_ps;
    }

    return tmp_ps;
}
