#include "Ram_functions.h"
#include "../ct/Ct_functions.h"







/********************************************************************
 * 
 *  ----------------------------DEFINES----------------------------
 * 
 ********************************************************************/



/********************************************************************
 * 
 *  -----------------------EXTERN DECLARATIONS-----------------------
 * 
 ********************************************************************/


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
extern void Ram_AllocArrays(
    Cplr_info_cps info_cps
);
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

/********************************************************************
 * 
 *  -----------------------STATIC DECLARATIONS-----------------------
 * 
 ********************************************************************/


static void Ram_Insert(
    Cplr_info_cps info_cps,
    Ram_node_ps ram_node_ps
);
static Ram_id Ram_AllocId(
    Ram_node_ps added_node_ps
);
static Ram_node_ps Ram_Last(
    Cplr_info_cps info_cps
);


/********************************************************************
 * 
 *  -----------------------EXTERN DEFINITIONS-----------------------
 * 
 ********************************************************************/

extern Ram_id Ram_Alloc(
    Cplr_info_cps info_cps,
    Cplr_index size
)
{
    Ram_node_ps node_to_add_ps = malloc(sizeof(*node_to_add_ps));
    if(NULL == node_to_add_ps)
    {
        ERROR_PRINT("malloc failed");
    }

    Ram_Insert(info_cps, node_to_add_ps);

    Ram_id id = Ram_AllocId(node_to_add_ps);
    Ram_id up_lim = id;
    if(1 < size)
    {
        up_lim = id + size - 1;
    }

    node_to_add_ps->id = id;
    node_to_add_ps->array_upper_lim = up_lim;

    node_to_add_ps->type_e = RAM_UNRELATED;
    node_to_add_ps->pid_ps = NULL;
    node_to_add_ps->ct_branch_head_ps = NULL;

    return id;
}

extern Ram_node_ps Ram_FindByPid(
    Ram_node_cps listHead_cps,
    Pid_node_cps pid_cps
)
{
    if(NULL == listHead_cps || NULL == pid_cps)
    {
        return NULL;
    }

    Ram_node_ps ram_ps = listHead_cps;
    Pid_node_ps curent_pid_ps = ram_ps->pid_ps;
    while(pid_cps != curent_pid_ps)
    {
        ram_ps = ram_ps->next_ps;
        
        if(NULL == ram_ps)
        {
            break;
        }

        curent_pid_ps = ram_ps->pid_ps;
    }

    return ram_ps;
}

extern Ram_node_ps Ram_FindByName(
    Ram_node_cps listHead_cps,
    Pid_name_c name_c
)
{
    if(NULL == listHead_cps || NULL == name_c)
    {
        return NULL;
    }

    Ram_node_ps ret_ps = NULL;
    Ram_node_ps ram_ps = listHead_cps;
    int namesUnequal = 1;
    if(NULL != ram_ps->pid_ps)
    {
        namesUnequal = strcmp(name_c, ram_ps->pid_ps->name_p);
        if(0 == namesUnequal)
        {
            ret_ps = ram_ps;
            return ret_ps;
        }
    }

    while(namesUnequal != 0)
    {
        ram_ps = ram_ps->next_ps;
        
        if(NULL == ram_ps)
        {
            break;
        }

        if(NULL != ram_ps->pid_ps)
        {
            namesUnequal = strcmp(name_c, ram_ps->pid_ps->name_p);
            if(0 == namesUnequal)
            {
                ret_ps = ram_ps;
                break;
            }
        }
    }

    return ret_ps;
}

extern void Ram_DelList(
    Cplr_info_cps info_cps
)
{
    Ram_node_ps listHead_ps = info_cps->ram_head_ps;

    while(info_cps->ram_head_ps != NULL)
    {
        listHead_ps = info_cps->ram_head_ps;
        Ram_DelByPtr(info_cps, listHead_ps);
    }
}

extern void Ram_Init(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_alloc_cps,
    Pid_node_cps pid_cps
)
{
    Ram_node_ps ram_ps = Ram_Last(info_cps);

    if(NULL == ram_ps)
    {
        ERROR_PRINT("Init of null ram");
    }
    
    Ram_type_e type_e = RAM_UNRELATED;
    if(NULL != pid_cps)
    {
        switch(pid_cps->type_e)
        {
            case TYPE_ARRAY:    type_e = RAM_ARRAY;   break;
            case TYPE_NUMBER:   type_e = RAM_NUMBER;  break;
            case TYPE_VARIABLE: type_e = RAM_PID;     break;
            case TYPE_ITERATOR: type_e = RAM_PID;     break;
        
            default: ERROR_PRINT("Unknown type of pid"); break;    
        }
        pid_cps->ram_address = ram_ps->id;
    }
    else if(RAM_NUMB_OF_REGISTERS > ram_ps->id)
    {
        type_e = RAM_REGISTER;
    }
    ram_ps->type_e = type_e;
    ram_ps->pid_ps = pid_cps;
    ram_ps->ct_branch_head_ps = Ct_HeadOfBranch(ct_node_alloc_cps);
}

extern void Ram_DelAllAllocInBranch(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_branch_head_cps
)
{
    Ram_node_ps ram_node_ps = info_cps->ram_head_ps;
    Ram_node_ps tmp_ram_ps = info_cps->ram_head_ps;
    while(ram_node_ps != NULL)
    {
        tmp_ram_ps = ram_node_ps->next_ps;
        if(ct_branch_head_cps == ram_node_ps->ct_branch_head_ps)
        {
            Ram_DelByPtr(info_cps, ram_node_ps);
        }
        
        ram_node_ps = tmp_ram_ps;
    }
}


extern void Ram_CreateRegisters(
    Cplr_info_cps info_cps
)
{
    if(NULL != info_cps->ram_head_ps)
    {
        ERROR_PRINT("Ram already have registers");
    }

    Cplr_index i = 0;
    while(i < RAM_NUMB_OF_REGISTERS)
    {
        (void)Ram_Alloc(info_cps, 1);
        Ram_Init(info_cps, NULL, NULL);
        i++;
    }
}

extern void Ram_DelByPtr(
    Cplr_info_cps info_cps,
    Ram_node_ps ram_to_del_ps
)
{
    Ram_node_ps listHead_ps = info_cps->ram_head_ps;

    if(ram_to_del_ps != NULL && listHead_ps != NULL)
    {
        if(ram_to_del_ps == listHead_ps)
        {
            info_cps->ram_head_ps = ram_to_del_ps->next_ps;
        }

        if(ram_to_del_ps->prev_ps != NULL)
        {
            ram_to_del_ps->prev_ps->next_ps = ram_to_del_ps->next_ps;
        }

        if(ram_to_del_ps->next_ps != NULL)
        {
            ram_to_del_ps->next_ps->prev_ps = ram_to_del_ps->prev_ps;
        }

        ram_to_del_ps->prev_ps = NULL;
        ram_to_del_ps->next_ps = NULL;

        free(ram_to_del_ps);
    }
}



extern Ram_addresses_s Ram_RetAdr(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_cps
)
{
    Ram_id id_1 = -1;
    Ram_id id_2 = -1;
    Ram_id id_3 = -1;
    Ram_id id_1_idx = -1;
    Ram_id id_2_idx = -1;
    Ram_id id_3_idx = -1;
    Cmd_command_s cmd_s = ct_node_cps->command_s;
    if(NULL != cmd_s.pid_1_ps)
    {
        id_1 = Ram_Adr(info_cps, cmd_s.pid_1_ps, ct_node_cps);
    }

    if(NULL != cmd_s.pid_2_ps)
    {
        id_2 = Ram_Adr(info_cps, cmd_s.pid_2_ps, ct_node_cps);
    }

    if(NULL != cmd_s.pid_3_ps)
    {
        id_3 = Ram_Adr(info_cps, cmd_s.pid_3_ps, ct_node_cps);
    }

    if(NULL != cmd_s.index_1_ps)
    {
        //if(VAL_ZERO != cmd_s.index_1_ps->value)
        //{
            id_1_idx = Ram_Adr(info_cps, cmd_s.index_1_ps, ct_node_cps);
        //}
    }

    if(NULL != cmd_s.index_2_ps)
    {
        // if(VAL_ZERO != cmd_s.index_2_ps->value)
        // {
            id_2_idx = Ram_Adr(info_cps, cmd_s.index_2_ps, ct_node_cps);
        //}
    }

    if(NULL != cmd_s.index_3_ps)
    {
        //if(VAL_ZERO != cmd_s.index_3_ps->value)
        //{
            id_3_idx = Ram_Adr(info_cps, cmd_s.index_3_ps, ct_node_cps);
        //}
    }
    
    Ram_addresses_s adr_s = {
                            .adr_pid_1 = id_1,
                            .adr_pid_2 = id_2,
                            .adr_pid_3 = id_3,

                            .adr_idx_1 = id_1_idx,
                            .adr_idx_2 = id_2_idx,
                            .adr_idx_3 = id_3_idx
                        };

    return adr_s;
}

extern Ram_id Ram_Adr(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_cps,
    Ct_node_cps ct_node_cps
)
{
    if(NULL == pid_cps)
    {
        ERROR_PRINT("Ram for null pid");
    }

    Ram_id ram_id = 0;
    Ram_node_ps ram_node_ps = Ram_FindByPid(info_cps->ram_head_ps, pid_cps);
    if(NULL == ram_node_ps)
    {
        ram_id = Ram_Alloc(info_cps, 1);
        Ram_Init(info_cps, ct_node_cps, pid_cps);
    }
    else
    {
        if(TYPE_ARRAY == pid_cps->type_e)
        {
            ram_id = pid_cps->array_data_s.memory_address;
        }
        else
        {
            ram_id = ram_node_ps->id;
        }
    }
    
    return ram_id;
}

extern Ram_id Ram_ArraySize(
    Pid_val lower_lim,
    Pid_val upper_lim
)
{
    if(upper_lim < lower_lim)
    {
        ERROR_PRINT("Array 2nd length index cant be lower than the first");
    }

    Ram_id size = (Ram_id)0;

    if(0 == lower_lim && 0 == upper_lim)
    {   /*nowy*/
        //ERROR_PRINT("Array cant be(0:0)");
        size = 1;
    }
    else
    {
        size = upper_lim - lower_lim + 1;
    }
    
    return size;
}


extern void Ram_DelById(
    Cplr_info_cps info_cps,
    Ram_id ram_to_del
)
{
    Ram_node_ps ram_ps = info_cps->ram_head_ps;
    while(NULL != ram_ps)
    {
        if(ram_to_del == ram_ps->id)
        {
            Ram_DelByPtr(info_cps, ram_ps);
            break;
        }
        ram_ps = ram_ps->next_ps;
    }
}


extern Ram_id Ram_RetIdOfZero(
    Cplr_info_cps info_cps,
    Pid_node_cps array_ps
)
{
    Ram_id id_of_zero_element = array_ps->array_data_s.memory_address;
    Ram_node_ps ram_tmp_ps = info_cps->ram_head_ps;
    while(NULL != ram_tmp_ps)
    {
        if(id_of_zero_element == ram_tmp_ps->id)
        {
            break;
        }
        ram_tmp_ps = ram_tmp_ps->next_ps;
    }

    if(NULL == ram_tmp_ps)
    {
        ERROR_PRINT("zero element holder not found in ram");
    }

    return ram_tmp_ps->pid_ps->value;
}



/********************************************************************
 * 
 *  -----------------------STATIC DEFINITIONS-----------------------
 * 
 ********************************************************************/


static void Ram_Insert(
    Cplr_info_cps info_cps,
    Ram_node_ps ram_node_ps
)
{

    if(NULL == info_cps->ram_head_ps)
    {
        ram_node_ps->prev_ps = NULL;
        ram_node_ps->next_ps = NULL;
        info_cps->ram_head_ps = ram_node_ps;
    }
    else
    {
        Ram_node_ps tmp_ps = info_cps->ram_head_ps;
        while(tmp_ps->next_ps != NULL)
        {
            tmp_ps = tmp_ps->next_ps;
        }

        tmp_ps->next_ps = ram_node_ps;
        ram_node_ps->prev_ps = tmp_ps;
        ram_node_ps->next_ps = NULL;
    }
}

static Ram_id Ram_AllocId(
    Ram_node_ps added_node_ps
)
{
    if(NULL == added_node_ps)
    {
        ERROR_PRINT("Searching for ram in empty heap");
    }

    Ram_id id = (Ram_id)-1;
    Ram_node_ps prev_node_ps = added_node_ps;
    
    prev_node_ps = added_node_ps->prev_ps;
    if(NULL != prev_node_ps)
    {
        id = prev_node_ps->array_upper_lim + 1;
    }
    else
    {
        id = INDEX_ZERO;//RAM_NUMB_OF_REGISTERS;
    }
    
    return id;
}


static Ram_node_ps Ram_Last(
    Cplr_info_cps info_cps
)
{
    Ram_node_ps ram_ps = info_cps->ram_head_ps;
    while(ram_ps->next_ps != NULL)
    {
        ram_ps = ram_ps->next_ps;
    }

    return ram_ps;
}

