#include <fstream>
#include <iostream>

int atlikejai[20];	//atlikejai <=20
int n;				//atlikeju skaicius
int suma = 0;		//kiek dainu yra isviso

void skaityti() {
	std::ifstream in ("U2.txt");
	in >> n;
	for (int i = 0; i < n; i++) {
		in >> atlikejai[i];
		suma += atlikejai[i];
	}
	in.close();
	return;
}

int did(int last) {
	int maxnr=-1, max=0;		//jeigu neranda didesnio uz nuli kuris nesikartoja su "last" grazina -1
	for (int i = 0; i < n; i++) {
		if (atlikejai[i] > max && i!=last) {
			maxnr = i;
			max = atlikejai[i];
		}
	}
	return maxnr;	//grazina didziausio skaiciaus masyvo indeksa
}

void spausdinti(int playlist[]) {
	for (int i = 0; i < suma; i++) {
		std::cout << playlist[i] << " ";
	}
	return;
}

void createPlaylist(int playlist[]) {
	int last = -1;
	int counter = 0;
	while (counter != suma) {
		if (did(last) == -1) {			//jeigu nera kito skaiciaus naudoja paskutini
			playlist[counter] = last + 1;
			if(last>=0)atlikejai[last]--;
		}
		else {							//jeigu yra kitas skaicius naudoja ji
			playlist[counter] = did(last) + 1;
			atlikejai[did(last)]--;
			last = did(last);			//atnaujina paskutini skaiciu
		}
		counter++;
	}
	return;
}

int main() {
	skaityti();
	int playlist[2000];		//2000 nes 20 atlikeju po 100 dainu yra 2000 maksimumas
	createPlaylist(playlist);
	spausdinti(playlist);
}
