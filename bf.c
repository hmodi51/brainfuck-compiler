#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* code;


void bftoc(char* buf){
    int length = strlen(buf);

    for (int i =0 ; i < length ; i++){
        if(buf[i] == '>'){
            strcat(code , "ptr++;\n");
        }
        else if(buf[i] == '<'){
            strcat(code , "ptr--;\n");
        }

        else if(buf[i] == '+'){
            strcat(code , "(*ptr)++;\n");
        }

        else if(buf[i] == '-'){
            strcat(code , "(*ptr)--;\n");
        }

        else if(buf[i] == '['){
            strcat(code , "while (*ptr) {\n");
        }

        else if(buf[i] == ']'){
            strcat(code , "    }\n");
        }

        else if(buf[i] == '.'){
            strcat(code , "putchar(*ptr);\n");
        }

        else if(buf[i] == ','){
            strcat(code , "*ptr = getchar();\n");

        }
    }

}



int main(int argc , char* argv[]) {

    if(argc < 2){
        return 1;
    }

    code = malloc(10000);
    strcpy(code , "#include <stdio.h>\n int main(){ \n char array[30000] = {0}; \n char *ptr = array;\n");

    FILE *fptr;



    char* filename = argv[1];
    fptr = fopen(filename , "r");
    
    char buf[10000];

    while (fgets(buf + strlen(buf), sizeof(buf) - strlen(buf), fptr) != NULL);

    bftoc(buf);

    strcat(code , "return 0; \n }\n");

    fclose(fptr);
    fptr = fopen("output.c" , "w");
    fprintf(fptr , code);
    fclose(fptr);


    printf("%s" , code);

    return 0;
}