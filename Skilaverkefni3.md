# Skilaverkefni 3, kóðar:
## Flækjustig:
Big O er merkt sem flækjustig á reikniritum, til dæmis fyrir tímamælingar og svona.

a) O(n) er þegar við erum með lista og notum algrím sem þarf að fara í gegnum allan listann einu sinni til að virka
b) O(n^2) kemur þegar við erum til dæmis með lykkju inn í lykkju, BubbleSort er til dæmis með flækjustigið O(n^2) í versta tilfelli
c) O(n\*log(n)) er þegar algríðmið getur sparað sér tíma í að gera það sem það gerir

## Röðunaralgrím:

Hér notaðist ég við Bubblesort, og bar saman við qsort (úr stdlib í C) og counting sort (sem ég kóðaði sjálfur), cmpfunc sem þú sérð er fall sem maður þarf út af einhverri ástæðu að skrifa sjálfur fyrir qsort og láta qort svo kalla á það til að bera tölur saman til að raða.

```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // Fyrir tímamæingar

#define MILLION 1000000
#define MALLOC 400000 // Það sem við ætlum að taka langan lista

void bubblesort(int size, int* listi) {
	int count;
	do {
		count = 0;
		for(int i = 1; i < size; i++) {
			if(listi[i] < listi[i-1]) {
				int tmp = listi[i];
				listi[i] = listi[i - 1];
				listi[i - 1] = tmp;
				count++;
			}
		}
		size--;
		
	} while(count > 1);
}

int* countingsort(int size, int* listi, int min, int max) {
	
	int count[max+1];
	for(int i = 0; i < max+1; i++)
		count[i] = 0;
	for(int i = 0; i < size; i++) {
		count[listi[i]]++;
	}
	for(int i = 1; i < max+1; i++) {
		count[i] += count[i-1];
	}
	
	int* result = malloc(size*sizeof(int));
	
	for(int i = 0; i < size; i++) {
		
		int index1 = listi[i];
		int index2 = count[index1-1]--;
		
		//printf("%i, index2: %i\n", i, index2);
		result[index2] = listi[i];
	}
	
	return result;
}



int cmpfunc(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}


int main(){

	int* listi = malloc(MALLOC*sizeof(int));

	for(int i = 0; i < MALLOC; i++) {
		listi[i] = MALLOC - i;
		
	}
	
	struct timespec start, end;
	// BUBBLESORT BEGIN
	
	printf("Sorting list...\n");
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	bubblesort(MALLOC, listi);
	
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("BubbleSorting took %f seconds\n", (double)((((double)((double)end.tv_sec - start.tv_sec) * MILLION) + (((double)end.tv_nsec - (double)start.tv_nsec) / 1000))/MILLION));
	printf("%i, %i, %i, %i\n", listi[0], listi[MALLOC-1], listi[500], listi[MALLOC/2]);
	// BUBBLESORT END
	
	// C qsort BEGIN (innbyggða sorting fallið í C úr stdlib)
	int* listi2 = malloc(MALLOC*sizeof(int));
	for(int i = 0; i < MALLOC; i++) {
		listi2[i] = MALLOC - i;
	}
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	qsort(listi2, MALLOC, sizeof(int), cmpfunc);
	
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("QSorting took %f seconds\n", (double)((((double)((double)end.tv_sec - start.tv_sec) * MILLION) + (((double)end.tv_nsec - (double)start.tv_nsec) / 1000))/MILLION));
	
	printf("%i, %i, %i, %i\n", listi2[0], listi2[MALLOC-1], listi2[500], listi2[MALLOC/2]);
	// C qsort END
	// COUNTINGSORT BEGIN
	for(int i = 0; i < MALLOC; i++) {
		listi2[i] = MALLOC - i;
	}
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	int* res = countingsort(MALLOC, listi2, 0, MALLOC-1);
	
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("CountingSorting took %f seconds\n", (double)((((double)((double)end.tv_sec - start.tv_sec) * MILLION) + (((double)end.tv_nsec - (double)start.tv_nsec) / 1000))/MILLION));
	
	printf("%i, %i, %i, %i\n", res[0], res[MALLOC-1], res[500], res[MALLOC/2]);
	// COUNTINGSORT END

	
	free(listi);
	free(listi2);
	
}
```

## Stafróf:
Fallið:
```C
// Recursive fall til að raða í stafrófsröð!!
// Aðferðin byggir á bubblesort
void stafrof(int len, char** strengir) {	
	if(!len) // Ef len er 0 þá þurfum við ekki að gera neitt
		return;
	
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
```C
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

## Fallið fall úr verkefninu:


#### a)
Fyrsta for-lykkjan er til að telja hvað hver tala kemur oft fyrir á listanum, og setja það í count listann

Önnur lykkjan er til að plúsa saman tölurnar í count listanum

Þriðja lykkjan er einmitt síðasta lykkjan og hún notar count listann til að raða öllum listanum rétt

#### b)
Reikniritið heitir Countingsort

#### c)
Tímaflækjustigið er O(n+k) og minnisflækjustigið er O(k)