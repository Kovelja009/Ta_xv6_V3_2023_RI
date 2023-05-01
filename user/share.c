#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

int
main(int argc, char *argv[])
{	

	int size = 100000;
	if(argc > 1)
		size = atoi(argv[1]);

	int *fib_arr = malloc(100000*sizeof(int));
	int cnt = -1;
	int cmd = 0;
	
	share_mem("fib_arr", fib_arr, 100000*sizeof(int));
	share_mem("cnt", &cnt, sizeof(cnt));
	share_mem("cmd", &cmd, sizeof(cmd));
	share_mem("size", &size, sizeof(size));

	int pid = fork();

	if(pid == 0){
		char *argv2[] = {"/bin/fib", 0};
		exec("/bin/fib", argv2);
	}else{
		int pid2 = fork();
		if(pid2 == 0){
			char *argv3[] = {"/bin/comm", 0};
			exec("/bin/comm", argv3);
		}else{
			wait();	
			wait();
		}
	}
	exit();
}
