# Skilaverkefni 3, kóðar:

## Stafróf:
Fallið:
```C
// Recursive fall til að raða í stafrófsröð!!
void stafrof(int len, char** strengir) {	
	if(!len)
		return;
	int count = 0;
	for(int i = 1; i < len; i++) {
		int j = 0;
		for(; strengir[i][j] && strengir[i-1][j] && strengir[i][j] == strengir[i-1][j]; j++);
	
		if(strengir[i][j] < strengir[i-1][j]) {
			char* tmp = strengir[i];
			strengir[i] = strengir[i - 1];
			strengir[i - 1] = tmp;
		}
	}
	stafrof(--len, ++strengir);
}
```
Notkun:
```C
stafrof(lengd á lista, listi af strengjum);
```

## Raða strax í lista:
```
#include <stdio.h>
#include <stdlib.h>

char rada_i_lista(int* listi, int lengd, int tala) {
	int i;
	for(i = 0; i < lengd && listi[i] < tala; i++); // Finna stað
	for(int j = lengd; j >= i; j--){
		listi[j+1] = listi[j];
	}
	listi[i] = tala;
	return 1; // 1 er sama og true í C (í raun er true og false ekki skilgreint í C eins og í C++, en það er hægt að skilgreina það með #define og fleiri leiðum)
}

int main(){
	int N;
	printf("Sláðu inn hvað þú vilt hafa margar tölur í listanum: ");
	scanf("%i", &N); // int input, breytan N verður að tölunni sem þú slærð inn

	int* listi = malloc(N * sizeof(int)); // sama og new í C++, bara new er ekki til í C

	for(int i = 0; i < N; i++) {
		printf("Sláðu inn tölu: ");
		int tala;
		scanf("%i", &tala); // Input, breytan tala verður að tölunni sem þú slærð inn
		rada_i_lista(listi, i, tala);
	}

	// Prenta lista
	for(int i = 0; i < N; i++) {
		printf("%i, ", listi[i]);
	}
	printf("\n");

	free(listi); // sama og delete í C++, bara delete er ekki til í C
}
```