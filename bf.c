#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char code[10000];


void bftoc(char* buf){
    int length = strlen(buf);

    for (int i =0 ; i < length ; i++){
        if(buf[i] == '>'){
            snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "ptr++;\n");
        }
        else if(buf[i] == '<'){
            snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "ptr--;\n");
        }

        else if(buf[i] == '+'){
            snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "(*ptr)++;\n");
        }

        else if(buf[i] == '-'){
            snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "(*ptr)--;\n");
        }

        else if(buf[i] == '['){
            snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "while (*ptr) {\n");
        }

        else if(buf[i] == ']'){
            snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "    }\n");
        }

        else if(buf[i] == '.'){
            snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "putchar(*ptr);\n");
        }

        else if(buf[i] == ','){
            snprintf(code + strlen(code) , sizeof(code) - strlen(code) ,"*ptr = getchar();\n");

        }
    }

}



int main(int argc , char* argv[]) {

    if(argc < 2){
        return 1;
    }
    snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "#include <stdio.h>\n int main(){ \n char array[30000] = {0}; \n char *ptr = array;\n");

    FILE *fptr;



    char* filename = argv[1];
    fptr = fopen(filename , "r");
    
    char buf[10000];

    while (fgets(buf + strlen(buf), sizeof(buf) - strlen(buf), fptr) != NULL);

    bftoc(buf);

    snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "return 0; \n }\n");

    fclose(fptr);
    fptr = fopen("output.c" , "w");
    fprintf(fptr , code);
    fclose(fptr);


    printf("%s" , code);

    return 0;
}