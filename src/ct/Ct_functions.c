#include "Ct_functions.h"
#include "../asm/Asm_functions.h"
#include "../cmd/Cmd_functions.h"




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


extern void Ct_AddNode(
    Cplr_info_cps cplr_info_cps
);
extern bool Ct_IterNotEmbeded(
    Ct_node_cps last_ct_node_cps,
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


/********************************************************************
 * 
 *  -----------------------STATIC DECLARATIONS-----------------------
 * 
 ********************************************************************/


static void Ct_InsertAsLastNode(
    Cplr_info_cps cplr_info_cps ,
    Ct_node_cps node_to_add_cps
);
static void Ct_InsertNodeBellow(
    Ct_node_cps node_above_cps,
    Ct_node_cps node_bellow_cps
);
static void Ct_InsertNodeInNewBranch(
    Ct_node_cps node_branch_cps,
    Ct_node_cps node_first_in_branch_cps
);
static bool Ct_IsCmdBeginOfBranch(
    Cmd_type_e command
);
static void Ct_AddBranch(
    Cplr_info_cps cplr_info_cps 
);
static void Ct_AddAsLastNode(
    Cplr_info_cps cplr_info_cps ,
    Cmd_command_cs command_cs
);
static void Ct_UpdateLastNode(
    Cplr_info_cps cplr_info_cps ,
    Ct_node_cps node_cps
);
static bool Ct_NodeIsNewBranch(
    Ct_node_cps node_cps
);
static void Ct_IncPidOccurrInCt(
    Ct_node_cps ct_node_ps
);
static void Ct_CalcAllOccurr(
    Ct_node_cps first_node_in_tree_ps
);
static void Ct_DeleteBranch(
    Cplr_info_cps cplr_info_cps,
    Ct_node_ps node_ps,
    Ct_node_ps start_ps
);
static void Ct_DeleteN(
    Ct_node_ps node_ps
);
static bool Ct_NodeIsHead(
    Cplr_info_cps cplr_info_cps,
    Ct_node_ps node_ps
);
/*static void Ct_HeadDeleteCorrection(
    Cplr_info_cps cplr_info_cps,
    Ct_node_ps node_ps
);*/
static bool Ct_IsCmdExpressionLike(
    Ct_node_cps node_cps
);

/********************************************************************
 * 
 *  -----------------------EXTERN DEFINITIONS-----------------------
 * 
 ********************************************************************/


extern void Ct_AddNode(
    Cplr_info_cps cplr_info_cps
)
{   
    Cmd_command_cs cmd_cs = cplr_info_cps->current_cmd_s;
    Cmd_type_e cmd_type = cmd_cs.type_e;

    if(Ct_IsCmdBeginOfBranch(cmd_type))
    {
        Ct_AddBranch(cplr_info_cps );
    }

    Ct_AddAsLastNode(cplr_info_cps, cmd_cs);
}

extern bool Ct_IterNotInScope(
    Ct_node_cps last_ct_node_cps,
    Pid_node_ps iter_pid_ps
)
{
    Cmd_type_e type_e;
    Ct_node_ps ct_node_ps = last_ct_node_cps;
    while(TRUE)
    {
        if(NULL == ct_node_ps)
        {
            return TRUE;
        }

        type_e = ct_node_ps->command_s.type_e;
        if(CMD_FOR == type_e ||
           CMD_FOR_DOWNTO == type_e
        )
        {
            if(ct_node_ps->command_s.pid_1_ps == iter_pid_ps)
            {
                return FALSE;
            }
        }

        if(NULL == ct_node_ps->prev_ps)
        {
            if( NULL != ct_node_ps->branch_ps &&
                FALSE == ct_node_ps->is_branch
            )
            {
                ct_node_ps = ct_node_ps->branch_ps;
            }
        }
        ct_node_ps = ct_node_ps->prev_ps;
    }

    return FALSE;
}

extern bool Ct_IterNotEmbeded(
    Ct_node_cps last_ct_node_cps,
    Pid_node_ps pid_ps
)
{
    Cmd_type_e type_e;
    Ct_node_ps ct_node_ps = last_ct_node_cps;
    while(TRUE)
    {
        type_e = ct_node_ps->command_s.type_e;
        if(CMD_FOR == type_e ||
           CMD_FOR_DOWNTO == type_e
        )
        {
            if(ct_node_ps->command_s.pid_1_ps == pid_ps)
            {
                return FALSE;
            }
        }

        if(NULL == ct_node_ps->prev_ps)
        {
            if( NULL != ct_node_ps->branch_ps &&
                FALSE == ct_node_ps->is_branch
            )
            {
                ct_node_ps = ct_node_ps->branch_ps;
            }
            else
            {
                break;
            }
        }
        else
        {
            ct_node_ps = ct_node_ps->prev_ps;
        }
    }

    return TRUE;
}

extern void Ct_CalcPidOccurr(
    Cplr_info_cps cplr_info_cps
)
{
    Ct_node_ps head_ps = Ct_Head(cplr_info_cps);
    Ct_CalcAllOccurr(head_ps);
}

extern Ct_node_ps Ct_Head(
    Cplr_info_cps cplr_info_cps 
)
{

    return cplr_info_cps->ct_head_ps;
}

extern void Ct_DeleteNode(
    Cplr_info_cps cplr_info_cps,
    Ct_node_ps node_ps
)
{
    if(NULL == node_ps)
    {
        return;
    }

    if(Ct_NodeIsHead(cplr_info_cps, node_ps))
    {
        cplr_info_cps->ct_head_ps = cplr_info_cps->ct_head_ps->next_ps;
    }

    Asm_DeleteCode(node_ps);

    if(node_ps->is_branch)
    {
        Ct_DeleteBranch(cplr_info_cps, node_ps, node_ps);
    }
    else
    {
        Ct_DeleteN(node_ps);
    }
}

extern void Ct_LastNodeToNULL(
    Cplr_info_cps cplr_info_cps
)
{
    cplr_info_cps->last_ct_node_ps = NULL;   
}

extern Ct_node_ps Ct_NextNode(
    Ct_node_ps node_ps
)
{
    if(Ct_NodeIsBranch(node_ps))
    {
        return node_ps->branch_ps;
    }
    else if(Ct_NodeIsEndOfBranch(node_ps))
    {
        node_ps = Ct_HeadOfBranch(node_ps);
        node_ps = node_ps->branch_ps;
    }

    return node_ps->next_ps;
}

extern Ct_node_ps Ct_NextCmdNode(
    Ct_node_ps node_ps
)
{
    while(TRUE)
    {
        node_ps = Ct_NextNode(node_ps);
        if(NULL == node_ps)
        {
            break;
        }
        else if(Ct_IsCmdExpressionLike(node_ps))
        {
            break;
        }
    }

    return node_ps;
}

extern Ct_node_ps Ct_HeadOfBranch(
    Ct_node_cps node_cps
)
{
    Ct_node_ps tmp_ps = node_cps;
    if(NULL != node_cps)
    {
        while(tmp_ps->prev_ps != NULL)
        {
            tmp_ps = tmp_ps->prev_ps;
        }
    }

    return tmp_ps;
}

extern bool Ct_NodeIsBranch(
    Ct_node_cps node_cps
)
{   
    return node_cps->is_branch == TRUE;
}

extern bool Ct_NodeIsEndOfBranch(
    Ct_node_cps last_node_cps
)
{
    if(NULL == last_node_cps)
    {
        return FALSE;
        //ERROR_PRINT("Code tree node should not be null");
    }

    bool isEnd = FALSE;
    Cmd_type_e const type_e = last_node_cps->command_s.type_e;
    switch(type_e)
    {
        case CMD_ENDIF:     isEnd = TRUE;  break;
        case CMD_ENDWHILE:  isEnd = TRUE;  break;
        case CMD_ENDDO:     isEnd = TRUE;  break;
        case CMD_ENDFOR:    isEnd = TRUE;  break;
        //case CMD_END:       isEnd = TRUE;  break;
        default:            isEnd = FALSE; break;
    }

    return isEnd;
}

/********************************************************************
 * 
 *  -----------------------STATIC DEFINITIONS-----------------------
 * 
 ********************************************************************/

static void Ct_InsertAsLastNode(
    Cplr_info_cps cplr_info_cps ,
    Ct_node_cps node_to_add_cps
)
{
    node_to_add_cps->branch_ps = NULL;
    node_to_add_cps->prev_ps   = NULL;
    node_to_add_cps->next_ps   = NULL;

    /*Instructions have to have correct order*/
    /*EndOfBranch cannot appear before opening it*/
    /*fulfillment of this condition is assured by bison grammar*/
    /*In case of different order there will be unreachable allocated memory*/

    Ct_node_cps last_node_cps = cplr_info_cps->last_ct_node_ps;
    if(NULL != last_node_cps)
    {
        if(TRUE == Ct_NodeIsNewBranch(last_node_cps))
        {
            Ct_InsertNodeInNewBranch(last_node_cps, node_to_add_cps);
        }
        else
        {
            Ct_InsertNodeBellow(last_node_cps, node_to_add_cps);
        }
    }
    else
    {
        cplr_info_cps->ct_head_ps = node_to_add_cps;
    }
    

    Ct_UpdateLastNode(cplr_info_cps , node_to_add_cps);
}

static bool Ct_NodeIsNewBranch(
    Ct_node_cps node_cps
)
{
    if(NULL == node_cps)
    {
        ERROR_PRINT("Code tree node should not be null");
    }

    if(TRUE == Ct_NodeIsBranch(node_cps))
    {
        if(NULL == node_cps->branch_ps)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static void Ct_UpdateLastNode(
    Cplr_info_cps cplr_info_cps ,
    Ct_node_cps node_to_add_cps
)
{
    Ct_node_cps last_node_cps = cplr_info_cps->last_ct_node_ps;

    bool is_end_of_branch = Ct_NodeIsEndOfBranch(node_to_add_cps);
    if(TRUE == is_end_of_branch)
    {
        Ct_node_cps head_cps = Ct_HeadOfBranch(last_node_cps);
        if(NULL == head_cps->branch_ps)
        {// only when end of branch appears before open branch. Grammar error
            cplr_info_cps->last_ct_node_ps = node_to_add_cps;
        }
        else
        {
            cplr_info_cps->last_ct_node_ps = head_cps->branch_ps;
        }
    }
    else
    {
        cplr_info_cps->last_ct_node_ps = node_to_add_cps;
    }
}



static bool Ct_IsCmdBeginOfBranch(
    Cmd_type_e command
)
{
    bool isBegin = FALSE;
    switch(command)
    {
        case CMD_IF:         isBegin = TRUE;  break;
        case CMD_WHILE:      isBegin = TRUE;  break;
        case CMD_DO:         isBegin = TRUE;  break;
        case CMD_FOR:        isBegin = TRUE;  break;
        case CMD_FOR_DOWNTO: isBegin = TRUE;  break;
        default:             isBegin = FALSE; break;
    }

    return isBegin;
}

static void Ct_InsertNodeBellow(
    Ct_node_cps node_above_cps,
    Ct_node_cps node_bellow_cps
)
{
    node_above_cps->next_ps = node_bellow_cps;
    node_bellow_cps->prev_ps = node_above_cps;
}

static void Ct_InsertNodeInNewBranch(
    Ct_node_cps node_branch_cps,
    Ct_node_cps node_first_in_branch_cps
)
{
    node_branch_cps->branch_ps = node_first_in_branch_cps;
    node_first_in_branch_cps->branch_ps = node_branch_cps;
}

static void Ct_AddAsLastNode(
    Cplr_info_cps cplr_info_cps ,
    Cmd_command_cs command_cs
)
{
    Ct_node_ps node_to_add_ps = malloc(sizeof(*node_to_add_ps));
    if(NULL == node_to_add_ps)
    {
        ERROR_PRINT("malloc failed");
    }

    node_to_add_ps->command_s = command_cs;

    node_to_add_ps->asm_code_head_ps = NULL;
    node_to_add_ps->asm_code_length  = VAL_ZERO;
    node_to_add_ps->is_branch = FALSE;

    Ct_InsertAsLastNode(cplr_info_cps , node_to_add_ps); 
}

static void Ct_AddBranch(
    Cplr_info_cps cplr_info_cps 
)
{
    Ct_node_ps node_to_add_ps = malloc(sizeof(*node_to_add_ps));
    if(NULL == node_to_add_ps)
    {
        ERROR_PRINT("malloc failed");
    }

    node_to_add_ps->command_s = Cmd_Clean();

    node_to_add_ps->asm_code_head_ps = NULL;
    node_to_add_ps->asm_code_length  = VAL_ZERO;
    node_to_add_ps->is_branch = TRUE;

    Ct_InsertAsLastNode(cplr_info_cps , node_to_add_ps); 
}

static void Ct_CalcAllOccurr(
    Ct_node_cps first_node_in_tree_ps
)
{
    if(first_node_in_tree_ps == NULL)
    {
        return;
    }

    if(FALSE == first_node_in_tree_ps->is_branch)
    {
        Ct_IncPidOccurrInCt(first_node_in_tree_ps);
    }

    if(TRUE == first_node_in_tree_ps->is_branch)
    {
        Ct_CalcAllOccurr(first_node_in_tree_ps->branch_ps);
    }
    Ct_CalcAllOccurr(first_node_in_tree_ps->next_ps);
}

static void Ct_IncPidOccurrInCt(
    Ct_node_cps ct_node_ps
)
{
    if(NULL == ct_node_ps)
    {
        return;
    }

    Cmd_command_s cmd_s = ct_node_ps->command_s;
 
    if(NULL != cmd_s.pid_1_ps)
    {
        ct_node_ps->command_s.pid_1_ps->occurrences++;
    }
      
    if(NULL != cmd_s.pid_2_ps)
    {
        ct_node_ps->command_s.pid_2_ps->occurrences++;
    }

    if(NULL != cmd_s.pid_3_ps)
    {
        ct_node_ps->command_s.pid_3_ps->occurrences++;
    }

    /*if(NULL != cmd_s.pid_4_ps)
    {
        ct_node_ps->command_s.pid_4_ps->occurrences++;
    }*/

}

static void Ct_DeleteN(
    Ct_node_ps node_ps
)
{
    if(NULL == node_ps)
    {
        return;
    }

    if(Ct_IsCmdBeginOfBranch(node_ps->command_s.type_e))
    {
        if(NULL == node_ps->branch_ps)
        {
            ERROR_PRINT("branch like node without branch");
        }
        else
        {
            node_ps->branch_ps->branch_ps = NULL;
            node_ps->branch_ps = NULL;
        }
    }

    if(NULL != node_ps->prev_ps)
    {   
        node_ps->prev_ps->next_ps = node_ps->next_ps;
    }

    if(NULL != node_ps->next_ps)
    {
        node_ps->next_ps->prev_ps = node_ps->prev_ps;
    }

    node_ps->prev_ps   = NULL;
    node_ps->next_ps   = NULL;
    node_ps->branch_ps = NULL;

    node_ps->command_s = Cmd_Clean();
    
    printf("Frie %p\n",node_ps);
    free(node_ps);
}

static void Ct_DeleteBranch(
    Cplr_info_cps cplr_info_cps,
    Ct_node_ps node_ps,
    Ct_node_ps start_ps
)
{
    if( NULL == node_ps ||
        node_ps == start_ps->next_ps
    )
    {
        return;
    }

    if(TRUE == node_ps->is_branch)
    {
        Ct_DeleteBranch(cplr_info_cps, node_ps->branch_ps, start_ps);
        Ct_DeleteBranch(cplr_info_cps, node_ps->next_ps,   start_ps);
    }
    else
    {
        Ct_DeleteBranch(cplr_info_cps, node_ps->next_ps, start_ps);
    }

    Ct_DeleteN(node_ps);
}

static bool Ct_NodeIsHead(
    Cplr_info_cps cplr_info_cps,
    Ct_node_ps node_ps
)
{
    if(node_ps == cplr_info_cps->ct_head_ps)
    {
        return TRUE;
    }

    return FALSE;
}

/*static void Ct_HeadDeleteCorrection(
    Cplr_info_cps cplr_info_cps,
    Ct_node_ps node_ps
)
{
    if(Ct_NodeIsHead(cplr_info_cps, node_ps))
    {
        cplr_info_cps->ct_head_ps = cplr_info_cps->ct_head_ps->next_ps;
    }
}*/

static bool Ct_IsCmdExpressionLike(
    Ct_node_cps node_cps
)
{
    return Cmd_IsExpressionLike(node_cps->command_s.type_e);
}
