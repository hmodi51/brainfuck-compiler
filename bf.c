#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *code;                             // Stores generated assembly code
int codeSize = 20000;                   // Max size of assembly code
int *loopIds;                           // Stack to manage nested loops
int loopCount = 0;                       //  Counter for unique loop labels
int totalLoopCap = 100;                   // Initial capacity for loop stack
int currId = 0;                           // Current loop ID
int lastLoopIndex = 0;                     // Index to last loop



// Function to convert Brainfuck code to x86_64 assembly
void bftoc(char* buf){
    int length = strlen(buf);

    for (int i =0 ; i < length ; i++){
        if(buf[i] == '>'){                 // Move pointer to the right
            char *text = "incq %rsi\n";                  
            snprintf(code + strlen(code) , codeSize - strlen(code) , text);
        }
        else if(buf[i] == '<'){            // Move pointer to the left
            char *text = "decq %rsi\n";
            snprintf(code + strlen(code) , codeSize - strlen(code) , text);
        }

        else if(buf[i] == '+'){            // Increment byte at pointer
            char *text = "incb (%rsi)\n";
            snprintf(code + strlen(code) , codeSize- strlen(code) , text);
        }

        else if(buf[i] == '-'){             // Decrement byte at pointer
            char *text = "decb (%rsi)\n";
            snprintf(code + strlen(code) , codeSize - strlen(code) , text);
        }

        else if(buf[i] == '['){             // Start loop
            

            // if loopcount exceeds total loop capacity then dynamically reallocate more loop space
            if(loopCount == totalLoopCap){
                totalLoopCap *=2;
                loopIds = realloc(loopIds , totalLoopCap * sizeof(int));
            }

            // add loop to the array
            loopIds[lastLoopIndex++] = loopCount;
            snprintf(code + strlen(code) , codeSize - strlen(code) , "loop%d:\n"
                                                                     "  cmpb $0 , (%rsi)\n"
                                                                      "  jz  loop_end%d\n" ,
                                                                       loopCount , loopCount);
            loopCount++;
        }



        else if(buf[i] == ']'){
            currId = loopIds[--lastLoopIndex];    // Pop loop ID from array
            snprintf(code + strlen(code) , codeSize - strlen(code) , "jmp loop%d\nloop_end%d:\n" , currId , currId);
        }

        else if(buf[i] == '.'){    // Output character to stdout
           char* text = "mov $1 , %rax\n"
                        "mov $1 , %rdi\n"
                        "mov $1 , %rdx\n"
                        "syscall\n";

            snprintf(code + strlen(code) , codeSize - strlen(code) , text);
        }

        else if(buf[i] == ','){    // input character from stdinc
            
            char* text = "mov $0 , %rax\n"
                         "mov $0 , %rdi\n"
                         "mov $1 , %rdx\n"
                         "syscall\n";

            snprintf(code + strlen(code) , codeSize - strlen(code) , text);

        }
    }

}



int main(int argc , char* argv[]) {

    // Check for input file
    if(argc < 2){
        return 1;
    }

    // initialize memory
    char text[1000] = "# bf to asm code\n"
                    ".section     .text      # declare the .text section\n"
                    ".globl       _start    # declare global section\n"
                    " _start:\n"
                    "   subq $30000 , %rsp    # allocate 30000 bytes on stack \n"
                    "   movq %rsp , %rcx       # have rcx point to same place as rsp\n"     
                    "   movq $30000 , %rbx     # copy 30000 into rbx register as it will serve as count\n"
                    "   zeroed:                 # make label zeroed which will zero all 30000 bytes\n"              
                    "    movb  $0 , (%rcx)       # copy 0 into current byte\n"     
                    "    incq %rcx                # move rcx to next byte\n"
                    "    decq %rbx                # decrement rbx by 1 \n"
                    "    cmpq $0 , %rbx           # compare rbx and 0\n"
                    "    jne zeroed              # if rbx still not zero then go loop again\n"
                    
                    "#zeroed all 30000 bytes till here\n"
                    "   movq %rsp , %rsi           #copy rsp to rsi as char* ptr = array\n";

    // Allocate memory for code
    code = malloc(20000); 
    code[0] = '\0';    // input null character to make it empty string
    snprintf(code + strlen(code) , codeSize - strlen(code) , text);

    // Allocate memory for loop array
    loopIds = malloc(totalLoopCap * sizeof(int));


    // Open Brainfuck source file
    FILE *fptr;
    char* filename = argv[1];
    fptr = fopen(filename , "r");
    
    char buf[20000];

    // Read file contents into buffer
    while (fgets(buf + strlen(buf), sizeof(buf) - strlen(buf), fptr) != NULL);

    bftoc(buf);  // call bftoc func which will convert bf code to assembly

    // Append exit syscall
    snprintf(code + strlen(code) , sizeof(code) - strlen(code) , "movq $60 , %rax\n"
                                                                  "xor %rdi , %rdi\n"
                                                                   "syscall\n");
    // Write assembly to file
    fclose(fptr);
    fptr = fopen("output.s" , "w");
    fprintf(fptr , code);
    fclose(fptr);


    printf("%s" , code);

    return 0;
}