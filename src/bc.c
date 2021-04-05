%{
	#include<stdio.h>
	//#include<stdlib.h>
	//#include <string.h>
	#include "basic_types.h"
	#include "cplr/Cplr_functions.h"
	#include "cmd/Cmd_functions.h"
	#include "pid/Pid_functions.h"
	#include "ct/Ct_functions.h"
	#include "opt/Opt_functions.h"
	#include "ram/Ram_functions.h"
	#include "asm/Asm_functions.h"

	#define PRINT (FALSE)
	void yyset_in( FILE * in_str );
    long long yylex(void);
    void yyerror(const char *);
    //void yyerror2(const char *, const char *);

	Cmd_pidAction_e cmd_pid_action_e = UNKNOWNPID;
	Pid_decRes_e decRes_e = DOUBLE_DECLARATION;

	Cplr_registers_s registers_s = {};
	Pid_node_s *listHead_ps = NULL;
	Cplr_info_s info_s = INIT_INFO(&listHead_ps, &registers_s);
%}

%locations

%union YYSTYPE{ 
  char *str;
  char *num;
}

%nonassoc THEN
%nonassoc ELSE

%token <str> DECLARE IN END
%token <str> PIDENTIFIER
%token <num> NEG_NUM NUM
%token <str> SEMICOLON COMMA LEFT_LIM RIGHT_LIM ARRAY_INDEX_PID ARRAY_INDEX_NUM
%token <str> READ WRITE
%token <str> IF THEN ELSE ENDIF
%token <str> WHILE REPEAT FOR DO DOWNTO FROM TO ENDWHILE UNTIL ENDFOR //ENDDO
%token <str> ASSIGN
%token <str> PLUS MINUS MUL DIV MOD
%token <str> EQ DIFF LE GE LEQ GEQ
%%

program			:	DECLARE
                            {
								Cplr_SetCplrState_Declare(&info_s);
								Cmd_Clear(&info_s);
								
								if(PRINT) printf("\nbiso: DECLARE\n");
								//free(yylval.str);
                            }
                    declarations IN
                            {
								/*arrays ?*/
								Cplr_SetCplrState_Begin(&info_s);
								Cmd_Clear(&info_s);
								if(PRINT) printf("\nbiso: IN\n");
								//free(yylval.str);
                            }
                    commands END 
							{
								Cplr_SetCplrState_End(&info_s);
								Cmd_Clear(&info_s);
								if(PRINT) printf("\nbiso: END \n");

								Ct_CalcPidOccurr(&info_s);
								Ct_LastNodeToNULL(&info_s);
								
								Ram_CreateRegisters(&info_s);

								/* nowy 
								Asm_Alloc_1_m1(&info_s, info_s.ct_head_ps);
								*/

								if(PRINT){
								Cplr_PrintDecorator("Pid list");
								Cplr_PrintPids(&info_s);
								Cplr_PrintDecorator("/Pid list");
								}

								if(PRINT){
								Cplr_PrintDecorator("ALLOC ARRAYS");}

								Cplr_AllocArrays_nowy(&info_s);

								Cplr_AllocPids(&info_s);
								
								if(PRINT){
								Cplr_PrintDecorator("/ALLOC ARRAYS");}

								if(PRINT){
								Cplr_PrintDecorator("Ct");
								Cplr_PrintWholeCt(&info_s);
								Cplr_PrintDecorator("/Ct");}

								if(PRINT){
								Cplr_PrintDecorator("Pid list");
								Cplr_PrintPids(&info_s);
								Cplr_PrintDecorator("/Pid list");}


								if(PRINT){
								Cplr_PrintDecorator("RAM list");
								Cplr_PrintRam(&info_s);
								Cplr_PrintDecorator("/RAM list");}

								if(PRINT){
								Cplr_PrintDecorator("ASM Reader");
								Cplr_AsmReader(&info_s);
								Cplr_PrintDecorator("/ASM Reader");}

								//Cplr_PrintDecorator("Ct");
								//Cplr_PrintWholeCt(&info_s);
								//Cplr_PrintDecorator("/Ct");

								//Ram_Alloc(&info_s, 1);
								//Ram_Alloc(&info_s, 2);
								//Ram_Alloc(&info_s, 3);

								// Cplr_PrintDecorator("Pid list");
								// Cplr_PrintPids(&info_s);
								// Cplr_PrintDecorator("/Pid list");

								// Cplr_PrintDecorator("RAM list");
								// Cplr_PrintRam(&info_s);
								// Cplr_PrintDecorator("/RAM list");

								//Cplr_TIMES(&info_s);

								//Cplr_PrintDecorator("Pid list");
								//Cplr_PrintPids(&info_s);
								//Cplr_PrintDecorator("/Pid list");

								if(PRINT){
								Cplr_PrintDecorator("Code Generator");}

								Cplr_CodeGenerator(&info_s);

								if(PRINT){
								Cplr_PrintDecorator("/Code Generator");}





								if(PRINT){
								Cplr_PrintDecorator("Ct");
								Cplr_PrintWholeCt(&info_s);
								Cplr_PrintDecorator("/Ct");}

								if(PRINT){
								Cplr_PrintDecorator("Pid list");
								Cplr_PrintPids(&info_s);
								Cplr_PrintDecorator("/Pid list");}

								if(PRINT){
								Cplr_PrintDecorator("RAM list");
								Cplr_PrintRam(&info_s);
								Cplr_PrintDecorator("/RAM list");}

								
								//Cplr_PrintDecorator("ASM Reader");
								
								
								//Cplr_AsmReader(&info_s);

								Cplr_AsmReader_nowy(&info_s);

								//Cplr_TESTWRITE(&info_s);

								//Cplr_PrintDecorator("/ASM Reader");

								// Cplr_PrintDecorator("Pid list");
								// Cplr_PrintPids(&info_s);
								// Cplr_PrintDecorator("/Pid list");
							
								// Cplr_PrintDecorator("RAM list");
								// Cplr_PrintRam(&info_s);
								// Cplr_PrintDecorator("/RAM list");

								// Cplr_PrintDecorator("ASM Reader");
								// Cplr_AsmReader(&info_s);
								// Cplr_PrintDecorator("/ASM Reader");

								// Cplr_PrintDecorator("Pid list");
								// Cplr_PrintPids(&info_s);
								// Cplr_PrintDecorator("/Pid list");

								// Cplr_PrintDecorator("RAM list");
								// Cplr_PrintRam(&info_s);
								// Cplr_PrintDecorator("/RAM list");

								/*puts("Deleter$$$$$$$$$$$$$$$$");
								Ct_node_ps head = Ct_Head(&info_s);
								head = head->next_ps;
								
								printf("+++++++++++++++ delete %p\n",head);
								Ct_DeleteNode(&info_s, head);

								printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@last node: %p\n",info_s.last_ct_node_ps);
								Pid_DelList(&info_s);

								Cplr_PrintDecorator("RAM list");
								Cplr_PrintRam(&info_s);
								Cplr_PrintDecorator("/RAM list");

								puts("Ram_delList()");
								Ram_DelList(&info_s);

								Cplr_PrintDecorator("RAM list");
								Cplr_PrintRam(&info_s);
								Cplr_PrintDecorator("/RAM list");

								printf("ct_head: %p\n", info_s.ct_head_ps);
								printf("ct_last: %p\n", info_s.last_ct_node_ps);

								head = Ct_Head(&info_s);
								Cplr_PrintDecorator("ASM Number Gen");
								Asm_NumberGenerator(&info_s, 10, head);
								Cplr_PrintDecorator("/ASM Number Gen");
				

								printf("+++++++++++++++ delete %p\n",head);
								Ct_DeleteNode(&info_s, head);

								Cplr_PrintDecorator("Pid list");
								Cplr_PrintPids(&info_s);
								Cplr_PrintDecorator("/Pid list");
								
								Cplr_PrintDecorator("Ct");
								Cplr_PrintWholeCt(&info_s);
								Cplr_PrintDecorator("/Ct");*/

								

								/*Opt_methods_cs methods_cs = {
									.delete_unused_assign = FALSE,
									.delete_unnecessary_code = FALSE,

									.reposition_assign = FALSE,
									.reposition_read = FALSE,

									.satisfiable_condition = FALSE,
									.un_satisfiable_condition = FALSE,

									.known_value_of_expression = FALSE
								};*/

								//printf("HALT");
								fprintf(info_s.outputFile,"HALT\n");
							}
				|			{
								if(PRINT) printf("\nbiso: przed IN \n");
								Cmd_Clear(&info_s);
							}
					IN 
							{
								Cplr_SetCplrState_Begin(&info_s);
								Cmd_Clear(&info_s);
								if(PRINT) printf("\nbiso: IN \n");
							}
					commands END
							{
								Cplr_SetCplrState_End(&info_s);
								Cmd_Clear(&info_s);
								if(PRINT) printf("\nbiso: END \n");

								Ct_CalcPidOccurr(&info_s);
								Ct_LastNodeToNULL(&info_s);
							}
;

declarations	:	/*empty*/
					declarations COMMA identifier
							{
								//;
							}
				|	declarations COMMA identifier LEFT_LIM RIGHT_LIM
							{
								/*($4:$5)*/
								Pid_UpdateToArray(&info_s);

								Pid_AddArray_LowerLim(&info_s, $4);
								decRes_e =  Pid_AddArray_UpperLim(&info_s, $5);
								if(LOWER_LIM_BIGGER == decRes_e)
								{
									yyerror("declaration of array failed due to wrong indexing");
								}
								//free($4);
								//free($5);
							}
				|   identifier
							{
								//free(yylval.str);
							}
				|	identifier LEFT_LIM RIGHT_LIM
							{
								Pid_UpdateToArray(&info_s);
								
								Pid_AddArray_LowerLim(&info_s, $2);
								decRes_e = Pid_AddArray_UpperLim(&info_s, $3);
								if(LOWER_LIM_BIGGER == decRes_e)
								{
									yyerror("declaration of array failed due to wrong indexing");
								}
								//free($2);
								//free($3);
								//free(yylval.str);
							}
				|			{
								;
							}
;

commands		:	/*empty*/
					commands command
				|	command
;

command			:			{
								if(PRINT) printf("\nbiso: Przed ASSIGN-----------------------------\n");
								Cmd_AddType(&info_s, CMD_ASSIGN);
								Ct_AddNode(&info_s);
							}
					identifier ASSIGN expression SEMICOLON
							{
                            	if(PRINT) printf("\nbiso: SEMICOLON\n");
								Cmd_UpdateLastCt(&info_s);

								if(Cmd_UninitializedAssign_nowy(&info_s))
								{
									yyerror("Assign of uninitalized value");
								}
								
								Cmd_InitializedPid_nowy(&info_s);
								
								Cmd_Clear(&info_s);

								//free(yylval.str);
							}

				|			{
								Cmd_AddType(&info_s, CMD_IF);
							}
					IF condition THEN
							{
								if(PRINT) printf("\nbiso: po IF cond THEN\n");
								Ct_AddNode(&info_s);

								if(Cmd_UninitializedCondition_nowy(&info_s))
								{
									yyerror("Condition made of uninitalized value");
								}

								Cmd_Clear(&info_s);

								//free(yylval.str);
							}
						elses

				|	WHILE condition DO 
							{
								if(PRINT) printf("\nbiso: po WHILE DO\n");
								Cmd_AddType(&info_s, CMD_WHILE);
								Ct_AddNode(&info_s);

								Cmd_Clear(&info_s);
								//free(yylval.str);
							}
					commands ENDWHILE
							{
								Cmd_AddType(&info_s, CMD_ENDWHILE);
								Ct_AddNode(&info_s);

								Cmd_Clear(&info_s);
								//free(yylval.str);
							}

				/*|			{
								if(PRINT) printf("\nbiso: przed DO-WHILE\n");

								Cmd_AddType(&info_s, CMD_DO);
								Ct_AddNode(&info_s);
								
								Cmd_Clear(&info_s);
							}
					DO commands whiles
							{
								Cmd_AddType(&info_s, CMD_ENDDO);
								Ct_AddNode(&info_s);

								Cmd_Clear(&info_s);
								//free(yylval.str);
							}
					ENDDO*/
				|	 		{
								if(PRINT) printf("\nbiso: przed DO-WHILE new REPEAT UNTIL\n");

								Cmd_AddType(&info_s, CMD_DO);
								Ct_AddNode(&info_s);
								
								Cmd_Clear(&info_s);
							}
					REPEAT commands UNTIL condition
							{
								Cmd_AddType(&info_s, CMD_ENDDO);
								Ct_AddNode(&info_s);

								Cmd_Clear(&info_s);
								//free(yylval.str);
							}
					SEMICOLON

				|			{
								Cmd_AddType(&info_s, CMD_FOR);
							}
					FOR identifier FROM value upordown value DO
							{
                                if(PRINT) printf("\nbiso: fors-FOR\n");
								Ct_AddNode(&info_s);

								if(Cmd_UninitializedAssign_nowy(&info_s))
								{
									yyerror("FOR loop range uninitialized");
								}

								Cmd_Clear(&info_s);
							}
					commands ENDFOR
							{
								if(PRINT) printf("\nbiso: ENDFOR\n");
								Cmd_AddType(&info_s, CMD_ENDFOR);
								Ct_AddNode(&info_s);

								Cmd_Clear(&info_s);
							}

				|			{
								if(PRINT) printf("\nbiso: przed READ\n");
								Cmd_AddType(&info_s, CMD_READ);
							}
					READ identifier SEMICOLON
							{	
                                if(PRINT) printf("\nbiso: READ identifier SEMICOLON\n");
								Ct_AddNode(&info_s);

								Cmd_InitializedPid_nowy(&info_s);
								
								Cmd_Clear(&info_s);

								//free(yylval.str);
							}

				|			{
								if(PRINT) printf("\nbiso: przed WRITE\n");
								Cmd_AddType(&info_s, CMD_WRITE);
							}
					WRITE value SEMICOLON
							{
                                if(PRINT) printf("\nbiso: WRITE value SEMICOLON\n");
								Ct_AddNode(&info_s);

								if(Cmd_UninitializedWRITE_nowy(&info_s))
								{
									yyerror("Print of uninitalized value");
								}

								Cmd_Clear(&info_s);

								//free(yylval.str);
							}
;

	/*whiles			:	WHILE condition // było do obs. do while i while do
	;*/


elses			:	commands ENDIF 
							{
								Cmd_AddType(&info_s, CMD_ENDIF);
								Ct_AddNode(&info_s);

								Cmd_Clear(&info_s);
								//free(yylval.str);
							}
				|	commands 
							{
								Cmd_AddType(&info_s, CMD_ELSE);
								Ct_AddNode(&info_s);
								
								Cmd_Clear(&info_s);
							}
					ELSE commands ENDIF
							{
								Cmd_AddType(&info_s, CMD_ENDIF);
								Ct_AddNode(&info_s);
								
								Cmd_Clear(&info_s);
								//free(yylval.str);
							}
;

upordown		:	TO
							{
								if(PRINT) printf("\nbiso: TO\n");
								Cmd_AddType(&info_s, CMD_FOR);
							}

				|	DOWNTO
							{
								if(PRINT) printf("\nbiso: DOWNTO\n");
								Cmd_AddType(&info_s, CMD_FOR_DOWNTO);
							}
;

expression		:	value
							{
                                if(PRINT) printf("\nbiso: value\n");
								Cmd_AddExpr(&info_s, EXPR_NOTAPPLICABLE);
							}

				|	value PLUS value
							{
                                if(PRINT) printf("\nbiso: value PLUS value\n");
								Cmd_AddExpr(&info_s, EXPR_PLUS);
							}

				|	value MINUS value
							{
                                if(PRINT) printf("\nbiso: value MINUS value\n");
								Cmd_AddExpr(&info_s, EXPR_MINUS);
							}

				|	value MUL value
							{
                                if(PRINT) printf("\nbiso: value MUL value\n");
								Cmd_AddExpr(&info_s, EXPR_TIMES);
							}

				|	value DIV value
							{
                                if(PRINT) printf("\nbiso: value DIV value\n");
								Cmd_AddExpr(&info_s, EXPR_DIV);
							}

				|	value MOD value
							{
                                if(PRINT) printf("\nbiso: value MOD value\n");
								Cmd_AddExpr(&info_s, EXPR_MOD);
							}
;

condition		:	value EQ value
							{
                                if(PRINT) printf("\nbiso: value EQ value\n");
								
								Cmd_AddCond(&info_s, COND_EQ);
							}

				|	value DIFF value
							{
                                if(PRINT) printf("\nbiso: value DIFF value\n");\
								
								Cmd_AddCond(&info_s, COND_NEQ);
							}

				|	value LE value
							{
                                if(PRINT) printf("\nbiso: value LE value\n");
								
								Cmd_AddCond(&info_s, COND_LE);
							}

				|	value GE value
							{
                                if(PRINT) printf("\nbiso: value GE value\n");
								
								Cmd_AddCond(&info_s, COND_GE);
							}

				|	value LEQ value
							{					
                                if(PRINT) printf("\nbiso: value LEQ value\n");
								
								Cmd_AddCond(&info_s, COND_LEQ);
							}	

				|	value GEQ value
							{												
                                if(PRINT) printf("\nbiso: value GEQ value\n");
								
								Cmd_AddCond(&info_s, COND_GEQ);
							}
;

value			:	NUM		
							{
                                if(PRINT) printf("\nbiso: NUM %s\n", $1);
								
								if(Cplr_InSection_Declare(info_s))
								{/*-------------DECLARE--------------*/
									yyerror("invalid declaration");
								}
								else if(Cplr_InSection_Begin(info_s))
								{/*-------------BEGIN--------------*/
									Pid_AddToList_Number(&info_s, $1);

									cmd_pid_action_e = Cmd_AddPid(&info_s, $1);
									if(INVALIDPID == cmd_pid_action_e)
									{
										//yyerror2("invalid variable", $1);
										yyerror("invalid variable");
									}
									else if(ITERATOR_FAIL == cmd_pid_action_e)
									{
										yyerror("number cannot be a loop iterator");
									}
								}
								//free(yylval.str);
								//free(yylval.num);
								//free($1);
							}

				|	identifier
							{ 
                                if(PRINT) printf("\nbiso: identifier\n");
							}
;

identifier		:	PIDENTIFIER
							{
								if(PRINT) printf("\nbiso: PIDENTIFER |%s|\n", $1);
								
								if(Cplr_InSection_Declare(info_s))
								{/*-------------DECLARE--------------*/
									Pid_decRes_e dec_res = Pid_AddToList_Variable(&info_s, $1);
									if(DOUBLE_DECLARATION == dec_res)
									{
										//yyerror2("double declaration of variable", $1);
										yyerror("double declaration of variable");
									}
								}
								else if(Cplr_InSection_Begin(info_s))
								{/*-------------BEGIN--------------*/
    								/*Pid_node_ps pid_ps = Pid_FindByName(info_s.pid_listHead_cpps, $1);
									if(TYPE_ARRAY == pid_ps->type_e)
									{
										yyerror("wrong usage of array");
									}*/

									cmd_pid_action_e = Cmd_AddPidNotArray_nowy(&info_s, $1);
									if(INVALIDPID == cmd_pid_action_e)
									{
										//yyerror2("invalid variable", $1);
										yyerror("invalid variable");
									}
									else if(ITERATOR_FAIL == cmd_pid_action_e)
									{
										//yyerror2("invalid iterator", $1);
										yyerror("invalid iterator");
									}
								}
								//ree(yylval.str);
							}

				|	PIDENTIFIER ARRAY_INDEX_PID
							{
								if(PRINT) printf("\nbiso: PIDENTIFER %s ARRAY_INDEX_PID \"%s\"\n", $1, $2);
								if(Cplr_InSection_Declare(info_s))
								{/*-------------DECLARE--------------*/
									yyerror("Can't declare VLA");
								}
								else if(Cplr_InSection_Begin(info_s))
								{/*-------------BEGIN--------------*/
									//nothing yet to do
									cmd_pid_action_e = Cmd_AddArray_nowy(&info_s, $1, $2);
									if(INVALIDPID == cmd_pid_action_e)
									{
										//yyerror2("invalid variable", $1);
										yyerror("invalid variable");
									}
									else if(ITERATOR_FAIL == cmd_pid_action_e)
									{
										//yyerror2("invalid iterator", $1);
										yyerror("invalid iterator");
									}
									else if(VARIABLE_MISSUSAGE == cmd_pid_action_e)
									{
										yyerror("variable used as array");
									}
								}
								//free(yylval.str);
								//free($1);
								//free($2);
							}

				|	PIDENTIFIER ARRAY_INDEX_NUM
							{
								if(PRINT) printf("\nbiso: PIDENTIFER %s ARRAY_INDEX_NUM %s\n", $1, $2);
								if(Cplr_InSection_Declare(info_s))
								{/*-------------DECLARE--------------*/
									yyerror("Can't declare with single number try: array([number]:[higher number])");
								}
								else if(Cplr_InSection_Begin(info_s))
								{/*-------------BEGIN--------------*/
									Pid_AddToList_Number(&info_s, $2);
									
									cmd_pid_action_e = Cmd_AddArray_nowy(&info_s, $1, $2);
									if(INVALIDPID == cmd_pid_action_e)
									{
										//yyerror2("invalid variable", $1);
										yyerror("invalid variable");
									}
									else if(ITERATOR_FAIL == cmd_pid_action_e)
									{
										yyerror("invalid iterator");
									}
									else if(VARIABLE_MISSUSAGE == cmd_pid_action_e)
									{
										yyerror("variable used as array");
									}
								}
								//free($1);
								//free($2);
							}
;
%%


int main(int argc, char *argv[]) 
{
	if(2 >= argc)
	{
		ERROR_PRINT("expects file name");
	}

	FILE* data = fopen(argv[1], "r");

	FILE* output = fopen(argv[2], "w");

	info_s.outputFile = output;

	yyset_in( data );
	yyparse();

	fclose(output);
	fclose(data);

	return 0;
}
