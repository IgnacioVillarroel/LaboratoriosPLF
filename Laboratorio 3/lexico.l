%{ 
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
%}
%option noyywrap

%%
"procedure" {return "PROCEDURE";}
"function" {return "FUNCTION"; }
"program" {return "PROGRAM"; }
"integer" {return "INTEGER"; }
"boolean" {return "BOOLEAN"; }
"forward" {return "FORWARD"; }
"repeat" {return "REPEAT"; }
"downto" {return "DOWNTO"; }
"until" {return "UNTIL"; }
"while" {return "WHILE"; }
"const" {return "CONST"; }
"begin" {return "BEGIN"; }
"type" {return "TYPE"; }
"real" {return "REAL"; }
"char" {return "CHAR"; }
"then" {return "THEN"; }
"else" {return "ELSE"; }
"case" {return "CASE"; }
"div" {return "DIV"; }
"mod" {return "MOD"; }
"and" {return "AND"; }
"not" {return "NOT"; }
"for" {return "FOR"; }
"var" {return "VAR"; }
"end" {return "END"; }
"if" {return "IF"; }
"of" {return "OF"; }
"do" {return "DO"; }
"to" {return "TO"; }
"or" {return "OR"; }
".." {return "RANGO"; }
":=" {return "ASIGNACION"; }
"<=" {return "MENOR_IGUAL"; }
"<>" {return "DISTINTO"; }
">=" {return "MAYOR_IGUAL"; }
";" {return ";"; }
"." {return "."; }
"=" {return "="; }
":" {return ":"; }
"," {return ","; }
"+" {return "+"; }
"-" {return "-"; }
"'" {return "'"; }
"(" {return "("; }
")" {return ")"; }
"<" {return "<"; }
">" {return ">"; }
"*" {return "*"; }
"/" {return "/"; }
[0-9]+E[0-9]+ { return "EXPONENCIAL"; }
[0-9]+E"+"[0-9]+ {return "EXPONENCIAL";}
[0-9]+E"-"[0-9]+ {return "EXPONENCIAL";}
[0-9]+"."[0-9]+E[0-9]+ {return "EXPONENCIAL";}
[0-9]+"."[0-9]+E"+"[0-9]+ {return "EXPONENCIAL";}
[0-9]+"."[0-9]+E"-"[0-9]+ {return "EXPONENCIAL";}
[0-9]+"."[0-9]+ { return "DECIMAL"; }
[0-9]+ {return "ENTERO"; }
[_a-zA-Z][_a-zA-Z0-9]* {return "IDENTIFICADOR"; }
\n {return EOF;}

%%