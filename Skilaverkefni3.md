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