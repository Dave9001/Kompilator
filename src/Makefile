CC=gcc
CFLAGS= -Wall -Wextra -Walloc-zero -Walloca -c

all: Kompilator

Kompilator: Types Pid Cmd Asm Ct Cplr Opt Ram bc.c bison.tab.c lex.yy.c
	$(CC) -o kompilator Pid_functions.o Cmd_functions.o Asm_instructions.o Asm_functions.o Ct_functions.o Cplr_functions.o Opt_functions.o Ram_functions.o bison.tab.c lex.yy.c -Wall -Wextra -Walloc-zero -Walloca

Types: Basic Pid_types Cmd_types Asm_types Ct_types Ram_types Cplr_types Opt_types
	

Basic: basic_types.h
	$(CC) basic_types.h $(CFLAGS)

Pid_types: Basic pid/Pid_types.h
	$(CC) pid/Pid_types.h $(CFLAGS)

Cmd_types: Basic Pid_types cmd/Cmd_types.h
	$(CC) cmd/Cmd_types.h $(CFLAGS)

Asm_types: Basic asm/Asm_types.h
	$(CC) asm/Asm_types.h $(CFLAGS)

Ct_types: Basic Asm_types Cmd_types ct/Ct_types.h
	$(CC) ct/Ct_types.h $(CFLAGS)

Ram_types: Basic Pid_types Ct_types ram/Ram_types.h
	$(CC) ram/Ram_types.h $(CFLAGS)

Cplr_types: Basic Ram_types Ct_types cplr/Cplr_types.h
	$(CC) cplr/Cplr_types.h $(CFLAGS)

Opt_types: Basic opt/Opt_types.h
	$(CC) opt/Opt_types.h $(CFLAGS)

Pid: Pid_types Cplr pid/Pid_functions.h pid/Pid_functions.c
	$(CC) pid/Pid_functions.h pid/Pid_functions.c $(CFLAGS)

Cmd: Cmd_types Cplr cmd/Cmd_functions.h cmd/Cmd_functions.c
	$(CC) cmd/Cmd_functions.h cmd/Cmd_functions.c $(CFLAGS)

Asm: Asm_types Asm_instr Ct asm/Asm_functions.h asm/Asm_functions.c
	$(CC) asm/Asm_functions.h asm/Asm_functions.c $(CFLAGS)

Asm_instr: Asm_types Ct_types Cplr_types asm/Asm_instructions.h asm/Asm_instructions.c
	$(CC) asm/Asm_instructions.h asm/Asm_instructions.c $(CFLAGS)

Ct: Ct_types Cplr Pid ct/Ct_functions.h ct/Ct_functions.c
	$(CC) ct/Ct_functions.h ct/Ct_functions.c $(CFLAGS)

Cplr: Cplr_types cplr/Cplr_functions.h cplr/Cplr_functions.c
	$(CC) cplr/Cplr_functions.h cplr/Cplr_functions.c $(CFLAGS)

Opt: Opt_types opt/Opt_functions.h opt/Opt_functions.c
	$(CC) opt/Opt_functions.h opt/Opt_functions.c $(CFLAGS)

Ram: Ram_types Cplr ram/Ram_functions.h ram/Ram_functions.c
	$(CC) ram/Ram_functions.h ram/Ram_functions.c $(CFLAGS)

lex.yy.c: flex.l
	flex flex.l

bison.tab.c: bison.y
	bison -dy -o bison.tab.c bison.y

bison.y: bc.c
	cp bc.c bison.y

