#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

int isPrime(int num){
    int flag=1;
    for(int i = 2; i <= num / 2; i++) {
       if(num % i == 0) {
          flag = 0;
          break;
       }
    }
    return flag;
}

int
main(int argc, char *argv[])
{

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
	*((int *)fib_arr) = 0;
	*((int *)fib_arr + 1) = 1;
	*((int *)fib_arr + 2) = 1;
	*((int *)cnt) = 2;

	int should_continue = 1;
	while(1){
		
		if(should_continue){
			sleep(100);
			int curr = ++(*(int *)cnt);
			*(((int *)fib_arr + curr)) = *((int *) fib_arr + curr - 1) + *((int *) fib_arr + curr - 2);
		}
		if(*(int *) cmd == 3)
			should_continue = 1;
		if(*(int *) cmd == 2)
			should_continue = 0;
		if(*(int *) cmd == 4 || *(int *) size == *(int *) cnt)
			break;
		sleep(1);
	}
	printf("Done calculating fibonacci numbers (X_X)\n");


	exit();
}
