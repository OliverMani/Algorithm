#include <stdio.h>

/*
Dæmi 1:
str = ""
x = tala
á meðan x er meira en núll:
	ef x er oddatala:
		þá bætist 1 við str
	annars:
		bætist 0 við str
	x deilist með tveim en verður heiltala
	
*/

int summa(int n) {
	int m = 0;
	if(n == 1)
		return 1;
	return (n*n) + summa(n-1);
}

void runa(int r){
	if(r == 1){
		printf("1, ");
	}
	else {
		runa(r-1);
		int j = ((r*(r+1))/2);
		printf("%i, ", j);
	}
}

// Þversumma með streng
int s_tsumma(char* num) {
	if(num[0] == 0)
		return 0;
	return num[0] - 48 + s_tsumma(num + 1); // num + 1 tengist pointers
}

// Þversumma með int
int i_tsumma(int num) {
	if(num == 0)
		return 0;
	return (num % 10) + i_tsumma(num / 10);
}

int samnefnari(int n, int m) {
	if(n > m)
		return samnefnari(m, n);
	if(!(m % n))
		return n;
	return samnefnari(m % n, m);
}

int main(){
	printf("Summa með öðru veldi: %i\n", summa(5));
	printf("Runa: ");
	runa(7);
	printf("\n");
	printf("Þversumma með streng (192719): %i\n", s_tsumma("192719"));
	printf("Þversumma með int (192719): %i\n", i_tsumma(192719));
	printf("Samnefnari: %i\n", samnefnari(101, 1004));
}
