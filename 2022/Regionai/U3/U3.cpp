#include <fstream>
#include <iostream>

int lentele[50][50];
int n;

void skaityti() {
	std::ifstream in ("U3.txt");
	in >> n;
	int x = 0, y = 0;
	for (int i = 0; i < n * n; i++) {
		in >> lentele[x][y];
		if (x == n-1) {
			y++;
			x = 0;
		}
		else x++;
	}
	in.close();
	return;
}

void spausdinti(int size, int score, int x1, int y1, int x2, int y2) {    //spasudina
	std::cout << score << std::endl << size << std::endl;
	int cordx[5000], cordy[5000];
	int x = x1, y = y1, counter = 0;
	for (int i = 0; i < size; i++) {
		for (int p = 0; p < size; p++) {
			cordx[counter] = x;
			cordy[counter] = y;
			counter++;
			x++;
		}
		x = x1;
		y++;
	}
	x = x2;
	y = y2;
	for (int i = 0; i < size; i++) {
		for (int p = 0; p < size; p++) {
			cordx[counter] = x;
			cordy[counter] = y;
			counter++;
			x++;
		}
		x = x2;
		y++;
	}
	for (int i = 0; i < n; i++) {        //isspausdina 0 ir 1 lenetele parodancia vietas kur yra kvadratai
        for (int p = 0; p < n; p++) {
            bool yra = false;
            for (int l = 0; l < counter; l++) {
                if (cordx[l] == p && cordy[l] == i) {
                    yra = true;
                    break;
                }
            }
            if (yra) std::cout << "1 ";
            else std::cout << "0 ";
        }
        std::cout << std::endl;
    }
	return;
}

bool inFrame(int x, int y, int size) {                  //patikrina ar kvadratas telpa
	if (x + size - 1 <= n - 1 && y + size - 1 <= n - 1) {
		return true;
	}
	return false;
}

bool removeRepeat(int x, int y, int size, int cordx[], int cordy[]) {        //panaikina kordinates jeigu jos persidengia
	for (int i = 0; i < size * size; i++) {
		if (cordx[i]==x && cordy[i] == y) {
			cordx[i] = -1;
			cordy[i] = -1;
			return false;
		}
	}
	return true;
}

int Kvadratai(int x1, int y1, int x2, int y2, int size) {        //suranda suma pagal dydi ir kvadratu kordinates
	if (inFrame(x1, y1, size) && inFrame(x2, y2, size)) {
		int cordx[5000], cordy[5000];
		int x = x1, y = y1, counter = 0;
		for (int i = 0; i < size; i++) {
			for (int p = 0; p < size; p++) {
				cordx[counter] = x;
				cordy[counter] = y;
				counter++;
				x++;
			}
			x = x1;
			y++;
		}
		x = x2;
		y = y2;
		for (int i = 0; i < size; i++) {
			for (int p = 0; p < size; p++) {
				if (removeRepeat(x, y, size, cordx, cordy)) {
					cordx[counter] = x;
					cordy[counter] = y;
					counter++;
				}
				x++;
			}
			x = x2;
			y++;
		}
		int suma = 0;
		for (int i = 0; i < counter; i++) {
			if (cordx[i] != -1 && cordy[i] != -1) {
				suma += lentele[cordx[i]][cordy[i]];
			}
		}

		return suma;
	}
	return -1;
}

int bestPlace(int size, int& bestx1, int& besty1, int& bestx2, int& besty2) {      //suranda geriausia vieta
	int bestscore = 0;
	bestx1 = 0;
	besty1 = 0;
	bestx2 = 0;
	besty2 = 0;
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	for (int i = 0; i < n - (size - 1); i++) {
		for (int p = 0; p < n - (size - 1); p++) {
			for (int a = 0; a < n - (size - 1); a++) {
				for (int c = 0; c < n - (size - 1); c++) {
					int temp = Kvadratai(x1, y1, x2, y2, size);
					if (temp > bestscore) {
						bestscore = temp;
						bestx1 = x1;
						besty1 = y1;
						bestx2 = x2;
						besty2 = y2;
					}
					x1++;
				}
				x1 = 0;
				y1++;
			}
			x1 = 0;
			y1 = 0;
			x2++;
		}
		x2 = 0;
		y2++;
	}
	return bestscore;
}

int allSize(int& size, int& bestx1, int& besty1, int& bestx2, int& besty2) {    //suranda geriausia dydi
	int bestscore = 0;
	for (int i = 1; i <= n - 1; i++) {
		int x1, x2, y1, y2;
		int temp = bestPlace(i, x1, y1, x2, y2);
		if (temp > bestscore) {
			bestx1 = x1;
			bestx2 = x2;
			besty1 = y1;
			besty2 = y2;
			bestscore = temp;
			size = i;
		}
	}
	return bestscore;
}

int main() {
	skaityti();
	int size, x1, y1, x2, y2, score = allSize(size, x1, y1, x2, y2);
	spausdinti(size, score, x1, y1, x2, y2);
}
