#ifndef __OPT_TYPES_H__
#define __OPT_TYPES_H__

#include "../basic_types.h"

typedef struct tag_methods_set_s
{
    bool delete_unused_assign;
    bool un_satisfiable_condition;
    bool satisfiable_condition;
    bool known_value_of_expression;
    bool reposition_assign;
    bool reposition_read;
    bool delete_unnecessary_code;
}Opt_methods_s;
typedef Opt_methods_s const Opt_methods_cs;


#endif /*__OPT_TYPES_H__*/
