#include "Cplr_functions.h"
#include "../cmd/Cmd_functions.h" // delete after CT creation TODO
#include "../ct/Ct_functions.h" 
#include "../asm/Asm_functions.h" 
#include "../asm/Asm_instructions.h" 
#include "../ram/Ram_functions.h" 
#include "../pid/Pid_functions.h" 





/********************************************************************
 * 
 *  ----------------------------DEFINES----------------------------
 * 
 ********************************************************************/
#define TABS(n)\
    do{\
        for (int i = 0; i < n; i++)\
        {\
            printf("\t");\
        }\
    }while(FALSE)



/********************************************************************
 * 
 *  -----------------------EXTERN DECLARATIONS-----------------------
 * 
 ********************************************************************/


extern void Cplr_SetCplrState_Declare(
    Cplr_info_cps info_cps
);
extern void Cplr_SetCplrState_Begin(
    Cplr_info_cps info_cps
);
extern void Cplr_SetCplrState_End(
    Cplr_info_cps info_cps
);
extern bool Cplr_InSection_End(
    Cplr_info_s const info_cs
);
extern bool Cplr_InSection_Declare(
    Cplr_info_s const info_cs
);
extern bool Cplr_InSection_Begin(
    Cplr_info_s const info_cs
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
extern void Cplr_PrintRam(
    Cplr_info_cps info_cps
);



extern void Cplr_AsmReader(
    Cplr_info_cps info_cps
);
extern void Cplr_AsmReader_nowy(
    Cplr_info_cps info_cps
);

/*extern void Cplr_AllocArrays(
    Cplr_info_cps info_cps
);*/
extern void Cplr_AllocArrays_nowy(
    Cplr_info_cps info_cps
);
extern void Cplr_AllocPids(
    Cplr_info_cps info_cps
);

extern void Cplr_TESTWRITE(
    Cplr_info_cps info_cps
);

/********************************************************************
 * 
 *  -----------------------STATIC DECLARATIONS-----------------------
 * 
 ********************************************************************/


static void Cplr_PrintPid(
    Pid_node_s *pid
);
static void Cplr_PrintCt(
    Ct_node_cps first_node_in_tree_ps,
    Cplr_val number_of_indents
);
static void Cplr_PrintRamNode(
    Ram_node_ps ram_ps
);
static void Cplr_PrintAsmNode(
    Asm_node_ps asm_node
);
static void Cplr_PrintAsmAsInstr(
    Asm_node_ps asm_node
);
static void Cplr_PrintAsmAsInstr_nowy(
    Cplr_info_cps info_cps,
    Asm_node_ps asm_node
);
static void Cplr_PrintAsmAsInstructions(
    Ct_node_ps ct_node_ps
);
static void Cplr_PrintAsmAsInstructions_nowe(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps
);
static Asm_node_ps Cplr_Code(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_cps
);
static void Cplr_InsertCode(
    Asm_node_ps asm_ps,
    Ct_node_ps ct_node_ps
);
static void Cplr_JumpCorrect(
    Ct_node_ps ct_end_of_branch_ps
);
static Cplr_val Cplr_AsmLenCodeInScope(
    Ct_node_ps head_ps,
    Ct_node_ps tail_ps
);
static void Cplr_READ(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_READ_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static bool Cplr_NumberNotInRam(
    Cplr_info_cps info_cps,
    Pid_node_cps number_cps
);
static void Cplr_PrintCmd(
    Cmd_command_cs cmd_cs
);
static Cplr_val Cplr_Abs(
    Cplr_val value
);
static Asm_val Cplr_WriteInArrayAddress(
    Cplr_info_cps info_cps,
    Asm_val save_adr_in,
    Ct_node_ps ct_node_ps,
    Pid_node_ps array_ps,
    Pid_node_ps index_ps
);
static void Cplr_AddAsmCode(
    Ct_node_ps ct_node_ps,
    Asm_node_ps asm_ps
);
static void Cplr_WRITE(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_WRITE_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static Ram_id Cplr_LoadToP0ArrayIndex(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps,
    Pid_node_ps array_ps,
    Pid_node_ps index_ps
);
static void Cplr_ASSIGN_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_TIMES(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_TIMES_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static bool Cplr_NoValueSkipAssign(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs
);
static void Cplr_PLUS(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_PLUS_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_MINUS(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_MINUS_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_DIV(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_DIV_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_MOD(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_MOD_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
/*static void Cplr_CONST(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);*/
static void Cplr_CONST_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static bool Cplr_SkipAssign(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs
);
static bool Cplr_CheckPidIfSkip(
    Cplr_info_cps info_cps,
    Pid_node_ps pid_ps,
    Pid_node_ps idx_ps
);
static Cplr_ramids_s Cplr_RamIdForOneArg(
    Cplr_info_cps info_cps,
    Ram_id ram_save_in,
    Pid_node_ps pid_ps,
    Pid_node_ps idx_ps,
    Ct_node_ps ct_node_ps
);
static Cplr_ramids_s Cplr_CorrectRamids(
    Cplr_ramids_s ramids_1_s,
    Cplr_ramids_s ramids_2_s,
    Cplr_ramids_s ramids_3_s
);
static Ram_id Cplr_RamAdr(
    Cplr_info_cps info_cps,
    Ram_id ram_save_in,
    Pid_node_ps pid_ps,
    Pid_node_ps idx_ps,
    Ct_node_ps ct_node_ps
);
static Cplr_ramids_s Cplr_RetRamIds(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_IF(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);

static void Cplr_IF_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);

static void Cplr_ELSE(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_ELSE_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_END_IF(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);

static void Cplr_END_IF_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);

static void Cplr_WHILE(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_WHILE_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_ENDWHILE(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_ENDWHILE_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_ENDDO(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_ENDDO_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_FOR(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_FOR_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
/*static void Cplr_ENDFOR(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);*/
static void Cplr_ENDFOR_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
);
static void Cplr_SetRegToRamAddressOfPid_nowy(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps,
    Cplr_registers_ce reg,
    Pid_node_cps pid,
    Pid_node_cps pid_index,
    Cplr_registers_ce reg_forIndex
);
static void Cplr_SetRegToValueOfPid_nowy(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps,
    Cplr_registers_ce reg,
    Pid_node_cps pid,
    Pid_node_cps pid_index,
    Cplr_registers_ce reg_forIndex // this one is temp used only here
);
static bool Cplr_AllArgumentsAreNumbers(
    Cmd_command_cs cmd_cs
);
static bool Cplr_OneArgumentIs_2(
    Cmd_command_cs cmd_cs
);
static bool Cplr_OneArgumentIs_1(
    Cmd_command_cs cmd_cs
);
static bool Cplr_ArgumentAreTheSame(
    Cmd_command_cs cmd_cs
);
static bool Cplr_ArraysHaveIndexes_nowy(
    Cmd_command_cs cmd_cs
);
static Pid_node_s* Cplr_LastPid_new(
    Pid_node_s ** listHead_cpps
);

/********************************************************************
 * 
 *  -----------------------EXTERN DEFINITIONS-----------------------
 * 
 ********************************************************************/

extern bool Cplr_InSection_Declare(
    Cplr_info_s const info_cs
)
{
    return info_cs.cplr_state_e == CPLR_DECLARE;
}

extern bool Cplr_InSection_Begin(
    Cplr_info_s const info_cs
)
{
    return info_cs.cplr_state_e == CPLR_BEGIN;
}

extern bool Cplr_InSection_End(
    Cplr_info_s const info_cs
)
{
    return info_cs.cplr_state_e == CPLR_END;
}

extern void Cplr_SetCplrState_Declare(
    Cplr_info_cps info_cps
)
{
    info_cps->cplr_state_e = CPLR_DECLARE;
}

extern void Cplr_SetCplrState_Begin(
    Cplr_info_cps info_cps
)
{
    info_cps->cplr_state_e = CPLR_BEGIN;
}

extern void Cplr_SetCplrState_End(
    Cplr_info_cps info_cps
)
{
    info_cps->cplr_state_e = CPLR_END;
}

extern void Cplr_PrintDecorator(
    Cplr_name title
)
{
    puts("");
    puts("");

    printf("*********************************************************\n");
    printf("\t\t\t%s\n",title);
    printf("*********************************************************\n");

    puts("");
    puts("");
}

extern void Cplr_PrintPids(
    Cplr_info_cps info_cps
)
{
    if(NULL == info_cps->pid_listHead_cpps)
    {
        puts("Pid list is empty");
        return;
    }

    Pid_node_ps tmp_pid_ps = *(info_cps->pid_listHead_cpps);
    while(NULL != tmp_pid_ps)
    {
        Cplr_PrintPid(tmp_pid_ps);
        puts("");
        tmp_pid_ps = tmp_pid_ps->next_ps;
    }
}

extern void Cplr_PrintWholeCt(
    Cplr_info_cps info_cps
)
{
    Ct_node_ps first_ct_ps = Ct_Head(info_cps);//Cplr_FirstNodeInCt(info_cps->last_ct_node_ps);
    printf("Ct_Head(): %p\n",first_ct_ps);
    if(NULL != first_ct_ps)
    {
        Cplr_PrintCt(first_ct_ps, VAL_ZERO);
    }
    else
    {
        puts("Ct is empty");
    }
}

extern void Cplr_PrintRam(
    Cplr_info_cps info_cps
)
{
    if(NULL == info_cps->ram_head_ps)
    {
        puts("Ram list is empty");
        return;
    }

    Ram_node_ps tmp_ram_ps = info_cps->ram_head_ps;
    while(NULL != tmp_ram_ps)
    {
        Cplr_PrintRamNode(tmp_ram_ps);
        puts("");
        tmp_ram_ps = tmp_ram_ps->next_ps;
    }
}

extern void Cplr_AsmReader(
    Cplr_info_cps info_cps
)
{
    Ct_node_ps ct_current_ps = info_cps->ct_head_ps;
    while(NULL != ct_current_ps)
    {
        //if(FALSE == Ct_NodeIsBranch(ct_current_ps))
        //{   
            //Cplr_PrintCt(ct_current_ps, 1);
            Cplr_PrintAsmAsInstructions(ct_current_ps);
        //}

        ct_current_ps = Ct_NextNode(ct_current_ps);
    }
}

extern void Cplr_AsmReader_nowy(
    Cplr_info_cps info_cps
)
{
    Ct_node_ps ct_current_ps = info_cps->ct_head_ps;
    while(NULL != ct_current_ps)
    {
        //if(FALSE == Ct_NodeIsBranch(ct_current_ps))
        //{   
            //Cplr_PrintCt(ct_current_ps, 1);
            Cplr_PrintAsmAsInstructions_nowe(info_cps, ct_current_ps);
        //}

        ct_current_ps = Ct_NextNode(ct_current_ps);
    }
}

extern void Cplr_CodeGenerator(
    Cplr_info_cps info_cps
)
{
    Asm_node_ps asm_ps = NULL;
    Cmd_command_s cmd_s = Cmd_Clean();
    Ct_node_ps ct_node_ps = info_cps->ct_head_ps;
    Ct_node_ps head_ps = NULL;
    while(NULL != ct_node_ps)
    {
        //puts("Code generator w ct:");
        //Cplr_PrintCt(ct_node_ps, 1);
        cmd_s = ct_node_ps->command_s;

        if(CMD_ELSE == cmd_s.type_e)
        {            
            head_ps = Ct_HeadOfBranch(ct_node_ps);
            Ram_DelAllAllocInBranch(info_cps, head_ps);
            head_ps = NULL;
        }

        if(Cmd_IsExpressionLike(cmd_s.type_e))
        {
            //puts("Generuje kod, dla cmd:");
            //Cplr_PrintCmd(cmd_s);
            asm_ps = Cplr_Code(info_cps, cmd_s, ct_node_ps);
            //puts("Wygenerowany kod:");
           // Cplr_PrintAsmAsInstructions(ct_node_ps);

            //Cplr_InsertCode(asm_ps, ct_node_ps);
        }

        /* nowe
        if(CMD_ENDFOR == cmd_s.type_e)
        {
            
        }*/

        if(Ct_NodeIsEndOfBranch(ct_node_ps))
        {
            head_ps = Ct_HeadOfBranch(ct_node_ps);
            Ram_DelAllAllocInBranch(info_cps, head_ps);
            head_ps = NULL;
        }

       ct_node_ps = Ct_NextCmdNode(ct_node_ps);
    }

    // ct_node_ps = info_cps->ct_head_ps;
    // while(NULL != ct_node_ps)
    // {
    //     if(Ct_NodeIsEndOfBranch(ct_node_ps))
    //     {
    //         Cplr_JumpCorrect(ct_node_ps);
    //     }
        
    //     ct_node_ps = Ct_NextNode(ct_node_ps);
    // }

    //Asm_HALT(&asm_ps);
    //Asm_Print(asm_ps);
}


/* nowyextern void Cplr_AllocArrays(
    Cplr_info_cps info_cps
)
{
    Pid_val lower_lim = VAL_ZERO;
    Pid_val upper_lim = VAL_ZERO;
    Ram_id arr_size = 0;
    Ram_id id = 0;
    Ram_id id_index = 0;
    Asm_node_ps asm_ps = NULL;
    Pid_node_ps pid_ps = *(info_cps->pid_listHead_cpps);
    const Cplr_registers_e reg_to_use = a;
    while(NULL != pid_ps)
    {
        if(0 < pid_ps->occurrences)
        {
            if(TYPE_ARRAY == pid_ps->type_e)
            {
                lower_lim = pid_ps->array_data_s.lower_lim;
                upper_lim = pid_ps->array_data_s.upper_lim;
                arr_size = Ram_ArraySize(lower_lim, upper_lim);
                
                id = Ram_Alloc(info_cps, arr_size);
                
                // if(VAL_ZERO > lower_lim)
                // {
                //     //puts("::::::::::::::::::::::::::::::::::::::::::");

                //     //printf("id: %ld\n",id);
                //     id = Cplr_Abs(lower_lim) + id;
                //     //printf("id: %ld\n",id);
                //     pid_ps->array_data_s.memory_address = id;
                //     //puts("::::::::::::::::::::::::::::::::::::::::::");
                // }
                if(VAL_ZERO > lower_lim && upper_lim >= VAL_ZERO)
                {
                    //puts("::::::::::::::::::::::::::::::::::::::::::");
                    //printf("id: %ld\n",id);
                    id = Cplr_Abs(lower_lim) + id;
                    //printf("id: %ld\n",id);
                    pid_ps->array_data_s.memory_address = id;
                    //puts("::::::::::::::::::::::::::::::::::::::::::");                
                }

                Ram_Init(info_cps, NULL, pid_ps);

                if(VAL_ZERO < lower_lim)
                {
                    if(VAL_ZERO < ((Cplr_val)id - lower_lim))
                        ERROR_PRINT("Nie moze byc liczb ujemnych!"); // jeśli to to skasuj tego ifa ?
                    asm_ps = Asm_NumberGenerator_nowy(
                                        info_cps,
                                        (Cplr_val)id - lower_lim,
                                        info_cps->ct_head_ps
                                    );
                }
                else
                {
                    asm_ps = Asm_NumberGenerator_nowy(
                                        info_cps,
                                        (Cplr_val)id,
                                        info_cps->ct_head_ps
                                    );
                }
*/                
                
                /*działa tez bez tego, ale ram nie wie wtedy jaka wartosc jest w ramie zaw. adres początkowy tablicy*/
/*nowy                char str[256] = {};
                (void)snprintf(str, 256, "%ld", id);
                Pid_AddToList_Number(info_cps, (Pid_name_c)str);
                Pid_node_ps pid_id_ps =  Pid_FindByName(info_cps->pid_listHead_cpps, (Pid_name_c)str);

                id_index = Ram_Alloc(info_cps, 1);
                Ram_Init(info_cps, NULL, pid_id_ps);
                Asm_STORE((Asm_val)id_index, &asm_ps);
               
                Asm_AppendCode(&(info_cps->ct_head_ps->asm_code_head_ps), asm_ps);
                
                //Cplr_PrintAsmAsInstructions(info_cps->ct_head_ps);
                pid_ps->array_data_s.memory_address = id_index;
            }
        }
        pid_ps = pid_ps->next_ps;
    }
}
*/

extern void Cplr_AllocArrays_nowy(
    Cplr_info_cps info_cps
)
{
    Pid_val lower_lim = VAL_ZERO;
    Pid_val upper_lim = VAL_ZERO;
    Ram_id arr_size = 0;
    Ram_id id = 0;
    Ram_id id_index = 0;
    Asm_node_ps asm_ps = NULL;
    Pid_node_ps pid_ps = *(info_cps->pid_listHead_cpps);
    const Cplr_registers_e reg_to_use = a;
    while(NULL != pid_ps)
    {
        if(0 < pid_ps->occurrences)
        {
            if(TYPE_ARRAY == pid_ps->type_e)
            {
                lower_lim = pid_ps->array_data_s.lower_lim;
                upper_lim = pid_ps->array_data_s.upper_lim;
                arr_size = Ram_ArraySize(lower_lim, upper_lim);
                //printf("###################### arr_size: %ld\n", arr_size);
                
                id = Ram_Alloc(info_cps, arr_size);

                //printf("###################### id: %ld\n", id);

                Ram_Init(info_cps, NULL, pid_ps);
                /*
                if(VAL_ZERO < lower_lim)
                {
                    asm_ps = Asm_NumberGenerator_nowy(
                                info_cps,
                                (Cplr_val)id - lower_lim,
                                info_cps->ct_head_ps,
                                reg_to_use
                            );
                }
                else
                {
                    asm_ps = Asm_NumberGenerator_nowy(
                                info_cps,
                                (Cplr_val)id,
                                info_cps->ct_head_ps,
                                reg_to_use
                            );
                }
                */
                
                /*działa tez bez tego, ale ram nie wie wtedy jaka wartosc jest w ramie zaw. adres początkowy tablicy*/
                /*char str[256] = {};
                (void)snprintf(str, 256, "%ld", id);
                Pid_AddToList_Number(info_cps, (Pid_name_c)str);
                Pid_node_ps pid_id_ps =  Pid_FindByName(info_cps->pid_listHead_cpps, (Pid_name_c)str);
                */
                /*id_index = Ram_Alloc(info_cps, 1);
                Ram_Init(info_cps, NULL, pid_id_ps);
                Asm_STORE((Asm_val)id_index, &asm_ps);

                Asm_AppendCode(&(info_cps->ct_head_ps->asm_code_head_ps), asm_ps);
                
                //Cplr_PrintAsmAsInstructions(info_cps->ct_head_ps);
                pid_ps->array_data_s.memory_address = id_index;*/
            }
        }
        pid_ps = pid_ps->next_ps;
    }
}

extern void Cplr_AllocPids(
    Cplr_info_cps info_cps
)
{
    Ram_id id;
    Pid_node_ps pid_ps = *(info_cps->pid_listHead_cpps);
    while(NULL != pid_ps)
    {
        if(0 < pid_ps->occurrences)
        {
            if( TYPE_ARRAY != pid_ps->type_e &&
                TYPE_NUMBER != pid_ps->type_e
            )
            {
                id = Ram_Alloc(info_cps, 1);
                Ram_Init(info_cps, NULL, pid_ps);
                pid_ps->ram_address = id;
            }
        }

        pid_ps = pid_ps->next_ps;
    }
}




extern void Cplr_TESTWRITE(
    Cplr_info_cps info_cps
)
{
    printf("%p",info_cps->outputFile);
    fprintf(info_cps->outputFile,"test\n");
    fclose(info_cps->outputFile);
}




/********************************************************************
 * 
 *  -----------------------STATIC DEFINITIONS------------------------
 * 
 ********************************************************************/



static void Cplr_PrintPid(Pid_node_s *pid)
{
    printf("&pid:\t\t%p\n",pid);
    printf("pid->next:\t%p\n",pid->next_ps);
    printf("pid->prev:\t%p\n",pid->prev_ps);
    //printf("array_data_s:\n");
    printf("name_p:\t\t%s\n",pid->name_p);
    printf("value:\t\t%ld\n",pid->value);
    printf("ram_address:\t%ld\n",pid->ram_address);
    printf("occurrence:\t%ld\n",pid->occurrences);
    printf("lower_lim:\t%ld\n",pid->array_data_s.lower_lim);
    printf("upper_lim:\t%ld\n",pid->array_data_s.upper_lim);
    
    if(pid->type_e == TYPE_VARIABLE)
        printf("type_e:\t\tTYPE_VARIABLE\n");
    else if(pid->type_e == TYPE_ARRAY)
    {
        printf("type_e:\t\tTYPE_ARRAY\n");
        printf("pid->arr_data.memory_adr:\t\t%ld\n",pid->array_data_s.memory_address);
    }
    else if(pid->type_e == TYPE_NUMBER)
        printf("type_e:\t\tTYPE_NUMBER\n");
    else if(pid->type_e == TYPE_ITERATOR)
        printf("type_e:\t\tTYPE_ITERATOR\n");
    else
        printf("type_e:\t\tnot in type_e\n");

    if(pid->status_e == STATUS_INITIALIZED)
        printf("status_e:\tSTATUS_INITIALIZED\n");
    else if(pid->status_e == STATUS_UNINITIALIZED)
        printf("status_e:\tSTATUS_UNINITIALIZED\n");
    else if(pid->status_e == STATUS_VALUE_KNOWN)
        printf("status_e:\tSTATUS_VALUE_KNOWN\n");
    else
        printf("status_e:\tCnot in Cplr_type_e\n");

}

static void Cplr_PrintCmd(
    Cmd_command_cs cmd_cs
)
{
    printf("command:  ");
    switch (cmd_cs.type_e)
    {
        case CMD_EMPTY:     printf("CMD_EMPTY_CMD");    break;
        case CMD_ASSIGN:    printf("CMD_ASSIGN");       break;
        case CMD_IF:        printf("CMD_IF");           break;
        case CMD_ELSE:      printf("CMD_ELSE");         break;
        case CMD_ENDIF:     printf("CMD_ENDIF");        break;
        case CMD_WHILE:     printf("CMD_WHILE");        break;
        case CMD_DO:        printf("CMD_DO");           break;
        case CMD_WHILE_DO:  printf("CMD_WHILE_DO");     break;
        case CMD_ENDWHILE:  printf("CMD_ENDWHILE");     break;
        case CMD_ENDDO:     printf("CMD_ENDDO");        break;
        case CMD_FOR:       printf("CMD_FOR");          break;
        case CMD_FOR_DOWNTO: printf("CMD_FOR_DOWNTO");  break;
        case CMD_ENDFOR:    printf("CMD_ENDFOR");       break;
        case CMD_READ:      printf("CMD_READ");         break;
        case CMD_WRITE:     printf("CMD_WRITE");        break;
        case CMD_END:       printf("CMD_END");          break;
    
    default: printf("!!!!!!!!!! Bład wydruku !!!!!!!!!!");
        break;
    }
    puts("");

    printf("cmd->pid_1: %p\n", cmd_cs.pid_1_ps);

    printf("cmd->pid_2: %p\n", cmd_cs.pid_2_ps);

    printf("cmd->pid_3: %p\n", cmd_cs.pid_3_ps);

    printf("cmd->idx_1: %p\n", cmd_cs.index_1_ps);

    printf("cmd->idx_2: %p\n", cmd_cs.index_2_ps);

    printf("cmd->idx_3: %p\n", cmd_cs.index_3_ps);

    printf("cmd->type:  %d\n", cmd_cs.type_e);

    printf("cmd->expr:  %d\n", cmd_cs.expression_e);

    printf("cmd->cond:  %d\n", cmd_cs.condition_e);
    puts("");
}

static void Cplr_PrintCt(
    Ct_node_cps first_node_in_tree_ps,
    Cplr_val number_of_indents
)
{
    if(NULL == first_node_in_tree_ps)
    {
        return;
    }

    TABS(number_of_indents);
    printf("node:   %p\n", first_node_in_tree_ps);
    TABS(number_of_indents);
    printf("prev:   %p\n", first_node_in_tree_ps->prev_ps);
    TABS(number_of_indents);
    printf("next:   %p\n", first_node_in_tree_ps->next_ps);
    TABS(number_of_indents);
    printf("branch: %p\n", first_node_in_tree_ps->branch_ps);
    TABS(number_of_indents);
    printf("asm_he: %p\n", first_node_in_tree_ps->asm_code_head_ps);
    TABS(number_of_indents);
    if(TRUE == first_node_in_tree_ps->is_branch)
    {
        printf("isBranch: CT_NODE_BRANCH\n");
    }
    else
    {
        printf("isBranch: CT_NODE_NOT_BRANCH\n");
    }
    TABS(number_of_indents);
    printf("command:  ");
    switch (first_node_in_tree_ps->command_s.type_e)
    {
        case CMD_EMPTY:     printf("CMD_EMPTY_CMD");    break;
        case CMD_ASSIGN:    printf("CMD_ASSIGN");       break;
        case CMD_IF:        printf("CMD_IF");           break;
        case CMD_ELSE:      printf("CMD_ELSE");         break;
        case CMD_ENDIF:     printf("CMD_ENDIF");        break;
        case CMD_WHILE:     printf("CMD_WHILE");        break;
        case CMD_DO:        printf("CMD_DO");           break;
        case CMD_WHILE_DO:  printf("CMD_WHILE_DO");     break;
        case CMD_ENDWHILE:  printf("CMD_ENDWHILE");     break;
        case CMD_ENDDO:     printf("CMD_ENDDO");        break;
        case CMD_FOR:       printf("CMD_FOR");          break;
        case CMD_FOR_DOWNTO: printf("CMD_FOR_DOWNTO");  break;
        case CMD_ENDFOR:    printf("CMD_ENDFOR");       break;
        case CMD_READ:      printf("CMD_READ");         break;
        case CMD_WRITE:     printf("CMD_WRITE");        break;
        case CMD_END:       printf("CMD_END");          break;
    
    default: printf("!!!!!!!!!! Bład wydruku !!!!!!!!!!");
        break;
    }
    puts("");
    TABS(number_of_indents);
    printf("cmd->pid_1: %p\n", first_node_in_tree_ps->command_s.pid_1_ps);
    TABS(number_of_indents);
    printf("cmd->pid_2: %p\n", first_node_in_tree_ps->command_s.pid_2_ps);
    TABS(number_of_indents);
    printf("cmd->pid_3: %p\n", first_node_in_tree_ps->command_s.pid_3_ps);
    /*TABS(number_of_indents);
    printf("cmd->pid_4: %p\n", first_node_in_tree_ps->command_s.pid_4_ps);*/
    TABS(number_of_indents);
    printf("cmd->idx_1: %p\n", first_node_in_tree_ps->command_s.index_1_ps);
    TABS(number_of_indents);
    printf("cmd->idx_2: %p\n", first_node_in_tree_ps->command_s.index_2_ps);
    TABS(number_of_indents);
    printf("cmd->idx_3: %p\n", first_node_in_tree_ps->command_s.index_3_ps);
    TABS(number_of_indents);
    printf("cmd->type:  %d\n", first_node_in_tree_ps->command_s.type_e);
    TABS(number_of_indents);
    printf("cmd->expr:  %d\n", first_node_in_tree_ps->command_s.expression_e);
    TABS(number_of_indents);
    printf("cmd->cond:  %d\n", first_node_in_tree_ps->command_s.condition_e);
    puts("");

    Cplr_PrintAsmAsInstructions(first_node_in_tree_ps);

    if(TRUE == first_node_in_tree_ps->is_branch)
    {
        Cplr_PrintCt(first_node_in_tree_ps->branch_ps, number_of_indents+1);
        Cplr_PrintCt(first_node_in_tree_ps->next_ps, number_of_indents-1);
    }
    else
    {
        Cplr_PrintCt(first_node_in_tree_ps->next_ps, number_of_indents);
    }
}

static void Cplr_PrintRamNode(
    Ram_node_ps ram_ps
)
{
    printf("&ram:\t\t%p\n",ram_ps);
    printf("ram->next:\t%p\n",ram_ps->next_ps);
    printf("ram->prev:\t%p\n",ram_ps->prev_ps);

    printf("id:\t\t%ld\n",ram_ps->id);
    printf("up_lim:\t\t%ld\n",ram_ps->array_upper_lim);
    
    if(ram_ps->type_e == RAM_UNRELATED)
        printf("type_e:\t\tRAM_UNRELATED\n");
    else if(ram_ps->type_e == RAM_PID)
        printf("type_e:\t\tRAM_PID\n");
    else if(ram_ps->type_e == RAM_ARRAY)
        printf("type_e:\t\tRAM_ARRAY\n");
    else if(ram_ps->type_e == RAM_REGISTER)
        printf("type_e:\t\tRAM_REGISTER\n");
    else
        printf("type_e:\t\tnot in type_e\n");

    printf("pid:\t\t%p\n",ram_ps->pid_ps);
    if(NULL != ram_ps->pid_ps)
    {
        printf("pid->name:\t\t%s\n",ram_ps->pid_ps->name_p);
        if(ram_ps->pid_ps->status_e == STATUS_INITIALIZED)
            printf("pid->status_e:\t\tSTATUS_INITIALIZED\n");
        else if(ram_ps->pid_ps->status_e == STATUS_UNINITIALIZED)
            printf("pid->status_e:\t\tSTATUS_UNINITIALIZED\n");
        else if(ram_ps->pid_ps->status_e == STATUS_VALUE_KNOWN)
            printf("pid->status_e:\t\tSTATUS_VALUE_KNOWN\n");
        else
            printf("pid->status_e:\t\tCnot in Cplr_type_e\n");
    }

    printf("ct:\t\t%p\n",ram_ps->ct_branch_head_ps);
    if(NULL != ram_ps->ct_branch_head_ps)
    {
        printf("ct->cmd.type:\t\t%d\n",ram_ps->ct_branch_head_ps->command_s.type_e);
    }
}

static void Cplr_PrintAsmNode(
    Asm_node_ps asm_node
)
{
    printf("&asm:\t\t%p\n",asm_node);
    printf("asm->next:\t%p\n",asm_node->next_ps);
    printf("asm->prev:\t%p\n",asm_node->prev_ps);

    printf("arg:\t\t%ld\n",asm_node->instr_arg);

    if(asm_node->asm_instr_e == EMPTY_INSTR)
        printf("type_e:\t\t\t\tEMPTY_INSTR\n");
    else if(asm_node->asm_instr_e == GET)
        printf("type_e:\t\t\t\tGET %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == PUT)
        printf("type_e:\t\t\t\tPUT %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == LOAD)
        printf("type_e:\t\t\t\tLOAD %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == STORE)
        printf("type_e:\t\t\t\tSTORE %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == LOAD_I)
        printf("type_e:\t\t\t\tLOAD_I %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == STORE_I)
        printf("type_e:\t\t\t\tSTORE_I %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == ADD)
        printf("type_e:\t\t\t\tADD %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == SUB)
        printf("type_e:\t\t\t\tSUB %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == SHIFT)
        printf("type_e:\t\t\t\tSHIFT %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == INC)
        printf("type_e:\t\t\t\tINC\n");
    else if(asm_node->asm_instr_e == DEC)
        printf("type_e:\t\t\t\tDEC\n");
    else if(asm_node->asm_instr_e == JUMP)
        printf("type_e:\t\t\t\tJUMP %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == JPOS)
        printf("type_e:\t\t\t\tJPOS %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == JZERO)
        printf("type_e:\t\t\t\tJZERO %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == JNEG)
        printf("type_e:\t\t\t\tJNEG %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == HALT)
        printf("type_e:\t\t\t\tHALT\n");
    else
        printf("type_e:\t\tnot in type_e\n");
    
    puts("");
}



static void Cplr_PrintAsmAsInstructions(
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_node = ct_node_ps->asm_code_head_ps;

    //Asm_PrintList(asm_node);
    //printf("ct: %p\n",ct_node_ps);
    while(NULL != asm_node)
    {
        Cplr_PrintAsmAsInstr(asm_node);
        //Asm_Print(asm_node);
        asm_node = asm_node->next_ps;
    }
}

static void Cplr_PrintAsmAsInstructions_nowe(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_node = ct_node_ps->asm_code_head_ps;

    //Asm_PrintList(asm_node);
    //printf("ct: %p\n",ct_node_ps);
    while(NULL != asm_node)
    {
        Cplr_PrintAsmAsInstr_nowy(info_cps, asm_node);
        //Asm_Print(asm_node);
        asm_node = asm_node->next_ps;
    }
}

static void Cplr_PrintAsmAsInstr(
    Asm_node_ps asm_node
)
{
    static Asm_val pc = 0;

    if(NULL == asm_node)
    {
        return;
    }

    if(asm_node->asm_instr_e == EMPTY_INSTR)
        ;//printf("EMPTY_INSTR\n");
    else if(asm_node->asm_instr_e == GET)
        printf("GET %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == PUT)
        printf("PUT %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == LOAD)
        printf("LOAD %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == STORE)
        printf("STORE %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == LOAD_I)
        printf("LOADI ------ %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == STORE_I)
        printf("STOREI ------- %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == ADD)
        printf("ADD %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == SUB)
        printf("SUB %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == SHIFT)
        printf("SHIFT ------ %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == INC)
        printf("INC %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == DEC)
        printf("DEC %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == JUMP)
        printf("JUMP %ld\n",asm_node->reg_1);
    else if(asm_node->asm_instr_e == JPOS)
        printf("JPOS -------- %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == JZERO)
        printf("JZERO %c %ld\n", (char)asm_node->reg_1, asm_node->reg_2);
    else if(asm_node->asm_instr_e == JNEG)
        printf("JNEG ------ %ld\n", asm_node->instr_arg);

    else if(asm_node->asm_instr_e == SHR)
        printf("SHR %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == SHL)
        printf("SHL %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == RESET)
        printf("RESET %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == JODD)
        printf("JODD %c %ld\n", (char)asm_node->reg_1, asm_node->reg_2);
    
    else if(asm_node->asm_instr_e == HALT)
        printf("HALT\n");
    else
        ;//printf("type_e:\t\tnot in type_e\n");
    
    pc++;
    //puts("");
}


#ifdef __SIZEOF_INT128__

static void Cplr_PrintAsmAsInstr_nowy(
    Cplr_info_cps info_cps,
    Asm_node_ps asm_node
)
{
    static Asm_val pc = 0;

    if(NULL == asm_node)
    {
        return;
    }

    if(asm_node->asm_instr_e == EMPTY_INSTR)
        ;//fprintf(info_cps->outputFile,"EMPTY_INSTR\n");
    else if(asm_node->asm_instr_e == GET)
        fprintf(info_cps->outputFile,"GET %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == PUT)
        fprintf(info_cps->outputFile,"PUT %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == LOAD)
        fprintf(info_cps->outputFile,"LOAD %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == STORE)
        fprintf(info_cps->outputFile,"STORE %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == LOAD_I)
        fprintf(info_cps->outputFile,"LOADI ------ %lld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == STORE_I)
        fprintf(info_cps->outputFile,"STOREI ------- %lld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == ADD)
        fprintf(info_cps->outputFile,"ADD %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == SUB)
        fprintf(info_cps->outputFile,"SUB %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == SHIFT)
        fprintf(info_cps->outputFile,"SHIFT ------ %lld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == INC)
        fprintf(info_cps->outputFile,"INC %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == DEC)
        fprintf(info_cps->outputFile,"DEC %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == JUMP)
        fprintf(info_cps->outputFile,"JUMP %lld\n",asm_node->reg_1);
    else if(asm_node->asm_instr_e == JPOS)
        fprintf(info_cps->outputFile,"JPOS -------- %lld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == JZERO)
        fprintf(info_cps->outputFile,"JZERO %c %lld\n", (char)asm_node->reg_1, asm_node->reg_2);
    else if(asm_node->asm_instr_e == JNEG)
        fprintf(info_cps->outputFile,"JNEG ------ %lld\n", asm_node->instr_arg);

    else if(asm_node->asm_instr_e == SHR)
        fprintf(info_cps->outputFile,"SHR %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == SHL)
        fprintf(info_cps->outputFile,"SHL %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == RESET)
        fprintf(info_cps->outputFile,"RESET %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == JODD)
        fprintf(info_cps->outputFile,"JODD %c %lld\n", (char)asm_node->reg_1, asm_node->reg_2);
    
    else if(asm_node->asm_instr_e == HALT)
        fprintf(info_cps->outputFile,"HALT\n");
    else
        ;//fprintf(info_cps->outputFile,"type_e:\t\tnot in type_e\n");
    
    pc++;
    //puts("");
}




#else

static void Cplr_PrintAsmAsInstr_nowy(
    Cplr_info_cps info_cps,
    Asm_node_ps asm_node
)
{
    static Asm_val pc = 0;

    if(NULL == asm_node)
    {
        return;
    }

    if(asm_node->asm_instr_e == EMPTY_INSTR)
        ;//fprintf(info_cps->outputFile,"EMPTY_INSTR\n");
    else if(asm_node->asm_instr_e == GET)
        fprintf(info_cps->outputFile,"GET %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == PUT)
        fprintf(info_cps->outputFile,"PUT %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == LOAD)
        fprintf(info_cps->outputFile,"LOAD %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == STORE)
        fprintf(info_cps->outputFile,"STORE %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == LOAD_I)
        fprintf(info_cps->outputFile,"LOADI ------ %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == STORE_I)
        fprintf(info_cps->outputFile,"STOREI ------- %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == ADD)
        fprintf(info_cps->outputFile,"ADD %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == SUB)
        fprintf(info_cps->outputFile,"SUB %c %c\n", (char)asm_node->reg_1, (char)asm_node->reg_2);
    else if(asm_node->asm_instr_e == SHIFT)
        fprintf(info_cps->outputFile,"SHIFT ------ %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == INC)
        fprintf(info_cps->outputFile,"INC %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == DEC)
        fprintf(info_cps->outputFile,"DEC %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == JUMP)
        fprintf(info_cps->outputFile,"JUMP %ld\n",asm_node->reg_1);
    else if(asm_node->asm_instr_e == JPOS)
        fprintf(info_cps->outputFile,"JPOS -------- %ld\n",asm_node->instr_arg);
    else if(asm_node->asm_instr_e == JZERO)
        fprintf(info_cps->outputFile,"JZERO %c %ld\n", (char)asm_node->reg_1, asm_node->reg_2);
    else if(asm_node->asm_instr_e == JNEG)
        fprintf(info_cps->outputFile,"JNEG ------ %ld\n", asm_node->instr_arg);

    else if(asm_node->asm_instr_e == SHR)
        fprintf(info_cps->outputFile,"SHR %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == SHL)
        fprintf(info_cps->outputFile,"SHL %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == RESET)
        fprintf(info_cps->outputFile,"RESET %c\n", (char)asm_node->reg_1);
    else if(asm_node->asm_instr_e == JODD)
        fprintf(info_cps->outputFile,"JODD %c %ld\n", (char)asm_node->reg_1, asm_node->reg_2);
    
    else if(asm_node->asm_instr_e == HALT)
        fprintf(info_cps->outputFile,"HALT\n");
    else
        ;//fprintf(info_cps->outputFile,"type_e:\t\tnot in type_e\n");
    
    pc++;
    //puts("");
}

#endif



static Asm_node_ps Cplr_Code(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_cps
)
{
    Asm_node_ps asm_head_ps = NULL;
    switch(cmd_cs.type_e)
    {
        case CMD_DO:       break;
        case CMD_WHILE_DO: break;
        case CMD_ENDDO:    Cplr_ENDDO_nowy(info_cps, cmd_cs, ct_node_cps);    break;

        case CMD_WHILE:    Cplr_WHILE_nowy(info_cps, cmd_cs, ct_node_cps);    break;
        case CMD_ENDWHILE: Cplr_ENDWHILE_nowy(info_cps, cmd_cs, ct_node_cps); break;
        
        case CMD_END: ERROR_PRINT("Never should have come here!"); break;

        case CMD_FOR:        Cplr_FOR_nowy(info_cps, cmd_cs, ct_node_cps);    break;
        case CMD_FOR_DOWNTO: Cplr_FOR_nowy(info_cps, cmd_cs, ct_node_cps);    break;
        case CMD_ENDFOR:     Cplr_ENDFOR_nowy(info_cps, cmd_cs, ct_node_cps); break;

        case CMD_IF:    Cplr_IF_nowy(info_cps, cmd_cs, ct_node_cps);      break;
        case CMD_ELSE:  Cplr_ELSE_nowy(info_cps, cmd_cs, ct_node_cps);    break;
        case CMD_ENDIF: Cplr_END_IF_nowy(info_cps, cmd_cs, ct_node_cps);  break;

        case CMD_ASSIGN: Cplr_ASSIGN_nowy(info_cps, cmd_cs, ct_node_cps); break;
        
        case CMD_READ:   Cplr_READ_nowy(info_cps, cmd_cs, ct_node_cps);   break;
        case CMD_WRITE:  Cplr_WRITE_nowy(info_cps, cmd_cs, ct_node_cps);  break;

        case CMD_EMPTY: break;
        default: ERROR_PRINT("Unknown cmd type"); break;
    }

    return asm_head_ps;
}


static void Cplr_InsertCode(
    Asm_node_ps asm_ps,
    Ct_node_ps ct_node_ps
)
{
    ct_node_ps->asm_code_head_ps = asm_ps;
    
    Asm_node_ps tmp_ps = asm_ps;
    Cplr_val len = VAL_ZERO;
    while(NULL != tmp_ps)
    {
        len++;
        tmp_ps = tmp_ps->next_ps;
    }
    
    ct_node_ps->asm_code_length = len;
}

static void Cplr_JumpCorrect(
    Ct_node_ps ct_end_of_branch_ps
)
{
    // Ct_node_ps end_ps = ct_end_of_branch_ps;
    // Ct_node_ps head_ps = Ct_HeadOfBranch(ct_end_of_branch_ps);
    // Ct_node_ps tmp_ps = head_ps;
    // Cplr_val asm_len = Cplr_AsmLenCodeInScope(head_ps->next_ps, end_ps);
    
    // // tutaj asm_len jest długością kodów np. między FOR a ENDFOR,
    // // nie wliczajać do tego dlugosci kodu w FOR i ENDFOR

    // printf("TEGO JESZCZE NIE ZROBILES BO CZEKASZ NA INSTRUKCJE OTWIERAJACE BRANCHE\n");
    // printf("TEGO JESZCZE NIE ZROBILES BO CZEKASZ NA INSTRUKCJE OTWIERAJACE BRANCHE\n");
    // printf("TEGO JESZCZE NIE ZROBILES BO CZEKASZ NA INSTRUKCJE OTWIERAJACE BRANCHE\n");

    return;
}

static Cplr_val Cplr_AsmLenCodeInScope(
    Ct_node_ps head_ps,
    Ct_node_ps tail_ps
)
{
    if(NULL == head_ps)
    {
        return VAL_ZERO;
    }

    if(head_ps == tail_ps)
    {
        return VAL_ZERO;
    }

    Asm_node_ps asm_ps = head_ps->asm_code_head_ps;
    Cplr_val asm_len = VAL_ZERO;
    while(NULL != asm_ps)
    {
        asm_len++;
        asm_ps = asm_ps->next_ps;
    }

    if(TRUE == head_ps->is_branch)
    {
        asm_len += Cplr_AsmLenCodeInScope(head_ps->branch_ps, tail_ps);
        asm_len += Cplr_AsmLenCodeInScope(head_ps->next_ps, tail_ps);
    }
    else
    {
        asm_len += Cplr_AsmLenCodeInScope(head_ps->next_ps, tail_ps);
    }

    return asm_len;
}



static void Cplr_READ_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    
    Cplr_registers_e dest = a;
    Cplr_registers_e tmp_reg = b;

    Cplr_SetRegToRamAddressOfPid_nowy(
        info_cps,
        ct_node_ps,
        dest,
        cmd_cs.pid_1_ps,
        cmd_cs.index_1_ps,
        tmp_reg
    );

    Asm_GET_nowy(dest, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}


static void Cplr_WRITE(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    // Asm_node_ps asm_ps = NULL;

    Pid_node_ps pid_ps = cmd_cs.pid_1_ps;
    Pid_node_ps index_ps = cmd_cs.index_1_ps;

    Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);

    // Cplr_PrintRam(info_cps);
    // printf("in_dest = %ld\n", ramids_s.id_dest);
    // printf("id_dest_in = %ld\n", ramids_s.id_dest_in);
    // printf("id_A = %ld\n", ramids_s.id_A);
    // printf("id_A_in = %ld\n", ramids_s.id_A_in);
    // printf("id_B = %ld\n", ramids_s.id_B);
    // printf("id_B_in = %ld\n", ramids_s.id_B_in);
    

    Asm_node_ps asm_ps = NULL;

    if(TYPE_ARRAY == cmd_cs.pid_1_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_1_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_dest_in, &asm_ps);
        }
        else
        {
            Asm_LOAD(ramids_s.id_dest, &asm_ps);
        }
    }
    else
    {
        Asm_LOAD(ramids_s.id_dest, &asm_ps);
    }
    Asm_PUT(0, &asm_ps);

    Cplr_AddAsmCode(ct_node_ps, asm_ps);

    

    // Cplr_PrintAsmAsInstructions(ct_node_ps);
    // exit(0);


    
    // if(TYPE_ARRAY == pid_ps->type_e)
    // {
    //     Ram_node_ps ram_node_ps = Ram_FindByPid(info_cps->ram_head_ps, pid_ps);
    //     if(NULL != ram_node_ps)
    //     {
    //         Ram_id ram_id = Cplr_LoadToP0ArrayIndex(info_cps, ct_node_ps, pid_ps, index_ps);
    //         Asm_LOAD_I(ram_id, &asm_ps);
    //     }
       
    //     Asm_PUT(0, &asm_ps);
    // }
    // else
    // {
    //     if(TYPE_NUMBER != pid_ps->type_e)
    //     {
    //         Ram_node_ps ram_node_ps = Ram_FindByPid(info_cps->ram_head_ps, pid_ps);
    //         if(NULL != ram_node_ps)
    //         {
    //             Ram_id id_ram = Ram_Adr(info_cps, pid_ps, ct_node_ps);
    //             Asm_LOAD(id_ram, &asm_ps);
    //         }
    //         Asm_PUT(0, &asm_ps);
    //     }
    //     else
    //     {
    //         Asm_node_ps asm_num_ps = Asm_NumberGenerator(info_cps, pid_ps->value, ct_node_ps);
    //         Cplr_AddAsmCode(ct_node_ps, asm_num_ps);
    //         Asm_PUT(0, &asm_ps);
    //     }
    // }

}


static void Cplr_WRITE_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    
    Cplr_registers_e reg_to_write = a;
    Cplr_registers_e tmp_reg = b;

    if(TYPE_NUMBER != cmd_cs.pid_1_ps->type_e)
    {
        Cplr_SetRegToRamAddressOfPid_nowy(
            info_cps,
            ct_node_ps,
            reg_to_write,
            cmd_cs.pid_1_ps,
            cmd_cs.index_1_ps,
            tmp_reg
        );
    }
    else
    {
        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    cmd_cs.pid_1_ps->value,
                    ct_node_ps,
                    reg_to_write
                );

        Asm_RESET_nowy(tmp_reg, &asm_ps);
        Asm_STORE_nowy(reg_to_write, tmp_reg, &asm_ps);
        reg_to_write = tmp_reg;
    }
    Asm_PUT_nowy(reg_to_write, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}

static void Cplr_ASSIGN_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    /*if(!Cplr_ArraysHaveIndexes_nowy(cmd_cs))
    {
        printf("wrong usage of array");
        exit(0);
    }*/

    /*printf("###### cmd pid1: %p\n",cmd_cs.pid_1_ps);
    printf("###### cmd ind1: %p\n",cmd_cs.index_1_ps);
    printf("###### cmd pid2: %p\n",cmd_cs.pid_2_ps);
    printf("###### cmd ind2: %p\n",cmd_cs.index_2_ps);
    printf("###### cmd pid3: %p\n",cmd_cs.pid_3_ps);
    printf("###### cmd ind3: %p\n",cmd_cs.index_3_ps);*/



    if(NULL == Ram_FindByPid(info_cps->ram_head_ps, cmd_cs.pid_1_ps))
    {
       Ram_id ram_id_1st = Ram_Adr(info_cps, cmd_cs.pid_1_ps, ct_node_ps);
       Ram_Init(info_cps, ct_node_ps, cmd_cs.pid_1_ps);
    }

    switch(cmd_cs.expression_e)
    {
        case EXPR_PLUS:  Cplr_PLUS_nowy(info_cps, cmd_cs, ct_node_ps);  break;
        case EXPR_MINUS: Cplr_MINUS_nowy(info_cps, cmd_cs, ct_node_ps); break;
        case EXPR_TIMES: Cplr_TIMES_nowy(info_cps, cmd_cs, ct_node_ps); break;
        case EXPR_DIV:   Cplr_DIV_nowy(info_cps, cmd_cs, ct_node_ps);   break;
        case EXPR_MOD:   Cplr_MOD_nowy(info_cps, cmd_cs, ct_node_ps);   break;

        case EXPR_NOTAPPLICABLE: Cplr_CONST_nowy(info_cps, cmd_cs, ct_node_ps); break;
        default: ERROR_PRINT("Unknown expr in assign"); break;
    }
}


static bool Cplr_ArraysHaveIndexes_nowy(
    Cmd_command_cs cmd_cs
)
{
    if( NULL != cmd_cs.pid_1_ps &&
        TYPE_ARRAY == cmd_cs.pid_1_ps->type_e &&
        NULL == cmd_cs.index_1_ps
    )
    {
        return FALSE;
    }

    if( NULL != cmd_cs.pid_2_ps &&
        TYPE_ARRAY == cmd_cs.pid_2_ps->type_e &&
        NULL == cmd_cs.index_2_ps
    )
    {
        return FALSE;
    }

    if( NULL != cmd_cs.pid_3_ps &&
        TYPE_ARRAY == cmd_cs.pid_3_ps->type_e &&
        NULL == cmd_cs.index_3_ps
    )
    {
        return FALSE;
    }

    return TRUE;
}



static void Cplr_IF_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    /*
    // Cplr_PrintRam(info_cps);
    // printf("in_dest = %ld\n", ramids_s.id_dest);
    // printf("id_dest_in = %ld\n", ramids_s.id_dest_in);
    // printf("id_A = %ld\n", ramids_s.id_A);
    // printf("id_A_in = %ld\n", ramids_s.id_A_in);
    // printf("id_B = %ld\n", ramids_s.id_B);
    // printf("id_B_in = %ld\n", ramids_s.id_B_in);
    // Cplr_PrintAsmAsInstructions(ct_node_ps);
    // exit(0);
*/
    Asm_node_ps asm_ps = NULL;
    //Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);

    Cplr_registers_e A = a;
    Cplr_registers_e B = b;
    Cplr_registers_e C = c;

    Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, A, cmd_cs.pid_1_ps, cmd_cs.index_1_ps, b
    );
    Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, B, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, c
    );

    if(COND_NOTAPPLICABLE == cmd_cs.condition_e)
    {
        ERROR_PRINT("if with not applicable cond");
    }
    else if(COND_EQ == cmd_cs.condition_e)
    {
        asm_ps = Asm_EQ_nowy(A, B, C);
    }
    else if(COND_NEQ == cmd_cs.condition_e)
    {
        asm_ps = Asm_NEQ_nowy(A, B, C);
    }
    else if(COND_LE == cmd_cs.condition_e)
    {
        asm_ps = Asm_LE_nowy(A, B);
    }
    else if(COND_GE == cmd_cs.condition_e)
    {
        asm_ps = Asm_GE_nowy(A, B);
    }
    else if(COND_LEQ == cmd_cs.condition_e)
    {
        asm_ps = Asm_LEQ_nowy(A, B, C);
    }
    else if(COND_GEQ == cmd_cs.condition_e)
    {
        asm_ps = Asm_GEQ_nowy(A, B, C);
    }
    else
    {
        ERROR_PRINT("Wrong cond in if");
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}



static void Cplr_ELSE_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Ct_node_ps ct_if_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if(CMD_IF != ct_if_node_ps->command_s.type_e)
    {
        ERROR_PRINT("Else of branch withou IF");
    }

    Asm_index code_len = Asm_CodeLen(ct_if_node_ps->next_ps, ct_node_ps);

    Asm_node_ps asm_ps = Asm_LastAsmNode(ct_if_node_ps);
    if(NULL == asm_ps)
    {
        ERROR_PRINT("If without asm code");
    }
    asm_ps->instr_arg = code_len + 2;

    asm_ps = NULL;
    Asm_JUMP_nowy(-100000, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
/*
    puts("GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
    printf("ct_node: %p\n", ct_node_ps);
    Cplr_PrintAsmAsInstructions(ct_node_ps);*/
}



static void Cplr_END_IF_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_index code_len = -1;
    Ct_node_ps ct_if_node_ps = Ct_HeadOfBranch(ct_node_ps);
    Ct_node_ps ct_tmp_ps = ct_if_node_ps;
    while(NULL != ct_tmp_ps &&
          CMD_ELSE != ct_tmp_ps->command_s.type_e
    )
    {
        ct_tmp_ps = ct_tmp_ps->next_ps;
    }

 
    Ct_node_ps ct_node_else = NULL;
    if(NULL != ct_tmp_ps)
    {
        if(CMD_ELSE == ct_tmp_ps->command_s.type_e)
        {
            /*puts("+++$$$$++");
            Cplr_PrintAsmAsInstructions(ct_tmp_ps);
            puts("+++++$$$$+++");*/
            code_len = Asm_CodeLen(ct_tmp_ps, ct_if_node_ps);
            ct_tmp_ps->asm_code_head_ps->instr_arg = code_len;
            ct_tmp_ps->asm_code_head_ps->reg_1 = code_len;

            /*printf("CODE LEN ^^^^^^^^^^^^^^^^ %ld\n",code_len);

            puts("+++$$$$++");
            Cplr_PrintAsmAsInstructions(ct_tmp_ps->ne);
            puts("+++++$$$$+++");*/

            ct_node_else = ct_tmp_ps;
            //return;
        }
    }
    
    ct_if_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if(CMD_IF != ct_if_node_ps->command_s.type_e)
    {
        ERROR_PRINT("endif of branch withou IF");
    }
    
    if(NULL == ct_node_else)
    {
        code_len = Asm_CodeLen(ct_if_node_ps->next_ps, ct_node_ps);
    }
    else
    {
        code_len = Asm_CodeLen(ct_if_node_ps->next_ps, ct_node_else) + 1;
    }
    
    Asm_node_ps asm_ps = Asm_LastAsmNode(ct_if_node_ps);
    if(NULL == asm_ps)
    {
        ERROR_PRINT("If without asm code");
    }
    asm_ps->instr_arg = code_len + 1;
    if(JZERO == asm_ps->asm_instr_e)
    {
        asm_ps->reg_2 = code_len + 1;
    }
    else if(JUMP == asm_ps->asm_instr_e)
    {
        asm_ps->reg_1 = code_len + 1;
    }
    else
    {   
        printf("asm_ps->asm_instr_e: %d\n",asm_ps->asm_instr_e);
        ERROR_PRINT("unexpected instruction of condition");
    }
}



static void Cplr_WHILE(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Cplr_IF(info_cps, cmd_cs, ct_node_ps);
}

static void Cplr_WHILE_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Cplr_IF_nowy(info_cps, cmd_cs, ct_node_ps);
}


static void Cplr_ENDWHILE(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Ct_node_ps ct_while_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if(CMD_WHILE != ct_while_node_ps->command_s.type_e)
    {
        ERROR_PRINT("Endwhile of branch without while");
    }

    Asm_index code_len = Asm_CodeLen(ct_while_node_ps->next_ps, ct_node_ps);

    Asm_node_ps asm_ps = Asm_LastAsmNode(ct_while_node_ps);
    if(NULL == asm_ps)
    {
        ERROR_PRINT("while without asm code");
    }
    asm_ps->instr_arg = code_len + 2;
    
    asm_ps = NULL;
    code_len = Asm_CodeLen(ct_while_node_ps, ct_node_ps);
    Asm_JUMP(-code_len, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
}

static void Cplr_ENDWHILE_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Ct_node_ps ct_while_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if(CMD_WHILE != ct_while_node_ps->command_s.type_e)
    {
        ERROR_PRINT("Endwhile of branch without while");
    }
    Asm_node_ps asm_jump_cond_unfulfilled = Asm_LastAsmNode(ct_while_node_ps);
    if(NULL == asm_jump_cond_unfulfilled)
    {
        ERROR_PRINT("while loop asm is empty");
    }
   
    Asm_index code_len = Asm_CodeLen(ct_while_node_ps->next_ps, ct_node_ps);
    if(JZERO == asm_jump_cond_unfulfilled->asm_instr_e)
    {
        asm_jump_cond_unfulfilled->reg_2 = code_len + 2;
    }
    else if(JUMP == asm_jump_cond_unfulfilled->asm_instr_e)
    {
        asm_jump_cond_unfulfilled->reg_1 = code_len + 2;
    }
    else
    {   
        printf("asm_ps->asm_instr_e: %d\n",asm_jump_cond_unfulfilled->asm_instr_e);
        ERROR_PRINT("unexpected instruction of while loop");
    }

    Asm_node_ps asm_while_last_code_ps = Asm_LastAsmNode(ct_while_node_ps);
    if(NULL == asm_while_last_code_ps)
    {
        ERROR_PRINT("while without asm code");
    }
    asm_while_last_code_ps->instr_arg = code_len;
    asm_while_last_code_ps = NULL;
    
    Asm_node_ps asm_ps = NULL;
    code_len = Asm_CodeLen(ct_while_node_ps, ct_node_ps);
    Asm_JUMP_nowy(-code_len, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}


static void Cplr_ENDDO(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Cplr_IF(info_cps, cmd_cs, ct_node_ps);

    Ct_node_ps ct_do_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if(CMD_DO != ct_do_node_ps->command_s.type_e)
    {
        ERROR_PRINT("Endwhile of branch without while");
    }

    Asm_index code_len = Asm_CodeLen(ct_do_node_ps->next_ps, ct_node_ps);
    Asm_node_ps asm_ps = ct_node_ps->asm_code_head_ps;
    while(NULL != asm_ps)
    {
        code_len++;
        asm_ps = asm_ps->next_ps;
    }
    
    asm_ps = Asm_LastAsmNode(ct_node_ps);
    if(NULL == asm_ps)
    {
        ERROR_PRINT("while without asm code");
    }
    asm_ps->prev_ps->instr_arg = -code_len + 2;
    asm_ps->prev_ps->next_ps = NULL;
    free(asm_ps);
}


static void Cplr_ENDDO_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Cplr_IF_nowy(info_cps, cmd_cs, ct_node_ps);

    Ct_node_ps ct_do_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if(CMD_DO != ct_do_node_ps->command_s.type_e)
    {
        ERROR_PRINT("End of dowhile without dowhile");
    }

    Ct_node_ps ct_tmp_ps = Ct_HeadOfBranch(ct_node_ps);
    while(NULL != ct_tmp_ps->next_ps)
    {
        ct_tmp_ps = ct_tmp_ps->next_ps;
    }


    if(CMD_ENDDO != ct_node_ps->command_s.type_e)
    {
        ERROR_PRINT("DoWhile without end of while");
    }

    Asm_index code_len = Asm_CodeLen(ct_do_node_ps, NULL);
    
    Asm_node_ps asm_ps = Asm_LastAsmNode(ct_node_ps);
    if(NULL == asm_ps)
    {
        ERROR_PRINT("repeat until without asm code");
    }

    if(JZERO == asm_ps->asm_instr_e)
    {
        asm_ps->reg_2 = -(code_len - 1);
    }
    else if(JUMP == asm_ps->asm_instr_e)
    {
        asm_ps->reg_1 = -(code_len - 1);
    }
    else
    {   
        printf("asm_ps->asm_instr_e: %d\n",asm_ps->asm_instr_e);
        ERROR_PRINT("unexpected instruction of condition");
    }

    //asm_ps = NULL;
    //Asm_JUMP_nowy(-(code_len), &asm_ps);
    //Cplr_AddAsmCode(ct_node_ps, asm_ps);
    //asm_ps = NULL;
}





static void Cplr_FOR(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    (void)Ram_Adr(info_cps, cmd_cs.pid_1_ps, ct_node_ps);

    // Cplr_PrintRam(info_cps);
    // printf("in_dest = %ld\n", ramids_s.id_dest);
    // printf("id_dest_in = %ld\n", ramids_s.id_dest_in);
    // printf("id_A = %ld\n", ramids_s.id_A);
    // printf("id_A_in = %ld\n", ramids_s.id_A_in);
    // printf("id_B = %ld\n", ramids_s.id_B);
    // printf("id_B_in = %ld\n", ramids_s.id_B_in);
    // Cplr_PrintAsmAsInstructions(ct_node_ps);
    // exit(0);

    

    Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);
    Asm_node_ps asm_ps = NULL;

    Ram_id id_of_start = -1;
    Ram_id id_of_limit = -1;
    if(TYPE_NUMBER != cmd_cs.pid_3_ps->type_e)
    {
        id_of_limit = Ram_Alloc(info_cps, 1);

        if(TYPE_ARRAY == cmd_cs.pid_3_ps->type_e)
        {
            if(TYPE_NUMBER != cmd_cs.index_3_ps->type_e)
            {
                Asm_LOAD_I(ramids_s.id_B_in, &asm_ps);
            }
            else
            {
                Asm_LOAD(ramids_s.id_B, &asm_ps);
            }
        }
        else
        {
            Asm_LOAD(ramids_s.id_B, &asm_ps);
        }

        Asm_STORE(id_of_limit, &asm_ps);
    }
    else
    {
        id_of_limit = ramids_s.id_B;
    }
    
    if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_2_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_A_in, &asm_ps);
        }
        else
        {
            Asm_LOAD(ramids_s.id_A, &asm_ps);
        }
    }
    else
    {
        Asm_LOAD(ramids_s.id_A, &asm_ps);
    }
    
    Asm_STORE(ramids_s.id_dest, &asm_ps);
   
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;

    if(CMD_FOR == ct_node_ps->command_s.type_e)
    {
        //asm_ps = Asm_LE(ramids_s.id_dest, id_of_limit);
        asm_ps = Asm_LEQ(ramids_s.id_dest, id_of_limit);
    }
    else if(CMD_FOR_DOWNTO == ct_node_ps->command_s.type_e)
    {
        //asm_ps = Asm_GE(ramids_s.id_dest, id_of_limit);
        asm_ps = Asm_GEQ(ramids_s.id_dest, id_of_limit);
    }
    else
    {
        ERROR_PRINT("Wrong cmd in for");
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
}




static Pid_node_s* Cplr_LastPid_new(
    Pid_node_s ** listHead_cpps
)
{
    Pid_node_s *tmp_ps = *listHead_cpps;
    while(tmp_ps->next_ps != NULL)
    {
        tmp_ps = tmp_ps->next_ps;
    }

   return tmp_ps;
}



static void Cplr_FOR_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;

    Cplr_registers_e A = a;
    Cplr_registers_e B = b;
    Cplr_registers_e C = c;
    Cplr_registers_e D = d;

    /* tutaj ustalam na stale limid pid3 w ram*/ 

    Pid_AddToList_Iterator(info_cps, cmd_cs.pid_3_ps->name_p);
    Ram_id ram_id_lim = Ram_Alloc(info_cps, 1);
    Pid_node_cps pid_lim = Cplr_LastPid_new(info_cps->pid_listHead_cpps);
    pid_lim->ram_address = ram_id_lim;
    pid_lim->type_e = TYPE_VARIABLE;
    pid_lim->status_e = STATUS_INITIALIZED;
    
    Cplr_SetRegToValueOfPid_nowy(
        info_cps, ct_node_ps, A, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, D
    );
    Cplr_SetRegToRamAddressOfPid_nowy(
            info_cps, ct_node_ps, B, pid_lim, NULL, D
    );
    Asm_STORE_nowy(A, B, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
   
    ct_node_ps->command_s.pid_3_ps = pid_lim;
    ct_node_ps->command_s.index_3_ps = NULL;

    
    /* teraz zwykly for */

    Cplr_SetRegToValueOfPid_nowy(
        info_cps, ct_node_ps, A, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, D
    );

    Cplr_SetRegToRamAddressOfPid_nowy(
            info_cps, ct_node_ps, B, cmd_cs.pid_1_ps, cmd_cs.index_1_ps, D
    );
    /*zamieniona A z B bo endfor robi ladowanie*/
    Asm_STORE_nowy(A, B, &asm_ps);
    Asm_RESET_nowy(B, &asm_ps);
    Asm_ADD_nowy(B, A, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;

    Cplr_SetRegToValueOfPid_nowy(
            info_cps,
            ct_node_ps,
            C,
            ct_node_ps->command_s.pid_3_ps,
            ct_node_ps->command_s.index_3_ps,
            D
    );

    if(CMD_FOR == ct_node_ps->command_s.type_e)
    {
        asm_ps = Asm_LEQ_nowy(B, C, D);
    }
    else if(CMD_FOR_DOWNTO == ct_node_ps->command_s.type_e)
    {
        asm_ps = Asm_GEQ_nowy(B, C, D);
    }
    else
    {
        ERROR_PRINT("Wrong cmd in for");
    }
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}


/* nowy
static void Cplr_ENDFOR(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Ct_node_ps ct_for_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if( CMD_FOR != ct_for_node_ps->command_s.type_e &&
        CMD_FOR_DOWNTO != ct_for_node_ps->command_s.type_e
    )
    {
        ERROR_PRINT("Endfor of branch without for");
    }

    Asm_index code_len = Asm_CodeLen(ct_for_node_ps->next_ps, ct_node_ps);

    Asm_node_ps asm_ps = Asm_LastAsmNode(ct_for_node_ps);
    if(NULL == asm_ps)
    {
        ERROR_PRINT("while without asm code");
    }
    asm_ps->instr_arg = code_len + 5;
    

    asm_ps = NULL;

    Ram_id ram_id_iter = ct_for_node_ps->command_s.pid_1_ps->ram_address;
    if(CMD_FOR == ct_for_node_ps->command_s.type_e)
    {
        Asm_LOAD(ram_id_iter, &asm_ps);
        Asm_INC(&asm_ps);
        Asm_STORE(ram_id_iter, &asm_ps);
    }
    else
    {
        Asm_LOAD(ram_id_iter, &asm_ps);
        Asm_DEC(&asm_ps);
        Asm_STORE(ram_id_iter, &asm_ps);
    }
    
    Asm_JUMP(-(code_len +2 + 4), &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
}
*/

static void Cplr_ENDFOR_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Ct_node_ps ct_for_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if( CMD_FOR != ct_for_node_ps->command_s.type_e &&
        CMD_FOR_DOWNTO != ct_for_node_ps->command_s.type_e
    )
    {
        ERROR_PRINT("Endfor of branch without for");
    }

    Cplr_registers_e A = a;
    Cplr_registers_e B = b;
    Cplr_registers_e C = c;
    Cplr_registers_e D = d;

    Cplr_SetRegToValueOfPid_nowy(
        info_cps,
        ct_node_ps,
        A,
        ct_for_node_ps->command_s.pid_1_ps,
        ct_for_node_ps->command_s.index_1_ps,
        D
    );

    /* 0 = 0 */
    Asm_node_ps asm_jump_0_0 = NULL;

    Cplr_SetRegToValueOfPid_nowy(
        info_cps,
        ct_node_ps,
        B,
        ct_for_node_ps->command_s.pid_3_ps,
        NULL,
        D
    );

    Asm_JZERO_nowy(A, 2, &asm_jump_0_0);
    Asm_JUMP_nowy(2, &asm_jump_0_0);
    Cplr_AddAsmCode(ct_node_ps, asm_jump_0_0);
    asm_jump_0_0 = NULL;

    Asm_JZERO_nowy(B, 100000, &asm_jump_0_0);
    Cplr_AddAsmCode(ct_node_ps, asm_jump_0_0);
    

    /* end 0 = 0 */


    Cplr_SetRegToRamAddressOfPid_nowy(
        info_cps,
        ct_node_ps,
        B,
        ct_for_node_ps->command_s.pid_1_ps,
        ct_for_node_ps->command_s.index_1_ps,
        D
    );



    Asm_node_ps asm_ps = NULL;

    if(CMD_FOR == ct_for_node_ps->command_s.type_e)
    {
        Asm_INC_nowy(A, &asm_ps);
    }
    else
    {
        Asm_DEC_nowy(A, &asm_ps);
    }
    
    Asm_STORE_nowy(A, B, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;

    asm_ps = Asm_FindLastSTOREinList_nowy(info_cps, ct_for_node_ps);
    Asm_val number_of_instr_after_STORE = Asm_NumberOfinstrAfterGiven_nowy(
        info_cps, ct_for_node_ps, asm_ps
    );
    asm_ps = NULL;

    Asm_index body_len = Asm_CodeLen(ct_for_node_ps->next_ps, NULL);
    Asm_index code_len = Asm_CodeLen(ct_for_node_ps->next_ps, NULL);
    Asm_node_ps asm_jump_out_of_for_ps = Asm_LastAsmNode(ct_for_node_ps);
    
    asm_jump_out_of_for_ps->reg_1 = code_len + 2;
    code_len = code_len + number_of_instr_after_STORE;

    Asm_JUMP_nowy(-(code_len), &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    //asm_ps = NULL;


    /* 0 = 0 korekcja jzero*/
    Asm_val count = VAL_ZERO;
    while(asm_ps->prev_ps != asm_jump_0_0)
    {
        count++;
        asm_ps = asm_ps->prev_ps;
    }
    asm_jump_0_0->reg_2 = count + 2;

    /* end 0 = 0 korekcja jzero */
}

static bool Cplr_NumberNotInRam(
    Cplr_info_cps info_cps,
    Pid_node_cps number_cps
)
{
    if(NULL == number_cps)
    {
        return TRUE;
    }

    bool if_generate_number = FALSE;
    if(TYPE_NUMBER == number_cps->type_e)
    {
        Ram_node_cps ram_head_cps = info_cps->ram_head_ps;
        Ram_node_ps ram_idx_ps = Ram_FindByPid(ram_head_cps, number_cps);

        if(NULL == ram_idx_ps)
        {
            if_generate_number = TRUE;
        }
    }
    
    return if_generate_number;
}


static Cplr_val Cplr_Abs(
    Cplr_val value
)
{
    if(VAL_ZERO > value)
    {
        value = value * (VAL_MINUS_ONE);
    }

    return value;
}


/*zwraca gdzie jest zapisana wartosc indeksu*/
static Asm_val Cplr_WriteInArrayAddress(
    Cplr_info_cps info_cps,
    Asm_val save_adr_in,
    Ct_node_ps ct_node_ps,
    Pid_node_ps array_ps,
    Pid_node_ps index_ps
)
{
    Asm_val store_in_adr = save_adr_in;

    if(TYPE_ARRAY == array_ps->type_e)
    {   
        Asm_node_ps asm_ps = NULL;
        // jezeli jest index jest null, albo nie znalazla w ram
        bool generate_number = Cplr_NumberNotInRam(info_cps, index_ps);
        
        Ram_id id_pid = Ram_Adr(info_cps, array_ps, ct_node_ps);
        Ram_id id_idx = -1;
        if(VAL_ZERO != index_ps->value)
        {
            id_idx = Ram_Adr(info_cps, index_ps, ct_node_ps);
        }
        
        if( generate_number &&
            0 != index_ps->value
        )
        {
            asm_ps = Asm_NumberGenerator_nowy(
                        info_cps, 
                        index_ps->value,
                        ct_node_ps,
                        f
                    );

            Asm_STORE(id_idx, &asm_ps);    // p[NumberPlaceInRam] = Number
        }

        if(0 != index_ps->value)
        {
            Asm_LOAD(array_ps->array_data_s.memory_address, &asm_ps); // p[0] = x (x = tab->array.memory_addres)
            Asm_ADD(id_idx, &asm_ps); // p[0] = x + index
            Asm_STORE(save_adr_in, &asm_ps); // p[1] = x + index
            
            store_in_adr = save_adr_in;
        }
        else
        {
            store_in_adr = array_ps->array_data_s.memory_address;
        }

        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        //Asm_AppendCode(&(ct_node_ps->asm_code_head_ps), asm_ps);
    }
    else
    {
        ERROR_PRINT("Not and array");
    }

    return store_in_adr;
}


static void Cplr_AddAsmCode(
    Ct_node_ps ct_node_ps,
    Asm_node_ps asm_ps
)
{
    if(NULL != asm_ps)
    {
        Asm_AppendCode(&(ct_node_ps->asm_code_head_ps), asm_ps);
    }
}


static Ram_id Cplr_LoadToP0ArrayIndex(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps,
    Pid_node_ps array_ps,
    Pid_node_ps index_ps
)
{
    Ram_id store_in_adr = -1;

    if(TYPE_ARRAY == array_ps->type_e)
    {   
        Asm_node_ps asm_ps = NULL;
        // jezeli jest index jest null, albo nie znalazla w ram
        bool generate_number = Cplr_NumberNotInRam(info_cps, index_ps);
        
        Ram_id id_pid = Ram_Adr(info_cps, array_ps, ct_node_ps);
        Ram_id id_idx = -1;
        if(VAL_ZERO != index_ps->value)
        {
            id_idx = Ram_Adr(info_cps, index_ps, ct_node_ps);
        }
        
        if( generate_number &&
            0 != index_ps->value
        )
        {
            asm_ps = Asm_NumberGenerator_nowy(
                        info_cps, 
                        index_ps->value,
                        ct_node_ps,
                        f
                    );

            Asm_STORE(id_idx, &asm_ps);    // p[NumberPlaceInRam] = Number
        }

        if(0 != index_ps->value)
        {
            Asm_LOAD(array_ps->array_data_s.memory_address, &asm_ps); // p[0] = x (x = tab->array.memory_addres)
            Asm_ADD(id_idx, &asm_ps); // p[0] = x + index
            store_in_adr = 0;
        }
        else
        {
            store_in_adr = array_ps->array_data_s.memory_address;
            //Asm_LOAD(array_ps->array_data_s.memory_address, &asm_ps);
        }

        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        //Asm_AppendCode(&(ct_node_ps->asm_code_head_ps), asm_ps);
    }
    else
    {
        ERROR_PRINT("Not and array");
    }

    return store_in_adr;
}


static void Cplr_TIMES_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    
    Cplr_registers_e iloczyn = f;
    Cplr_registers_e zapisz = a;
    Cplr_registers_e tmp_reg = d;

    Cplr_SetRegToRamAddressOfPid_nowy(
        info_cps,
        ct_node_ps,
        zapisz,
        cmd_cs.pid_1_ps,
        cmd_cs.index_1_ps,
        tmp_reg
    );

    if(Cplr_AllArgumentsAreNumbers(cmd_cs))
    {
        Cplr_val result = VAL_ZERO;

        if(VAL_ZERO != cmd_cs.pid_3_ps->value &&
            VAL_ZERO != cmd_cs.pid_2_ps->value
        )
        {
            result = cmd_cs.pid_2_ps->value * cmd_cs.pid_3_ps->value;        
        }

        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    result,
                    ct_node_ps,
                    iloczyn
                );
    }
    else if(Cplr_OneArgumentIs_2(cmd_cs))
    {
        iloczyn = c;
        if(VAL_TWO == cmd_cs.pid_2_ps->value)
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, iloczyn, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, tmp_reg
            );
        }
        else
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, iloczyn, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, tmp_reg
            );
        }
        Asm_SHL_nowy(iloczyn, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else if(Cplr_OneArgumentIs_1(cmd_cs))
    {
        if(VAL_ONE == cmd_cs.pid_2_ps->value)
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, iloczyn, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, tmp_reg
            );
        }
        else
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, iloczyn, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, tmp_reg
            );
        }
    }
    else
    {
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, b, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, tmp_reg
        );
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, c, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, tmp_reg
        );

        if(Cplr_ArgumentAreTheSame(cmd_cs))
        {
            asm_ps = Asm_TIMESWithoutSwapAndOneCheck_nowy(b, c, tmp_reg, iloczyn);
        }
        else
        {
            asm_ps = Asm_TIMES_nowy(b, c, tmp_reg, iloczyn);
        }

        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }

    Asm_STORE_nowy(iloczyn, zapisz, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}


static void Cplr_PLUS_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    
    Cplr_registers_e suma = b;
    Cplr_registers_e zapisz = a;

    Cplr_SetRegToRamAddressOfPid_nowy(
        info_cps,
        ct_node_ps,
        zapisz,
        cmd_cs.pid_1_ps,
        cmd_cs.index_1_ps,
        b
    );

    if(Cplr_AllArgumentsAreNumbers(cmd_cs))
    {
        Cplr_val result = VAL_ZERO;

        if(VAL_ZERO != cmd_cs.pid_3_ps->value &&
            VAL_ZERO != cmd_cs.pid_2_ps->value
        )
        {
            result = cmd_cs.pid_2_ps->value + cmd_cs.pid_3_ps->value;        
        }

        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    result,
                    ct_node_ps,
                    suma
                );
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else if(Cplr_OneArgumentIs_1(cmd_cs))
    {
        if(VAL_ONE == cmd_cs.pid_2_ps->value)
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, suma, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, c
            );
        }
        else
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, suma, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, c
            );
        }
        Asm_INC_nowy(suma, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else if(Cplr_ArgumentAreTheSame(cmd_cs))
    {
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, suma, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, c
        );
        Asm_SHL_nowy(suma, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else
    {
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, b, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, c
        );
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, c, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, d
        );
        
        asm_ps = Asm_PLUS_nowy(suma, c);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }

    Asm_STORE_nowy(suma, zapisz, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}


static void Cplr_MINUS_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    
    Cplr_registers_e roznica = b;
    Cplr_registers_e zapisz = a;
    Cplr_registers_e tmp_reg = d;

    Cplr_SetRegToRamAddressOfPid_nowy(
        info_cps,
        ct_node_ps,
        zapisz,
        cmd_cs.pid_1_ps,
        cmd_cs.index_1_ps,
        tmp_reg
    );

    if(Cplr_AllArgumentsAreNumbers(cmd_cs))
    {
        Cplr_val result = VAL_ZERO;

        if(VAL_ZERO != cmd_cs.pid_3_ps->value &&
            VAL_ZERO != cmd_cs.pid_2_ps->value
        )
        {
            result = cmd_cs.pid_2_ps->value - cmd_cs.pid_3_ps->value;
            if(VAL_ZERO > result)
            {
                result = VAL_ZERO;
            }
        }

        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    result,
                    ct_node_ps,
                    roznica
                );
    }
    else if(Cplr_OneArgumentIs_1(cmd_cs))
    {
        if(VAL_ONE == cmd_cs.pid_2_ps->value)
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, roznica, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, tmp_reg
            );
        }
        else
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, roznica, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, tmp_reg
            );
        }
        Asm_DEC_nowy(roznica, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else if(Cplr_ArgumentAreTheSame(cmd_cs))
    {
        /*Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, roznica, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, tmp_reg
        );*/
        Asm_RESET_nowy(roznica, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else
    {
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, b, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, tmp_reg
        );
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, c, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, tmp_reg
        );
        
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;

        asm_ps = Asm_MINUS_nowy(roznica, c);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }

    Asm_STORE_nowy(roznica, zapisz, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}


static void Cplr_DIV_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    
    Cplr_registers_e iloraz = e;
    Cplr_registers_e zapisz = a;
    Cplr_registers_e tmp_reg = d;

    Cplr_SetRegToRamAddressOfPid_nowy(
        info_cps,
        ct_node_ps,
        zapisz,
        cmd_cs.pid_1_ps,
        cmd_cs.index_1_ps,
        tmp_reg
    );

    if(Cplr_AllArgumentsAreNumbers(cmd_cs))
    {
        Cplr_val result = VAL_ZERO;

        if(VAL_ZERO != cmd_cs.pid_3_ps->value &&
            VAL_ZERO != cmd_cs.pid_2_ps->value
        )
        {
            result = cmd_cs.pid_2_ps->value / cmd_cs.pid_3_ps->value;
        }

        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    result,
                    ct_node_ps,
                    iloraz
                );
    }
    else if(Cplr_OneArgumentIs_2(cmd_cs))
    {
        iloraz = c;
        if(VAL_TWO == cmd_cs.pid_2_ps->value)
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, iloraz, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, tmp_reg
            );
        }
        else
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps, ct_node_ps, iloraz, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, tmp_reg
            );
        }
        Asm_SHR_nowy(iloraz, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else if(Cplr_ArgumentAreTheSame(cmd_cs))
    {
        Asm_RESET_nowy(iloraz, &asm_ps);
        Asm_INC_nowy(iloraz, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else
    {
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, b, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, tmp_reg
        );
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, c, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, tmp_reg
        );
        
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;

        asm_ps = Asm_MOD_nowy(b, c, tmp_reg, iloraz, f); /*b - reszta; e - wynik dzielenia*/
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }

    Asm_STORE_nowy(iloraz, zapisz, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}

static bool Cplr_AllArgumentsAreNumbers(
    Cmd_command_cs cmd_cs
)
{
    bool bothNumbers = FALSE;
    if(TYPE_NUMBER == cmd_cs.pid_2_ps->type_e)
    {
        if(TYPE_NUMBER == cmd_cs.pid_3_ps->type_e)
        {
            bothNumbers = TRUE;
        }
    }

    return bothNumbers;
}


static bool Cplr_OneArgumentIs_2(
    Cmd_command_cs cmd_cs
)
{
    bool oneIs2 = FALSE;
    if(TYPE_NUMBER == cmd_cs.pid_2_ps->type_e)
    {
        if(VAL_TWO == cmd_cs.pid_2_ps->value)
        {
            oneIs2 = TRUE;
        }
    }

    if(TYPE_NUMBER == cmd_cs.pid_3_ps->type_e)
    {
        if(VAL_TWO == cmd_cs.pid_3_ps->value)
        {
            oneIs2 = TRUE;
        }
    }

    return oneIs2;
}

static bool Cplr_OneArgumentIs_1(
    Cmd_command_cs cmd_cs
)
{
    bool oneIs1 = FALSE;
    if(TYPE_NUMBER == cmd_cs.pid_2_ps->type_e)
    {
        if(VAL_ONE == cmd_cs.pid_2_ps->value)
        {
            oneIs1 = TRUE;
        }
    }

    if(TYPE_NUMBER == cmd_cs.pid_3_ps->type_e)
    {
        if(VAL_ONE == cmd_cs.pid_3_ps->value)
        {
            oneIs1 = TRUE;
        }
    }

    return oneIs1;
}



static bool Cplr_ArgumentAreTheSame(
    Cmd_command_cs cmd_cs
)
{
    bool theSame = FALSE;

    Pid_node_cps pid_2 = cmd_cs.pid_2_ps;
    Pid_node_cps pid_3 = cmd_cs.pid_3_ps;

    if(pid_2 == pid_3)
    {
        if(TYPE_ARRAY == pid_2->type_e)
        {
            if(cmd_cs.index_2_ps == cmd_cs.index_3_ps)
            {
                theSame = TRUE;
            }
        }
        else
        {
            theSame = TRUE;
        }
    }

    return theSame;
}



static void Cplr_MOD_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    
    Cplr_registers_e zapisz = a;
    Cplr_registers_e reszta = b;
    Cplr_registers_e iloraz = e;

    Cplr_SetRegToRamAddressOfPid_nowy(
        info_cps,
        ct_node_ps,
        zapisz,
        cmd_cs.pid_1_ps,
        cmd_cs.index_1_ps,
        b
    );

    if(Cplr_AllArgumentsAreNumbers(cmd_cs))
    {
        Cplr_val result = VAL_ZERO;

        if(VAL_ZERO != cmd_cs.pid_3_ps->value &&
            VAL_ZERO != cmd_cs.pid_2_ps->value
        )
        {
            result = cmd_cs.pid_2_ps->value % cmd_cs.pid_3_ps->value;
        }

        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    result,
                    ct_node_ps,
                    reszta
                );
    }
    else
    {
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, b, cmd_cs.pid_2_ps, cmd_cs.index_2_ps, c
        );
        Cplr_SetRegToValueOfPid_nowy(
            info_cps, ct_node_ps, c, cmd_cs.pid_3_ps, cmd_cs.index_3_ps, d
        );
        
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;

        asm_ps = Asm_MOD_nowy(b, c, d, iloraz, f); /*b - reszta; e - wynik dzielenia*/
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }

    Asm_STORE_nowy(reszta, zapisz, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}


static void Cplr_SetRegToValueOfPid_nowy(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps,
    Cplr_registers_ce reg,
    Pid_node_cps pid,
    Pid_node_cps pid_index,
    Cplr_registers_ce reg_forIndex // this one is temp used only here
)
{
    Cplr_registers_ce tmp_reg = e;
    if(tmp_reg == reg || tmp_reg == reg_forIndex)
    {
        printf("reg: %d reg_index: %d\n",reg,reg_forIndex);
        ERROR_PRINT("Tmp reg overwrite");
    }

    Asm_node_ps asm_ps = NULL;

    if(TYPE_NUMBER == pid->type_e)
    {
        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    pid->value,
                    ct_node_ps,
                    reg
                );
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else if(TYPE_ARRAY == pid->type_e)
    {
        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    pid->ram_address,
                    ct_node_ps,
                    reg
                );
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;

        if(TYPE_NUMBER == pid_index->type_e)
        {
            asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    pid_index->value - pid->array_data_s.lower_lim,
                    ct_node_ps,
                    reg_forIndex
                );
            Cplr_AddAsmCode(ct_node_ps, asm_ps);
            asm_ps = NULL;
        }
        else
        {
            asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    pid_index->ram_address,
                    ct_node_ps,
                    reg_forIndex
                );
            Cplr_AddAsmCode(ct_node_ps, asm_ps);
            asm_ps = NULL;

            Asm_LOAD_nowy(reg_forIndex, reg_forIndex, &asm_ps);
            Cplr_AddAsmCode(ct_node_ps, asm_ps);
            asm_ps = NULL;

            asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    pid->array_data_s.lower_lim,
                    ct_node_ps,
                    tmp_reg
            );

            Asm_SUB_nowy(reg_forIndex, tmp_reg, &asm_ps);
            Cplr_AddAsmCode(ct_node_ps, asm_ps);
            asm_ps = NULL;
        }
        
        Asm_ADD_nowy(reg, reg_forIndex, &asm_ps);
        Asm_LOAD_nowy(reg, reg, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else
    {
        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    pid->ram_address,
                    ct_node_ps,
                    reg
                );
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;

        Asm_LOAD_nowy(reg, reg, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
}


static void Cplr_SetRegToRamAddressOfPid_nowy(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps,
    Cplr_registers_ce reg,
    Pid_node_cps pid,
    Pid_node_cps pid_index,
    Cplr_registers_ce reg_forIndex // this one is temp used only here
)
{
    Asm_node_ps asm_ps = NULL;

    Cplr_register_id reg_tmp = f;
    if( reg == reg_tmp ||
        reg_forIndex == reg_tmp
    )
    {
        ERROR_PRINT("Register overwrite");
    }

    if(TYPE_NUMBER == pid->type_e)
    {
        ERROR_PRINT("Cant assign ram to number");
        /*zamiast tego powinno byc szukanie pierwszego wolnego miejsca i przypisanie go do pid liczby*/
    }
    else if(TYPE_ARRAY == pid->type_e)
    {
        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    pid->ram_address,
                    ct_node_ps,
                    reg
                );
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;

        if(TYPE_NUMBER != pid_index->type_e)
        {
            Cplr_SetRegToValueOfPid_nowy(
                info_cps,
                ct_node_ps,
                reg_forIndex,
                pid_index,
                NULL,
                reg_tmp
            );

            if(VAL_ZERO != pid->array_data_s.lower_lim)
            {
                asm_ps = Asm_NumberGenerator_nowy(
                            info_cps,
                            pid->array_data_s.lower_lim,
                            ct_node_ps, 
                            reg_tmp
                        );
                Cplr_AddAsmCode(ct_node_ps, asm_ps);
                asm_ps = NULL;

                Asm_SUB_nowy(reg_forIndex, reg_tmp, &asm_ps);
                Cplr_AddAsmCode(ct_node_ps, asm_ps);
                asm_ps = NULL;
            }

            Asm_ADD_nowy(reg, reg_forIndex, &asm_ps);
            Cplr_AddAsmCode(ct_node_ps, asm_ps);
            asm_ps = NULL;
        }
        else
        {
            Pid_val ram_adr_offset = pid_index->value;

            if(VAL_ZERO != pid->array_data_s.lower_lim)
            {
                ram_adr_offset = pid_index->value - pid->array_data_s.lower_lim;
            }

            if(VAL_ZERO != pid_index->value)
            {
                asm_ps = Asm_NumberGenerator_nowy(
                            info_cps,
                            ram_adr_offset,
                            ct_node_ps, 
                            reg_forIndex
                        );
                Cplr_AddAsmCode(ct_node_ps, asm_ps);
                asm_ps = NULL;

                Asm_ADD_nowy(reg, reg_forIndex, &asm_ps);
                Cplr_AddAsmCode(ct_node_ps, asm_ps);
                asm_ps = NULL;
            }
        }
    }
    else
    {
        asm_ps = Asm_NumberGenerator_nowy(
                    info_cps,
                    pid->ram_address,
                    ct_node_ps,
                    reg
                );
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
}

static void Cplr_CONST_nowy(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;

    Cplr_SetRegToRamAddressOfPid_nowy(
        info_cps,
        ct_node_ps,
        a,
        cmd_cs.pid_1_ps,
        cmd_cs.index_1_ps,
        b
    );

    Cplr_SetRegToValueOfPid_nowy(
        info_cps,
        ct_node_ps,
        b,
        cmd_cs.pid_2_ps,
        cmd_cs.index_2_ps,
        c
    );

    /*if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    {
        Asm_LOAD_nowy(b, b, &asm_ps);
    }*/

    Asm_STORE_nowy(b, a, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}


static bool Cplr_NoValueSkipAssign(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs
)
{
    if( cmd_cs.pid_2_ps->type_e == TYPE_VARIABLE)
    {
        Ram_node_ps ram_pid_2_ps = Ram_FindByPid(
                                        info_cps->ram_head_ps,
                                        cmd_cs.pid_2_ps
                                    );
        if(NULL == ram_pid_2_ps)
        {
            return TRUE;
        }
    }

    if(cmd_cs.pid_3_ps->type_e == TYPE_VARIABLE)
    {
        Ram_node_ps ram_pid_3_ps = Ram_FindByPid(
                                        info_cps->ram_head_ps,
                                        cmd_cs.pid_3_ps
                                    );
        if(NULL == ram_pid_3_ps)
        {
            return TRUE;
        }
    }

    return FALSE;
}



static bool Cplr_SkipAssign(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs
)
{
    if( Cplr_CheckPidIfSkip(info_cps, cmd_cs.pid_1_ps, cmd_cs.index_1_ps) ||
        Cplr_CheckPidIfSkip(info_cps, cmd_cs.pid_2_ps, cmd_cs.index_2_ps) ||
        Cplr_CheckPidIfSkip(info_cps, cmd_cs.pid_3_ps, cmd_cs.index_3_ps)
    )
    {
        return TRUE;
    }

    return FALSE;
}

static bool Cplr_CheckPidIfSkip(
    Cplr_info_cps info_cps,
    Pid_node_ps pid_ps,
    Pid_node_ps idx_ps
)
{
    if(NULL == pid_ps)
    {
        return FALSE;
    }

    if(TYPE_ARRAY == pid_ps->type_e)
    {
        Ram_node_ps ram_pid_ps = Ram_FindByPid(info_cps->ram_head_ps, idx_ps);
        if( NULL == ram_pid_ps &&
            TYPE_NUMBER != idx_ps->type_e
        )
        {
            return TRUE;
        }
    }
    else if(TYPE_VARIABLE == pid_ps->type_e)
    {
        Ram_node_ps ram_pid_ps = Ram_FindByPid(info_cps->ram_head_ps, pid_ps);
        if( NULL == ram_pid_ps &&
            TYPE_NUMBER != pid_ps->type_e
        )
        {
            return TRUE;
        }
    }
    
    return FALSE;
}

static Cplr_ramids_s Cplr_RetRamIds(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Pid_node_cps pid_1_ps = cmd_cs.pid_1_ps;
    Pid_node_cps pid_2_ps = cmd_cs.pid_2_ps;
    Pid_node_cps pid_3_ps = cmd_cs.pid_3_ps;

    Pid_node_cps idx_1_ps = cmd_cs.index_1_ps;
    Pid_node_cps idx_2_ps = cmd_cs.index_2_ps;
    Pid_node_cps idx_3_ps = cmd_cs.index_3_ps;

    Cplr_ramids_s ramids_1_s = Cplr_RamIdForOneArg(
                                    info_cps,
                                    2,
                                    pid_1_ps,
                                    idx_1_ps,
                                    ct_node_ps
                                );
    Cplr_ramids_s ramids_2_s = Cplr_RamIdForOneArg(
                                    info_cps,
                                    3,
                                    pid_2_ps,
                                    idx_2_ps,
                                    ct_node_ps
                                );
    Cplr_ramids_s ramids_3_s = Cplr_RamIdForOneArg(
                                    info_cps,
                                    4,
                                    pid_3_ps,
                                    idx_3_ps,
                                    ct_node_ps
                                );
    Cplr_ramids_s raids_s = Cplr_CorrectRamids(ramids_1_s, ramids_2_s, ramids_3_s);

    return raids_s;
}

static Cplr_ramids_s Cplr_RamIdForOneArg(
    Cplr_info_cps info_cps,
    Ram_id ram_save_in,
    Pid_node_ps pid_ps,
    Pid_node_ps idx_ps,
    Ct_node_ps ct_node_ps
)
{
    Cplr_ramids_s raids_s = {
        .id_dest = -1,
        .id_dest_in = -1,
        .id_A = -1,
        .id_A_in = -1,
        .id_B = -1,
        .id_B_in = -1
    };

    if(NULL != pid_ps)
    {
        if(TYPE_ARRAY == pid_ps->type_e)
        {
            if(TYPE_NUMBER == idx_ps->type_e)
            {
                Ram_id id_of_zero = Ram_RetIdOfZero(info_cps, pid_ps);
                raids_s.id_dest = id_of_zero + idx_ps->value;
                /*TU*/
                if(VAL_ZERO < pid_ps->array_data_s.lower_lim)
                {
                    raids_s.id_dest -= pid_ps->array_data_s.lower_lim;
                }
                /*TU*/
            }
            else
            {
                raids_s.id_dest = -1;
                raids_s.id_dest_in = Cplr_RamAdr(
                                        info_cps,
                                        ram_save_in,
                                        pid_ps,
                                        idx_ps,
                                        ct_node_ps
                                    );
            }
        }
        else if(TYPE_NUMBER != pid_ps->type_e)
        {
            raids_s.id_dest = pid_ps->ram_address;
        }
        else
        {
            Ram_node_ps ram_num_ps = Ram_FindByPid(
                                        info_cps->ram_head_ps,
                                        idx_ps
                                    );
            if(NULL == ram_num_ps)
            {
                raids_s.id_dest = Ram_Adr(info_cps, pid_ps, ct_node_ps);

                Asm_node_ps asm_ps = Asm_NumberGenerator_nowy(
                                        info_cps, 
                                        pid_ps->value,
                                        ct_node_ps,
                                        f
                                    );
                Cplr_AddAsmCode(ct_node_ps, asm_ps);
                asm_ps = NULL;

                Asm_STORE(raids_s.id_dest, &asm_ps);

                Cplr_AddAsmCode(ct_node_ps, asm_ps);
                asm_ps = NULL;
            }
            else
            {
                raids_s.id_dest = ram_num_ps->id;
            }
        }
    }
    return raids_s;
}

static Cplr_ramids_s Cplr_CorrectRamids(
    Cplr_ramids_s ramids_1_s,
    Cplr_ramids_s ramids_2_s,
    Cplr_ramids_s ramids_3_s
)
{
    Cplr_ramids_s raids_s = {
        .id_dest = -1,
        .id_dest_in = -1,
        .id_A = -1,
        .id_A_in = -1,
        .id_B = -1,
        .id_B_in = -1
    };

    if(-1 != ramids_1_s.id_dest)
    {
        raids_s.id_dest = ramids_1_s.id_dest;
    }
    else if(-1 != ramids_1_s.id_dest_in)
    {
        raids_s.id_dest_in = ramids_1_s.id_dest_in;
    }

    if(-1 != ramids_2_s.id_dest)
    {
        raids_s.id_A = ramids_2_s.id_dest;
    }
    else if(-1 != ramids_2_s.id_dest_in)
    {
        raids_s.id_A_in = ramids_2_s.id_dest_in;
    }

    if(-1 != ramids_3_s.id_dest)
    {
        raids_s.id_B = ramids_3_s.id_dest;
    }
    else if(-1 != ramids_3_s.id_dest_in)
    {
        raids_s.id_B_in = ramids_3_s.id_dest_in;
    }

    return raids_s;
}

 /* tutaj  pid jest tablica, a index zmienną*/
static Ram_id Cplr_RamAdr(
    Cplr_info_cps info_cps,
    Ram_id ram_save_in,
    Pid_node_ps pid_ps,
    Pid_node_ps idx_ps,
    Ct_node_ps ct_node_ps
)// tab(x)
{//pid(index)
    Ram_id ram_id_idx = idx_ps->ram_address;
    Ram_id ram_id_pid = pid_ps->array_data_s.memory_address;
    
    Asm_node_ps asm_ps = NULL;
    //Asm_LOAD_I(ram_id_pid, &asm_ps);
    Asm_LOAD(ram_id_pid, &asm_ps);
    Asm_ADD(ram_id_idx, &asm_ps);
    Asm_STORE(ram_save_in, &asm_ps);

    Cplr_AddAsmCode(ct_node_ps, asm_ps);

    return ram_save_in;
}



static void Cplr_TIMES2(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    if(Cplr_NoValueSkipAssign(info_cps, cmd_cs))
    {
        return;
    }

    Asm_node_ps asm_ps = NULL;

    Ram_id adr_result = 1; // 1
    Ram_id adr_dest_stored_D = 2; // 1
    Ram_id ram_A = -1; // 1
    Ram_id ram_B = -1; // 1
    Ram_id ram_reg_1 = 3;
    Ram_id ram_reg_2 = 4;

    bool del_A = FALSE;
    bool del_B = FALSE;

    if(TYPE_ARRAY == cmd_cs.pid_1_ps->type_e)
    {
        Ram_id ram_id = Cplr_LoadToP0ArrayIndex(
                            info_cps,
                            ct_node_ps,
                            cmd_cs.pid_1_ps,
                            cmd_cs.index_1_ps
                        );
        asm_ps = NULL;
        if(0 != ram_id)
        {
            Asm_LOAD(ram_id, &asm_ps);
        }      
        Asm_STORE(adr_dest_stored_D, &asm_ps);
        
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else
    {
        adr_result = Ram_Adr(info_cps, cmd_cs.pid_1_ps, ct_node_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }

    if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    {
        del_A = TRUE;
        ram_A = Ram_Alloc(info_cps, 1);

        Asm_val store_in = Cplr_WriteInArrayAddress(
                                info_cps,
                                (Asm_val)3,
                                ct_node_ps,
                                cmd_cs.pid_2_ps,
                                cmd_cs.index_2_ps
                            );
        asm_ps = NULL;
        Asm_LOAD_I(3, &asm_ps);
        Asm_STORE(ram_A, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else
    {
        ram_A = Ram_Adr(info_cps, cmd_cs.pid_2_ps, ct_node_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }

    if(TYPE_ARRAY == cmd_cs.pid_3_ps->type_e)
    {
        del_B = TRUE;
        ram_B = Ram_Alloc(info_cps, 1); 

        Asm_val store_in = Cplr_WriteInArrayAddress(
                                info_cps,
                                (Asm_val)3,
                                ct_node_ps,
                                cmd_cs.pid_3_ps,
                                cmd_cs.index_3_ps
                            );
        asm_ps = NULL;
        Asm_LOAD_I(3, &asm_ps);
        Asm_STORE(ram_B, &asm_ps);

        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    else
    {
        ram_B = Ram_Adr(info_cps, cmd_cs.pid_3_ps, ct_node_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }
    
    //Cplr_AddAsmCode(ct_node_ps, asm_ps);

    Asm_node_ps head = Asm_TIMES(
                            adr_result,
                            ram_reg_1,
                            ram_A,
                            ram_reg_2,
                            ram_B,
                            info_cps,
                            ct_node_ps
                        );
    Cplr_AddAsmCode(ct_node_ps, head);

    if(1 == adr_result)
    {
        asm_ps = NULL;
        Asm_LOAD(adr_result, &asm_ps);
        Asm_STORE_I(adr_dest_stored_D, &asm_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;
    }

    if(del_A)
        Ram_DelById(info_cps, ram_A);
    
    if(del_B)
        Ram_DelById(info_cps, ram_B);
}

static void Cplr_TIMES(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;

    Ram_id adr_result = 2; // 1
    Ram_id ram_A = -1; // 1
    Ram_id ram_B = -1; // 1
    Ram_id ram_reg_1 = 5;
    Ram_id ram_reg_2 = 6;
    
    Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);

    if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_2_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_A_in, &asm_ps);
            Asm_STORE(3, &asm_ps);
            
            ram_A = 3;
        }
        else
        {
            //Asm_LOAD(ramids_s.id_A, &asm_ps);
            //Asm_STORE(3, &asm_ps)
            //ramids_s.id_A = 3;
            if(ramids_s.id_A == ramids_s.id_dest)
            {
                Asm_LOAD(ramids_s.id_A, &asm_ps);
                Asm_STORE(3, &asm_ps);
                ram_A = 3;
            }
            else
            {
                ram_A = ramids_s.id_A;
            }
        }
    }
    else
    {
        if(ramids_s.id_A == ramids_s.id_dest)
        {
            Asm_LOAD(ramids_s.id_A, &asm_ps);
            Asm_STORE(3, &asm_ps);
            ram_A = 3;
        }
        else
        {
            ram_A = ramids_s.id_A;
        }

        //Asm_LOAD(ramids_s.id_A, &asm_ps);
        //Asm_STORE(3, &asm_ps)
        //ramids_s.id_A = 3;
    }
    
    if(TYPE_ARRAY == cmd_cs.pid_3_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_3_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_B_in, &asm_ps);
            Asm_STORE(ramids_s.id_B_in, &asm_ps);

            ram_B = ramids_s.id_B_in;
        }
        else
        {
            //Asm_LOAD(ramids_s.id_B, &asm_ps);
            //Asm_STORE(4, &asm_ps)
            //ramids_s.id_A = 4;

            ram_B = ramids_s.id_B;
        }
    }
    else
    {
        //Asm_LOAD(ramids_s.id_B, &asm_ps);
        //Asm_STORE(4, &asm_ps)
        //ramids_s.id_A = 4;

        ram_B = ramids_s.id_B;
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;

    if(-1 == ramids_s.id_dest)
    {
        adr_result = 7;
        asm_ps = Asm_TIMES(adr_result, ram_reg_1, ram_A, ram_reg_2, ram_B, info_cps, ct_node_ps);
        Cplr_AddAsmCode(ct_node_ps, asm_ps);
        asm_ps = NULL;

        Asm_LOAD(adr_result, &asm_ps);
        Asm_STORE_I(ramids_s.id_dest_in, &asm_ps);
    }
    else
    {
        adr_result = ramids_s.id_dest;
        asm_ps = Asm_TIMES(adr_result, ram_reg_1, ram_A, ram_reg_2, ram_B, info_cps, ct_node_ps);

        //Asm_STORE(ramids_s.id_dest, &asm_ps);
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    //Cplr_PrintAsmAsInstructions(ct_node_ps); exit(0);
    asm_ps = NULL;
}



static void Cplr_PLUS(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);
    // printf("in_dest = %ld\n", ramids_s.id_dest);
    // printf("id_dest_in = %ld\n", ramids_s.id_dest_in);
    // printf("id_A = %ld\n", ramids_s.id_A);
    // printf("id_A_in = %ld\n", ramids_s.id_A_in);
    // printf("id_B = %ld\n", ramids_s.id_B);
    // printf("id_B_in = %ld\n", ramids_s.id_B_in);
    // //exit(0);


    if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_2_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_A_in, &asm_ps);
        }
        else
        {
            Asm_LOAD(ramids_s.id_A, &asm_ps);
        }
    }
    else
    {
        Asm_LOAD(ramids_s.id_A, &asm_ps);
    }
    
    if(TYPE_ARRAY == cmd_cs.pid_3_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_3_ps->type_e)
        {
            Asm_STORE(3, &asm_ps);
            Asm_LOAD_I(ramids_s.id_B_in, &asm_ps);
            Asm_ADD(3, &asm_ps);
        }
        else
        {
            Asm_ADD(ramids_s.id_B, &asm_ps);
        }
    }
    else
    {
        Asm_ADD(ramids_s.id_B, &asm_ps);
    }
    
    if(-1 == ramids_s.id_dest)
    {
        Asm_STORE_I(ramids_s.id_dest_in, &asm_ps);
    }
    else
    {
        Asm_STORE(ramids_s.id_dest, &asm_ps);
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    //Cplr_PrintAsmAsInstructions(ct_node_ps); exit(0);
    asm_ps = NULL;
}





static void Cplr_MINUS(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);
    Ram_id universal_id_B = -1;

    if(TYPE_ARRAY == cmd_cs.pid_3_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_3_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_B_in, &asm_ps);
            Asm_STORE(ramids_s.id_B_in, &asm_ps);
            universal_id_B = ramids_s.id_B_in;
        }
        else
        {
            universal_id_B = ramids_s.id_B;
            //Asm_LOAD(ramids_s.id_B, &asm_ps);
        }
    }
    else
    {
        universal_id_B = ramids_s.id_B;
        //Asm_LOAD(ramids_s.id_B, &asm_ps);
    }

    if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_2_ps->type_e)
        {
            //Asm_STORE(4, &asm_ps);
            Asm_LOAD_I(ramids_s.id_A_in, &asm_ps);
            Asm_SUB(universal_id_B, &asm_ps);
        }
        else
        {
            Asm_LOAD(ramids_s.id_A, &asm_ps);
            Asm_SUB(universal_id_B, &asm_ps);
        }
    }
    else
    {
        Asm_LOAD(ramids_s.id_A, &asm_ps);
        Asm_SUB(universal_id_B, &asm_ps);
    }


    // if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    // {
    //     if(TYPE_NUMBER != cmd_cs.index_2_ps->type_e)
    //     {
    //         Asm_LOAD_I(ramids_s.id_A_in, &asm_ps);
    //     }
    //     else
    //     {
    //         Asm_LOAD(ramids_s.id_A, &asm_ps);
    //     }
    // }
    // else
    // {
    //     Asm_LOAD(ramids_s.id_A, &asm_ps);
    // }
    
    // if(TYPE_ARRAY == cmd_cs.pid_3_ps->type_e)
    // {
    //     if(TYPE_NUMBER != cmd_cs.index_3_ps->type_e)
    //     {
    //         Asm_STORE(3, &asm_ps);
    //         Asm_LOAD_I(ramids_s.id_B_in, &asm_ps);
    //         Asm_SUB(3, &asm_ps);
    //     }
    //     else
    //     {
    //         Asm_SUB(ramids_s.id_B, &asm_ps);
    //     }
    // }
    // else
    // {
    //     Asm_SUB(ramids_s.id_B, &asm_ps);
    // }
    
    if(-1 == ramids_s.id_dest)
    {
        Asm_STORE_I(ramids_s.id_dest_in, &asm_ps);
    }
    else
    {
        Asm_STORE(ramids_s.id_dest, &asm_ps);
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}




static void Cplr_DIV(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    /* nowy
    Asm_node_ps asm_ps = NULL;

    Ram_id adr_result = 2; // 1
    Ram_id ram_A = -1; // 1
    Ram_id ram_B = -1; // 1
    Ram_id ram_reg_1 = 5;
    Ram_id ram_reg_2 = 6;
    
    Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);

   
    if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_2_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_A_in, &asm_ps);
            Asm_STORE(ramids_s.id_A_in, &asm_ps);
            
            ram_A = ramids_s.id_A_in;
        }
        else
        {
            ram_A = ramids_s.id_A;
        }
    }
    else
    {
        ram_A = ramids_s.id_A;
    }
    
    if(TYPE_ARRAY == cmd_cs.pid_3_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_3_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_B_in, &asm_ps);
            Asm_STORE(ramids_s.id_B_in, &asm_ps);

            ram_B = ramids_s.id_B_in;
        }
        else
        {
            ram_B = ramids_s.id_B;
        }
    }
    else
    {
        ram_B = ramids_s.id_B;
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;

    if(-1 == ramids_s.id_dest)
    {
        adr_result = 7;
        if( TYPE_NUMBER == cmd_cs.pid_3_ps->type_e &&
            2 == cmd_cs.pid_3_ps->value
        )
        {
            Asm_LOAD(ram_A, &asm_ps);
            //Asm_STORE(pA, &head_ps);
            
            Asm_SHIFT(9, &asm_ps);
            Cplr_AddAsmCode(ct_node_ps, asm_ps);
             asm_ps = NULL;
        }
        else
        {
            Asm_node_ps div_asm_ps = Asm_DIV(adr_result, ram_A, ram_B, ram_reg_1, ram_reg_2);
            Cplr_AddAsmCode(ct_node_ps, div_asm_ps);
            Asm_LOAD(adr_result, &asm_ps);
        }
        
        Asm_STORE_I(ramids_s.id_dest_in, &asm_ps);
    }
    else
    {
        adr_result = ramids_s.id_dest;
        if( TYPE_NUMBER == cmd_cs.pid_3_ps->type_e &&
            2 == cmd_cs.pid_3_ps->value
        )
        {
            Asm_LOAD(ram_A, &asm_ps);
            //Asm_STORE(pA, &head_ps);
            
            Asm_SHIFT(9, &asm_ps);
            Asm_STORE(adr_result, &asm_ps);
            Cplr_AddAsmCode(ct_node_ps, asm_ps);
            asm_ps = NULL;
        }
        else
        {
            Asm_node_ps div_asm_ps = Asm_DIV(adr_result, ram_A, ram_B, ram_reg_1, ram_reg_2);
            Cplr_AddAsmCode(ct_node_ps, div_asm_ps);
        }
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    //Cplr_PrintAsmAsInstructions(ct_node_ps); exit(0);
    asm_ps = NULL;

    */
}




static void Cplr_MOD(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;

    Ram_id adr_result = 2; // 1
    Ram_id ram_A = -1; // 1
    Ram_id ram_B = -1; // 1
    Ram_id ram_reg_1 = 5;
    Ram_id ram_reg_2 = 6;
    
    Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);

   
    if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_2_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_A_in, &asm_ps);
            Asm_STORE(ramids_s.id_A_in, &asm_ps);
            
            ram_A = ramids_s.id_A_in;
        }
        else
        {
            ram_A = ramids_s.id_A;
        }
    }
    else
    {
        ram_A = ramids_s.id_A;
    }
    
    if(TYPE_ARRAY == cmd_cs.pid_3_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_3_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_B_in, &asm_ps);
            Asm_STORE(ramids_s.id_B_in, &asm_ps);

            ram_B = ramids_s.id_B_in;
        }
        else
        {
            ram_B = ramids_s.id_B;
        }
    }
    else
    {
        ram_B = ramids_s.id_B;
    }

    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
    
    if(-1 == ramids_s.id_dest)
    {
        adr_result = 7;
        if( TYPE_NUMBER == cmd_cs.pid_3_ps->type_e &&
            2 == cmd_cs.pid_3_ps->value
        )
        {
            Asm_LOAD(ram_A, &asm_ps);
            //Asm_STORE(pA, &head_ps);
            
            Asm_SHIFT(9, &asm_ps);
            Asm_SHIFT(8, &asm_ps);
            //Asm_SUB(ram_A, &asm_ps);
            Asm_STORE(7, &asm_ps);
            Asm_LOAD(ram_A, &asm_ps);
            Asm_SUB(7, &asm_ps);
            Cplr_AddAsmCode(ct_node_ps, asm_ps);
            asm_ps = NULL;
        }
        else
        {
            //adr_result = 7;
            Asm_node_ps div_asm_ps = Asm_MOD(adr_result, ram_A, ram_B, ram_reg_1, ram_reg_2);
            Cplr_AddAsmCode(ct_node_ps, div_asm_ps);

            Asm_LOAD(adr_result, &asm_ps);
        }

        Asm_STORE_I(ramids_s.id_dest_in, &asm_ps);
    }
    else
    {
        adr_result = ramids_s.id_dest;
        if( TYPE_NUMBER == cmd_cs.pid_3_ps->type_e &&
            2 == cmd_cs.pid_3_ps->value
        )
        {
            Asm_LOAD(ram_A, &asm_ps);
            //Asm_STORE(pA, &head_ps);
            
            Asm_SHIFT(9, &asm_ps);
            Asm_SHIFT(8, &asm_ps);
            Asm_STORE(7, &asm_ps);
            Asm_LOAD(ram_A, &asm_ps);
            Asm_SUB(7, &asm_ps);
            Asm_STORE(adr_result, &asm_ps);
            Cplr_AddAsmCode(ct_node_ps, asm_ps);
            asm_ps = NULL;
        }
        else
        {
            //adr_result = ramids_s.id_dest;
            Asm_node_ps div_asm_ps = Asm_MOD(adr_result, ram_A, ram_B, ram_reg_1, ram_reg_2);
            Cplr_AddAsmCode(ct_node_ps, div_asm_ps);
        }
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}


/* nowy
static void Cplr_CONST(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;
    Ram_id ram_A = -1;
    
    Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);
    // printf("in_dest = %ld\n", ramids_s.id_dest);
    // printf("id_dest_in = %ld\n", ramids_s.id_dest_in);
    // printf("id_A = %ld\n", ramids_s.id_A);
    // printf("id_A_in = %ld\n", ramids_s.id_A_in);
    // printf("id_B = %ld\n", ramids_s.id_B);
    // printf("id_B_in = %ld\n", ramids_s.id_B_in);
    //exit(0);
    
    if(TYPE_ARRAY == cmd_cs.pid_2_ps->type_e)
    {
        if(TYPE_NUMBER != cmd_cs.index_2_ps->type_e)
        {
            Asm_LOAD_I(ramids_s.id_A_in, &asm_ps);
            Asm_STORE(ramids_s.id_A_in, &asm_ps);
            
            ram_A = ramids_s.id_A_in;
        }
        else
        {
            ram_A = ramids_s.id_A;
        }
    }
    else
    {
        ram_A = ramids_s.id_A;
    }
        
    if(-1 == ramids_s.id_dest)
    {
        Asm_LOAD(ram_A, &asm_ps);
        Asm_STORE_I(ramids_s.id_dest_in, &asm_ps);
    }
    else
    {
        Asm_LOAD(ram_A, &asm_ps);
        Asm_STORE(ramids_s.id_dest, &asm_ps);
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;
}
*/


// static void Cplr_READ(
//     Cplr_info_cps info_cps,
//     Cmd_command_cs cmd_cs,
//     Ct_node_ps ct_node_ps
// )
// {
//     Asm_node_ps asm_ps = NULL;

//     Pid_node_ps pid_1_ps = cmd_cs.pid_1_ps;
//     Pid_node_ps index_1_ps = cmd_cs.index_1_ps;
    
//     bool generate_number = Cplr_NumberNotInRam(info_cps, index_1_ps);
    
//     Ram_addresses_s ram_adr_s = Ram_RetAdr(info_cps, ct_node_ps);
    
//     if(TYPE_ARRAY == pid_1_ps->type_e)
//     {
//         if( generate_number &&
//             0 != index_1_ps->value
//         )
//         {
//             asm_ps = Asm_NumberGenerator(
//                         info_cps, 
//                         index_1_ps->value,
//                         ct_node_ps
//                     );

//             Asm_STORE(ram_adr_s.adr_idx_1, &asm_ps);    // p[NumberPlaceInRam] = Number
//         }
//         //else
//         //{
//             //Asm_LOAD(ram_adr_s.adr_pid_1, &asm_ps);   // p[NumberPlaceInRam] = Number
//         //}
        
//         if(0 != index_1_ps->value)
//         {
//             Asm_LOAD(ram_adr_s.adr_pid_1, &asm_ps); // p[0] = x (tab->memory_addres)
//             Asm_ADD(ram_adr_s.adr_idx_1, &asm_ps); // p[0] = x + index
//             Asm_STORE((Asm_val)1, &asm_ps); // p[1] = x + index
//             Asm_GET(&asm_ps);    // p[0] = input
//             Asm_STORE_I(1, &asm_ps); // tab(index) = p0
//         }
//         else
//         {
//             Asm_GET(&asm_ps);
//             Asm_STORE_I(ram_adr_s.adr_idx_1, &asm_ps); // tab(index) = p0
//         }
//     }
//     else
//     {
//         Asm_GET(&asm_ps); 
//         Asm_STORE(ram_adr_s.adr_idx_1, &asm_ps); 
//     }

//     ct_node_ps->asm_code_head_ps = asm_ps;
// }


static void Cplr_READ(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_node_ps asm_ps = NULL;

    Pid_node_ps pid_ps = cmd_cs.pid_1_ps;
    Pid_node_ps index_ps = cmd_cs.index_1_ps;
    
    if(TYPE_ARRAY == pid_ps->type_e)
    {
        Asm_val store_in = Cplr_WriteInArrayAddress(
                                info_cps,
                                (Asm_val)1,
                                ct_node_ps,
                                pid_ps,
                                index_ps
                            );
        Asm_GET(&asm_ps);
        Asm_STORE_I(store_in, &asm_ps);
    }
    else
    {
        Ram_id id_ram = Ram_Adr(
                            info_cps,
                            pid_ps,
                            ct_node_ps
                        );

        Asm_GET(&asm_ps); 
        Asm_STORE(id_ram, &asm_ps); 
    }

    Cplr_AddAsmCode(ct_node_ps, asm_ps);
}




static void Cplr_IF(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    // Cplr_PrintRam(info_cps);
    // printf("in_dest = %ld\n", ramids_s.id_dest);
    // printf("id_dest_in = %ld\n", ramids_s.id_dest_in);
    // printf("id_A = %ld\n", ramids_s.id_A);
    // printf("id_A_in = %ld\n", ramids_s.id_A_in);
    // printf("id_B = %ld\n", ramids_s.id_B);
    // printf("id_B_in = %ld\n", ramids_s.id_B_in);
    // Cplr_PrintAsmAsInstructions(ct_node_ps);
    // exit(0);

    Asm_node_ps asm_ps = NULL;

    Cplr_ramids_s ramids_s = Cplr_RetRamIds(info_cps, cmd_cs, ct_node_ps);
    Ram_id ram_B;
    Ram_id ram_C;
    
    if(-1 != ramids_s.id_dest)
    {
        ram_B = ramids_s.id_dest;
    }
    else
    {
        Asm_LOAD_I(ramids_s.id_dest_in, &asm_ps);
        Asm_STORE(ramids_s.id_dest_in, &asm_ps);
        ram_B = ramids_s.id_dest_in;
    }

    if(-1 != ramids_s.id_A)
    {
        ram_C = ramids_s.id_A;
    }
    else
    {
        Asm_LOAD_I(ramids_s.id_A_in, &asm_ps);
        Asm_STORE(ramids_s.id_A_in, &asm_ps);
        ram_C = ramids_s.id_A_in;
    }
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
    asm_ps = NULL;


    if(COND_NOTAPPLICABLE == cmd_cs.condition_e)
    {
        ERROR_PRINT("if with not applicable cond");
    }
    else if(COND_EQ == cmd_cs.condition_e)
    {
        asm_ps = Asm_EQ(ram_B, ram_C);
    }
    else if(COND_NEQ == cmd_cs.condition_e)
    {
        asm_ps = Asm_NEQ(ram_B, ram_C);
    }
    else if(COND_LE == cmd_cs.condition_e)
    {
        asm_ps = Asm_LE(ram_B, ram_C);
    }
    else if(COND_GE == cmd_cs.condition_e)
    {
        asm_ps = Asm_GE(ram_B, ram_C);
    }
    else if(COND_LEQ == cmd_cs.condition_e)
    {
        asm_ps = Asm_LEQ(ram_B, ram_C);
    }
    else if(COND_GEQ == cmd_cs.condition_e)
    {
        asm_ps = Asm_GEQ(ram_B, ram_C);
    }
    else
    {
        ERROR_PRINT("Wrong cond in if");
    }
    
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
}


static void Cplr_ELSE(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Ct_node_ps ct_if_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if(CMD_IF != ct_if_node_ps->command_s.type_e)
    {
        ERROR_PRINT("Else of branch withou IF");
    }

    Asm_index code_len = Asm_CodeLen(ct_if_node_ps->next_ps, ct_node_ps);

    Asm_node_ps asm_ps = Asm_LastAsmNode(ct_if_node_ps);
    if(NULL == asm_ps)
    {
        ERROR_PRINT("If without asm code");
    }
    asm_ps->instr_arg = code_len + 2;

    asm_ps = NULL;
    Asm_JUMP(-100000, &asm_ps);
    Cplr_AddAsmCode(ct_node_ps, asm_ps);
}


static void Cplr_END_IF(
    Cplr_info_cps info_cps,
    Cmd_command_cs cmd_cs,
    Ct_node_ps ct_node_ps
)
{
    Asm_index code_len = -1;
    Ct_node_ps ct_if_node_ps = Ct_HeadOfBranch(ct_node_ps);
    Ct_node_ps ct_tmp_ps = ct_if_node_ps;
    while(NULL != ct_tmp_ps &&
          CMD_ELSE != ct_tmp_ps->command_s.type_e
    )
    {
        ct_tmp_ps = ct_tmp_ps->next_ps;
    }

    if(NULL != ct_tmp_ps)
    {
        if(CMD_ELSE == ct_tmp_ps->command_s.type_e)
        {
            code_len = Asm_CodeLen(ct_tmp_ps, ct_node_ps);
            ct_tmp_ps->asm_code_head_ps->instr_arg = code_len;

            return;
        }
    }
    
    //Ct_node_ps ct_if_node_ps = Ct_HeadOfBranch(ct_node_ps);
    if(CMD_IF != ct_if_node_ps->command_s.type_e)
    {
        ERROR_PRINT("endif of branch withou IF");
    }
    
    code_len = Asm_CodeLen(ct_if_node_ps->next_ps, ct_node_ps);

    Asm_node_ps asm_ps = Asm_LastAsmNode(ct_if_node_ps);
    if(NULL == asm_ps)
    {
        ERROR_PRINT("If without asm code");
    }
    asm_ps->instr_arg = code_len + 1;
}