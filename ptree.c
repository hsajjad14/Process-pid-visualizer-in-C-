#include <stdio.h>
// Add your system includes here.
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "ptree.h"

// Defining the constants described in ptree.h
const unsigned int MAX_PATH_LENGTH = 1024;
#define MAX_LINE 1000000
#define NAME 11111
void help_print(struct TreeNode *root,int depth, int max_depth); 
int help(struct TreeNode **root, int pid);

// If TEST is defined (see the Makefile), will look in the tests 
// directory for PIDs, instead of /proc.

#ifdef TEST
    const char *PROC_ROOT = "tests";
#else
    const char *PROC_ROOT = "/proc";
#endif

//const char *PROC_ROOT = "tests";


//char procfile[MAX_PATH_LENGTH + 1];

struct TreeNode *create_node_sibling(int pid, struct TreeNode *next){
	
        struct TreeNode *new_node = malloc(sizeof(struct TreeNode));
	//new_node->name = malloc(111111);
        new_node->pid = pid;

        new_node->next_sibling = next;

        char fname[NAME];

        char name[NAME];
        //snprintf(fname, 1024, "%s/%d/cmdline", PROC_ROO, new_node->pid);

        FILE *s;
	
	new_node->name = malloc(NAME);
//        char name[111111] = " ";
	snprintf(fname, 1024, "%s/%d/cmdline", PROC_ROOT, pid);
        //s = fopen(fname,"r");
	if( access( fname, F_OK ) != 0 ) {
             	new_node->name = strdup(" ");
	}else{
		//fclose(s);
	        
                s = fopen(fname,"r");
         	unsigned char c;

                
                int count = 0;
        	int flag = 0;
      		while (!feof(s) && flag == 0){                        // while not end of file
//              	printf("%d\n",count);
                 	c=fgetc(s);                         // get a character/byte from the file
//              	printf("%c\n",c);
                	if(c=='/'){
                        	count=0;
                	}else{
                        	if(c=='\0' || c==' ' || c=='\n'){
                                	flag = 1;
                        	}else{
                                
                                	name[count] = c;
                                	count+=1;
                        	}


                	}
        	}
        
        	name[count] = '\0';
        	
        	if(name[count-1] == '-' || name[count-1] == ')' ||name[count-1] == ':'){
//              	printf("this is nutzz\n\n");
                	name[count-1] = '\0';
        	}				//cleans up
        	if(name[0] == '-' || name[0] == '(' ||name[0] == ':'){
//                	printf("AA\n");
                	strncpy(name,name+1,strlen(name));
        	}
                new_node->name = strdup(name);
    
             
		fclose(s);
	}
	
	  return new_node;

}

/*
 * Creates a PTree rooted at the process pid. The root of the tree is
 * placed in root. The function returns 0 if the tree was created 
 * successfully and 1 if the tree could not be created or if at least
 * one PID was encountered that could not be found or was not an 
 * executing process.
 */
int generate_ptree(struct TreeNode **root, pid_t pid) {
    // Here's a trick to generate the name of a file to open. Note 
    // that it uses the PROC_ROOT variable
   
	

	*root = malloc(sizeof(struct TreeNode));
	int r;
	r = help(root,pid);
//	printf("return gen : %d\n",r);
	return r;

        
}

int help(struct TreeNode **temp, int pid){
	char procfile[MAX_PATH_LENGTH + 1];	
	
        if (snprintf(procfile, MAX_PATH_LENGTH + 1, "%s/%d/exe", PROC_ROOT, pid) < 0) {
//            fprintf(stderr, "snprintf failed to produce a filename\n");
            return 1;
        }

        FILE *f;


        snprintf(procfile, 1024, "%s/%d/task/%d/children", PROC_ROOT, pid,pid);
//	printf("A\n");//

        f = fopen(procfile,"r");
        if (f == NULL) {
//            fprintf(stderr, "file does not exist\n");
            return 1;
        }
 //	printf("B\n");
        (*temp)->pid = pid;

        int n;
        char fname[NAME];
      snprintf(fname, 1024, "%s/%d/cmdline", PROC_ROOT, pid);
	int r = 0;
        FILE *s;
	int count;
        char name[NAME];
	(*temp)->name = malloc(NAME);
        
	snprintf(fname, 1024, "%s/%d/cmdline", PROC_ROOT, pid);
        if( access( fname, F_OK ) != 0 ) {
                r+=1;
                (*temp)->name = strdup(" ");
	}else{
//	fclose(s);
                snprintf(fname, 1024, "%s/%d/cmdline", PROC_ROOT, pid);
		     
		 s = fopen(fname,"r");
                unsigned char c;


                count = 0;
                int flag = 0;
                while (!feof(s) && flag == 0){                        // while not end of file
//                      printf("%d\n",count);
                        c=fgetc(s);                         // get a character/byte from the file
//                      printf("%c\n",c);
                        if(c=='/'){
                                count=0;
                        }else{
                                if(c=='\0' || c==' ' || c=='\n'){
                                        flag = 1;
                                }else{

                                        name[count] = c;
                                        count+=1;
                                }


                        }
                }

                name[count] = '\0';

                if(name[count-1] == '-' || name[count-1] == ')' ||name[count-1] == ':'){
//                      printf("this is nutzz\n\n");
                        name[count-1] = '\0';
                }                               //cleans up
                if(name[0] == '-' || name[0] == '(' ||name[0] == ':'){
//                      printf("AA\n");
                        strncpy(name,name+1,strlen(name));
                }
                

		(*temp)->name = strdup(name);
                fclose(s);
          
	}
	

        struct TreeNode *child = malloc(sizeof(struct TreeNode));
        child = NULL;
	
	n=0;	
        int counter = 0;
        while (fscanf(f," %d",&n) == 1){
  //              printf("first :     %d\n",n);
		
		snprintf(procfile, 1024, "%s/%d", PROC_ROOT, n);
		      
		 if( !(access( procfile, F_OK ) != 0) ) {
//  			printf("inner : %d\n",n);
	              	counter += 1;
		}else{
			r+=1;
		}
//		printf("%s\n",procfile);
		
//                child = create_node_sibling(n,child);

        }
//	printf("counter for %d is: %d\n",pid,counter);


	fseek(f,0,SEEK_SET);

        int children[counter];
        counter = 0;
	n=0;
//	FILE *ch;
	
        while (fscanf(f," %d",&n) == 1){
                //printf("%d\n",n);
	 	snprintf(procfile, 1024, "%s/%d", PROC_ROOT, n);
		//checking if file exists
		if( !(access( procfile, F_OK ) != 0) ) {
                	children[counter] = n;
                	counter += 1;
                	//child = child->next_sibling;
		}else{
			r+=1;
		}


		snprintf(fname, 1024, "%s/%d/cmdline", PROC_ROOT, pid);
		if( access( fname, F_OK ) != 0 ) {
			r+=1;
		}
	
		

        }
	//printf("counter for %d is: %d\n",pid,counter);
	//fclose(f); cant happen before calling create_node ?
//	printf("counter is %d\n",counter);        
	int j;
        for (j = counter-1; j >= 0; j--){
                child = create_node_sibling(children[j],child);
//		printf("%d : pid\n",child->pid);
        }
	
	fclose(f);
	int x,y;
	x=0;
	y=0;
        (*temp)->child_procs = child;

	
        if ((*temp)->child_procs == NULL){
                //return 1;
        }else {
		snprintf(procfile, MAX_PATH_LENGTH + 1, "%s/%d/exe", PROC_ROOT, (*temp)->child_procs->pid);
		snprintf(fname, 1024, "%s/%d", PROC_ROOT, (*temp)->child_procs->pid);
             	if(!(access(procfile,F_OK) != 0) && !(access( fname, F_OK ) != 0) ){
			x = help(&((*temp)->child_procs),((*temp)->child_procs)->pid);
		}
        }
        if((*temp)->next_sibling != NULL){
		snprintf(procfile, MAX_PATH_LENGTH + 1, "%s/%d/exe", PROC_ROOT, (*temp)->next_sibling->pid);
                snprintf(fname, 1024, "%s/%d", PROC_ROOT, (*temp)->next_sibling->pid);
                if(!(access(procfile,F_OK) != 0) && !(access( fname, F_OK ) != 0) ){
                        y = help(&((*temp)->next_sibling),((*temp)->next_sibling)->pid);
                }
                
        }else{
		//return 1;
	}
//	printf("r:%d x:%d y%d\n",r,x,y);
	if(x+y+r>=1){
		return 1;
	}
	
        return 0;

}





/*
 * Prints the TreeNodes encountered on a preorder traversal of an PTree
 * to a specified maximum depth. If the maximum depth is 0, then the 
 * entire tree is printed.
 */
void print_ptree(struct TreeNode *root, int max_depth) {
    // Here's a trick for remembering what depth (in the tree) you're at
    // and printing 2 * that many spaces at the beginning of the line.

    static int depth = 1;//changed frm 0 to 1
    //static int child = 0;

    //printf("%*s", depth * 2, "");

    // Your implementation goes h
	
    help_print(root,depth,max_depth);





}

void help_print(struct TreeNode *root,int depth, int max_depth){

	if(max_depth == 0){
		if (root != NULL){
		
			printf("%*s", (depth-1) * 2, "");
			if(strcmp(root->name," ") != 0){
		        	printf("%d: %s\n",root->pid,root->name);	
			}else{
				printf("%d\n",root->pid);
			}
			if(root->child_procs != NULL){
				help_print(root->child_procs,depth + 1, max_depth);
			}
		help_print(root->next_sibling,depth ,max_depth);
		}
	} else if (max_depth >= 0){
		
		if (root != NULL && depth <= max_depth){
		
			printf("%*s", (depth-1) * 2, "");
		        if(strcmp(root->name," ") != 0){
                                printf("%d: %s\n",root->pid,root->name);
                        }else{
                                printf("%d\n",root->pid);
                        }
			if(root->child_procs != NULL){
				help_print(root->child_procs,depth + 1, max_depth);
			}
			help_print(root->next_sibling,depth ,max_depth);
		}
		
	}

}
