/**
 * 1. deleting all lines before `struct memory_region *get_mem_region`
 * 2. deleting `\n\n`.
 * 2. deleting all `extern` lines
 * 3. adding `st` to all possible places
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define CNT 1000

/* Function declaration */
void replaceAll(char *str, const char *oldWord, const char *newWord);


const char start_point[] = "unsigned long long eval_ins(unsigned int)";


const char old_words[][200] = {
	"unsigned char nat2opcode",
	"eval_ins_len()",
	"eval_ins(",
	"_Bool bpf_verifier_aux(",
	"_Bool bpf_verifier(void)",
	"return bpf_verifier_aux("
	
	};

const char new_words[][200] = {	
	"static __attribute__((always_inline)) inline unsigned char nat2opcode",
	"eval_ins_len(st)",
	"eval_ins(st, ",
	"static __attribute__((always_inline)) inline _Bool bpf_verifier_aux(struct verifier_state * st, ",
	"_Bool bpf_verifier(struct verifier_state * st)",
	"return bpf_verifier_aux(st, "
	
	};
	


const char delete_lines[] ="extern ";

int main()
{
    /* File pointer to hold reference of input file */
    FILE * ptr_r;
    FILE * ptr_w;
    int counter = CNT;
    int index;
    int before_start_point;
    int two_blanks;
    
    char buffer[BUFFER_SIZE];



    /*  Open all required files */
    ptr_r  = fopen("repatch1_generated.c", "r");
    ptr_w = fopen("repatch2_generated.c", "w+"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (ptr_r == NULL || ptr_w == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }

    before_start_point = 0;
    two_blanks = 0;
    while ((fgets(buffer, BUFFER_SIZE, ptr_r)) != NULL)
    {  //printf("%d\n", CNT-counter);
    	//if ((counter --) == 0) { break; }
    	/* deleting all lines before `struct memory_region *get_mem_region` */
    	if (before_start_point == 0 && strstr(buffer, start_point) == NULL){
    	  /* we just skip this line and don't write it */
    	  continue;
    	}
    	else {
    	  before_start_point = 1;
    	}
    	
    	if (strcmp(buffer, "\n") == 0){
    	  if(two_blanks == 0){
    	    two_blanks = 1;
    	  }
    	  else {//two_blanks == 1
    	    //printf("skip\n");
    	    continue;
    	  }
    	}
    	else if(strcmp(buffer, "}\n") == 0) {
    	  /* we just skip this line and don't write it */
    	  two_blanks = 0;
    	}
    	
    	/* Delete all lines starting by `extern  ` */
    	if (strstr(buffer, delete_lines) != NULL){
    	  /* we just skip this line and don't write it */
    	  continue;
    	}
    	
    	if(strcmp(buffer,"\n") == 0) { fputs(buffer, ptr_w); continue; }
    
    	//printf("readline: %s\n", buffer);
        // Replace all occurrence of word from current line
        for (index = 0; index < sizeof(old_words)/200; index ++){
          replaceAll(buffer, old_words[index], new_words[index]);
        }

        // After replacing write it to temp file.
        fputs(buffer, ptr_w);
    }

    //printf("repatch2 done!\n");
    /* Close all files to release resource */
    fclose(ptr_r);
    fclose(ptr_w);

    return 0;
}



/**
 * Replace all occurrences of a given a word in string.
 */
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);

    // Fix: If oldWord and newWord are same it goes to infinite loop
    if (!strcmp(oldWord, newWord)) {
        return;
    }

    if ((pos = strstr(str, oldWord)) == NULL) {return ;}
    /*
     * Repeat till all occurrences are replaced. 
     */
    //while ((pos = strstr(str, oldWord)) != NULL)
    //{
        // Backup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word 
        strcat(str, newWord);
        
        // Concatenate str with remaining words after 
        // oldword found index.
        strcat(str, temp + index + owlen);
    //}
}
