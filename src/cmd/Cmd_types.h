#ifndef __CMD_TYPES_H__
#define __CMD_TYPES_H__

#include "../basic_types.h"
#include "../pid/Pid_types.h"

typedef enum tag_Cmd_pidAction_e
{
    CORRECTPID,
    UNKNOWNPID,
    INVALIDPID,
    ITERATOR_FAIL,
    VARIABLE_MISSUSAGE
}Cmd_pidAction_e;
typedef Cmd_pidAction_e const Cmd_pidAction_ce;

typedef enum tag_Cmd_expr_type_e
{
    EXPR_NOTAPPLICABLE,
    //EXPR_NUMBER,
    //EXPR_PID,
    EXPR_PLUS,
    EXPR_MINUS,
    EXPR_TIMES,
    EXPR_DIV,
    EXPR_MOD
}Cmd_exprType_e;
typedef Cmd_exprType_e const Cmd_exprType_ce;

typedef enum tag_Cmd_condType_e
{
    COND_NOTAPPLICABLE,
    COND_EQ,
    COND_NEQ,
    COND_LE,
    COND_GE,
    COND_LEQ,
    COND_GEQ
}Cmd_condType_e;
typedef Cmd_condType_e const Cmd_condType_ce;

typedef enum tag_Cmd_type_e
{
    CMD_EMPTY,
    CMD_ASSIGN,
    CMD_IF,
    CMD_ELSE,
    CMD_ENDIF,
    CMD_WHILE,
    CMD_DO,        // -> DO <- commands WHILE condition ENDDO
    CMD_WHILE_DO,  //    DO commands -> WHILE <- condition ENDDO
    CMD_ENDWHILE,
    CMD_ENDDO,
    CMD_FOR,
    CMD_FOR_DOWNTO,
    CMD_ENDFOR,
    CMD_READ,
    CMD_WRITE,
    CMD_END
}Cmd_type_e;
typedef Cmd_type_e const Cmd_type_ce;

typedef struct tag_Cmd_command_s
{
    Pid_node_s *pid_1_ps;
    Pid_node_s *pid_2_ps;
    Pid_node_s *pid_3_ps;
    //Pid_node_s *pid_4_ps;

    Pid_node_s *index_1_ps;
    Pid_node_s *index_2_ps;
    Pid_node_s *index_3_ps;

    Cmd_type_e type_e;
    Cmd_condType_e condition_e;
    Cmd_exprType_e expression_e;
}Cmd_command_s;
typedef Cmd_command_s * Cmd_command_ps;
typedef Cmd_command_s const Cmd_command_cs;
typedef Cmd_command_s *const Cmd_command_cps;



#endif /*__CMD_TYPES_H__*/
