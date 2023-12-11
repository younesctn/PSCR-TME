#pragma once
#include <mutex>
#include <condition_variable>

namespace pr{
class Barrier {
	std::mutex m;
	std::condition_variable cv;
	int cpt;
	const int N;

public: 
	Barrier(int n) : cpt(0), N(n) {}
	
	void done(){
		std::unique_lock<std::mutex> lg(m);
		cpt++;
		if(cpt == N) cv.notify_all();
	}

	void waitFor(){
		std::unique_lock<std::mutex> lg(m);
		while(cpt != N){
			cv.wait(lg);
		}
	}		
};
}