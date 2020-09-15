# Algorithm
Reiknirits áfangi

## Skilaverkefni 2:
Dæmi 1:
```
str = ""
x = tala
á meðan x er meira en núll:
	ef x er oddatala:
		þá bætist 1 við str
	annars:
		bætist 0 við str
	x deilist með tveim en verður heiltala
```
Dæmi 2:
```C
int summa(int n) {
	return n == 1 ? 1 : ((n*n) + summa(n-1));
}
```
