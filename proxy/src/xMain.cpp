#include "Data/d_interface.h"		// Agent data (routage et transfert)
#include "Prob/p_interface.h"		// Agent du transfert des paquets probe
#include "Prob/p_agent.h"			// Agent de mesure de preformance
#include <time.h>
#include <thread>
#include <mutex>

using namespace std;

/*
 * Instancier l'entité 'Router' qui est commune au deux agents data et probe.
 * Nous passons par la suite un pointeur de cette instance à l'agent probe
 * 'p_agent' et aussi à l'agent date 'd_interface'.
 *
 */
router r;

// Instancier l'entité agent probe qui effectura les opérations de mesure.
p_agent a(&r);
// Instancier interface de réception et de transfert des paquets data
d_interface i(&r);
// Instancier interface de réception et de transfert des paquets probe
p_interface ii(&a);


/*
 * Premier thread : execute periodiquement les operations de mesure
 */
void mesurememt_func() {
	while (1) {
		cout << "Measurement Agent running..." << endl;
		if (a.execute() != 0) {
			cout << "Ce noeud n'est pas une source..." << endl;
			break;
		}
		std::this_thread::sleep_for(chrono::seconds(60));
	}
}

/*
 * Deuxieme thread : execute de façon permanante la fonction du
 * transfert des paquets mesures
 */

void forwarder_func() {
	while (1) {
		cout << "Measurement packet Forwarder running..." << endl;
		ii.process();
	}
}


/*
 * Troisieme thread : Le main thread qui lancera les deux autres et qui
 * execureta le transfert et le routage des paquets datas
 */

int main() {
	// Lancer le premier thread
	std::thread t1(mesurememt_func);
	// Lancer le deuxieme thread
	std::thread t2(forwarder_func);
	// Fonction de transfert et de routage des paquets data
	while (1) {
		cout << "Data packat Router and Forwarder running..." << endl;
		i.process();
	}
	t1.join();
	t2.join();
	return 0;
}
