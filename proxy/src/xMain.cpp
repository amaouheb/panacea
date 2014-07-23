#include "Forw/interface.h"
#include "Prob/p_forwarder.h"
#include "Prob/p_agent.h"

#include <time.h>
#include <thread>
#include <mutex>

using namespace std;

router r;
p_agent a(&r);
p_forwarder f;
interface i(&r);

void mesurememt_func() {
	while (1) {
		cout << "Measurement Agent running..." << endl;
		a.execute();
		std::this_thread::sleep_for(chrono::seconds(60));
	}
}

void forwarder_func() {
	while (1) {
		cout << "Measurement packet Forwarder running..." << endl;
		f.process(&a);
	}
}

int main() {
	//first
	std::thread t1(mesurememt_func);
	//second
	std::thread t2(forwarder_func);
	//third
	while (1) {
		cout << "Data packat Router and Forwarder running..." << endl;
		i.process();
	}
	t1.join();
	t2.join();
	return 0;
}
