#include "Cmd_functions.h"
#include "../pid/Pid_functions.h"
#include "../ct/Ct_functions.h"


/********************************************************************
 * 
 *  ----------------------------DEFINES------------------------------
 * 
 ********************************************************************/


/********************************************************************
 * 
 *  -----------------------EXTERN DECLARATIONS-----------------------
 * 
 ********************************************************************/


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
extern bool Cmd_UninitializedWRITE_nowy(
    Cplr_info_cps info_cps
);
extern bool Cmd_UninitializedCondition_nowy(
    Cplr_info_cps info_cps
);
extern void Cmd_InitializedPid_nowy(
    Cplr_info_cps info_cps
);

/********************************************************************
 * 
 *  -----------------------STATIC DECLARATIONS-----------------------
 * 
 ********************************************************************/


static void Cmd_InsertPid(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_cps
);
/*static bool Cmd_PidIsLoopIter(
    Pid_node_cps pid_cps
);*/
static bool Cmd_PidAssigningToCorrect(
    Cmd_command_cs current_cmd_cs,
    Pid_node_cps pid_cps
);
static bool Cmd_PidShouldBeIter(
    Cplr_info_cps info_cps
);
static Cmd_pidAction_e Cmd_AddIter(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c,
    Pid_node_ps pid_ps
);
static Cplr_index Cmd_LastPid(
    Cmd_command_cs command_cs
);
static bool Cmd_IsPidArray(
    Pid_node_cps pid_cps
);
static bool Cmd_PidArrayDontHaveIndex(
    Cmd_command_cs command_cs,
    Cplr_index last_pid_id
);
static void Cmd_InsertPidIndexOfArray(
    Cplr_info_cps info_cps,
    Cplr_index last_pid_id,
    Pid_node_cps pid_cps
);
static bool Cmd_IterInWrongPosition(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_to_add_cps
);
static bool Cmd_IterSelfIncluded(
    Cmd_command_cs command_cs,
    Pid_node_cps pid_to_add_cps
);
static bool Cmd_IsFor(
    Cmd_command_cs command_cs
);
static bool Cmd_IterNotInOwnScope(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_to_add_cps
);
static bool Cmd_IsArray_nowy(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_to_add_cps
);

/********************************************************************
 * 
 *  -----------------------EXTERN DEFINITIONS-----------------------
 * 
 ********************************************************************/


/*
static bool Cmd_IterNotInMyScope(
    Cplr_info_cps info_cps,
    Pid_node_ps pid_ps
)
{
    if(NULL == pid_ps)
    {
        ERROR_PRINT("pid jest null");
    }

    if(Ct_IterNotInScope(info_cps->last_ct_node_ps, pid_ps))
    {
        ;
    }
    


    return true;
}*/



static Cmd_pidAction_e Cmd_AddIter(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c,
    Pid_node_ps pid_ps
)
{
    Pid_node_cpps listHead_cpps = info_cps->pid_listHead_cpps;
    Ct_node_cps last_ct_node_cps = info_cps->last_ct_node_ps;
    if(NULL == pid_ps)
    {
        Pid_AddToList_Iterator(info_cps, pid_name_c);
        pid_ps = Pid_FindByName(listHead_cpps, pid_name_c);

        Cmd_InsertPid(info_cps, pid_ps);
    }
    else
    {
        if(TYPE_ITERATOR != pid_ps->type_e)
        {
            return ITERATOR_FAIL;
        }
        else if(Ct_IterNotEmbeded(last_ct_node_cps, pid_ps))
        {
            Cmd_InsertPid(info_cps, pid_ps);
            return CORRECTPID;
        }
        else
        {
            return ITERATOR_FAIL;
        }
    }
    
    return CORRECTPID;
}

extern Cmd_pidAction_e Cmd_AddPidNotArray_nowy(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c
)
{
    Pid_node_cpps listHead_cpps = info_cps->pid_listHead_cpps;
    Pid_node_ps pid_ps = Pid_FindByName(listHead_cpps, pid_name_c);

    Cmd_command_cs current_cmd_cs = info_cps->current_cmd_s;

    if(Cmd_PidShouldBeIter(info_cps))
    {
        return Cmd_AddIter(info_cps, pid_name_c, pid_ps);
    }
    else if(Cmd_IterInWrongPosition(info_cps, pid_ps))
    {
        return ITERATOR_FAIL;
    }
    else if(NULL == pid_ps)
    {
        return INVALIDPID;
    }
    else if(!Cmd_PidAssigningToCorrect(current_cmd_cs, pid_ps))
    {
        return INVALIDPID;
    }
    else if(Cmd_IsArray_nowy(info_cps, pid_ps))
    {
        return INVALIDPID;
    }

    Cmd_InsertPid(info_cps, pid_ps);

    return CORRECTPID;
}


extern Cmd_pidAction_e Cmd_AddPid(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c
)
{
    Pid_node_cpps listHead_cpps = info_cps->pid_listHead_cpps;
    Pid_node_ps pid_ps = Pid_FindByName(listHead_cpps, pid_name_c);

    Cmd_command_cs current_cmd_cs = info_cps->current_cmd_s;

    if(Cmd_PidShouldBeIter(info_cps))
    {
        return Cmd_AddIter(info_cps, pid_name_c, pid_ps);
    }
    else if(Cmd_IterInWrongPosition(info_cps, pid_ps))
    {
        return ITERATOR_FAIL;
    }
    else if(NULL == pid_ps)
    {
        return INVALIDPID;
    }
    else if(!Cmd_PidAssigningToCorrect(current_cmd_cs, pid_ps))
    {
        return INVALIDPID;
    }
    //else if(Cmd_IsArray_nowy(info_cps, pid_ps))
    //{
    //    return INVALIDPID;
    //}

    Cmd_InsertPid(info_cps, pid_ps);

    return CORRECTPID;
}

extern Cmd_pidAction_e Cmd_AddPidArray(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c
)
{
    Pid_node_cpps listHead_cpps = info_cps->pid_listHead_cpps;
    Pid_node_ps pid_ps = Pid_FindByName(listHead_cpps, pid_name_c);

    Cmd_command_cs current_cmd_cs = info_cps->current_cmd_s;

    if(Cmd_PidShouldBeIter(info_cps))
    {
        return Cmd_AddIter(info_cps, pid_name_c, pid_ps);
    }
    else if(Cmd_IterInWrongPosition(info_cps, pid_ps))
    {
        return ITERATOR_FAIL;
    }
    else if(NULL == pid_ps)
    {
        return INVALIDPID;
    }
    else if(!Cmd_PidAssigningToCorrect(current_cmd_cs, pid_ps))
    {
        return INVALIDPID;
    }

    Cmd_InsertPid(info_cps, pid_ps);

    return CORRECTPID;
}


extern Cmd_pidAction_e Cmd_AddPidArray_nowy(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c
)
{
    Pid_node_cpps listHead_cpps = info_cps->pid_listHead_cpps;
    Pid_node_ps pid_ps = Pid_FindByName(listHead_cpps, pid_name_c);

    Cmd_command_cs current_cmd_cs = info_cps->current_cmd_s;

    if(Cmd_PidShouldBeIter(info_cps))
    {
        return Cmd_AddIter(info_cps, pid_name_c, pid_ps);
    }
    else if(Cmd_IterInWrongPosition(info_cps, pid_ps))
    {
        return ITERATOR_FAIL;
    }
    else if(NULL == pid_ps)
    {
        return INVALIDPID;
    }
    else if(!Cmd_PidAssigningToCorrect(current_cmd_cs, pid_ps))
    {
        return INVALIDPID;
    }
    else if(TYPE_ARRAY != pid_ps->type_e)
    {
        return VARIABLE_MISSUSAGE;
    }

    Cmd_InsertPid(info_cps, pid_ps);

    return CORRECTPID;
}




extern Cmd_pidAction_e Cmd_AddArray(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c,
    Pid_name_c index_name_c
)
{
    Cmd_pidAction_e cmd_pid_action_e = CORRECTPID;
    
    cmd_pid_action_e = Cmd_AddPid(info_cps, pid_name_c);
    if( INVALIDPID == cmd_pid_action_e ||
        ITERATOR_FAIL == cmd_pid_action_e
    )
    {
        return cmd_pid_action_e;
    }

    cmd_pid_action_e = Cmd_AddPid(info_cps, index_name_c);

    return cmd_pid_action_e;
}

extern Cmd_pidAction_e Cmd_AddArray_nowy(
    Cplr_info_cps info_cps,
    Pid_name_c pid_name_c,
    Pid_name_c index_name_c
)
{
    Cmd_pidAction_e cmd_pid_action_e = CORRECTPID;
    
    cmd_pid_action_e = Cmd_AddPidArray_nowy(info_cps, pid_name_c);
    if( INVALIDPID == cmd_pid_action_e ||
        ITERATOR_FAIL == cmd_pid_action_e ||
        VARIABLE_MISSUSAGE == cmd_pid_action_e
    )
    {
        return cmd_pid_action_e;
    }

    cmd_pid_action_e = Cmd_AddPid(info_cps, index_name_c);

    return cmd_pid_action_e;
    

    return cmd_pid_action_e;
}

extern void Cmd_AddType(
    Cplr_info_cps info_cps,
    Cmd_type_ce cmd_type_ce
)
{
    info_cps->current_cmd_s.type_e = cmd_type_ce;
}

extern void Cmd_AddNumber(
    Cplr_info_cps info_cps,
    Pid_name_c number_name_c
)
{
    Pid_node_cpps listHead_cpps = info_cps->pid_listHead_cpps;
    Pid_node_ps pid_ps = Pid_FindByName(listHead_cpps, number_name_c);

    if(NULL == pid_ps)
    {
        Pid_AddToList_Number(info_cps, number_name_c);
        /*TODO CREATE Pid_AddToList_Number */
        pid_ps = Pid_FindByName(listHead_cpps, number_name_c);
    }
    Cmd_InsertPid(info_cps, pid_ps);
}

extern void Cmd_AddExpr(
    Cplr_info_cps info_cps,
    Cmd_exprType_ce expr_type_ce
)
{
    info_cps->current_cmd_s.expression_e = expr_type_ce;
}

extern void Cmd_AddCond(
    Cplr_info_cps info_cps,
    Cmd_condType_ce cond_type_ce
)
{
    info_cps->current_cmd_s.condition_e = cond_type_ce;
}

extern void Cmd_UpdateLastCt(
    Cplr_info_cps info_cps
)
{
    if(NULL == info_cps->last_ct_node_ps)
    {
        return;
    }
    info_cps->last_ct_node_ps->command_s = info_cps->current_cmd_s;
}
extern void Cmd_Clear(
    Cplr_info_cps info_cps
)
{

    info_cps->current_cmd_s = Cmd_Clean();
}


extern bool Cmd_UninitializedCondition_nowy(
    Cplr_info_cps info_cps
)
{
    Cmd_command_s cmd_s = info_cps->current_cmd_s;

    if(TYPE_ARRAY == cmd_s.pid_1_ps->type_e)
    {
        if(TYPE_VARIABLE == cmd_s.index_1_ps->type_e)
        {
            if(STATUS_INITIALIZED != cmd_s.index_1_ps->status_e)
            {
                return TRUE;
            }
        }
    }
    else if(TYPE_VARIABLE == cmd_s.pid_1_ps->type_e)
    {
        if(STATUS_INITIALIZED != cmd_s.pid_1_ps->status_e)
        {
            return TRUE;
        }
    }

    if(TYPE_ARRAY == cmd_s.pid_2_ps->type_e)
    {
        if(TYPE_VARIABLE == cmd_s.index_2_ps->type_e)
        {
            if(STATUS_INITIALIZED != cmd_s.index_2_ps->status_e)
            {
                return TRUE;
            }
        }
    }
    else if(TYPE_VARIABLE == cmd_s.pid_2_ps->type_e)
    {
        if(STATUS_INITIALIZED != cmd_s.pid_2_ps->status_e)
        {
            return TRUE;
        }
    }
   
    return FALSE;
}


extern bool Cmd_UninitializedAssign_nowy(
    Cplr_info_cps info_cps
)
{
    Cmd_command_s cmd_s = info_cps->current_cmd_s;

    if(TYPE_ARRAY == cmd_s.pid_1_ps->type_e)
    {
        if(TYPE_VARIABLE == cmd_s.index_1_ps->type_e)
        {
            if(STATUS_INITIALIZED != cmd_s.index_1_ps->status_e)
            {
                return TRUE;
            }
        }
    }
    
    /*if(NULL != cmd_s.pid_2_ps)
    {*/
        if(TYPE_VARIABLE == cmd_s.pid_2_ps->type_e)
        {
            if(STATUS_INITIALIZED != cmd_s.pid_2_ps->status_e)
            {
                return TRUE;
            }
        }
        else if(TYPE_ARRAY == cmd_s.pid_2_ps->type_e)
        {
            if(TYPE_VARIABLE == cmd_s.index_2_ps->type_e)
            {
                if(STATUS_INITIALIZED != cmd_s.index_2_ps->status_e)
                {
                    return TRUE;
                }
            }
        }
    /*}
    else
    {
        if(TYPE_VARIABLE == cmd_s.pid_1_ps->type_e)
        {
            if(STATUS_INITIALIZED != cmd_s.pid_1_ps->status_e)
            {
                return TRUE;
            }
        }
    }*/
    

    if(NULL != cmd_s.pid_3_ps)
    {
        if(TYPE_VARIABLE == cmd_s.pid_3_ps->type_e)
        {
            if(STATUS_INITIALIZED != cmd_s.pid_3_ps->status_e)
            {
                return TRUE;
            }
        }
        else if(TYPE_ARRAY == cmd_s.pid_3_ps->type_e)
        {
            if(TYPE_VARIABLE == cmd_s.index_3_ps->type_e)
            {
                if(STATUS_INITIALIZED != cmd_s.index_3_ps->status_e)
                {
                    return TRUE;
                }
            }
        }

    }
    
    return FALSE;
}

extern bool Cmd_UninitializedWRITE_nowy(
    Cplr_info_cps info_cps
)
{
    Cmd_command_s cmd_s = info_cps->current_cmd_s;

    if(TYPE_VARIABLE == cmd_s.pid_1_ps->type_e)
    {
        if(STATUS_INITIALIZED != cmd_s.pid_1_ps->status_e)
        {
            return TRUE;
        }
    }
    else if(TYPE_ARRAY == cmd_s.pid_1_ps->type_e)
    {
        if(TYPE_VARIABLE == cmd_s.index_1_ps->type_e)
        {
            if(STATUS_INITIALIZED != cmd_s.index_1_ps->status_e)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}


extern void Cmd_InitializedPid_nowy(
    Cplr_info_cps info_cps
)
{
    info_cps->current_cmd_s.pid_1_ps->status_e = STATUS_INITIALIZED;
}




extern Cmd_command_s Cmd_Clean(void)
{
    Cmd_command_s cmd = {
        .pid_1_ps = NULL,
        .pid_2_ps = NULL,
        .pid_3_ps = NULL,
        .index_1_ps = NULL,
        .index_2_ps = NULL,
        .index_3_ps = NULL,
        .type_e = CMD_EMPTY,
        .condition_e = COND_NOTAPPLICABLE,
        .expression_e = EXPR_NOTAPPLICABLE
    };
    return cmd;
}

extern bool Cmd_IsExpressionLike(
    Cmd_type_e type_e
)
{
    if( CMD_EMPTY != type_e &&
        CMD_END != type_e
    )
    {
        return TRUE;
    }

    return FALSE;
}

/********************************************************************
 * 
 *  -----------------------STATIC DEFINITIONS-----------------------
 * 
 ********************************************************************/


static void Cmd_InsertPid(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_cps
)
{
    Cmd_command_cs command_cs = info_cps->current_cmd_s;
    Cplr_index last_pid_id = Cmd_LastPid(command_cs);
    Pid_node_ps last_pid_node_ps = NULL;
    switch(last_pid_id)
    {
        case 0: last_pid_node_ps = NULL; break;
        case 1: last_pid_node_ps = command_cs.pid_1_ps; break;
        case 2: last_pid_node_ps = command_cs.pid_2_ps; break;
        case 3: last_pid_node_ps = command_cs.pid_3_ps; break;

        default: ERROR_PRINT("wrong number of pids in cmd"); break;
    }

    if( Cmd_IsPidArray(last_pid_node_ps) &&
        Cmd_PidArrayDontHaveIndex(command_cs, last_pid_id)
    )
    {
        Cmd_InsertPidIndexOfArray(info_cps, last_pid_id, pid_cps);
    }
    else
    {
        switch(last_pid_id)
        {
            case 0: info_cps->current_cmd_s.pid_1_ps = pid_cps; break;
            case 1: info_cps->current_cmd_s.pid_2_ps = pid_cps; break;
            case 2: info_cps->current_cmd_s.pid_3_ps = pid_cps; break;

            default: ERROR_PRINT("wrong number of pids in cmd"); break;
        }
    }
}

/*static bool Cmd_PidIsLoopIter(
    Pid_node_cps pid_cps
)
{
    if(NULL == pid_cps)
    {
       return FALSE;
    }

    if(TYPE_ITERATOR ==  pid_cps->type_e)
    {
        return TRUE;
    }

    return FALSE;
}*/

static bool Cmd_PidAssigningToCorrect(
    Cmd_command_cs current_cmd_cs,
    Pid_node_cps pid_cps
)
{
    if(CMD_ASSIGN == current_cmd_cs.type_e)
    {
        if(NULL == pid_cps)
        {
            return FALSE;
        }

        if(NULL == current_cmd_cs.pid_1_ps)
        {
            if( pid_cps->type_e != TYPE_VARIABLE &&
                pid_cps->type_e != TYPE_ARRAY
            )
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}

static bool Cmd_PidShouldBeIter(
    Cplr_info_cps info_cps
)
{
    Cmd_command_cs cmd_cs = info_cps->current_cmd_s;

    if(cmd_cs.type_e == CMD_FOR ||
       cmd_cs.type_e == CMD_FOR_DOWNTO)
    {
        if(NULL == cmd_cs.pid_1_ps)
        {
            return TRUE;
        }
    }

    return FALSE;
}

static Cplr_index Cmd_LastPid(
    Cmd_command_cs command_cs
)
{
    Cplr_index id_of_last_pid = (Cplr_index)0;

    if(NULL == command_cs.pid_1_ps)
    {
        id_of_last_pid = (Cplr_index)0;
    }
    else if(NULL == command_cs.pid_2_ps)
    {
        id_of_last_pid = (Cplr_index)1;
    }
    else if(NULL == command_cs.pid_3_ps)
    {
        id_of_last_pid = (Cplr_index)2;
    }
    else
    {
        id_of_last_pid = (Cplr_index)3;
    }

    return id_of_last_pid;
}

static bool Cmd_IsPidArray(
    Pid_node_cps pid_cps
)
{
    if(NULL != pid_cps)
    {
        if(TYPE_ARRAY == pid_cps->type_e)
        {
            return TRUE;
        }
    }

    return FALSE;
}

static bool Cmd_PidArrayDontHaveIndex(
    Cmd_command_cs command_cs,
    Cplr_index last_pid_id
)
{
    bool ret = FALSE;
    switch(last_pid_id)
    {
        case 0: ret = TRUE; break;

        case 1: if(NULL == command_cs.index_1_ps)
                {
                    ret = TRUE;
                }
            break;

        case 2: if(NULL == command_cs.index_2_ps)
                {
                    ret = TRUE;
                }
            break;

        case 3: if(NULL == command_cs.index_3_ps)
                {
                    ret = TRUE;
                }
            break;

        default: ERROR_PRINT("To many pids in cmd"); break;
    }

    return ret;
}

static void Cmd_InsertPidIndexOfArray(
    Cplr_info_cps info_cps,
    Cplr_index last_pid_id,
    Pid_node_cps pid_cps
)
{
    switch(last_pid_id)
    {
        case 1: info_cps->current_cmd_s.index_1_ps = pid_cps; break;
        case 2: info_cps->current_cmd_s.index_2_ps = pid_cps; break;
        case 3: info_cps->current_cmd_s.index_3_ps = pid_cps; break;

        default: ERROR_PRINT("wrong pid id"); break;
    }
}

static bool Cmd_IterInWrongPosition(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_to_add_cps
)
{
    if(NULL == pid_to_add_cps)
    {
        return FALSE;
    }

    if(TYPE_ITERATOR != pid_to_add_cps->type_e)
    {
        return FALSE;
    }

    Cmd_command_cs command_cs = info_cps->current_cmd_s;

    if(Cmd_IterSelfIncluded(command_cs, pid_to_add_cps))
    {//FOR i FROM i TO i DO
        return TRUE;
    }
    else if(Cmd_IterNotInOwnScope(info_cps, pid_to_add_cps))
    {
        return TRUE;
    }

    return FALSE;
}

static bool Cmd_IterSelfIncluded(
    Cmd_command_cs command_cs,
    Pid_node_cps pid_to_add_cps
)
{
    if(Cmd_IsFor(command_cs))
    {
        if(pid_to_add_cps == command_cs.pid_1_ps)
        {
            return TRUE;
        }
    }

    return FALSE;
}

static bool Cmd_IsFor(
    Cmd_command_cs command_cs
)
{
    if( CMD_FOR == command_cs.type_e ||
        CMD_FOR_DOWNTO == command_cs.type_e
    )
    {
        return TRUE;
    }

    return FALSE;
}

static bool Cmd_IterNotInOwnScope(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_to_add_cps
)
{
    Ct_node_ps ct_last_ps = info_cps->last_ct_node_ps;
    if(Ct_IterNotInScope(ct_last_ps, pid_to_add_cps))
    {
        return TRUE;
    }

    return FALSE;
}

static bool Cmd_IsArray_nowy(
    Cplr_info_cps info_cps,
    Pid_node_cps pid_to_add_cps
)
{
    if(TYPE_ARRAY == pid_to_add_cps->type_e)
    {
            return TRUE;
    }

    return FALSE;
}

