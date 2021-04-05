
#include "Asm_instructions.h"



/********************************************************************
 * 
 *  ----------------------------DEFINES----------------------------
 * 
 ********************************************************************/


/*#define GET(instr)\
        instr.asm_instr_e    = GET;*/

#define GET_nowy(reg_1, instr)\
        instr.asm_instr_e  = GET;\
        instr.reg_1    = reg_1;

/*#define PUT(arg, instr)\
        instr.asm_instr_e  = PUT;\
        instr.instr_arg    = arg;*/


#define PUT_nowy(reg_1, instr)\
        instr.asm_instr_e  = PUT;\
        instr.reg_1    = reg_1;

/*#define LOAD(arg, instr)\
        instr.asm_instr_e  = LOAD;\
        instr.instr_arg    = arg;*/

#define LOAD_nowy(reg_1, reg_2, instr)\
        instr.asm_instr_e  = LOAD;\
        instr.reg_1    = reg_1;\
        instr.reg_2    = reg_2;


#define LOAD_I(arg, instr)\
        instr.asm_instr_e  = LOAD_I;\
        instr.instr_arg    = arg;

/*#define STORE(arg, instr)\
        instr.asm_instr_e  = STORE;\
        instr.instr_arg    = arg;*/

#define STORE_nowy(reg_1, reg_2, instr)\
        instr.asm_instr_e  = STORE;\
        instr.reg_1    = reg_1;\
        instr.reg_2    = reg_2;

#define STORE_I(arg, instr)\
        instr.asm_instr_e  = STORE_I;\
        instr.instr_arg    = arg;


/*#define ADD(arg, instr)\
        instr.asm_instr_e  = ADD;\
        instr.instr_arg    = arg;*/

#define ADD_nowy(reg_1, reg_2, instr)\
        instr.asm_instr_e  = ADD;\
        instr.reg_1    = reg_1;\
        instr.reg_2    = reg_2;

/*#define SUB(arg, instr)\
        instr.asm_instr_e  = SUB;\
        instr.instr_arg    = arg;*/

#define SUB_nowy(reg_1, reg_2, instr)\
        instr.asm_instr_e  = SUB;\
        instr.reg_1    = reg_1;\
        instr.reg_2    = reg_2;

/*#define INC(instr)\
        instr.asm_instr_e  = INC;*/

#define INC_nowy(id, instr)\
        instr.asm_instr_e  = INC;\
        instr.reg_1 = id;

/*#define DEC(instr)\
        instr.asm_instr_e  = DEC;*/

#define DEC_nowy(reg_1, instr)\
        instr.asm_instr_e  = DEC;\
        instr.reg_1 = reg_1;

#define SHIFT(arg, instr)\
        instr.asm_instr_e  = SHIFT;\
        instr.instr_arg    = arg

/*#define JUMP(arg, instr)\
        instr.asm_instr_e  = JUMP;\
        instr.instr_arg    = arg;*/

#define JUMP_nowy(reg_1, instr)\
        instr.asm_instr_e  = JUMP;\
        instr.reg_1    = reg_1;

#define JPOS(arg, instr)\
        instr.asm_instr_e  = JPOS;\
        instr.instr_arg    = arg;

/*#define JZERO(arg, instr)\
        instr.asm_instr_e  = JZERO;\
        instr.instr_arg    = arg;*/

#define JODD_nowy(reg_1, reg_2, instr)\
        instr.asm_instr_e  = JODD;\
        instr.reg_1    = reg_1;\
        instr.reg_2    = reg_2;

#define JZERO_nowy(reg_1, reg_2, instr)\
        instr.asm_instr_e  = JZERO;\
        instr.reg_1    = reg_1;\
        instr.reg_2    = reg_2;

#define JNEG(arg, instr)\
        instr.asm_instr_e  = JNEG;\
        instr.instr_arg    = arg;

#define HALT(instr)\
        instr.asm_instr_e  = HALT;

#define RESET_nowy(arg, instr)\
        instr.asm_instr_e  = RESET;\
        instr.reg_1    = arg;

#define SHL_nowy(arg, instr)\
        instr.asm_instr_e  = SHL;\
        instr.reg_1    = arg;

#define SHR_nowy(arg, instr)\
        instr.asm_instr_e  = SHR;\
        instr.reg_1    = arg;



/********************************************************************
 * 
 *  -----------------------EXTERN DECLARATIONS-----------------------
 * 
 ********************************************************************/




/*extern Asm_node_ps Asm_EQ(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_EQ_0_C(void);
extern Asm_node_ps Asm_EQ_B_0(void);

extern Asm_node_ps Asm_NEQ(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_NEQ_0_C(void);
extern Asm_node_ps Asm_NEQ_B_0(void);

extern Asm_node_ps Asm_GE(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_GE_0_C(void);
extern Asm_node_ps Asm_GE_B_0(void);

extern Asm_node_ps Asm_LE(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_LE_0_C(void);
extern Asm_node_ps Asm_LE_B_0(void);

extern Asm_node_ps Asm_LEQ(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_LEQ_0_C(void);
extern Asm_node_ps Asm_LEQ_B_0(void);

extern Asm_node_ps Asm_GEQ(
    Asm_val B,
    Asm_val C,
    Asm_p0_e p0_val
);
extern Asm_node_ps Asm_GEQ_0_C(void);
extern Asm_node_ps Asm_GEQ_B_0(void);
*/
extern void Asm_GET(
    Asm_node_cpps asm_head_cpps
);
extern void Asm_GET_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_PUT(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_PUT_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_LOAD(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);

extern void Asm_LOAD_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);

extern void Asm_LOAD_I(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_STORE(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_STORE_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_STORE_I(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_ADD(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_ADD_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SUB(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SUB_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
/*extern void Asm_INC(
    Asm_node_cpps asm_head_cpps
);*/
extern void Asm_INC_nowy(
    Cplr_register_id_c register_id,
    Asm_node_cpps asm_head_cpps
);

extern void Asm_DEC(
    Asm_node_cpps asm_head_cpps
);
extern void Asm_DEC_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SHIFT(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JUMP(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JUMP_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JPOS(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JZERO(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JODD_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JZERO_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_JNEG(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_HALT(
    Asm_node_cpps asm_head_cpps
);

extern void Asm_RESET_nowy(
    Cplr_registers_e register_id,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SHL_nowy(
    Cplr_register_id_c register_id,
    Asm_node_cpps asm_head_cpps
);
extern void Asm_SHR_nowy(
    Cplr_register_id_c register_id,
    Asm_node_cpps asm_head_cpps
);


/********************************************************************
 * 
 *  -----------------------STATIC DECLARATIONS-----------------------
 * 
 ********************************************************************/

static inline Asm_node_s Asm_InitNode(void);
static void Asm_AddCode(
    Asm_node_cpps asm_head_cpps,
    Asm_node_s asm_code_s
);


/********************************************************************
 * 
 *  -----------------------EXTERN DEFINITIONS-----------------------
 * 
 ********************************************************************/


extern void Asm_GET(
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    //GET(node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_GET_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    GET_nowy(reg_1, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_PUT(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    //PUT(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}


extern void Asm_PUT_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    PUT_nowy(reg_1, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_LOAD(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    //LOAD(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_LOAD_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    LOAD_nowy(reg_1, reg_2, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_LOAD_I(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    LOAD_I(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_STORE(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    /*nowy*/
    /*STORE(arg, node_s);*/

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_STORE_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    STORE_nowy(reg_1, reg_2, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_STORE_I(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    STORE_I(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_ADD(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    //ADD(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_ADD_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    ADD_nowy(reg_1, reg_2, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}


extern void Asm_SUB(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    //SUB(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_SUB_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    SUB_nowy(reg_1, reg_2, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

/*extern void Asm_INC(
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    INC(node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}*/

extern void Asm_INC_nowy(
    Cplr_register_id_c register_id,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    INC_nowy(register_id, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_DEC(
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    //DEC(node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}
extern void Asm_DEC_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    DEC_nowy(reg_1, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_SHIFT(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    SHIFT(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_JUMP(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    //JUMP(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_JUMP_nowy(
    Asm_val reg_1,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    JUMP_nowy(reg_1, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_JPOS(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    JPOS(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_JZERO(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    //JZERO(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}


extern void Asm_JODD_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    JODD_nowy(reg_1, reg_2, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_JZERO_nowy(
    Asm_val reg_1,
    Asm_val reg_2,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    JZERO_nowy(reg_1, reg_2, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_JNEG(
    Asm_val arg,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    JNEG(arg, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_HALT(
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    HALT(node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_RESET_nowy(
    Cplr_registers_e register_id,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    RESET_nowy(register_id, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_SHL_nowy(
    Cplr_register_id_c register_id,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    SHL_nowy(register_id, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

extern void Asm_SHR_nowy(
    Cplr_register_id_c register_id,
    Asm_node_cpps asm_head_cpps
)
{
    Asm_node_s node_s = Asm_InitNode();

    SHR_nowy(register_id, node_s);

    Asm_AddCode(asm_head_cpps, node_s);
}

/*
extern Asm_node_ps Asm_GEQ(
    Asm_val pB,
    Asm_val pC,
    Asm_p0_e p0_val
)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    if(B_IN_P0 == p0_val)
    {
        SUB(pC, node_s);        Asm_AddCode(&head_ps, node_s);
        JNEG(VAL_ZERO, node_s); Asm_AddCode(&head_ps, node_s);
    }
    else if(C_IN_P0 == p0_val)
    {
        SUB(pB, node_s);        Asm_AddCode(&head_ps, node_s);
        JPOS(VAL_ZERO, node_s); Asm_AddCode(&head_ps, node_s);
    }
    else
    {
        ERROR_PRINT("Wrong p0 value");
    }
    
    return head_ps;
}

extern Asm_node_ps Asm_GEQ_0_C(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JNEG(3, node_s);    Asm_AddCode(&head_ps, node_s);
    JZERO(2, node_s);   Asm_AddCode(&head_ps, node_s);
    JZERO(0, node_s);   Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_GEQ_B_0(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JPOS(3, node_s);    Asm_AddCode(&head_ps, node_s);
    JZERO(2, node_s);   Asm_AddCode(&head_ps, node_s);
    JZERO(0, node_s);   Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_LEQ(
    Asm_val pB,
    Asm_val pC,
    Asm_p0_e p0_val
)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    if(B_IN_P0 == p0_val)
    {
        SUB(pC, node_s);        Asm_AddCode(&head_ps, node_s);
        JPOS(VAL_ZERO, node_s); Asm_AddCode(&head_ps, node_s);
    }
    else if(C_IN_P0 == p0_val)
    {
        SUB(pB, node_s);        Asm_AddCode(&head_ps, node_s);
        JNEG(VAL_ZERO, node_s); Asm_AddCode(&head_ps, node_s);
    }
    else
    {
        ERROR_PRINT("Wrong p0 value");
    }
    
    return head_ps;
}

extern Asm_node_ps Asm_LEQ_0_C(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JNEG(3, node_s);    Asm_AddCode(&head_ps, node_s);
    JZERO(2, node_s);   Asm_AddCode(&head_ps, node_s);
    JZERO(0, node_s);   Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_LEQ_B_0(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JPOS(3, node_s);    Asm_AddCode(&head_ps, node_s);
    JZERO(2, node_s);   Asm_AddCode(&head_ps, node_s);
    JZERO(0, node_s);   Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_LE(
    Asm_val pB,
    Asm_val pC,
    Asm_p0_e p0_val
)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    if(B_IN_P0 == p0_val)
    {
        SUB(pC, node_s);    Asm_AddCode(&head_ps, node_s);
        JNEG(2, node_s);    Asm_AddCode(&head_ps, node_s);
        JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    }
    else if(C_IN_P0 == p0_val)
    {
        SUB(pB, node_s);    Asm_AddCode(&head_ps, node_s);
        JPOS(2, node_s);    Asm_AddCode(&head_ps, node_s);
        JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    }
    else
    {
        ERROR_PRINT("Wrong p0 value");
    }
    
    return head_ps;
}

extern Asm_node_ps Asm_LE_0_C(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JPOS(2, node_s);    Asm_AddCode(&head_ps, node_s);
    JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_LE_B_0(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JNEG(2, node_s);    Asm_AddCode(&head_ps, node_s);
    JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_GE(
    Asm_val pB,
    Asm_val pC,
    Asm_p0_e p0_val
)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    if(B_IN_P0 == p0_val)
    {
        SUB(pC, node_s);    Asm_AddCode(&head_ps, node_s);
        JPOS(2, node_s);    Asm_AddCode(&head_ps, node_s);
        JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    }
    else if(C_IN_P0 == p0_val)
    {
        SUB(pB, node_s);    Asm_AddCode(&head_ps, node_s);
        JNEG(2, node_s);    Asm_AddCode(&head_ps, node_s);
        JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    }
    else
    {
        ERROR_PRINT("Wrong p0 value");
    }
    
    return head_ps;
}

extern Asm_node_ps Asm_GE_0_C(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JNEG(2, node_s);    Asm_AddCode(&head_ps, node_s);
    JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_GE_B_0(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JPOS(2, node_s);    Asm_AddCode(&head_ps, node_s);
    JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_EQ(
    Asm_val pB,
    Asm_val pC,
    Asm_p0_e p0_val
)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    if(B_IN_P0 == p0_val)
    {
        SUB(pC, node_s);    Asm_AddCode(&head_ps, node_s);
        JZERO(2, node_s);    Asm_AddCode(&head_ps, node_s);
        JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    }
    else if(C_IN_P0 == p0_val)
    {
        SUB(pB, node_s);    Asm_AddCode(&head_ps, node_s);
        JZERO(2, node_s);    Asm_AddCode(&head_ps, node_s);
        JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    }
    else
    {
        ERROR_PRINT("Wrong p0 value");
    }
    
    return head_ps;
}

extern Asm_node_ps Asm_EQ_0_C(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JZERO(2, node_s);    Asm_AddCode(&head_ps, node_s);
    JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_EQ_B_0(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JZERO(2, node_s);    Asm_AddCode(&head_ps, node_s);
    JUMP(0, node_s);    Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_NEQ(
    Asm_val pB,
    Asm_val pC,
    Asm_p0_e p0_val
)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    if(B_IN_P0 == p0_val)
    {
        SUB(pC, node_s);    Asm_AddCode(&head_ps, node_s);
        JZERO(0, node_s);    Asm_AddCode(&head_ps, node_s);
    }
    else if(C_IN_P0 == p0_val)
    {
        SUB(pB, node_s);    Asm_AddCode(&head_ps, node_s);
        JZERO(0, node_s);    Asm_AddCode(&head_ps, node_s);
    }
    else
    {
        ERROR_PRINT("Wrong p0 value");
    }
    
    return head_ps;
}

extern Asm_node_ps Asm_NEQ_0_C(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JZERO(0, node_s);    Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}

extern Asm_node_ps Asm_NEQ_B_0(void)
{
    Asm_node_ps head_ps = NULL;
    Asm_node_s node_s   = Asm_InitNode();
    JZERO(0, node_s);    Asm_AddCode(&head_ps, node_s);
    
    return head_ps;
}
*/

/********************************************************************
 * 
 *  -----------------------STATIC DEFINITIONS-----------------------
 * 
 ********************************************************************/


static inline Asm_node_s Asm_InitNode(void)
{
    Asm_node_s node_s  = {
        .asm_instr_e = EMPTY_INSTR,
        .instr_arg   = VAL_ZERO,
        .reg_1       = uninitialized,
        .reg_2       = uninitialized,
        .next_ps     = NULL,
        .prev_ps     = NULL
    };
    return node_s;
}

static void Asm_AddCode(
    Asm_node_cpps asm_head_cpps,
    Asm_node_s asm_code_s
)
{
    Asm_node_ps asm_node_ps = malloc(sizeof(*asm_node_ps));
    if(NULL == asm_node_ps)
    {
        ERROR_PRINT("malloc failed");
    }

    *asm_node_ps = asm_code_s;
    

    if(NULL == *asm_head_cpps)
    {
        asm_node_ps->prev_ps = NULL;
        asm_node_ps->next_ps = NULL;
        *asm_head_cpps = asm_node_ps;
    }
    else
    {
        Asm_node_s *tmp_ps = *asm_head_cpps;
        while(tmp_ps->next_ps != NULL)
        {
            tmp_ps = tmp_ps->next_ps;
        }

        tmp_ps->next_ps = asm_node_ps;
        asm_node_ps->prev_ps = tmp_ps;
        asm_node_ps->next_ps = NULL;
    }
}