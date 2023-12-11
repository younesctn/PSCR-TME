#include "Banque.h"

using namespace std;

void transfertWork(pr::Banque b){
	size_t sb = b.size();
	int i,j,m,tsp;
	for(int w = 0; w < 1000; w++){
		i = rand()%sb;
		j = rand()%sb;
		m = rand()%100 + 1;
		b.transfert_parallelwork(i, j, m);
		tsp = rand()%21;
		::this_thread::sleep_for(::chrono::milliseconds(tsp));
	}
}

const int NB_THREAD = 10;
int main () {
	vector<thread> threads;
	pr::Banque b(10,1000);
	// TODO : creer des threads qui font ce qui est demandé
	::srand(::time(nullptr));
	threads.reserve(NB_THREAD);

	for(int t = 0; t < NB_THREAD; t++){
		threads.emplace_back(transfertWork,std::ref(b));
	}



	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
