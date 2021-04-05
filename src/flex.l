
%option noyywrap
%option yylineno
%{
    #include<stdio.h>
	#include "bison.tab.h"
	#include "basic_types.h"
	#define PRINT (FALSE)

	int yylex();
	int line_num = 1;
	_Bool comment = FALSE;
	_Bool ENDPRINTDECORATOR = TRUE;
	void yyerror(const char *);
%}

%%


[ \t]+			{}
\n				{ line_num++; if(PRINT) printf("\nflex: %d: \n",line_num); if(ENDPRINTDECORATOR) puts(""); }
"["				{
					int c;
					
					while(1){
					
						while( (c = input()) != ']' && c != EOF )
							;
							
						if( c == ']' )
						{							
							break;
						}
						
						if( c == EOF ){
							yyerror( "EOF in comment" );
							break;
						}
					}
				}

DECLARE			{ if(PRINT) printf("\nflex: %d: %s ",line_num, yytext); if(!comment) return(DECLARE);	}
BEGIN			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(IN);	}
END				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) {ENDPRINTDECORATOR = TRUE; return(END);} 	}
READ			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(READ); 	}
WRITE			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(WRITE); }
IF				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(IF); 	}
THEN			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(THEN); 	}
ELSE			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(ELSE); 	}
ENDIF			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(ENDIF); }
WHILE			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(WHILE); }
FOR				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(FOR); 	}
DO				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(DO); 	}
DOWNTO			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(DOWNTO);}
FROM			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(FROM); 	}
TO				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(TO); 	}
ENDWHILE		{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(ENDWHILE);}
	/*ENDDO			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(ENDDO); }*/
ENDFOR			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(ENDFOR);}
	/*ASSIGN			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(ASSIGN);}*/
	/*PLUS			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(PLUS); 	}*/
	/*MINUS			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(MINUS); }*/
	/*TIMES		    { if(PRINT) printf("flex: %s ",yytext); if(!comment) return(MUL); 	}*/
	/*DIV				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(DIV); 	}*/
	/*MOD				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(MOD); 	}*/
	/*EQ				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(EQ); 	}*/
	/*NEQ			    { if(PRINT) printf("flex: %s ",yytext); if(!comment) return(DIFF); 	}*/
	/*LE				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(LE); 	}*/
	/*GE				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(GE); 	}*/
	/*LEQ			    { if(PRINT) printf("flex: %s ",yytext); if(!comment) return(LEQ); 	}*/
	/*GEQ			    { if(PRINT) printf("flex: %s ",yytext); if(!comment) return(GEQ); 	}*/

	/*****new******/
REPEAT			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(REPEAT);}
UNTIL			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(UNTIL); }
":="			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(ASSIGN);}
\+				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(PLUS); 	}
\-				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(MINUS); }
\*		    	{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(MUL); 	}
\/				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(DIV); 	}
\%				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(MOD); 	}
\=				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(EQ); 	}
"!="			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(DIFF); 	}
\<				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(LE); 	}
\>				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(GE); 	}
"<="			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(LEQ); 	}
">="			{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(GEQ); 	}





\,				{ if(PRINT) printf("flex: %s ",yytext); if(!comment) return(COMMA);}

	/*\-[0-9]+\)		{
					if(!comment)
					{
						char * left = strdup(yytext);
						int i = 0;
						while(left[i] != ')')
						{
							i++;
						}
						left[i] = '\0';

						yylval.num = strdup(left);
						free(left);
						if(PRINT) printf("flex: %s ",yylval.num); 
						return(RIGHT_LIM);
					}
				}*/

[0-9]+[ \t\n]*\)		{
					if(!comment)
					{
						char * left = strdup(yytext);
						int i = 0;
						while(left[i] != ')')
						{
							i++;
						}
						left[i] = '\0';

						yylval.num = strdup(left);
						free(left);
						if(PRINT) printf("flex: %s ",yylval.num); 
						return(RIGHT_LIM);
					}
				}

	/*\-[0-9]+		{
				  	if(!comment)
					{
						yylval.num = strdup(yytext);
						if(PRINT) printf("flex: %s ",yylval.num); 
						return(NEG_NUM);
					}
					
				}*/

[0-9]+			{
				  	if(!comment)
					{
						yylval.num = strdup(yytext);
						if(PRINT) printf("flex: %s ",yylval.num); 
						return(NUM);
					}
					
				}

[0-9]+[a-z]+	{ if(!comment) yyerror("Unexpected format of data");}
[0-9]+[A-Z]+	{ if(!comment) yyerror("Unexpected format of data");}

\([ \t\n]*[0-9]+[ \t\n]*\)		{
					if(!comment)
					{
						char * left = strdup(yytext);
						char c = '1';
						int i = 0;
						while(c != '\0')
						{
							left[i] = left[i+1];
							i++;

							c = left[i];
						}
						left[i - 2] = '\0';

						yylval.num = strdup(left);
						free(left);
						if(PRINT) printf("flex: %s ",yylval.num); 
						return(ARRAY_INDEX_NUM);
					}
				}
	/*\(\-[0-9]+\)		{
					if(!comment)
					{
						char * left = strdup(yytext);
						char c = '1';
						int i = 0;
						while(c != '\0')
						{
							left[i] = left[i+1];
							i++;

							c = left[i];
						}
						left[i - 2] = '\0';

						yylval.num = strdup(left);
						free(left);
						if(PRINT) printf("flex: %s ",yylval.num); 
						return(ARRAY_INDEX_NUM);
					}
				}*/

	/*\(\-[0-9]+\:	{
					if(!comment)
					{
						char * left = strdup(yytext);
						char c = '1';
						int i = 0;
						while(c != '\0')
						{
							left[i] = left[i+1];
							i++;

							c = left[i];
						}
						left[i - 2] = '\0';

						yylval.num = strdup(left);
						free(left);
						if(PRINT) printf("flex: %s ",yylval.num); 
						return(LEFT_LIM);
					}
				}*/

\([ \t\n]*[0-9]+[ \t\n]*\:		{
					if(!comment)
					{
						char * left = strdup(yytext);
						char c = '1';
						int i = 0;
						while(c != '\0')
						{
							left[i] = left[i+1];
							i++;

							c = left[i];
						}
						left[i - 2] = '\0';

						yylval.num = strdup(left);
						free(left);
						if(PRINT) printf("flex: %s ",yylval.num); 
						return(LEFT_LIM);
					}
				}

\([ \t\n]*[_a-z]+[ \t\n]*\)		{
					if(!comment)
					{
						char * left = strdup(yytext);
						char c = '1';
						int i = 0;
						while(c != '\0')
						{
							left[i] = left[i+1];
							i++;

							c = left[i];
						}
						left[i - 2] = '\0';

						yylval.str = strdup(left);
						free(left);
						if(PRINT) printf("flex: %s ",yylval.str); 
						return(ARRAY_INDEX_PID);
					}
				}

\([ \t\n]*[_A-Z]+[ \t\n]*\)		{
					if(!comment)
					{
						char * left = strdup(yytext);
						char c = '1';
						int i = 0;
						while(c != '\0')
						{
							left[i] = left[i+1];
							i++;

							c = left[i];
						}
						left[i - 2] = '\0';

						yylval.str = strdup(left);
						free(left);
						if(PRINT) printf("flex: %s ",yylval.str); 
						return(ARRAY_INDEX_PID);
					}
				}

[_a-z]+			{
					if(!comment)
					{
						yylval.str = strdup(yytext);
						if(PRINT) printf("flex: %s ",yylval.str); 
						return(PIDENTIFIER);
					}
				}

[_A-Z]+			{
					if(!comment)
					{
						yylval.str = strdup(yytext);
						if(PRINT) printf("flex: %s ",yylval.str); 
						return(PIDENTIFIER);
					}
				}

[a-z]+[0-9]+ 	{ if(!comment) yyerror("Unexpected format of data");}
[A-Z]+[0-9]+ 	{ if(!comment) yyerror("Unexpected format of data");}


\;				{
					if(!comment)
					{
						/*yylval.str = strdup(yytext);*/
						/*if(PRINT) printf("flex: %s ",yytext);*/
						return(SEMICOLON);
					}
				}
.				{	if(!comment) yyerror("Unexpected character"); }
%%
/*
int main(int argc, char* argv[]) {
    FILE *fh;

    if (argc == 2 && (fh = fopen(argv[1], "r")))
        yyin = fh;
    yylex();
    return 0;
}*/

void yyerror (char const *str)
{
	printf("Error: \"%s\": \"%s\" in line: %d\n", str, yytext, yylineno);
	exit(0);
}
