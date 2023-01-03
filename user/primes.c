
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void func(int* right) {
	close(right[1]);
	int left[2];
	pipe(left);
	int pid = fork();
	if (pid == 0) {
		func(left);
		//printf("hello\n");
	}
	else {
		int m, n;
		read(right[0], &n, sizeof(int));
		if (n)
			printf("prime %d\n", n);
		else
			exit(0);
		while (read(right[0], &m, sizeof(int)) == sizeof(int)) {
			if (m % n) {
				write(left[1], &m, sizeof(int));
			}
		}
		close(right[0]);
		close(left[1]);
		pid = wait((int*) 0);
		//printf("child %d is done\n", pid);
	}
}

int main(int argc, char *argv[]){
	int p[2];
	pipe(p);
	int pid = fork();
	if (pid == 0) {
		func(p);
	}
	else {
		close(p[0]);
		int i = 2;
		while (i <= 35) {
			write(p[1], &i, sizeof(int));
			++i;
		}
		close(p[1]);
		pid = wait((int*) 0);
		//printf("child %d is done\n", pid);
	}
	return 0;
}