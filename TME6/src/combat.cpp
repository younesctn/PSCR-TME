#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <cstdio>
#include "rsleep.h"

//pts de vie
int pv = 5;

void handler(int sig){
    if (sig == SIGINT){
        pv--;
        printf("BOUFFON il me reste encore %d points de vie, moi le grand %d vais t'exploser la tronche!\n",pv, getpid());
        if (pv == 0) {
            printf("Moi %d me vengerai gamin\n",getpid());
            exit(1);
        }
    }
}

void attaque (pid_t adversaire){
  signal(SIGINT,handler);
  int i = kill(adversaire,SIGINT);
  if (i < 0){
    exit(0);
  }
  randsleep();
}

void defense(){
  signal(SIGINT,SIG_IGN);
  randsleep();
}

void combat(pid_t adversaire){
  while (true)
  {
    defense();
    attaque(adversaire);
  }
}

int main(){
  pid_t pere = getpid();
  pid_t fils = fork();
  if (fils == 0){
    srand(fils); //on fait ça pour s'assurer que le pére et le fils ont des graines différents
    combat(pere); //le fils
  }
  else{
    srand(pere);
    combat(fils); //pere
  }

  return 0;
}

/*
Question 6
Le combat serait inéquitable car le fils attendrait juste que le père envoit un signal pour paré.
Il va parer tous les coups
*/