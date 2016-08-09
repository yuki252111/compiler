%{
/*
 * Lexer.l file
 * To generate the lexical analyzer run: "flex Lexer.l"
 */

#include "parser.h"
#include "defination.h"
#include <string.h>
%}

%option warn noyywrap nodefault yylineno reentrant bison-bridge
%option header-file="lexer.h"
%option outfile="lexer.cpp"

EXP ([Ee][-+]?[0-9]+)

%%
%{
	struct pcdata* pp=(struct pcdata*)yyextra;
%}

"+"	|
"-"	|
"/"	|
"*"	|
"%"	|
"~"	|
"&"	|
"|"	|
"="	|
"|"	|
","		|
";"		|
"("	|
")"	|
"["	|
"]"	{pp->tokens+=yytext[0]; return yytext[0];	}

">" {pp->tokens+=yytext; yylval->fn=1; return CMP; }
"<" { pp->tokens+=yytext;yylval->fn=2; return CMP; }
"<>" { pp->tokens+=yytext;yylval->fn=3; return CMP; }
"==" {pp->tokens+=yytext; yylval->fn=4; return CMP; }
">=" { pp->tokens+=yytext;yylval->fn=5; return CMP; }
"<=" {pp->tokens+=yytext; yylval->fn=6; return CMP; }
"->"  { pp->tokens+=yytext;return GET; }

"if"	{ pp->tokens+=yytext;return IF; }
"then"	{ pp->tokens+=yytext;return THEN; }
"else"	{ pp->tokens+=yytext;return ELSE; }
"endif"	{pp->tokens+=yytext; return ENDIF;}
"while"	{pp->tokens+=yytext; return WHILE; }
"endwhile"	{pp->tokens+=yytext; return ENDWHILE; }
"for"		{ pp->tokens+=yytext;return FOR; }
"from"	{ pp->tokens+=yytext;return FROM; }
"to"	{ pp->tokens+=yytext;return TO; }
"step"	{pp->tokens+=yytext; return STEP; }
"endfor"	{ pp->tokens+=yytext;return ENDFOR; }
"foreach"	{ pp->tokens+=yytext;return FOREACH; }
"in"	{ pp->tokens+=yytext;return YYIN;}
"endforeach" { pp->tokens+=yytext;return ENDFOREACH; }
"let"	{ pp->tokens+=yytext;return LET; }
"define" { pp->tokens+=yytext;return DEFINE;}
"endfunc"	{pp->tokens+=yytext; return ENDFUNC; }
"return"	{ pp->tokens+=yytext;return RETURN; }
"class"	{ pp->tokens+=yytext;return CLASS;}
"extends" {pp->tokens+=yytext; return EXTENDS;}
"endclass" { pp->tokens+=yytext;return ENDCLASS;}

"var"		{ pp->tokens+=yytext;return VAR;}
"as"		{ pp->tokens+=yytext;return AS;}
"of"		{ pp->tokens+=yytext;return OF;}
"char"	{ pp->tokens+=yytext;yylval->type=0; return TYPE;  }
"int"	{ pp->tokens+=yytext;yylval->type = 1; return TYPE; }
"double"	{pp->tokens+=yytext; yylval->type = 2; return TYPE; }
"void" { pp->tokens+=yytext;yylval->type = -1; return TYPE; }
"array"	{ pp->tokens+=yytext;return ARRAY; }

"sqrt"	{ pp->tokens+=yytext;yylval->fn=B_sqrt; return FUNC; }
"exp"	{pp->tokens+=yytext; yylval->fn=B_exp; return FUNC; }
"log"		{pp->tokens+=yytext; yylval->fn=B_log; return FUNC; }
"print" { pp->tokens+=yytext;yylval->fn=B_print; return FUNC; }

[\'|\"][^ \n\r][\'|\"]	{ pp->tokens+=yytext;yylval->c=yytext[1]; return TYPECHAR; }
[0-9]+{EXP}?		{pp->tokens+=yytext; yylval->i=atoi(yytext);return TYPEINT; }
[0-9]+"."[0-9]*{EXP}? { pp->tokens+=yytext;yylval->d=atof(yytext); return TYPEDOUBLE; }

[_a-zA-Z][_a-zA-Z0-9]* {pp->tokens+=yytext; char* t=new char[strlen(yytext)+1];
									strcpy_s(t,strlen(yytext)+1,yytext) ;
									yylval->name=t;
									return NAME; }

"//".*
[ \t]
\\n	
"\n" {pp->tokens+=yytext;}

.	{ yyerror(pp,"invalid character %s\n",yytext); }
<<EOF>>	{ return FILEEND; }
%%