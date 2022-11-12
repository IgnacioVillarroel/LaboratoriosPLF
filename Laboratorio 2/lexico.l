%{ 
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
%}
%option noyywrap

%%
'procedure' { fprintf(yyout, "PROCEDURE\n"); }
'function' { fprintf(yyout, "FUNCTION\n"); }
'program' { fprintf(yyout, "PROGRAM\n"); }
'integer' { fprintf(yyout, "INTEGER\n"); }
'boolean' { fprintf(yyout, "BOOLEAN\n"); }
'forward' { fprintf(yyout, "FORWARD\n"); }
'repeat' { fprintf(yyout, "REPEAT\n"); }
'downto' { fprintf(yyout, "DOWNTO\n"); }
'until' { fprintf(yyout, "UNTIL\n"); }
'while' { fprintf(yyout, "WHILE\n"); }
'const' { fprintf(yyout, "CONST\n"); }
'begin' { fprintf(yyout, "BEGIN\n"); }
'type' { fprintf(yyout, "TYPE\n"); }
'real' { fprintf(yyout, "REAL\n"); }
'char' { fprintf(yyout, "CHAR\n"); }
'then' { fprintf(yyout, "THEN\n"); }
'else' { fprintf(yyout, "ELSE\n"); }
'case' { fprintf(yyout, "CASE\n"); }
'div' { fprintf(yyout, "DIV\n"); }
'mod' { fprintf(yyout, "MOD\n"); }
'and' { fprintf(yyout, "AND\n"); }
'not' { fprintf(yyout, "NOT\n"); }
'for' { fprintf(yyout, "FOR\n"); }
'var' { fprintf(yyout, "VAR\n"); }
'end' { fprintf(yyout, "END\n"); }
'if' { fprintf(yyout, "IF\n"); }
'of' { fprintf(yyout, "OF\n"); }
'do' { fprintf(yyout, "DO\n"); }
'to' { fprintf(yyout, "TO\n"); }
'or' { fprintf(yyout, "OR\n"); }
'..' { fprintf(yyout, "RANGO\n"); }
':=' { fprintf(yyout, "ASIGNACION\n"); }
'<=' { fprintf(yyout, "MENOR IGUAL\n"); }
'<>' { fprintf(yyout, "DISTINTO\n"); }
'>=' { fprintf(yyout, "MAYOR IGUAL\n"); }
';' { fprintf(yyout, ";\n"); }
'.' { fprintf(yyout, ".\n"); }
'=' { fprintf(yyout, "=\n"); }
':' { fprintf(yyout, ":\n"); }
',' { fprintf(yyout, ",\n"); }
'+' { fprintf(yyout, "+\n"); }
'-' { fprintf(yyout, "-\n"); }
'`' { fprintf(yyout, "`\n"); }
'(' { fprintf(yyout, "(\n"); }
')' { fprintf(yyout, ")\n"); }
'<' { fprintf(yyout, "<\n"); }
'>' { fprintf(yyout, ">\n"); }
'*' { fprintf(yyout, "*\n"); }
'/' { fprintf(yyout, "/\n"); }
[0-9]+E[0-9]+ { fprintf(yyout, "EXPONENCIAL\n"); }
[0-9]+E
[0-9]+'.'[0-9]+ { fprintf(yyout, "DECIMAL"); }
[0-9]+ { fprintf(yyout, "ENTERO\n"); }
[_a-zA-Z][_a-zA-Z0-9]* { fprintf(yyout, "IDENTIFICADOR\n"); }
[\r\n]* {}
<<EOF>> { exit(0); }
%%

void main(int argc, char *argv[]) {

    char archivoEntrada[100], archivoSalida[100];

    if (argc < 2){
        printf("Error: Faltan par%cmetros.", 160);
        printf("\nUso: lexico.exe archivo_entrada archivo_salida \n");
    }

    else if (argc == 2){
        printf("Error: Falta par%cmetro.", 160);
        printf("\nUso: lexico.exe archivo_entrada archivo_salida\n");
    }

    else if (argc > 3){
        printf("Error: Demasiados par%cmetros.", 160);
        printf("\nUso: lexico.exe archivo_entrada archivo_salida\n");
    }

    else{
        strcpy(archivoEntrada,argv[1]);
        strcpy(archivoSalida,argv[2]);
        yyin = fopen(archivoEntrada, "r");
        yyout = fopen(archivoSalida, "r");
        if(yyin == NULL){
            printf("Error: El archivo de entrada no existe.\n");
        }
        else if(yyout != NULL){
            printf("Error: El archivo de salida ya existe.\n");
        }
        else{
            yyout = fopen(archivoSalida, "w");
            yylex();
            fclose(yyout);
        }
    }
}