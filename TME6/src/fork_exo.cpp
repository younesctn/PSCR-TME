#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

/*question 1 : on engendre 10 processus
[28632942@ppti-14-508-06:~/git/PSCR-TME/TME6/src]$./tme6
main pid=44213
pid=44214 ppid=44213 i:j 1:3
pid=44215 ppid=44214 i:j 1:0
pid=44216 ppid=44214 i:j 2:3
pid=44217 ppid=44216 i:j 2:0
pid=44218 ppid=44216 i:j 2:0
pid=44219 ppid=44216 i:j 3:3
pid=44220 ppid=44219 i:j 3:0
pid=44221 ppid=44219 i:j 3:0
pid=44222 ppid=44219 i:j 3:0
*/

int main () {
	int cpt = 0;
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	for (int i=1, j=N; i<=N && j==N ; i++ ) {
		if (fork() == 0) {
			cpt = 0;
		} else {
			cpt++;
			break;
				}	
		std::cout << "pid=" << getpid() << " ppid=" << getppid() << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			cpt++;
			if ( fork() == 0) {
				cpt = 0;
				j=0;
				std::cout << "pid=" << getpid() << " ppid=" << getppid() << " i:j " << i << ":" << j << std::endl;
			}else{
				cpt++;
			}
		}
	}
	for (int i = 0; i<cpt; i++){
		wait(NULL);
	}
	return 0;
}