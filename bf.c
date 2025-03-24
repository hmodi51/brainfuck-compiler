#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *code;
int codeSize = 10000;


void bftoc(char* buf){
    int length = strlen(buf);

    for (int i =0 ; i < length ; i++){
        if(buf[i] == '>'){
            char *text = "inc %rsi";
            snprintf(code + strlen(code) , codeSize - strlen(code) , text);
        }
        else if(buf[i] == '<'){
            char *text = "dec %rsi";
            snprintf(code + strlen(code) , codeSize - strlen(code) , text);
        }

        else if(buf[i] == '+'){
            char *text = "inc (%rsi)";
            snprintf(code + strlen(code) , codeSize- strlen(code) , text);
        }

        else if(buf[i] == '-'){
            char *text = "dec (%rsi)";
            snprintf(code + strlen(code) , codeSize - strlen(code) , text);
        }

        else if(buf[i] == '['){
            char* text = "loop:  "
                         "  cmp $0 , (%rsi)"
                         "  jz  loop_end"
                         "  jne loop";
            snprintf(code + strlen(code) , codeSize - strlen(code) , text);
        }

        else if(buf[i] == ']'){
            char*text = "loop_end: ";
            snprintf(code + strlen(code) , codeSize - strlen(code) , text);
        }

        else if(buf[i] == '.'){
            snprintf(code + strlen(code) , codeSize - strlen(code) , "putchar(*ptr);\n");
        }

        else if(buf[i] == ','){
            snprintf(code + strlen(code) , codeSize - strlen(code) ,"*ptr = getchar();\n");

        }
    }

}



int main(int argc , char* argv[]) {

    if(argc < 2){
        return 1;
    }

    char text[1000] = "; bf to asm code"
                    ".section     .text      # declare the .text section"
                    "globl       _start    # declare global section"
                    " _start:"
                    "   subq $30000 , %rsp    # allocate 30000 bytes on stack "
                    "   movq %rsp , %rcx       # have rcx point to same place as rsp"     
                    "   movq $30000 , %rbx     # copy 30000 into rbx register as it will serve as count"
                    "   zeroed:                 # make label zeroed which will zero all 30000 bytes"              
                    "    movb  $0 , (%rcx)       # copy 0 into current byte"     
                    "    inc %rcx                # move rcx to next byte"
                    "    dec %rbx                # decrement rbx by 1 "
                    "    cmp $0 , %rbx           # compare rbx and 0"
                    "    jne zeroed              # if rbx still not zero then go loop again"
                    
                    "#zeroed all 30000 bytes till here"
                    "   movq %rsp , %rsi           #copy rsp to rsi as char* ptr = array";

    code = malloc(10000); 
    code[0] = '\0';
    snprintf(code + strlen(code) , codeSize - strlen(code) , text);

    FILE *fptr;



    char* filename = argv[1];
    fptr = fopen(filename , "r");
    
    char buf[10000];

    while (fgets(buf + strlen(buf), sizeof(buf) - strlen(buf), fptr) != NULL);

    bftoc(buf);

    snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "return 0; \n }\n");

    fclose(fptr);
    fptr = fopen("output.s" , "w");
    fprintf(fptr , code);
    fclose(fptr);


    printf("%s" , code);

    return 0;
}