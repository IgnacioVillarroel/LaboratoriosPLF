%{
#include <stdio.h>
#include <stdlib.h>
extern int yylex();
void yyerror(char *s);
%}

%token "PROCEDURE"
%token "FUNCTION"
%token "PROGRAM" 
%token "INTEGER"
%token "BOOLEAN"
%token "FORWARD"
%token "REPEAT"
%token "DOWNTO"
%token "UNTIL"
%token "WHILE"
%token "CONST"
%token "BEGIN"
%token "TYPE"
%token "REAL"
%token "CHAR"
%token "THEN"
%token "ELSE"
%token "CASE"
%token "DIV"
%token "MOD"
%token "AND"
%token "NOT"
%token "FOR"
%token "VAR"
%token "END"
%token "IF"
%token "OF"
%token "DO"
%token "TO"
%token "OR"
%token "ASIGNACION"
%token "MENOR_IGUAL"
%token "DISTINTO"
%token "MAYOR_IGUAL"
%token ";"
%token "."
%token "="
%token ":"
%token ","
%token "+"
%token "-"
%token "'"
%token "("
%token ")"
%token "<"
%token ">"
%token "*"
%token "/"
%token "EXPONENCIAL"
%token "EXPONENCIAL"
%token "EXPONENCIAL"
%token "EXPONENCIAL"
%token "EXPONENCIAL"
%token "EXPONENCIAL"
%token "DECIMAL"
%token "ENTERO"
%token "IDENTIFICADOR"

%%
programa : "PROGRAM" "IDENTIFICADOR" ";" bloque "." ;
bloque : "END";
%%

void yyerror(char *s)
{
    printf("\nAn%clisis sint%cctico incorrecto.\n", 160, 160);
    exit(1);
}

void main(int argc, char const *argv[])
{
    if (argc > 1){
        printf("Error: Ingreso de par%cmetros en la l%cnea de comandos.",160, 161);
        printf("\nUso: sintac.exe\n");
        exit(1);
    }
    else{
        printf("\nIngrese el texto a analizar: ");
        int error = yyparse();
        if (error == 0){
            printf("\nAn%clisis sint%cctico correcto.\n", 160, 160);
            exit(1);
        }   
        else{
            printf("\nAn%clisis sint%cctico incorrecto.\n", 160, 160);
            exit(1);
        }
    }

}