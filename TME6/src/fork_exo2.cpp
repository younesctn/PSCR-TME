#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

/*question 2 :
[28632942@ppti-14-508-06:~/git/PSCR-TME/TME6/src]$./tme6exo2
main pid=45187
pid=45188 ppid=45187 i:j 1:3
pid=45189 ppid=45188 i:j 1:0
Fin du processus 45189
pid=45190 ppid=45188 i:j 2:3
detection par 45188 de fin du fils de pid=45189
pid=45191 ppid=45190 i:j 2:0
Fin du processus 45191
pid=45192 ppid=45190 i:j 2:0
Fin du processus 45192
pid=45193 ppid=45190 i:j 3:3
detection par 45190 de fin du fils de pid=45191
pid=45194 ppid=45193 i:j 3:0
Fin du processus 45194
detection par 45190 de fin du fils de pid=45192
pid=45195 ppid=45193 i:j 3:0
Fin du processus 45195
pid=45196 ppid=45193 i:j 3:0
Fin du processus 45196
detection par 45193 de fin du fils de pid=45194
detection par 45193 de fin du fils de pid=45195
detection par 45193 de fin du fils de pid=45196
detection par 45193 de fin du fils de pid=-1
detection par 45193 de fin du fils de pid=-1
detection par 45193 de fin du fils de pid=-1
Fin du processus 45193
detection par 45190 de fin du fils de pid=45193
detection par 45190 de fin du fils de pid=-1
detection par 45190 de fin du fils de pid=-1
Fin du processus 45190
detection par 45188 de fin du fils de pid=45190
detection par 45188 de fin du fils de pid=-1
Fin du processus 45188
detection par 45187 de fin du fils de pid=45188
Fin du processus 45187
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
		int status;
		int pid = wait(&status);
		std::cout << "detection par " << getpid() << " de fin du fils de pid=" << pid << std::endl;
	}
	std::cout << "Fin du processus " << getpid() << std::endl;
	return 0;
}