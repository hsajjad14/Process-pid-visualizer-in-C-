#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ptree.h"
#include <ctype.h>
int main(int argc, char **argv) {
    // TODO: Update error checking and add support for the optional -d flag
    // printf("Usage:\n\tptree [-d N] PID\n");

    // NOTE: This only works if no -d option is provided and does not
    // error check the provided argument or generate_ptree. Fix this!

	int d, depth,pid;
	d = 0;
	depth = 0;

	//printf("argc is %d\n",argc);
	if(argc == 1 || argc > 4){
//		fprintf(stderr,"wrong number of arguments");
		return 1;
	}
		int r = 0;
		int i;
		int x = 0;
		while((i = getopt(argc,argv,"d:")) != -1){

			switch (i){
				case 'd' :
					for (x = 0; x < strlen(optarg); x++){
                                        	if(isdigit(optarg[x])==0){
//                                                	printf("nan depth\n");
                                                	return 1;
                                        	}

                                 	}
					depth = strtol(optarg,NULL,10);
					d = 1;
					break;

				case '?':
					return 1;	
					
				default :
					return 1;
					
			}	
		
		}
		int c;
		if(d == 1){
			if(argc == 4){
				c = 1;
                                if(strcmp(argv[1],"-d")==0);
                                        c+=2;
                                 x = 0;
                                for (x = 0; x < strlen(argv[c]); x++){
                                        if(isdigit(argv[c][x])==0){
                                                //printf("nan\n");
                                                return 1;
                                        }

                                 }
                                pid = strtol(argv[c],NULL,10);
//				printf("-d is true, depth is: %d, pid is %d\n",depth,pid);
				if(depth == pid){
                                 //       printf("depth not provided\n");
                                        return 1;
                                }
				struct TreeNode *root = NULL;
   				r = generate_ptree(&root, pid);
				
				if(root->pid==0 || !(root->name)){
					return 1;
				}else{
					if(depth != 0){
    						print_ptree(root, depth);
					}else{
						print_ptree(root,0);
					}
				}
				
				if(r==1){
                                        return 2;
                                }
			}else if(argc == 3){
				c = 1;
//                                printf("argc = 3, d is true\n");
                                if(strcmp(argv[1],"-d")==0);
                                        c+=1;

                                x = 0;
                                for (x = 0; x < strlen(argv[c]); x++){
                                        if(isdigit(argv[c][x])==0){
                                               // printf("nan\n");
                                                return 1;
                                        }

                                 }

                                pid = strtol(argv[c],NULL,10);
				if(depth == pid){
                                 //       printf("depth not provided\n");
                                        return 1;
                                }
//				printf("-d is true, depth is: %d, pid is %d\n",depth,pid);

				struct TreeNode *root = NULL;
   				r = generate_ptree(&root, pid);
    				if(root->pid==0 || !(root->name)){
					return 1;
				}else{
					if(depth != 0){
                                                print_ptree(root, depth);
                                        }else{
                                                print_ptree(root,0);
					}
				}

				if(r==1){
                                        return 2;
                                }
			}


		}else if(d == 0 && argc==2){
				x = 0;
                                for (x = 0; x < strlen(argv[1]); x++){
                                        if(isdigit(argv[1][x])==0){
                        //                        printf("nan\n");
                                                return 1;
                                        }

                                 }
                        
				pid = strtol(argv[1],NULL,10);
//			printf("-d is false, depth is: full tree, pid is %d\n",pid);

				struct TreeNode *root = NULL;
   				r = generate_ptree(&root, pid);
    				if(root->pid ==0 || !(root->name)){

					return 1;
				}else{
					print_ptree(root, 0);
				}

				if(r==1){
                                        return 2;
                                }
		}else{
			return 1;
		}
		

 

    return 0;
}

