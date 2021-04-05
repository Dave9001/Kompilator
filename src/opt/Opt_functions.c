#include "Opt_functions.h"
#include "../ct/Ct_functions.h"
#include "../pid/Pid_functions.h"


#define NUM_OF_OPT_FUNCT (Cplr_index)(0x0007)

typedef void(*Opt_pf)(Cplr_info_cps);
typedef Opt_pf const Opt_cpf;

typedef Opt_pf Opt_apf[NUM_OF_OPT_FUNCT];

typedef Opt_apf * Opt_papf;


typedef enum tag_Opt_funct_order_e
{
    KNOWN_VALUE_OF_EXPRESSION = 0U,
    DELETE_UNUSED_ASSIGN = 10U,
    UN_SATISFIABLE_CONDITION = 20U,
    SATISFIABLE_CONDITION = 30U,
	DELETE_UNNECESSARY_CODE = 40U,
	REPOSITION_ASSIGN,
	REPOSITION_READ = NUM_OF_OPT_FUNCT
}Opt_funct_order_e;



/********************************************************************
 * 
 *  ----------------------------DEFINES----------------------------
 * 
 ********************************************************************/

#define MAX_NUM_LENGTH (Cplr_val)256


/********************************************************************
 * 
 *  -----------------------EXTERN DECLARATIONS-----------------------
 * 
 ********************************************************************/

extern void Opt_Start(
	Cplr_info_cps cplr_info_cps
);


/********************************************************************
 * 
 *  -----------------------STATIC DECLARATIONS-----------------------
 * 
 ********************************************************************/

static void Opt_InitSeqToNull(
	Opt_papf seq_papf
);
static void Opt_DeleteUnusedAssign(
	Cplr_info_cps info_cps
);
static void Opt_DeleteUnnecessaryCode(
	Cplr_info_cps info_cps
);
static void Opt_RepositionAssign(
	Cplr_info_cps info_cps
);
static void Opt_RepositionRead(
	Cplr_info_cps info_cps
);
static void Opt_SatisfiableCondition(
	Cplr_info_cps info_cps
);
static void Opt_UnSatisfiableCondition(
	Cplr_info_cps info_cps
);
static void Opt_KnownValueOfExpression(
	Cplr_info_cps info_cps
);
static void Opt_InsertToSeq(
	Opt_papf seq_papf,
	Opt_cpf function_cpf
);
static void Opt_Manager(
	Cplr_info_cps info_cps,
	Opt_apf seq_apf
);
static void Opt_FunctSequence(
	Opt_papf seq_papf
);
static void Opt_KnownValueOfExpressionNumbers(
	Cplr_info_cps info_cps
);
static bool Opt_ArePid1And2Numbers(
	Ct_node_ps node_ps
);
static Cplr_val Opt_CalcPLUS(
	Ct_node_ps node_ps
);
static Cplr_val Opt_CalcMINUS(
	Ct_node_ps node_ps
);
static Cplr_val Opt_CalcTIMES(
	Ct_node_ps node_ps
);
static Cplr_val Opt_CalcDIV(
	Ct_node_ps node_ps
);
static Cplr_val Opt_CalcMOD(
	Ct_node_ps node_ps
);
static void Opt_PidAndCmdCorrection(
	Cplr_info_cps info_cps,
	Cplr_val val,
	Ct_node_ps node_ps
);
static Cplr_val Opt_CalcValOf2NumExpr(
	Ct_node_ps node_ps
);


/********************************************************************
 * 
 *  -----------------------EXTERN DEFINITIONS-----------------------
 * 
 ********************************************************************/

extern void Opt_Start(
	Cplr_info_cps info_cps
)
{
	Opt_apf seq_af = {};
	Opt_FunctSequence(&seq_af);

	Opt_Manager(info_cps, seq_af);
}



/********************************************************************
 * 
 *  -----------------------STATIC DEFINITIONS-----------------------
 * 
 ********************************************************************/


static void Opt_FunctSequence(
	Opt_papf seq_papf
)
{
	Opt_InitSeqToNull(seq_papf);
	
	Cplr_index i = 0U;
	while(i < NUM_OF_OPT_FUNCT)
	{
		switch(i)
		{
			case DELETE_UNUSED_ASSIGN:
				Opt_InsertToSeq(seq_papf, &Opt_DeleteUnusedAssign);
				break;
			case DELETE_UNNECESSARY_CODE:
				Opt_InsertToSeq(seq_papf, &Opt_DeleteUnnecessaryCode);
				break;
			case REPOSITION_ASSIGN:
				Opt_InsertToSeq(seq_papf, &Opt_RepositionAssign);
				break;
			case REPOSITION_READ:
				Opt_InsertToSeq(seq_papf, &Opt_RepositionRead);
				break;
			case SATISFIABLE_CONDITION:
				Opt_InsertToSeq(seq_papf, &Opt_SatisfiableCondition);
				break;
			case UN_SATISFIABLE_CONDITION:
				Opt_InsertToSeq(seq_papf, &Opt_UnSatisfiableCondition);
				break;
			case KNOWN_VALUE_OF_EXPRESSION:
				Opt_InsertToSeq(seq_papf, &Opt_KnownValueOfExpression);
				break;
			default:
				ERROR_PRINT("Unknown Opt_function");
				break;
		}

		i++;
	}
}

static void Opt_InitSeqToNull(
	Opt_papf seq_papf
)
{
	Cplr_index i = 0U;
	while(i < NUM_OF_OPT_FUNCT)
	{
		*seq_papf[i] = NULL;
		i++;
	}
}

static void Opt_InsertToSeq(
	Opt_papf seq_papf,
	Opt_cpf function_cpf
)
{
	Cplr_index i = 0;
	while(TRUE)
	{
		if(i >= NUM_OF_OPT_FUNCT)
		{
			ERROR_PRINT("no space in array");
		}
		else if(NULL != *seq_papf[i])
		{
			break;
		}

		i++;
	}

	*seq_papf[i] = function_cpf;
}

static void Opt_DeleteUnusedAssign(
	Cplr_info_cps info_cps
)
{
	printf("Opt_dump %p\n",info_cps);
	return;
}

static void Opt_DeleteUnnecessaryCode(
	Cplr_info_cps info_cps
)
{
	/*	a = 2 * t
		b = 32 * b
		if b > c then
			...
		endif
		WRITE 1

		-> WRITE 1
	*/
	printf("Opt_dump %p\n",info_cps);
	return;
}

static void Opt_RepositionAssign(
	Cplr_info_cps info_cps
)
{	/*
		a = 3
		b = 4
		if a > c then
			...
		endif

		-> 	b = 4
			a = 3
			if a > c then
				...
			endif

		or

		c = 4
		a = b
		d = a + c

		-> 	a = b
			c = 4
			d = a + c
	*/
	printf("Opt_dump %p\n",info_cps);
	return;
}

static void Opt_RepositionRead(
	Cplr_info_cps info_cps
)
{
	printf("Opt_dump %p\n",info_cps);
	return;
}

static void Opt_SatisfiableCondition(
	Cplr_info_cps info_cps
)
{
	printf("Opt_dump %p\n",info_cps);
	return;
}

static void Opt_UnSatisfiableCondition(
	Cplr_info_cps info_cps
)
{
	printf("Opt_dump %p\n",info_cps);
	return;
}

static void Opt_KnownValueOfExpression(
	Cplr_info_cps info_cps
)
{
	/* 	a = 2 + 2
		-> a = 4
		
		b = 3
		a = 2 + b
		-> a = 5
	*/

	Opt_KnownValueOfExpressionNumbers(info_cps);
	//Opt_KnownValueOfExpressionNumbers(info_cps);

	return;
}

static void Opt_Manager(
	Cplr_info_cps info_cps,
	Opt_apf seq_apf
)
{
	Opt_pf Function = NULL;

	Cplr_index i = 0U;
	while(i < NUM_OF_OPT_FUNCT)
	{
		if(NULL == seq_apf[i])
		{
			break;
		}

		Function = seq_apf[i];
		Function(info_cps);

		i++;
	}
}

static void Opt_KnownValueOfExpressionNumbers(
	Cplr_info_cps info_cps
)
{
	Ct_node_ps node_ps = info_cps->ct_head_ps;
	while(NULL != node_ps)
	{
		if(Opt_ArePid1And2Numbers(node_ps))
		{
			Cplr_val val_of_expr = Opt_CalcValOf2NumExpr(node_ps);
			Opt_PidAndCmdCorrection(info_cps, val_of_expr, node_ps);
		}

		node_ps = Ct_NextCmdNode(node_ps);
	}
}

static bool Opt_ArePid1And2Numbers(
	Ct_node_ps node_ps
)
{
	if(EXPR_NOTAPPLICABLE == node_ps->command_s.expression_e)
	{
		return FALSE;
	}

	Pid_type_e pid_1_type = node_ps->command_s.pid_1_ps->type_e;
	Pid_type_e pid_2_type = node_ps->command_s.pid_2_ps->type_e;
	if(TYPE_NUMBER == pid_1_type)
	{
		if(TYPE_NUMBER == pid_2_type)
		{
			return TRUE;
		}
	}

	return FALSE;
}

static Cplr_val Opt_CalcValOf2NumExpr(
	Ct_node_ps node_ps
)
{
	Cplr_val result_of_expr = VAL_ZERO;
	Cmd_exprType_e expr_e = node_ps->command_s.expression_e;
	switch(expr_e)
	{
		case EXPR_PLUS:
			result_of_expr = Opt_CalcPLUS(node_ps);
			break;
		case EXPR_MINUS:
			result_of_expr = Opt_CalcMINUS(node_ps);
			break;
		case EXPR_TIMES:
			result_of_expr = Opt_CalcTIMES(node_ps);
			break;
		case EXPR_DIV:
			result_of_expr = Opt_CalcDIV(node_ps);
			break;
		case EXPR_MOD:
			result_of_expr = Opt_CalcMOD(node_ps);
			break;
		default:
			ERROR_PRINT("ct node does not have expression type");
			break;
	}

	return result_of_expr;
}

static Cplr_val Opt_CalcPLUS(
	Ct_node_ps node_ps
)
{
	Pid_node_ps pid_1_ps = node_ps->command_s.pid_1_ps;
	Pid_node_ps pid_2_ps = node_ps->command_s.pid_2_ps;
	if(NULL == pid_1_ps || NULL == pid_2_ps)
	{
		ERROR_PRINT("Ct node have null pids");
	}

	if( TYPE_NUMBER != pid_1_ps->type_e ||
		TYPE_NUMBER != pid_2_ps->type_e
	)
	{
		ERROR_PRINT("Ct node have pids that are not numbers");
	}

	Cplr_val result = pid_1_ps->value + pid_2_ps->value;
	return result;
}

static Cplr_val Opt_CalcMINUS(
	Ct_node_ps node_ps
)
{
	Pid_node_ps pid_1_ps = node_ps->command_s.pid_1_ps;
	Pid_node_ps pid_2_ps = node_ps->command_s.pid_2_ps;
	if(NULL == pid_1_ps || NULL == pid_2_ps)
	{
		ERROR_PRINT("Ct node have null pids");
	}

	if( TYPE_NUMBER != pid_1_ps->type_e ||
		TYPE_NUMBER != pid_2_ps->type_e
	)
	{
		ERROR_PRINT("Ct node have pids that are not numbers");
	}

	Cplr_val result = pid_1_ps->value - pid_2_ps->value;
	return result;
}

static Cplr_val Opt_CalcTIMES(
	Ct_node_ps node_ps
)
{
	Pid_node_ps pid_1_ps = node_ps->command_s.pid_1_ps;
	Pid_node_ps pid_2_ps = node_ps->command_s.pid_2_ps;
	if(NULL == pid_1_ps || NULL == pid_2_ps)
	{
		ERROR_PRINT("Ct node have null pids");
	}

	if( TYPE_NUMBER != pid_1_ps->type_e ||
		TYPE_NUMBER != pid_2_ps->type_e
	)
	{
		ERROR_PRINT("Ct node have pids that are not numbers");
	}

	Cplr_val result = pid_1_ps->value * pid_2_ps->value;
	return result;
}

static Cplr_val Opt_CalcDIV(
	Ct_node_ps node_ps
)
{
	Pid_node_ps pid_1_ps = node_ps->command_s.pid_1_ps;
	Pid_node_ps pid_2_ps = node_ps->command_s.pid_2_ps;
	if(NULL == pid_1_ps || NULL == pid_2_ps)
	{
		ERROR_PRINT("Ct node have null pids");
	}

	if( TYPE_NUMBER != pid_1_ps->type_e ||
		TYPE_NUMBER != pid_2_ps->type_e
	)
	{
		ERROR_PRINT("Ct node have pids that are not numbers");
	}

	Cplr_val result = (Cplr_val)(pid_1_ps->value / pid_2_ps->value);
	return result;
}

static Cplr_val Opt_CalcMOD(
	Ct_node_ps node_ps
)
{
	Pid_node_ps pid_1_ps = node_ps->command_s.pid_1_ps;
	Pid_node_ps pid_2_ps = node_ps->command_s.pid_2_ps;
	if(NULL == pid_1_ps || NULL == pid_2_ps)
	{
		ERROR_PRINT("Ct node have null pids");
	}

	if( TYPE_NUMBER != pid_1_ps->type_e ||
		TYPE_NUMBER != pid_2_ps->type_e
	)
	{
		ERROR_PRINT("Ct node have pids that are not numbers");
	}

	Cplr_val result = pid_1_ps->value % pid_2_ps->value;
	if(VAL_ZERO <= pid_2_ps->value)
	{
		if(VAL_ZERO > result)
		{
			result = result * VAL_MINUS_ONE;
		}
	}
	else
	{
		if(VAL_ZERO < result)
		{
			result = result * VAL_MINUS_ONE;
		}
	}

	return result;
}

static void Opt_PidAndCmdCorrection(
	Cplr_info_cps info_cps,
	Cplr_val val,
	Ct_node_ps node_ps
)
{
	char buffor[MAX_NUM_LENGTH];
	sprintf(buffor, "%ld", val);
	Cplr_index i = 0;
	while('\0' != buffor[i])
	{
		i++;
	}

	//Pid_name name = malloc(sizeof(*name)*(i+1));
	//strcpy(name, buffor);

	Pid_node_ps pid_ps = Pid_FindByName(info_cps->pid_listHead_cpps, buffor);
	if(NULL == pid_ps)
	{
		Pid_AddToList_Number(info_cps, buffor);
		pid_ps = Pid_FindByName(info_cps->pid_listHead_cpps, buffor);
	}
	
	node_ps->command_s.pid_1_ps = pid_ps;
	node_ps->command_s.pid_2_ps = NULL;
	node_ps->command_s.type_e   = EXPR_NOTAPPLICABLE;
}

