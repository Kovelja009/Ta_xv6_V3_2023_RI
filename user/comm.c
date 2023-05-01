#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

void commands(){
	printf("Commands:\n");
	printf("0 (>_<)=> latest\n");
	printf("1 (>_<)=> fib <n>\n");
	printf("2 (>_<)=> pause\n");
	printf("3 (>_<)=> resume\n");
	printf("4 (>_<)=> end\n");
}

int
main(int argc, char *argv[])
{
	commands();
	/////////////////////////////////////////	
	// get shared memory

		void *fib_arr;
		get_shared("fib_arr", &fib_arr);

		void *cnt;
		get_shared("cnt", &cnt);
		
		void *cmd;
		get_shared("cmd", &cmd);

		void *size;
		get_shared("size", &size);

	/////////////////////////////////////////	
	while(1){
		char command[100] = {};
		gets(command, 100);
		char prvi[10] = {};
		char drugi[100] = {};
		int broj = 0;
		int ii = 0;
		int jj = 0;
		for(int i = 0; i < 100; i++){
			if(broj)
				drugi[jj++] = command[i];
			else{
				if(command[i] != '\n' || command[i] != ' ')
					prvi[ii++] = command[i];
			}
			if(command[i] == ' ')
				broj = 1;
			if(command[i] == '\n')
				break;
		}



		if(strcmp(prvi, "fib\n") == 0 || strcmp(prvi, "fib ") == 0 || strcmp(prvi, "fib") == 0){
			*(int *) cmd = 1;

			if(*(int *)cnt < atoi(drugi))
				printf("Still haven't calculated fibonacci no. %d. We have fibonacci sequence up to %d!\n", atoi(drugi), *(int *)cnt);
			else
				printf("Fibonacci no. %d is %d\n", atoi(drugi), *(((int *)fib_arr + atoi(drugi))));
		}
		else if(strcmp(prvi, "latest\n") == 0){
			*(int *) cmd = 0;
			printf("Latest fibonacci is no. %d, value: %d\n", *(int *)cnt, *(((int *)fib_arr+(*((int *)cnt)))));		
		}
		else if(strcmp(prvi, "pause\n") == 0){
			printf("Pausing...\n");
			*(int *) cmd = 2;
		}
		else if(strcmp(prvi, "resume\n") == 0){
			printf("Resuming...\n");
			*(int *) cmd = 3;
		}
		else if(strcmp(prvi, "end\n") == 0){
			*(int *) cmd = 4;
			break;
		}else{
			printf("Invalid command!\n");
			commands();
		}
		
	}
	exit();
}
