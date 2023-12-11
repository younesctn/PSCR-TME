#include <ctime>
#include <cstdlib>
#include "rsleep.h"

void randsleep() {
  int r = rand();
  double ratio = (double)r / (double) RAND_MAX;
  struct timespec tosleep;
  tosleep.tv_sec =0;
  // 300 millions de ns = 0.3 secondes
  tosleep.tv_nsec = 300000000 + ratio*700000000;
  struct timespec remain;
  while ( nanosleep(&tosleep, &remain) != 0) {
    /*
     tant qu'on sleep pas jusqu'au bout on fait boucle, on fait ça car nanosleep peut se faire interrompre par les signaux.
     Or durant l'attaque on veut se faire signaler pour prendre des dégats mais pas forcement ce reveiller.
     On quitte la boucle quand le temps restant = 0   
     */
    tosleep = remain;
  }
}
