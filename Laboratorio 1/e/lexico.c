//Autor: Carlos Retamales
//Ramo: Procesamiento de lenguajes formales (PLF)
//Profesora: Consuelo Ramírez

//LIBRERIAS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <sys/stat.h>


// FUNCIONES
void iniAnalizadorLexico(char const *entradas[]);
void readLexemas(FILE *arch_entrada,FILE * arch_salida,const char * arch_name);
int checkInputs(int cantidad_entradas, char const *entradas[]);
void isComponenteLexico(FILE * arch_salida,char * linea_arch);
void writeComponent(FILE * arch_salida,int tipo);

// DESARROLLO DE FUNCIONES

//- checkInputs
// Entrada: entero (cantidad de entradas), lista de constante char (entradas) 
// Descripcion: dado los inputs por consola analiza si estas son validas para hacer el analizador lexico
// Salida: un entero que representa un booleano 0 si es no es valido y 1 si es valido hacer el analizador lexico

int checkInputs(int cantidad_entradas, char const *entradas[])
{   
    //Si la son más parametros 
    if (cantidad_entradas>3)
    {
        printf("Error: Demasiados par%cmetros.\nUso: lexico.exe archivo_entrada archivo_salida\n",-31);
        return 0;
    }
    else if (cantidad_entradas<3) //Si no ingresa todos
    {
        if(cantidad_entradas == 2) //Si le falta 1
        {
            printf("Error: Falta par%cmetroS.\nUso: lexico.exe archivo_entrada archivo_salida\n",-31);
            return 0;
        }
        else //Si le falta más de 1
        {
            printf("Error: Faltan par%cmetros.\nUso: lexico.exe archivo_entrada archivo_salida\n",-31);
            return 0;
        }
    }
    else //Si la cantidad entradas esta ok
    {
        FILE *aux;
        aux = fopen(entradas[1],"r");
        //Si el archivo de entrada existe en el directorio
        if(aux == NULL)
        {
            printf("Error:El archivo de entrada no existe.\n");
            return 0;
        }
        aux = fopen(entradas[2],"r");
        if(aux !=NULL)
        {
            printf("Error:El archivo de salida ya existe.\n");
            return 0; 
        }
        return 1;
    }
    return 0;
} 

//- iniAnalizadorLexico
// Entrada:  lista constantes char (entradas)
// Descripcion: inicializa el analizador lexico
// Salida: ninguna, pero escribe un archivo de salida

void iniAnalizadorLexico(char const *entradas[])
{
    //Inicializa los archivos de entrada y salida 
    FILE *arch_entrada;
    FILE *arch_salida;
    arch_entrada = fopen(entradas[1],"r");
    arch_salida = fopen(entradas[2],"w");
    //Recorre el archivo para escribir 
    readLexemas(arch_entrada,arch_salida,entradas[1]);
    return;
}

//- readLexemas
// Entrada: un archivo de entrada, un archivo de salida, el nombre del archivo de entrada
// Descripcion: Toma linea a linea del archivo de entrada y hace el analizador lexico
// Salida:ninguna 

void readLexemas(FILE *arch_entrada,FILE *arch_salida,const char *arch_name)
{
    struct stat tam;
    stat(arch_name, &tam);
    char *linea_arch = malloc(tam.st_size);
    
    //Lee linea por linea para ver los lexemas generados
    while(fscanf(arch_entrada,"%[^\n] ",linea_arch) != EOF)
    {
        isComponenteLexico(arch_salida,linea_arch);
    }
    //Se cierran los archivos
    fclose(arch_entrada);
    fclose(arch_salida);
}

//- isComponent
// Entrada: Un caracter
// Descripcion: toma el caracter y evalua cual tipo de componente lexico corresponde
// Salida: un entero que representa un id de tipo de componente lexico

int isComponent(char caracter)
{
    char actual[2] = {caracter,'\0'};
    //TERMINALES
    //Entero
    if(strcmp("0",actual)==0 || strcmp("1",actual)==0 || strcmp("2",actual)==0 || strcmp("3",actual)==0 || strcmp("4",actual)==0 || strcmp("5",actual)==0 || strcmp("6",actual)==0 || strcmp("7",actual)==0 || strcmp("8",actual)==0 || strcmp("9",actual)==0)
    {
        return 1;
    }
    else if(strcmp(".",actual)==0)//posible real
    {
        return 2;
    }
    else if(strcmp("+",actual)==0) //suma
    {
        return 3;
    }
    else if(strcmp("-",actual)==0)//resta
    {
        return 4;
    }
    else if(strcmp("/",actual)==0)//division
    {
        return 5;
    }
    else if(strcmp("*",actual)==0)//multiplicacion
    {
        return 6;
    }
    else if(strcmp("(",actual)==0)//parentesis
    {
        return 71;
    }
    else if(strcmp(")",actual)==0)//parentesis
    {
        return 72;
    }
    else if(strcmp("'",actual)==0)
    {
        return 8;
    }
    else if(strcmp(";", actual)==0)
    {
        return 9;
    }
    else if(strcmp("=", actual)==0)
    {
        return 10;
    }
    else if (strcmp(":", actual)==0)
    {
        return 11;
    }
    /*else if(strcmp("<", actual)==0)
    {
        return 12;
    }
    else if(strcmp(">", actual)==0)
    {
        return 13;
    }*/
    else if(strcmp("a",actual)==0 || strcmp("b",actual)==0 || strcmp("c",actual)==0 || strcmp("d",actual)==0 || strcmp("e",actual)==0 || strcmp("f",actual)==0 || strcmp("g",actual)==0 || strcmp("h",actual)==0 
        || strcmp("i",actual)==0 || strcmp("j",actual)==0 || strcmp("k",actual)==0 || strcmp("l",actual)==0 || strcmp("m",actual)==0 || strcmp("n",actual)==0 || strcmp("o",actual)==0 || strcmp("p",actual)==0 
        || strcmp("q",actual)==0 || strcmp("r",actual)==0 || strcmp("s",actual)==0 || strcmp("t",actual)==0 || strcmp("u",actual)==0 || strcmp("v",actual)==0 || strcmp("w",actual)==0 || strcmp("y",actual)==0
        || strcmp("<",actual)==0 || strcmp(">",actual)==0)
    {
        return 14;//puede ser mod o int
    }
    
    else 
    {
        return 0;//ninguno de los lexemas aceptados, es decir, terminales
    }
    return 0;
}

//- writeComponent
// Entrada: archivo de salida y el tipo de componente lexico que es 
// Descripcion: Escribe en un archivo de salida con formato, el tipo de componente que es 
// Salida: ninguna, pero escribe en el archivo de salida 

void writeComponent(FILE * arch_salida,int tipo)
{
    if(tipo == 1)
    {
        fprintf(arch_salida,"%s\n","ENTERO");
    }
    else if(tipo == 2)
    {
        fprintf(arch_salida,"%s\n","DECIMAL");
    }
    else if(tipo == 3)
    {
        fprintf(arch_salida,"%s\n","+");
    }
    else if(tipo == 4)
    {
        fprintf(arch_salida,"%s\n","-");
    }
    else if(tipo == 5)
    {
        fprintf(arch_salida,"%s\n","/");
    }
    else if(tipo == 6)
    {
        fprintf(arch_salida,"%s\n","*");
    }
    else if(tipo == 71)
    {
        fprintf(arch_salida,"%s\n","(");
    }
    else if(tipo == 72)
    {
        fprintf(arch_salida,"%s\n",")");
    }
    else if(tipo == 8)
    {
        fprintf(arch_salida,"%s\n","'");
    }
    else if(tipo == 9)
    {
        fprintf(arch_salida,"%s\n",";");
    }
    else if(tipo == 10)
    {
        fprintf(arch_salida, "%s\n","=");
    }
    else if(tipo == 11)
    {
        fprintf(arch_salida, "%s\n",":");
    }
    else if(tipo == 12)
    {
        fprintf(arch_salida, "%s\n","<");
    }
    else if(tipo == 13)
    {
        fprintf(arch_salida, "%s\n",">");
    }
    else if(tipo == 14)
    {
        fprintf(arch_salida,"%s\n","FOR"); // 3 letras
    }
    else if(tipo == 15)
    {
        fprintf(arch_salida,"%s\n","VAR");
    }
    else if(tipo == 16)
    {
        fprintf(arch_salida,"%s\n","DIV");
    }
    else if(tipo == 17)
    {
        fprintf(arch_salida,"%s\n","END");
    }
    else if(tipo == 18)
    {
        fprintf(arch_salida,"%s\n","MOD");
    }
    else if(tipo == 19)
    {
        fprintf(arch_salida,"%s\n","AND");
    }
    else if(tipo == 20)
    {
        fprintf(arch_salida,"%s\n","NOT");
    }
    else if(tipo == 21)
    {
        fprintf(arch_salida,"%s\n","IF"); // 2 letras
    }
    else if(tipo == 22)
    {
        fprintf(arch_salida,"%s\n","TO");
    }
    else if(tipo == 23)
    {
        fprintf(arch_salida,"%s\n","OR");
    }
    else if(tipo == 24)
    {
        fprintf(arch_salida,"%s\n","DO");
    }
    else if(tipo == 25)
    {
        fprintf(arch_salida,"%s\n","OF");
    }
    else if(tipo == 26)
    {
        fprintf(arch_salida,"%s\n","THEN"); // 4 letras
    }
    else if(tipo == 27)
    {
        fprintf(arch_salida,"%s\n","ELSE");
    }
    else if(tipo == 28)
    {
        fprintf(arch_salida,"%s\n","CASE");
    }
    else if(tipo == 29)
    {
        fprintf(arch_salida,"%s\n","TYPE");
    }
    else if(tipo == 30)
    {
        fprintf(arch_salida,"%s\n","REAL");
    }
    else if(tipo == 31)
    {
        fprintf(arch_salida,"%s\n","CHAR");
    }
    else if(tipo == 32)
    {
        fprintf(arch_salida,"%s\n","CONST"); // 5 letras
    }
    else if(tipo == 33)
    {
        fprintf(arch_salida,"%s\n","BEGIN");
    }
    else if(tipo == 34)
    {
        fprintf(arch_salida,"%s\n","WHILE");
    }
    else if(tipo == 35)
    {
        fprintf(arch_salida,"%s\n","UNTIL");
    }
    else if(tipo == 36)
    {
        fprintf(arch_salida,"%s\n","DOWNTO"); // 6 letras
    }
    else if(tipo == 37)
    {
        fprintf(arch_salida,"%s\n","REPEAT");
    }
    else if(tipo == 38)
    {
        fprintf(arch_salida,"%s\n","PROGRAM"); // 7 letras
    }
    else if(tipo == 39)
    {
        fprintf(arch_salida,"%s\n","INTEGER");
    }
    else if(tipo == 40)
    {
        fprintf(arch_salida,"%s\n","BOOLEAN");
    }
    else if(tipo == 41)
    {
        fprintf(arch_salida,"%s\n","FORWARD");
    }
    else if(tipo == 42)
    {
        fprintf(arch_salida,"%s\n","FUNCTION"); //8 LETRAS
    }
    else if(tipo == 43)
    {
        fprintf(arch_salida,"%s\n","PROCEDURE");
    }
    else if(tipo == 44)
    {
        fprintf(arch_salida,"%s\n","RANGO");
    }
    else if(tipo == 45)
    {
        fprintf(arch_salida,"%s\n","ASIGNACION");
    }
    else if(tipo == 46)
    {
        fprintf(arch_salida,"%s\n","MENOR_IGUAL");
    }
    else if(tipo == 47)
    {
        fprintf(arch_salida,"%s\n","DISTINTO");
    }
    else if(tipo == 48)
    {
        fprintf(arch_salida,"%s\n","MAYOR_IGUAL");
    }
    else
    {
        return;
    }
    return;
}

//- isComponenteLexico
// Entrada: el archivo de salida, y una de las lineas del archivo de entrada 
// Descripcion: Recorre la linea, analizando si hay lexemas que correspondan a un componente lexico
// Salida: ninguna

void isComponenteLexico(FILE * arch_salida,char * linea_arch)
{
    
    int cantidad_caracteres = strlen(linea_arch);
    int allLine = 0, i = 0,tipo,tipo_aux,paso=0;

    //Si aun no reviso toda la linea hace algo 
    while(!allLine)
    {
        //si no excedo la cantidad de caracteres que tiene la linea
        if(i < cantidad_caracteres)
        {
            tipo = isComponent(linea_arch[i]);
            //printf("> %c | ",linea_arch[i]);
            //ver el siguiente para ver si hay un componente de mayor tamano
            if(i+1 < cantidad_caracteres)
            {
                tipo_aux = isComponent(linea_arch[i+1]);
                //puede ser un real o un entero
                if(tipo == 1 && tipo_aux == 2)
                {
                    int cantidad = 0;
                    i = i + 2;
                    //Analizo hasta llegar un componente distinto de entero
                    while(tipo == 1 && i<cantidad_caracteres)
                    {
                        
                        tipo = isComponent(linea_arch[i]);
                        if(tipo == 1)
                        {
                            cantidad++;
                        }
                        i++;
                    }
                    if(cantidad>0) //si hay al menos 1 o mas sera un real 
                    {
                        writeComponent(arch_salida,2);
                        paso = 1;
                    }
                    else //sino sera un entero
                    {
                        writeComponent(arch_salida,1);
                        paso = 1;
                    }
                    i=i-2;
                }
                if(tipo == 1 && tipo_aux == 1)
                {
                    i = i + 2;
                    //Se analiza la parte del entero hasta llegar un componente distinto
                    while(tipo == 1 && i<cantidad_caracteres)
                    {
                        tipo = isComponent(linea_arch[i]);
                        i++;
                    }
                    if(tipo == 2) //puede ser un real largo
                    {
                        //printf("aca = %c\n",linea_arch[i]);
                        int cantidad = 0;
                        tipo = isComponent(linea_arch[i]);
                        while(tipo == 1 && i<cantidad_caracteres)
                        {
                            //printf("Aca = %c\n",linea_arch[i]);
                            tipo = isComponent(linea_arch[i]);
                            if(tipo == 1)
                            {
                                cantidad++;
                            }
                            i++;
                        }
                        if(cantidad>0) //es un numero decimal
                        {
                            writeComponent(arch_salida,2);
                            paso = 1;
                        }
                        else // es un numero entero
                        {
                            writeComponent(arch_salida,1);
                            paso = 1;
                        }
                        //i--;
                        i = i - 2;
                    }
                    else
                    {
                        //printf("ANOTA UN 1\n");
                        writeComponent(arch_salida,1);
                        paso = 1;
                        i--;
                    }
                }
                if (tipo == 14 && tipo_aux == 14 && i+8<cantidad_caracteres)//  PARA 10 LETRAS
                {   
                    if(isComponent(linea_arch[i+8])==14)
                    {
                        char aux[10] = {linea_arch[i],linea_arch[i+1],linea_arch[i+2],linea_arch[i+3],linea_arch[i+4],linea_arch[i+5],linea_arch[i+6],linea_arch[i+7],linea_arch[i+8],'\0'};
                        if(strcmp(aux,"procedure")==0)
                        {
                            writeComponent(arch_salida,43);
                            paso = 1;
                        }
                        if(paso == 1)
                        {
                            i = i+8;
                        }
                    }
                }
                if (tipo == 14 && tipo_aux == 14 && i+7<cantidad_caracteres)//  PARA 9 LETRAS
                {   
                    if(isComponent(linea_arch[i+7])==14)
                    {
                        char aux[9] = {linea_arch[i],linea_arch[i+1],linea_arch[i+2],linea_arch[i+3],linea_arch[i+4],linea_arch[i+5],linea_arch[i+6],linea_arch[i+7],'\0'};
                        if(strcmp(aux,"function")==0)
                        {
                            writeComponent(arch_salida,42);
                            paso = 1;
                        }
                        if(paso == 1)
                        {
                            i = i+7;
                        }
                    }
                }
                if (tipo == 14 && tipo_aux == 14 && i+6<cantidad_caracteres)// PARA 7 LETRAS
                {   
                    if(isComponent(linea_arch[i+6])==14)
                    {
                        char aux[8] = {linea_arch[i],linea_arch[i+1],linea_arch[i+2],linea_arch[i+3],linea_arch[i+4],linea_arch[i+5],linea_arch[i+6],'\0'};
                        if(strcmp(aux,"program")==0)
                        {
                            writeComponent(arch_salida,38);
                            paso = 1;
                        }
                        if(strcmp(aux,"integer")==0)
                        {
                            writeComponent(arch_salida,39);
                            paso = 1;
                        }
                        if(strcmp(aux,"boolean")==0)
                        {
                            writeComponent(arch_salida,40);
                            paso = 1;
                        }
                        if(strcmp(aux,"forward")==0)
                        {
                            writeComponent(arch_salida,41);
                            paso = 1;
                        }
                        if(paso == 1)
                        {
                            i = i+6;
                        }
                    }
                }
                if (tipo == 14 && tipo_aux == 14 && i+5<cantidad_caracteres)// PARA 6 LETRAS
                {   
                    if(isComponent(linea_arch[i+5])==14)
                    {
                        char aux[7] = {linea_arch[i],linea_arch[i+1],linea_arch[i+2],linea_arch[i+3],linea_arch[i+4],linea_arch[i+5],'\0'};
                        if(strcmp(aux,"downto")==0)
                        {
                            writeComponent(arch_salida,36);
                            paso = 1;
                        }
                        if(strcmp(aux,"repeat")==0)
                        {
                            writeComponent(arch_salida,37);
                            paso = 1;
                        }
                        if(paso == 1)
                        {
                            i = i+5;
                        }
                    }
                }
                if (tipo == 14 && tipo_aux == 14 && i+4<cantidad_caracteres)// PARA 5 LETRAS
                {   
                    if(isComponent(linea_arch[i+4])==14)
                    {
                        char aux[6] = {linea_arch[i],linea_arch[i+1],linea_arch[i+2],linea_arch[i+3],linea_arch[i+4],'\0'};
                        if(strcmp(aux,"const")==0)
                        {
                            writeComponent(arch_salida,32);
                            paso = 1;
                        }
                        if(strcmp(aux,"begin")==0)
                        {
                            writeComponent(arch_salida,33);
                            paso = 1;
                        }
                        if(strcmp(aux,"while")==0)
                        {
                            writeComponent(arch_salida,34);
                            paso = 1;
                        }
                        if(strcmp(aux,"until")==0)
                        {
                            writeComponent(arch_salida,35);
                            paso = 1;
                        }
                        if(paso == 1)
                        {
                            i = i+4;
                        }
                    }
                }
                if (tipo == 14 && tipo_aux == 14 && i+3<cantidad_caracteres)// PARA 4 LETRAS
                {   
                    if(isComponent(linea_arch[i+3])==14)
                    {
                        char aux[5] = {linea_arch[i],linea_arch[i+1],linea_arch[i+2],linea_arch[i+3],'\0'};
                        if(strcmp(aux,"then")==0)
                        {
                            writeComponent(arch_salida,26);
                            paso = 1;
                        }
                        if(strcmp(aux,"else")==0)
                        {
                            writeComponent(arch_salida,27);
                            paso = 1;
                        }
                        if(strcmp(aux,"case")==0)
                        {
                            writeComponent(arch_salida,28);
                            paso = 1;
                        }
                        if(strcmp(aux,"type")==0)
                        {
                            writeComponent(arch_salida,29);
                            paso = 1;
                        }
                        if(strcmp(aux,"real")==0)
                        {
                            writeComponent(arch_salida,30);
                            paso = 1;
                        }
                        if(strcmp(aux,"char")==0)
                        {
                            writeComponent(arch_salida,31);
                            paso = 1;
                        }
                        if(paso == 1)
                        {
                            i = i+3;
                        }
                    }
                }
                if (tipo == 14 && tipo_aux == 14 && i+2<cantidad_caracteres) // PARA 3 LETRAS
                {
                    if(isComponent(linea_arch[i+2])==14)
                    {
                        char aux[4] = {linea_arch[i],linea_arch[i+1],linea_arch[i+2],'\0'};
                        if(strcmp(aux,"for")==0)
                        {
                            writeComponent(arch_salida,14);
                            paso = 1;
                        }
                        if(strcmp(aux,"var")==0)
                        {
                            writeComponent(arch_salida,15);
                            paso = 1;
                        }
                        if(strcmp(aux,"div")==0)
                        {
                            writeComponent(arch_salida,16);
                            paso = 1;
                        }
                        if(strcmp(aux,"end")==0)
                        {
                            writeComponent(arch_salida,17);
                            paso = 1;
                        }
                        if(strcmp(aux,"mod")==0)
                        {
                            writeComponent(arch_salida,18);
                            paso = 1;
                        }
                        if(strcmp(aux,"and")==0)
                        {
                            writeComponent(arch_salida,19);
                            paso = 1;
                        }
                        if(strcmp(aux,"not")==0)
                        {
                            writeComponent(arch_salida,20);
                            paso = 1;
                        }
                        if(paso == 1)
                        {
                            i = i+2;
                        }
                    }
                }
                if (tipo == 14 && tipo_aux == 14 && i+1<cantidad_caracteres)
                {    
                    if(isComponent(linea_arch[i+1])==14)
                    {
                        char aux[3] = {linea_arch[i],linea_arch[i+1],'\0'};
                        if(strcmp(aux,"if")==0)
                        {
                            writeComponent(arch_salida,21);
                            paso = 1;
                        }
                        if(strcmp(aux,"to")==0)
                        {
                            writeComponent(arch_salida,22);
                            paso = 1;
                        }
                        if(strcmp(aux,"or")==0)
                        {
                            writeComponent(arch_salida,23);
                            paso = 1;
                        }
                        if(strcmp(aux,"do")==0)
                        {
                            writeComponent(arch_salida,24);
                            paso = 1;
                        }
                        if(strcmp(aux,"of")==0)
                        {
                            writeComponent(arch_salida,25);
                            paso = 1;
                        }
                        if(strcmp(aux,"<>")==0)
                        {
                            writeComponent(arch_salida,47);
                            paso = 1;
                        }
                        if(strcmp(aux,">=")==0)
                        {
                            writeComponent(arch_salida,48);
                            paso = 1;
                        }
                        if(paso == 1)
                        {
                            i = i+1;
                        }
                    }
                }
                
            }
            if (tipo>0 && paso == 0 && tipo != 2 && tipo != 14)//un solo caracter 
            {
                //printf("ANOTA UN TIPO %d\n",tipo);
                    writeComponent(arch_salida,tipo);
            }
            i++;
            //printf("IMPRIME: %c ||| ",linea_arch[i]);
            paso = 0;
        }
        else // ya recorri toda la linea 
        {
            allLine = 1;
        }
    }
}

//MAIN PRINCIPAL
int main(int argc, char const *argv[])
{     
    // Establecer el idioma a espaol
    setlocale(LC_ALL, "spanish"); // Cambiar locale - Suficiente para uinas Linux
    SetConsoleCP(1252); // Cambiar STDIN -  Para mquinas Windows
    SetConsoleOutputCP(1252); // Cambiar STDOUT - Para mquinas Windows
    
    // Chequea que las entradas esten bien, en caso 
    // de una entrada mal ingresada sino envia uno
    // de los errores solicitados
    
    if(checkInputs(argc,argv))
    {
        iniAnalizadorLexico(argv);
    }

    return 0;
}
