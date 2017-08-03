#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int usage(){
	printf("Usage: -s 'separator' -i n x x x\n"
		"number n to ignore the first n line and number x is the column to print\n");
	return 0;
}

/*the function to see if the column need to print */
int isincols(int * cols, int curcol, int colsize){
	int i;
	for (i = 0; i < colsize; i++)
	{
		
		if (curcol == cols[i])
		{
			return 1;
		}
	}
	return 0;
}

int main(int argc,char *argv[]){
	int opt = 0;
	char separator;
	int ignr = 0;

	if(argc < 4){
	usage();
	return 0;
    }
    else{

	/*switch the option */
	while((opt = getopt(argc, argv, "s:i:")) != -1){
		switch(opt){
			/*get the separator */
			case 's':
			separator = optarg[0];
			//printf("separator: %c\n", separator);
			break;

			/*how many lines to ignore */
			case 'i':
			if(strtol(optarg,NULL,10)!=0){
			    ignr = strtol(optarg, NULL, 10);
		    }else{
		    	usage();
		    	return 0;
		    }
			//printf("ignr: %d\n", ignr);
			break;

			/*other option ?*/
			default:
			usage();
			return 0;
			//break;
		}

	}
	//printf("optind: %d\n", optind);
    //printf("argv[optind]: %s\n", argv[optind]);

    
    int * columns = NULL;
    int colsize = 0;
    /*have column to output*/
	if(argc >= optind){

		/*ensure the indexes are not reversed and repeated*/
		if (argc!=optind)
		{
			int i = 0;
			for(i = optind;i<argc-1;i++){
				if(argv[i]>=argv[(i+1)]){
					printf("the indexes cannot be repeated or provided in decreasing sequence\n");
					return 0;
				}
			}
		}
		
		/*how many column to print */
		int i;
		for(i = optind; i<argc;i++){
			if(strtol(argv[i], NULL, 10)!=0){
				colsize++;
			}
		}
		//printf("%d\n",colsize);

		/*have a dynamic alloc to store index */
		columns = (int *) malloc(sizeof(int)*colsize);
		int j =0;
		for(i = optind; i<argc ;i++){
			/*make sure that the following is a number */
			if(strtol(argv[i], NULL, 10)!=0){
				columns[j] = strtol(argv[i], NULL, 10);
				j++;
			}else{
				usage();
				return 0;
			}
			/*ensure we have enough column to print*/
		    if (strtol(argv[argc-1],NULL,10)>66){
			    printf("We only have 66 columns.\n");
			    return 0;
		    }
		}
		
		/*for(i=0;i<colsize;i++){
			printf("%d\n",columns[i]);
		}*/

	}else{
		printf("Please enter the column indexes you want to read.\n");
		return 0;
	}/*have not enter the column to read */


    int row = 0;
    int column = 1;
    char ch;
    int quota = 0;
    /*read through the text */
    while((ch = getchar())!=EOF){
    	//putchar(ch);
    	if (ch == '\n')
    	{
    		row++;
    		quota = 0;
    		column = 1;
    		if(quota==0){
    			if(row>=ignr){
    				putchar(ch);
    			}
    		}
    	}else if(ch == separator){
    		/*outside the quotation */
    		if(quota==0){
    			if(row>=ignr && isincols(columns,column,colsize)){
    				putchar(ch);
    			}
    			column++;
    		}
    		/*inside the quotation*/
    		else{
    			if(row>=ignr && isincols(columns,column,colsize)){
    				putchar(ch);
    			}
    		}

    	}else if(ch == '"'){
    		quota = (quota +1)%2;
    		if(row>=ignr && isincols(columns,column,colsize)){
    			putchar(ch);
    		}
    	}else{
    		if(row>=ignr && isincols(columns,column,colsize)){
    			putchar(ch);
    		}

    	}
    }
    	


	free(columns);
	return 0;
    }
}
