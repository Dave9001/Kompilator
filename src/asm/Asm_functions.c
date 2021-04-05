#include "Asm_functions.h"
#include "Asm_instructions.h"
#include "../ram/Ram_functions.h"
#include "../pid/Pid_functions.h"
#include "../cplr/Cplr_functions.h"


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

extern void Asm_DeleteCode(
    Ct_node_ps node_ps
);

extern void Asm_PrintList(
    Asm_node_ps asm_head_ps
);
/*extern Asm_node_ps Asm_NumberGenerator(
    Cplr_info_cps info_cps,
    Cplr_val number,
    Ct_node_cps ct_node_cps
);*/

extern Asm_node_ps Asm_NumberGenerator_nowy(
    Cplr_info_cps info_cps,
    Cplr_val number,
    Ct_node_cps ct_node_cps,
    const Cplr_registers_e reg_to_use
);


extern void Asm_CorrectKthFromTop(
    Asm_node_ps asm_head_ps,
    Cplr_index k,
    Asm_val jump_to
);

extern void Asm_ASSIGN(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_IF(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ELSE(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ENDIF(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_WHILE(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_DO(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ENDWHILE(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ENDDO(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_FOR(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern void Asm_ENDFOR(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern Asm_node_ps Asm_READ(
    Asm_val D
);
extern void Asm_WRITE(
    Cplr_info_cpcs info_cpcs,
    Ct_node_ps node_ps
);
extern Asm_node_ps Asm_PLUS(
    //Asm_val D,
    Asm_val A,
    Asm_val B
);
extern Asm_node_ps Asm_PLUS_nowy(
    Asm_val reg_A,
    Asm_val reg_B
);
extern Asm_node_ps Asm_MINUS(
    Asm_val D,
    Asm_val A,
    Asm_val B
);
extern Asm_node_ps Asm_MINUS_nowy(
    Asm_val reg_A,
    Asm_val reg_B
);
extern Asm_node_ps Asm_TIMES(
    Asm_val pD,
    Asm_val pA,
    Asm_val A,
    Asm_val pB,
    Asm_val B,
    Cplr_info_cps info_cps,
    Ct_node_cps ct_cps
);
extern Asm_node_ps Asm_TIMES_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C,
    Asm_val reg_D
);

extern Asm_node_ps Asm_TIMESWithoutSwapAndOneCheck_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C,
    Asm_val reg_D
);
/*nowy extern Asm_node_ps Asm_DIV(
    Asm_val D,
    Asm_val A,
    Asm_val B,
    Asm_val pA,
    Asm_val pB
);*/
extern Asm_node_ps Asm_MOD(
    Asm_val D,
    Asm_val A,
    Asm_val B,
    Asm_val pA,
    Asm_val pB
);
extern Asm_node_ps Asm_MOD_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C,
    Asm_val reg_E,
    Asm_val reg_tA
);

extern Asm_node_ps Asm_GEQ(
    Asm_val B,
    Asm_val C
);

extern Asm_node_ps Asm_GEQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
);


extern Asm_node_ps Asm_LEQ(
    Asm_val B,
    Asm_val C
);

extern Asm_node_ps Asm_LEQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
);

extern Asm_node_ps Asm_LE(
    Asm_val B,
    Asm_val C
);
extern Asm_node_ps Asm_LE_nowy(
    Asm_val reg_A,
    Asm_val reg_B
);
extern Asm_node_ps Asm_GE(
    Asm_val B,
    Asm_val C
);

extern Asm_node_ps Asm_GE_nowy(
    Asm_val reg_A,
    Asm_val reg_B
);

extern Asm_node_ps Asm_EQ(
    Asm_val B,
    Asm_val C
);
extern Asm_node_ps Asm_NEQ(
    Asm_val B,
    Asm_val C
);
extern Asm_node_ps Asm_NEQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
);

extern void Asm_AppendCode(
    Asm_node_cpps asm_head_cpps,
    Asm_node_ps asm_code_ps
);
extern void Asm_Print(
    Asm_node_ps asm_ps
);
/*extern void Asm_Alloc_1_m1(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps
);*/
extern Asm_node_ps Asm_LastAsmNode(
    Ct_node_ps ct_node_ps
);
extern Asm_index Asm_CodeLen(
    Ct_node_ps ct_from_ps,
    Ct_node_ps ct_to_ps
);
extern Asm_val Asm_NumberOfinstrAfterGiven_nowy(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_cps,
    Asm_node_ps asm_ps
);
extern Asm_node_ps Asm_FindLastSTOREinList_nowy(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_cps
);

/********************************************************************
 * 
 *  -----------------------STATIC DECLARATIONS-----------------------
 * 
 ********************************************************************/

static void Asm_AddToCt(
    Ct_node_cps ct_node_cps,
    Asm_node_s asm_code_s
);
static void Asm_DelAsmByPtr(
    Asm_node_cpps listHead_pps,
    Asm_node_s *asm_code_to_del_ps
);
static void Asm_DelWholeAsmCode(
    Asm_node_cpps listHead_pps
);
static void Asm_InsertAsLastAsmCode(
    Ct_node_cps ct_node_cps,
    Asm_node_cps asm_code_ps
);

static Asm_val Asm_P1(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_cps
);
static Asm_val Asm_Pm1(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_cps
);
/*static void Asm_DecInc(
    Asm_node_cpps asm_head_cpps,
    bool sgn_minus
);*/
static void Asm_Reverse(
    Asm_node_cpps asm_head_cpps
);
static Asm_index Asm_CodeCounter(
    Ct_node_ps ct_current_ps,
    Ct_node_ps ct_to_ps
);
static Asm_index Asm_Count(
    Ct_node_ps ct_node_ps
);

/********************************************************************
 * 
 *  -----------------------EXTERN DEFINITIONS-----------------------
 * 
 ********************************************************************/

extern void Asm_DeleteCode(
    Ct_node_ps node_ps
)
{
    if(NULL == node_ps)
    {
        return;
    }

    Asm_node_ps asm_code_ps = node_ps->asm_code_head_ps;
    if(NULL == asm_code_ps)
    {
        return;
    }

    Asm_node_ps tmp_asm_ps  = asm_code_ps;   
    while(NULL != asm_code_ps)
    {
        tmp_asm_ps = asm_code_ps;
        asm_code_ps = asm_code_ps->next_ps;
        
        tmp_asm_ps->prev_ps = NULL;
        tmp_asm_ps->next_ps = NULL;
        free(tmp_asm_ps);
    }
    
    node_ps->asm_code_head_ps = NULL;
    node_ps->asm_code_length  = VAL_ZERO;
}

extern void Asm_PrintList(
    Asm_node_ps asm_head_ps
)
{
    Asm_node_ps tmp_ps = asm_head_ps;
    while(NULL != tmp_ps)
    {
        Asm_Print(tmp_ps);
        tmp_ps = tmp_ps->next_ps;
    }
}

/*nowy*/
/*extern void Asm_Alloc_1_m1(
    Cplr_info_cps info_cps,
    Ct_node_ps ct_node_ps
)
{
    Pid_AddToList_Number(info_cps, "1");
    Ram_id id1 = Ram_Alloc(info_cps, (Cplr_index)1);
    Pid_node_ps pid_1_ps = Pid_FindByName(info_cps->pid_listHead_cpps, "1");
    Ram_Init(info_cps, ct_node_ps, pid_1_ps);

    Pid_AddToList_Number(info_cps, "-1");
    Ram_id idm1 = Ram_Alloc(info_cps, (Cplr_index)1);
    Pid_node_ps pid_m1_ps = Pid_FindByName(info_cps->pid_listHead_cpps, "-1");
    Ram_Init(info_cps, ct_node_ps, pid_m1_ps);

    Asm_node_ps asm_head_ps = NULL;

    Asm_SUB(0, &asm_head_ps);
    Asm_INC(&asm_head_ps);
    Asm_STORE(id1, &asm_head_ps);

    Asm_SUB(0, &asm_head_ps);
    Asm_DEC(&asm_head_ps);
    Asm_STORE(idm1, &asm_head_ps);

    Asm_AppendCode(&(ct_node_ps->asm_code_head_ps), asm_head_ps);
}*/

/*extern Asm_node_ps Asm_NumberGenerator(
    Cplr_info_cps info_cps,
    Cplr_val number,
    Ct_node_cps ct_node_cps
)
{
    Asm_node_ps asm_head_ps = NULL;

    bool n_is_not_zero = TRUE;
    if(0 == number)
    {
        n_is_not_zero = FALSE;
    }

    /* nowe*/
    /*bool sgn_minus = FALSE; 
    if(number < 0)
    {
        number = number * (VAL_MINUS_ONE);
        sgn_minus = TRUE;
    }

    Asm_val p1 = -1; //Asm_P1(info_cps, ct_node_cps);
    
    if(number != VAL_ZERO)
    {
        while(number > VAL_ZERO)
        {
            if(VAL_ZERO == number % VAL_TWO)
            {
                if(number >= (Cplr_val)5)
                {
                    if(-1 == p1)
                    {
                        p1 = Asm_P1(info_cps, ct_node_cps);
                    }

                    Asm_SHIFT(p1, &asm_head_ps);
                    number = (Cplr_val)(number / VAL_TWO);
                }
                else
                {
                    Asm_DecInc(&asm_head_ps, sgn_minus);
                    number--;
                }
            }
            else
            {
                Asm_DecInc(&asm_head_ps, sgn_minus);
                number--;
            }
        }
    }
    Asm_SUB(0, &asm_head_ps);
    
    if(n_is_not_zero)
    {
        Asm_Reverse(&asm_head_ps);
    }

    return asm_head_ps;
}*/

extern Asm_node_ps Asm_NumberGenerator_nowy(
    Cplr_info_cps info_cps,
    Cplr_val number,
    Ct_node_cps ct_node_cps,
    const Cplr_registers_e reg_to_use
)
{
    Asm_node_ps asm_head_ps = NULL;
    bool n_is_not_zero = TRUE;

    if(number != VAL_ZERO)
    {
        while(number > VAL_ZERO)
        {
            if(VAL_ZERO == number % VAL_TWO)
            {
                Asm_SHL_nowy(reg_to_use, &asm_head_ps);
                number = (Cplr_val)(number / VAL_TWO);
            }
            else
            {
                Asm_INC_nowy(reg_to_use, &asm_head_ps);
                number--;
            }
        }
    }
    else
    {
       n_is_not_zero = FALSE; 
    }

    Asm_RESET_nowy(reg_to_use, &asm_head_ps);
    
    if(n_is_not_zero)
    {
        Asm_Reverse(&asm_head_ps);
    }

    return asm_head_ps;
}



extern Asm_node_ps Asm_TIMES(
    Asm_val pD,
    Asm_val pA,
    Asm_val A,
    Asm_val pB,
    Asm_val B,
    Cplr_info_cps info_cps,
    Ct_node_cps ct_cps
)
{/*Assumes that pA, pB, pD are allocated and  A i B are written in ram, and pD is id of D in ram*/
    Ram_id pm1 = -1;
    Ram_id p1 = -1;

    Ram_node_ps ram_node_ps = info_cps->ram_head_ps;
    while(NULL != ram_node_ps)
    {
        if(NULL != ram_node_ps->pid_ps)
        {
            if(-1 == ram_node_ps->pid_ps->value)
            {
                pm1 = ram_node_ps->id;
            }
            else if(1 == ram_node_ps->pid_ps->value)
            {
                p1 = ram_node_ps->id;
            }
        }
        ram_node_ps = ram_node_ps->next_ps;
    }

    if( -1 == pm1 ||
        -1 == p1
    )
    {
        ERROR_PRINT("no 1 and -1");
    }

    Asm_node_ps head_ps = NULL;

    Asm_LOAD(A, &head_ps);
    Asm_JNEG(2, &head_ps);
    Asm_JUMP(28, &head_ps);

    Asm_SUB(0, &head_ps);
    Asm_STORE(pD, &head_ps);
    Asm_SUB(A, &head_ps);
    Asm_STORE(pA, &head_ps);

    Asm_LOAD(B, &head_ps);
    Asm_JZERO(44, &head_ps);
    Asm_STORE(pB, &head_ps);

    Asm_LOAD(pA, &head_ps);
    

    Asm_JZERO(15, &head_ps);
    Asm_STORE(pA, &head_ps);

    Asm_SHIFT(pm1, &head_ps);
    Asm_SHIFT(p1, &head_ps);
    Asm_SUB(pA, &head_ps);
    Asm_JZERO(4, &head_ps);

    Asm_LOAD(pD, &head_ps);
    Asm_ADD(pB, &head_ps);
    Asm_STORE(pD, &head_ps);

    Asm_LOAD(pB, &head_ps);
    Asm_SHIFT(p1, &head_ps);
    Asm_STORE(pB, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_SHIFT(pm1, &head_ps);

    Asm_JUMP(-14, &head_ps);


    /* -a , ale czy +b ? */
    //Asm_LOAD(B, &head_ps);
    //Asm_JPOS(30, &head_ps); // KONIEC

    Asm_SUB(0, &head_ps);
    Asm_SUB(pD, &head_ps);
    Asm_STORE(pD, &head_ps);
    Asm_JUMP(26, &head_ps);







    Asm_LOAD(B, &head_ps);
    Asm_JZERO(22, &head_ps);
    Asm_STORE(pB, &head_ps);

    Asm_SUB(0, &head_ps);
    Asm_STORE(pD, &head_ps);

    Asm_LOAD(A, &head_ps);
    Asm_JZERO(17, &head_ps);
    Asm_STORE(pA, &head_ps);

    Asm_JZERO(17, &head_ps);
    Asm_STORE(pA, &head_ps);

    Asm_SHIFT(pm1, &head_ps);
    Asm_SHIFT(p1, &head_ps);
    Asm_SUB(pA, &head_ps);
    Asm_JZERO(4, &head_ps);

    Asm_LOAD(pD, &head_ps);
    Asm_ADD(pB, &head_ps);
    Asm_STORE(pD, &head_ps);

    Asm_LOAD(pB, &head_ps);
    Asm_SHIFT(p1, &head_ps);
    Asm_STORE(pB, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_SHIFT(pm1, &head_ps);

    Asm_JUMP(-14, &head_ps);
 
    Asm_SUB(0, &head_ps);
    Asm_STORE(pD, &head_ps);

    
    // Cplr_index count_jump = INDEX_ZERO;
    // Asm_node_ps head_ps = NULL;
    
    // Asm_LOAD(B, &head_ps);
    // Asm_JZERO(0, &head_ps);
    // Asm_STORE(pB, &head_ps);

    // Asm_LOAD(A, &head_ps);
    // Asm_JZERO(0, &head_ps);

    // Asm_SUB(pB, &head_ps);
    // Asm_JNEG(9, &head_ps);
    // Asm_JZERO(8, &head_ps);

    // Asm_LOAD(A, &head_ps);
    // Asm_STORE(pB, &head_ps);

    // Asm_SUB(0, &head_ps);
    // Asm_STORE(pD, &head_ps);

    // Asm_LOAD(B, &head_ps);
    // Asm_STORE(pA, &head_ps);

    // Asm_JUMP(0, &head_ps);

    // Asm_SUB(0, &head_ps);
    // Asm_STORE(pD, &head_ps);

    // bool created_p1 = FALSE;
    // Asm_val p1 = 0;
    // Ram_node_ps ram_p1_ps = Ram_FindByName(info_cps->ram_head_ps, "1");
    // if(NULL == ram_p1_ps)
    // {
    //     Asm_INC(&head_ps);
    //     Asm_STORE(p1, &head_ps);
        
    //     p1 = Asm_P1(info_cps, ct_cps);

    //     count_jump += 2;
    //     created_p1 = TRUE;
    // }
    // else
    // {
    //     p1 = ram_p1_ps->id;
    // }
    
    // Asm_val pm1 = 0;
    // Ram_node_ps ram_pm1_ps = Ram_FindByName(info_cps->ram_head_ps, "-1");
    // if(NULL == ram_pm1_ps)
    // {
    //     if(created_p1)
    //     {
    //         Asm_SUB(0, &head_ps);
    //         count_jump++;
    //     }

    //     Asm_DEC(&head_ps);
    //     Asm_STORE(pm1, &head_ps);

    //     pm1 = Asm_Pm1(info_cps, ct_cps);

    //     count_jump += 2;
    // }
    // else
    // {
    //     pm1 = ram_pm1_ps->id;
    // }

    // Asm_LOAD(A, &head_ps);

    // Asm_JZERO(17, &head_ps);
    // Asm_STORE(pA, &head_ps);

    // Asm_SHIFT(pm1, &head_ps);
    // Asm_SHIFT(p1, &head_ps);
    // Asm_SUB(pA, &head_ps);
    // Asm_JZERO(4, &head_ps);

    // Asm_LOAD(pD, &head_ps);
    // Asm_ADD(pB, &head_ps);
    // Asm_STORE(pD, &head_ps);

    // Asm_LOAD(pB, &head_ps);
    // Asm_SHIFT(p1, &head_ps);
    // Asm_STORE(pB, &head_ps);

    // Asm_LOAD(pA, &head_ps);
    // Asm_SHIFT(pm1, &head_ps);

    // Asm_JUMP(-15, &head_ps);
 
    // Asm_SUB(0, &head_ps);
    // Asm_STORE(pD, &head_ps);

    // Asm_CorrectKthFromTop(head_ps, 15, 6 + count_jump);
    // Asm_CorrectKthFromTop(head_ps, 2, 34 + count_jump);
    // Asm_CorrectKthFromTop(head_ps, 5, 31 + count_jump);

    return head_ps;
}



extern Asm_node_ps Asm_TIMES_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C,
    Asm_val reg_D
)/*D=A*B*/
{
    Asm_node_ps head_ps = NULL;

    /*0 ?*/
    Asm_RESET_nowy(reg_D, &head_ps);
    Asm_JZERO_nowy(reg_A, 32, &head_ps);
    Asm_JZERO_nowy(reg_B, 31, &head_ps);

    Asm_DEC_nowy(reg_A, &head_ps);
    Asm_JZERO_nowy(reg_A, 6, &head_ps);
    Asm_INC_nowy(reg_A, &head_ps);
    
    Asm_DEC_nowy(reg_B, &head_ps);
    Asm_JZERO_nowy(reg_B, 5, &head_ps);
    Asm_INC_nowy(reg_B, &head_ps);

    Asm_JUMP_nowy(5, &head_ps);
    Asm_ADD_nowy(reg_D, reg_B, &head_ps);
    Asm_JUMP_nowy(22, &head_ps);
    Asm_ADD_nowy(reg_D, reg_A, &head_ps);
    Asm_JUMP_nowy(20, &head_ps);

    Asm_RESET_nowy(reg_C, &head_ps);
    Asm_ADD_nowy(reg_C, reg_A, &head_ps);
    Asm_SUB_nowy(reg_C, reg_B, &head_ps);
    Asm_JZERO_nowy(reg_C, 2, &head_ps);
    Asm_JUMP_nowy(8, &head_ps);

    Asm_JZERO_nowy(reg_A, 14, &head_ps);
    Asm_JODD_nowy(reg_A, 2, &head_ps);
    Asm_JUMP_nowy(2, &head_ps);
    Asm_ADD_nowy(reg_D, reg_B, &head_ps);
    Asm_SHR_nowy(reg_A, &head_ps);
    Asm_SHL_nowy(reg_B, &head_ps);
    Asm_JUMP_nowy(-6, &head_ps);

    Asm_JZERO_nowy(reg_B, 7, &head_ps);
    Asm_JODD_nowy(reg_B, 2, &head_ps);
    Asm_JUMP_nowy(2, &head_ps);
    Asm_ADD_nowy(reg_D, reg_A, &head_ps);
    Asm_SHR_nowy(reg_B, &head_ps);
    Asm_SHL_nowy(reg_A, &head_ps);
    Asm_JUMP_nowy(-6, &head_ps);

    return head_ps;
}



extern Asm_node_ps Asm_TIMESWithoutSwapAndOneCheck_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C,
    Asm_val reg_D
)/*D=A*B*/
{
    Asm_node_ps head_ps = NULL;

    /*0 ?*/
    Asm_RESET_nowy(reg_D, &head_ps);
    Asm_JZERO_nowy(reg_A, 9, &head_ps);
    Asm_JZERO_nowy(reg_B, 8, &head_ps);

    Asm_JZERO_nowy(reg_A, 7, &head_ps);
    Asm_JODD_nowy(reg_A, 2, &head_ps);
    Asm_JUMP_nowy(2, &head_ps);
    Asm_ADD_nowy(reg_D, reg_B, &head_ps);
    Asm_SHR_nowy(reg_A, &head_ps);
    Asm_SHL_nowy(reg_B, &head_ps);
    Asm_JUMP_nowy(-6, &head_ps);

    return head_ps;
}



extern void Asm_CorrectKthFromTop(
    Asm_node_ps asm_head_ps,
    Cplr_index k,
    Asm_val jump_to
)
{
    if(NULL == asm_head_ps)
    {
        return;
    }

    Cplr_index i = 1;
    Asm_node_ps tmp_ps = asm_head_ps;
    while(NULL != tmp_ps)
    {
        if(i == k)
        {
            break;
        }

        tmp_ps = tmp_ps->next_ps;
        i++;
    }

    if(NULL != tmp_ps)
    {
        tmp_ps->instr_arg = jump_to;
    }
}

extern Asm_node_ps Asm_GEQ(
    Asm_val B,
    Asm_val C
)/*B >= C*/
{/*Assumes that B, C are alloceted in ram*/
    Asm_node_ps head_ps = NULL;
    
    Asm_LOAD(B, &head_ps);
    Asm_SUB(C, &head_ps);
    Asm_JNEG(0, &head_ps);

    return head_ps;
}


extern Asm_node_ps Asm_GEQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
)/*A >= B*/
{
    Asm_node_ps head_ps = NULL;
    
    Asm_RESET_nowy(reg_C, &head_ps);
    Asm_ADD_nowy(reg_C, reg_A, &head_ps);
    Asm_SUB_nowy(reg_A, reg_B, &head_ps);
    Asm_JZERO_nowy(reg_A, 2, &head_ps);
    Asm_JUMP_nowy(4, &head_ps); // jump to true

    Asm_SUB_nowy(reg_B, reg_C, &head_ps);
    Asm_JZERO_nowy(reg_B, 2, &head_ps); // jump to true
    Asm_JUMP_nowy(0, &head_ps); // jump to false

    return head_ps;
}



extern Asm_node_ps Asm_LEQ(
    Asm_val B,
    Asm_val C
)/*B <= C*/
{/*Assumes that B, C are alloceted in ram*/
    Asm_node_ps head_ps = NULL;
    
    Asm_LOAD(B, &head_ps);
    Asm_SUB(C, &head_ps);
    Asm_JPOS(0, &head_ps);

    return head_ps;
}


extern Asm_node_ps Asm_LEQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
)/*A <= B*/
{
    Asm_node_ps head_ps = NULL;
    
    Asm_RESET_nowy(reg_C, &head_ps);
    Asm_ADD_nowy(reg_C, reg_B, &head_ps);
    Asm_SUB_nowy(reg_B, reg_A, &head_ps);
    Asm_JZERO_nowy(reg_B, 2, &head_ps);
    Asm_JUMP_nowy(4, &head_ps); // jump to true

    Asm_SUB_nowy(reg_A, reg_C, &head_ps);
    Asm_JZERO_nowy(reg_A, 2, &head_ps); // jump to true
    Asm_JUMP_nowy(0, &head_ps); // jump to false

    return head_ps;
}



extern Asm_node_ps Asm_LE(
    Asm_val B,
    Asm_val C
)/*B < C*/
{/*Assumes that B, C are alloceted in ram*/
    Asm_node_ps head_ps = NULL;
    
    Asm_LOAD(B, &head_ps);
    Asm_SUB(C, &head_ps);
    Asm_JNEG(2, &head_ps);
    Asm_JUMP(0, &head_ps);

    return head_ps;
}


extern Asm_node_ps Asm_LE_nowy(
    Asm_val reg_A,
    Asm_val reg_B
)/*A < B*/
{
    Asm_node_ps head_ps = NULL;
    
    Asm_SUB_nowy(reg_B, reg_A, &head_ps);
    Asm_JZERO_nowy(reg_B, 0, &head_ps); // jump to false
    
    return head_ps;
}



extern Asm_node_ps Asm_GE(
    Asm_val B,
    Asm_val C
)/*B > C*/
{/*Assumes that B, C are alloceted in ram*/
    Asm_node_ps head_ps = NULL;
    
    Asm_LOAD(B, &head_ps);
    Asm_SUB(C, &head_ps);
    Asm_JPOS(2, &head_ps);
    Asm_JUMP(0, &head_ps);

    return head_ps;
}



extern Asm_node_ps Asm_GE_nowy(
    Asm_val reg_A,
    Asm_val reg_B
)/*A > B*/
{
    Asm_node_ps head_ps = NULL;
    
    Asm_SUB_nowy(reg_A, reg_B, &head_ps);
    Asm_JZERO_nowy(reg_A, 0, &head_ps); // jump to false
    
    return head_ps;
}




extern Asm_node_ps Asm_EQ(
    Asm_val B,
    Asm_val C
)/*B = C*/
{/*Assumes that B, C are alloceted in ram*/
    Asm_node_ps head_ps = NULL;
    
    Asm_LOAD(B, &head_ps);
    Asm_SUB(C, &head_ps);
    Asm_JZERO(2, &head_ps);
    Asm_JUMP(0, &head_ps);

    return head_ps;
}

extern Asm_node_ps Asm_EQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
)/*A == C*/
{
    Asm_node_ps head_ps = NULL;
    
    Asm_RESET_nowy(reg_C, &head_ps);
    Asm_ADD_nowy(reg_C, reg_A, &head_ps);
    Asm_SUB_nowy(reg_A, reg_B, &head_ps);
    Asm_JZERO_nowy(reg_A, 2, &head_ps);
    Asm_JUMP_nowy(3, &head_ps); // jump to false

    Asm_SUB_nowy(reg_B, reg_C, &head_ps);
    Asm_JZERO_nowy(reg_B, 2, &head_ps); // jump to true
    Asm_JUMP_nowy(0, &head_ps); // jump to false

    return head_ps;
}

extern Asm_node_ps Asm_NEQ(
    Asm_val B,
    Asm_val C
)/*B = C*/
{/*Assumes that B, C are alloceted in ram*/
    Asm_node_ps head_ps = NULL;
    
    Asm_LOAD(B, &head_ps);
    Asm_SUB(C, &head_ps);
    Asm_JZERO(0, &head_ps);

    return head_ps;
}


extern Asm_node_ps Asm_NEQ_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C
)/*B != C*/
{
    Asm_node_ps head_ps = NULL;
    
    Asm_RESET_nowy(reg_C, &head_ps);
    Asm_ADD_nowy(reg_C, reg_A, &head_ps);
    Asm_SUB_nowy(reg_A, reg_B, &head_ps);
    Asm_JZERO_nowy(reg_A, 2, &head_ps);
    Asm_JUMP_nowy(3, &head_ps); // jump to true

    Asm_SUB_nowy(reg_B, reg_C, &head_ps);
    Asm_JZERO_nowy(reg_B, 0, &head_ps); // jump to false

    return head_ps;
}



extern Asm_node_ps Asm_MINUS(
    Asm_val D,
    Asm_val A,
    Asm_val B
)/*D = A - B*/
{/*Assumes that B, C are alloceted in ram*/
    Asm_node_ps head_ps = NULL;
    
    Asm_LOAD(A, &head_ps);
    Asm_SUB(B, &head_ps);
    Asm_STORE(D, &head_ps);

    return head_ps;
}

extern Asm_node_ps Asm_MINUS_nowy(
    Asm_val reg_A,
    Asm_val reg_B
)
{
    Asm_node_ps head_ps = NULL;
    Asm_SUB_nowy(reg_A, reg_B, &head_ps);

    return head_ps;
}


extern Asm_node_ps Asm_PLUS(
    //Asm_val D,
    Asm_val A,
    Asm_val B
)/*D = A - B*/
{/*Assumes that B, C are alloceted in ram*/
    Asm_node_ps head_ps = NULL;
    
    Asm_LOAD(A, &head_ps);
    Asm_ADD(B, &head_ps);
    //Asm_STORE(D, &head_ps);

    return head_ps;
}

extern Asm_node_ps Asm_PLUS_nowy(
    Asm_val reg_A,
    Asm_val reg_B
)
{
    Asm_node_ps head_ps = NULL;
    Asm_ADD_nowy(reg_A, reg_B, &head_ps);

    return head_ps;
}

/* nowy
extern Asm_node_ps Asm_DIV_bin(
    Asm_val D,
    Asm_val A,
    Asm_val B,
    Asm_val pA,
    Asm_val pB,
    Asm_val quot,
    Asm_val npos*/
//)/*D = A / B*/
/*{




}*/




/*extern Asm_node_ps Asm_DIV(
    Asm_val D,
    Asm_val A,
    Asm_val B,
    Asm_val pA,
    Asm_val pB
)/*D = A / B*/
/*nowy{*//*Assumes that B, C are alloceted in ram*/
/*nowy    Asm_node_ps head_ps = NULL;

    Asm_LOAD(A, &head_ps);
    Asm_STORE(pA, &head_ps);
    
    Asm_JZERO(49, &head_ps);
    Asm_JNEG(14, &head_ps);

    Asm_LOAD(B, &head_ps);

    Asm_JZERO(46, &head_ps);
    Asm_JNEG(35, &head_ps);
*/
    /* +a i +b */
/* nowy
    Asm_SUB(0, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_SUB(B, &head_ps);

    Asm_JNEG(42, &head_ps); // KONIEC
    Asm_STORE(pA, &head_ps);

    Asm_LOAD(D, &head_ps);
    Asm_INC(&head_ps);
    Asm_STORE(D, &head_ps);

    Asm_JUMP(-7, &head_ps);

    Asm_LOAD(B, &head_ps);
    Asm_JZERO(33, &head_ps);
    Asm_JPOS(2, &head_ps);
    Asm_JUMP(11, &head_ps);
*/
    /* -a i +b */
/*nowy
    Asm_SUB(0, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_ADD(B, &head_ps);

    Asm_JPOS(28, &head_ps);  // KONIEC
    Asm_STORE(pA, &head_ps);

    Asm_LOAD(D, &head_ps);
    Asm_DEC(&head_ps);
    Asm_STORE(D, &head_ps);

    Asm_JUMP(-7, &head_ps);
*/
    /* -a i -b */
/*nowy
    Asm_SUB(0, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_SUB(B, &head_ps);

    Asm_JPOS(18, &head_ps);  // KONIEC
    Asm_STORE(pA, &head_ps);

    Asm_LOAD(D, &head_ps);
    Asm_INC(&head_ps);
    Asm_STORE(D, &head_ps);

    Asm_JUMP(-7, &head_ps);
*/

    /* +a i -b */
/* nowy
    Asm_SUB(0, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_ADD(B, &head_ps);

    Asm_JNEG(8, &head_ps);  // KONIEC
    Asm_STORE(pA, &head_ps);

    Asm_LOAD(D, &head_ps);
    Asm_DEC(&head_ps);
    Asm_STORE(D, &head_ps);

    Asm_JUMP(-7, &head_ps);



    Asm_SUB(0, &head_ps);
    Asm_STORE(D, &head_ps);



    // Asm_LOAD(B, &head_ps);
    // Asm_JNEG(4, &head_ps);
    
    // Asm_LOAD(A, &head_ps);
    // Asm_JNEG(4, &head_ps);
    // Asm_JUMP(21, &head_ps);

    // Asm_LOAD(A, &head_ps);
    // Asm_JPOS(19, &head_ps);

    // /*A i B różnych znaków*/

    // Asm_SUB(0, &head_ps);
    // Asm_STORE(D, &head_ps);

    // Asm_LOAD(B, &head_ps);
    // Asm_STORE(pB, &head_ps);

    // Asm_JZERO(14, &head_ps);

    // Asm_LOAD(A, &head_ps);
    // Asm_STORE(pA, &head_ps);

    // Asm_ADD(pB, &head_ps);
    // Asm_JPOS(2, &head_ps);
    // Asm_JUMP(9, &head_ps);

    // Asm_LOAD(pA, &head_ps);
    // Asm_SUB(pB, &head_ps);
    // Asm_STORE(pA, &head_ps);

    // Asm_LOAD(D, &head_ps);
    // Asm_INC(&head_ps);
    // Asm_STORE(D, &head_ps);

    // Asm_LOAD(pA, &head_ps);
    // Asm_JUMP(-10, &head_ps);


    // /* A i B tego samego znaku*/

    // Asm_SUB(0, &head_ps);
    // Asm_STORE(D, &head_ps);

    // Asm_LOAD(B, &head_ps);
    // Asm_STORE(pB, &head_ps);

    // Asm_JZERO(14, &head_ps);

    // Asm_LOAD(A, &head_ps);
    // Asm_STORE(pA, &head_ps);

    // Asm_SUB(pB, &head_ps);
    // Asm_JPOS(2, &head_ps);
    // Asm_JUMP(9, &head_ps);

    // Asm_LOAD(pA, &head_ps);
    // Asm_SUB(pB, &head_ps);
    // Asm_STORE(pA, &head_ps);

    // Asm_LOAD(D, &head_ps);
    // Asm_INC(&head_ps);
    // Asm_STORE(D, &head_ps);

    // Asm_LOAD(pA, &head_ps);
    // Asm_JUMP(-10, &head_ps);
/*nowy
    return head_ps;
}*/

extern Asm_node_ps Asm_MOD(
    Asm_val D,
    Asm_val A,
    Asm_val B,
    Asm_val pA,
    Asm_val pB
)/*D = A / B*/
{/*Assumes that B, C are alloceted in ram*/
    Asm_node_ps head_ps = NULL;

    Asm_LOAD(A, &head_ps);
    Asm_STORE(pA, &head_ps);
    
    Asm_JZERO(41, &head_ps);
    Asm_JNEG(12, &head_ps);

    Asm_LOAD(B, &head_ps);

    Asm_JZERO(38, &head_ps);
    Asm_JNEG(29, &head_ps);

    /* +a i +b */

    //Asm_SUB(0, &head_ps);
    Asm_LOAD(pA, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_SUB(B, &head_ps);

    Asm_JNEG(34, &head_ps); // KONIEC
    Asm_STORE(D, &head_ps);
    Asm_STORE(pA, &head_ps);

    Asm_JUMP(-5, &head_ps);

    Asm_LOAD(B, &head_ps);
    Asm_JZERO(27, &head_ps);
    Asm_JPOS(2, &head_ps);
    Asm_JUMP(9, &head_ps);

    /* -a i +b */

    Asm_SUB(0, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_ADD(B, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_JPOS(21, &head_ps);  // KONIEC
    
    Asm_STORE(pA, &head_ps);

    Asm_JUMP(-5, &head_ps);

    /* -a i -b */

    //Asm_SUB(0, &head_ps);
    Asm_LOAD(pA, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_SUB(B, &head_ps);

    Asm_JPOS(14, &head_ps);  // KONIEC
    Asm_STORE(D, &head_ps);
    Asm_STORE(pA, &head_ps);

    Asm_JUMP(-5, &head_ps);


    /* +a i -b */

    Asm_SUB(0, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_LOAD(pA, &head_ps);
    Asm_ADD(B, &head_ps);
    Asm_STORE(D, &head_ps);

    Asm_JNEG(5, &head_ps);  // KONIEC
    
    Asm_STORE(pA, &head_ps);

    Asm_JUMP(-5, &head_ps);



    Asm_SUB(0, &head_ps);
    Asm_STORE(D, &head_ps);
    


    // Asm_SUB(0, &head_ps);
    // Asm_STORE(D, &head_ps);

    // Asm_LOAD(B, &head_ps);
    // Asm_STORE(pB, &head_ps);

    // Asm_JZERO(14, &head_ps);

    // Asm_LOAD(A, &head_ps);
    // Asm_STORE(pA, &head_ps);

    // Asm_SUB(pB, &head_ps);
    // Asm_JPOS(2, &head_ps);
    // Asm_JUMP(9, &head_ps);

    // Asm_LOAD(pA, &head_ps);
    // Asm_SUB(pB, &head_ps);
    // Asm_STORE(pA, &head_ps);

    // Asm_LOAD(D, &head_ps);
    // Asm_INC(&head_ps);
    // Asm_STORE(D, &head_ps);

    // Asm_LOAD(pA, &head_ps);
    // Asm_JUMP(-10, &head_ps);

    return head_ps;
}

extern Asm_node_ps Asm_MOD_nowy(
    Asm_val reg_A,
    Asm_val reg_B,
    Asm_val reg_C,
    Asm_val reg_E,
    Asm_val reg_tA
)/*reszta jest w reg_A, wynik dzielenia w reg_E*/
{
    Asm_node_ps head_ps = NULL;

    /*0 ?*/
    Asm_JZERO_nowy(reg_B, 3, &head_ps);
    Asm_JZERO_nowy(reg_A, 2, &head_ps);
    Asm_JUMP_nowy(4, &head_ps);
    Asm_RESET_nowy(reg_A, &head_ps);
    Asm_RESET_nowy(reg_E, &head_ps);
    Asm_JUMP_nowy(38, &head_ps);
    
    Asm_RESET_nowy(reg_C, &head_ps);
    Asm_INC_nowy(reg_C, &head_ps);
    Asm_RESET_nowy(reg_E, &head_ps);

    Asm_RESET_nowy(reg_tA, &head_ps);
    Asm_ADD_nowy(reg_tA, reg_A, &head_ps);
    Asm_SUB_nowy(reg_tA, reg_B, &head_ps);
    Asm_JZERO_nowy(reg_tA, 4, &head_ps);
    
    Asm_SHL_nowy(reg_B, &head_ps);
    Asm_SHL_nowy(reg_C, &head_ps);
    Asm_JUMP_nowy(-6, &head_ps);

    Asm_ADD_nowy(reg_tA, reg_B, &head_ps);
    Asm_SUB_nowy(reg_tA, reg_A, &head_ps);
    Asm_JZERO_nowy(reg_tA, 2, &head_ps);
    Asm_JUMP_nowy(3, &head_ps);
    
    Asm_SHL_nowy(reg_B, &head_ps);
    Asm_SHL_nowy(reg_C, &head_ps);

    Asm_DEC_nowy(reg_C, &head_ps);
    Asm_JZERO_nowy(reg_C, 20, &head_ps);
    Asm_INC_nowy(reg_C, &head_ps);

    Asm_SHR_nowy(reg_B, &head_ps);
    Asm_SHR_nowy(reg_C, &head_ps);

    Asm_RESET_nowy(reg_tA, &head_ps);
    Asm_ADD_nowy(reg_tA, reg_A, &head_ps);
    Asm_SUB_nowy(reg_tA, reg_B, &head_ps);
    Asm_JZERO_nowy(reg_tA, 5, &head_ps);

    Asm_RESET_nowy(reg_A, &head_ps);
    Asm_ADD_nowy(reg_A, reg_tA, &head_ps);
    Asm_ADD_nowy(reg_E, reg_C, &head_ps);
    Asm_JUMP_nowy(-12, &head_ps);

    Asm_RESET_nowy(reg_tA, &head_ps);
    Asm_ADD_nowy(reg_tA, reg_B, &head_ps);
    Asm_SUB_nowy(reg_tA, reg_A, &head_ps);
    Asm_JZERO_nowy(reg_tA, 2, &head_ps);
    Asm_JUMP_nowy(-17, &head_ps);

    Asm_SUB_nowy(reg_A, reg_B, &head_ps);
    Asm_ADD_nowy(reg_E, reg_C, &head_ps);
    Asm_JUMP_nowy(-20, &head_ps);

    return head_ps;
}


/*extern void Asm_READ(
    Asm_val D
)
{
    Asm_node_ps head_ps = NULL;

    Asm_GET(D, head_ps);
}*/


extern void Asm_AppendCode(
    Asm_node_cpps asm_head_cpps,
    Asm_node_ps asm_code_ps
)
{
    if(NULL == asm_code_ps)
    {
        ERROR_PRINT("malloc failed");
    }

    if(NULL == *asm_head_cpps)
    {
        *asm_head_cpps = asm_code_ps;
    }
    else
    {
        Asm_node_ps tmp_ps = *asm_head_cpps;
        while(tmp_ps->next_ps != NULL)
        {
            tmp_ps = tmp_ps->next_ps;
        }

        tmp_ps->next_ps = asm_code_ps;
        asm_code_ps->prev_ps = tmp_ps;
        //asm_code_ps->next_ps = NULL;
    }
}


extern void Asm_Print(
    Asm_node_ps asm_ps
)
{
    if(NULL == asm_ps)
    {
        return;
    }

    printf("asm_node: %p\n", asm_ps);
    printf("next_ps: %p\n", asm_ps->next_ps);
    printf("prev_ps: %p\n", asm_ps->prev_ps);

    printf("instr_e: ");
    switch(asm_ps->asm_instr_e)
    {
        case EMPTY_INSTR:   printf("EMPTY_INSTR");  break;
        case GET:           printf("GET");          break;
        case PUT:           printf("PUT");          break;
        case LOAD:          printf("LOAD");         break;
        case STORE:         printf("STORE");        break;
        case LOAD_I:        printf("LOAD_I");       break;
        case STORE_I:       printf("STORE_I");      break;
        case ADD:           printf("ADD");          break;
        case SUB:           printf("SUB");          break;
        case SHIFT:         printf("SHIFT");        break;
        case INC:           printf("INC");          break;
        case DEC:           printf("DEC");          break;
        case JUMP:          printf("JUMP");         break;
        case JPOS:          printf("JPOS");         break;
        case JZERO:         printf("JZERO");        break;
        case JNEG:          printf("JNEG");         break;
        case SHR:           printf("SHR");          break;
        case SHL:           printf("SHL");          break;
        case RESET:         printf("RESET");        break;
        case JODD:          printf("JODD");         break;
        case HALT:          printf("HALT");         break;

        default: printf("UNKNOWN !"); break;
    }puts("");

    printf("arg: %ld\n",asm_ps->instr_arg);
    puts("");
}

extern Asm_node_ps Asm_LastAsmNode(
    Ct_node_ps ct_node_ps
)
{
    if(NULL == ct_node_ps)
    {
        return NULL;
    }
    
    Asm_node_ps asm_ps = ct_node_ps->asm_code_head_ps;
    while(NULL != asm_ps)
    {
        if(NULL == asm_ps->next_ps)
        {
            break;
        }

        asm_ps = asm_ps->next_ps;
    }

    return asm_ps;
}

extern Asm_index Asm_CodeLen(
    Ct_node_ps ct_from_ps,
    Ct_node_ps ct_to_ps
)
{
    Asm_index code_len = Asm_CodeCounter(ct_from_ps, ct_to_ps);
    return code_len;
}



extern Asm_node_ps Asm_FindLastSTOREinList_nowy(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_cps
)
{
    Asm_node_ps asm_ps = Asm_LastAsmNode(ct_node_cps); 
    while(NULL != asm_ps)
    {   
        if(STORE == asm_ps->asm_instr_e)
        {
            break;
        }
        asm_ps = asm_ps->prev_ps;
    }

    return asm_ps;
}

extern Asm_val Asm_NumberOfinstrAfterGiven_nowy(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_node_cps,
    Asm_node_ps asm_ps
)
{
    if(NULL == asm_ps)
    {
        ERROR_PRINT("there shoudl be sth");
    }

    Asm_val count = VAL_ZERO;
    Asm_node_ps asm_tmp_ps = asm_ps;
    while(NULL != asm_tmp_ps)
    {
        asm_tmp_ps = asm_tmp_ps->next_ps;
        if(NULL != asm_tmp_ps)
        {
            count++;
        }
    }

    return count;
}



/********************************************************************
 * 
 *  -----------------------STATIC DEFINITIONS-----------------------
 * 
 ********************************************************************/

static void Asm_AddToCt(
    Ct_node_cps ct_node_cps,
    Asm_node_s asm_code_s
)
{
    Asm_node_s *asm_code_to_add_ps = malloc(sizeof(*asm_code_to_add_ps));
    if(NULL == asm_code_to_add_ps)
    {
        ERROR_PRINT("malloc failed");
    }

    *asm_code_to_add_ps = asm_code_s;

    Asm_InsertAsLastAsmCode(ct_node_cps, asm_code_to_add_ps);
}


static void Asm_DelAsmByPtr(
    Asm_node_cpps listHead_pps,
    Asm_node_s *asm_code_to_del_ps
)
{
    if(asm_code_to_del_ps != NULL && *listHead_pps != NULL)
    {
        if(asm_code_to_del_ps == *listHead_pps)
        {
            *listHead_pps = asm_code_to_del_ps->next_ps;
        }

        if(asm_code_to_del_ps->prev_ps != NULL)
        {
            asm_code_to_del_ps->prev_ps->next_ps = asm_code_to_del_ps->next_ps;
        }

        if(asm_code_to_del_ps->next_ps != NULL)
        {
            asm_code_to_del_ps->next_ps->prev_ps = asm_code_to_del_ps->prev_ps;
        }

        asm_code_to_del_ps->prev_ps = NULL;
        asm_code_to_del_ps->next_ps = NULL;

        free(asm_code_to_del_ps);
    }
}

static void Asm_DelWholeAsmCode(
    Asm_node_cpps listHead_pps
)
{
    while(*listHead_pps != NULL)
    {
        Asm_DelAsmByPtr(listHead_pps, *listHead_pps);
    }
}

static void Asm_InsertAsLastAsmCode(
    Ct_node_cps ct_node_cps,
    Asm_node_cps asm_code_ps
)
{
    Asm_node_ps head_ps = ct_node_cps->asm_code_head_ps;

    if(NULL == head_ps)
    {
        asm_code_ps->prev_ps = NULL;
        asm_code_ps->next_ps = NULL;
        ct_node_cps->asm_code_head_ps = asm_code_ps;
    }
    else
    {
        Asm_node_s *tmp_ps = head_ps;
        while(tmp_ps->next_ps != NULL)
        {
            tmp_ps = tmp_ps->next_ps;
        }

        tmp_ps->next_ps = asm_code_ps;
        asm_code_ps->prev_ps = tmp_ps;
        asm_code_ps->next_ps = NULL;
    }
}

static Asm_val Asm_P1(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_cps
)
{
    Ram_id id = (Ram_id)0;
    Ram_node_ps ram_p1_ps = Ram_FindByName(info_cps->ram_head_ps, "1");
    if(NULL == ram_p1_ps)
    {
        Pid_AddToList_Number(info_cps, "1");

        id = Ram_Alloc(info_cps, (Cplr_index)1);

        Pid_node_ps pid_ps = Pid_FindByName(info_cps->pid_listHead_cpps, "1");
        Ram_Init(info_cps, ct_cps, pid_ps); 
    }
    else
    {
        id = ram_p1_ps->id;
    }
    
    return id;
}

static Asm_val Asm_Pm1(
    Cplr_info_cps info_cps,
    Ct_node_cps ct_cps
)
{
    Ram_id id = (Ram_id)0;
    Ram_node_ps ram_p1_ps = Ram_FindByName(info_cps->ram_head_ps, "-1");
    if(NULL == ram_p1_ps)
    {
        Pid_AddToList_Number(info_cps, "-1");

        id = Ram_Alloc(info_cps, (Cplr_index)1);

        Pid_node_ps pid_ps = Pid_FindByName(info_cps->pid_listHead_cpps, "-1");
        Ram_Init(info_cps, ct_cps, pid_ps);
    }
    else
    {
        id = ram_p1_ps->id;
    }
    
    return id;
}


/* nowy
static void Asm_DecInc(
    Asm_node_cpps asm_head_cpps,
    bool sgn_minus
)
{
    if(sgn_minus)
    {
        Asm_DEC(asm_head_cpps);
    }
    else
    {
        Asm_INC(asm_head_cpps);
    }
}*/

/*nowy*/
static void Asm_Reverse(
    Asm_node_cpps asm_head_cpps
)
{
    //if(NULL == (*asm_head_cpps)->prev_ps)
    //{
    //    return;
    //}

    Asm_node_ps nonull_head_ps = NULL;
    Asm_node_ps tmp_ps = NULL;
    while(NULL != *asm_head_cpps)
    {
        tmp_ps = (*asm_head_cpps)->prev_ps;
        (*asm_head_cpps)->prev_ps = (*asm_head_cpps)->next_ps;
        (*asm_head_cpps)->next_ps = tmp_ps;

        *asm_head_cpps = (*asm_head_cpps)->prev_ps;
        if(NULL != *asm_head_cpps)
        {
            nonull_head_ps = *asm_head_cpps;
        }
    }
    *asm_head_cpps = nonull_head_ps;
}


static Asm_index Asm_CodeCounter(
    Ct_node_ps ct_current_ps,
    Ct_node_ps ct_to_ps
)
{
    if(NULL == ct_current_ps)
    {
        return 0;
    }

    if(ct_current_ps == ct_to_ps)
    {
        return 0;
    }

    Asm_index counter = Asm_Count(ct_current_ps);
    
    if(TRUE == ct_current_ps->is_branch)
    {
        counter += Asm_CodeCounter(ct_current_ps->branch_ps, ct_to_ps);
        counter += Asm_CodeCounter(ct_current_ps->next_ps, ct_to_ps);
    }
    else
    {
        counter += Asm_CodeCounter(ct_current_ps->next_ps, ct_to_ps);
    }
    
    return counter;
}

static Asm_index Asm_Count(
    Ct_node_ps ct_node_ps
)
{
    Asm_index counter = 0;
    Asm_node_ps asm_ps = ct_node_ps->asm_code_head_ps;
    while(NULL != asm_ps)
    {
        counter++;
        asm_ps = asm_ps->next_ps;
    }

    return counter;
}
