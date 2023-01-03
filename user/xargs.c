
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]){
	char *args[MAXARG];
	char buf[1024];
	if (argc < 2) {
		fprintf(2, "xargs: should take at least two argments");
		exit(0);
	}
	if (argc >= MAXARG) {
		fprintf(2, "xargs: arguments should be less than 32.");
		exit(0);
	}
	int l = argc;
	if (!strcmp(argv[1], "-n")) {
		for (int i = 3; i != argc; ++i) {
			args[i-3]= argv[i];
			l -= 2;
		}
	} else {
		for (int i = 1; i != argc; ++i)
			args[i-1] = argv[i];
	}
  	int n, m;
  	char *p, *q;

  	m = 0;
  	while((n = read(0, buf+m, sizeof(buf)-m-1)) > 0){
  	  	m += n;
  	  	buf[m] = '\0';
  	  	p = buf;
  	  	while((q = strchr(p, '\n')) != 0){
  	  	  	*q = 0;
			char arg[1024];
  	  	  	memmove(arg, p, q+1 - p);
			if (fork() == 0) {
				args[l - 1] = arg;
				args[l] = 0;
	 			exec(args[0], args);
	 			exit(0);
	 		} else {
	 			wait((int *) 0);
	 		}
  	  	  	p = q+1;
  	  	}
  	  	if(m > 0){
  	  	  	m -= p - buf;
  	  	  	memmove(buf, p, m);
  	  	}
	}
 	return 0;
}