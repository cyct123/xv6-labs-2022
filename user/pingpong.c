
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	int p[2];
	pipe(p);
	if (fork() == 0) {
		char *ret[4];
		read(p[0], ret, 4);
		close(p[0]);
		printf("%d: received %s\n", getpid(), ret);
		write(p[1], "pong", 4);
		close(p[1]);
	} else {
		write(p[1], "ping", 4);
		close(p[1]);
		char *ret[4];
		read(p[0], ret, 4);
		close(p[0]);
		printf("%d: received %s\n", getpid(), ret);
	}
	return 0;
}