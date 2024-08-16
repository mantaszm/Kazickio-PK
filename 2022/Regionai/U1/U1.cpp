#include <fstream>
#include <iostream>

int n;

struct atvejai
{
	int kaina;
	int duota;
	int atiduoti;
	int kiek[6];
	int graza[6];
  // Masyvu numeriai ir ju vertes
	// 0 - 100
	// 1 - 50 
	// 2 - 20
	// 3 - 10
	// 4 - 5
	// 5 - 1
}A[10];

void skaityti() {
	std::ifstream in ("U1.txt");
	in >> n;
	for (int i = 0; i < n; i++) {
		in >> A[i].kaina >> A[i].duota;
		for (int p = 0; p < 6; p++) {
			in >> A[i].kiek[p];
		}
	}
	in.close();
	return;
}

int Num2Val(int a){      //pavercia masyvo numeri i pinigo verte
	if (a == 0) return 100;
	if (a == 1) return 50;
	if (a == 2) return 20;
	if (a == 3) return 10;
	if (a == 4) return 5;
	else return 1;
}

void graza() {
	for (int i = 0; i < n; i++) {
		int counter = 0;
		A[i].atiduoti = A[i].duota - A[i].kaina;
		while (A[i].atiduoti != 0 && counter != 6) {  //kartoja grazos paieska 6 kartas arba kol ji bus lygi 0
			while (A[i].atiduoti - Num2Val(counter) >= 0 && A[i].kiek[counter] != 0) {  //patikrina kiek kartu gali paimti sia kupiura
				A[i].atiduoti -= Num2Val(counter);
				A[i].graza[counter]++;
				A[i].kiek[counter]--;
			}
			counter++;  //pereina prie mazesnes kupiuros
		}
		if (A[i].atiduoti != 0) {
			A[i].atiduoti = -1;
		}
	}
}

int kiek(int a) {    // suskaiciuoja kiek kupiuru reikia
	int suma=0;
	for (int b = 0; b < 6; b++) {
		suma += A[a].graza[b];
	}
	return suma;
}

void spausdinti() {
	for (int i = 0; i < n; i++) {
		if (A[i].atiduoti == -1) {
			std::cout << "Negalima";
			if (i != n - 1) { std::cout << std::endl << "--------" <<std::endl; }
		}
		else {
			std::cout << kiek(i) << std::endl;
			for (int b = 0; b < 6; b++) {
				if (A[i].graza[b] != 0) std::cout << Num2Val(b) << " - " << A[i].graza[b] << std::endl;
			}
			if (i != n - 1) { std::cout << std::endl << "--------" << std::endl; }
		}
	}
}

int main() {
	skaityti();
	graza();
	spausdinti();
}
