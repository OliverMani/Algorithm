#include <stdio.h>
#include <math.h>

class Vigur {
private:
	int x;
	int y;
public:
	Vigur(int x, int y) {
		this->x = x;
		this->y = y;
	}

	double lengd() {
		return sqrt(pow(this->x, 2) + pow(this->y, 2));
	}

	Vigur normalize(){
		return Vigur(this->x/this->lengd(), this->y/this->lengd());
	}

	Vigur thvervigur() {
		return Vigur(-this->y, this->x);
	}

	void prenta(){
		cout << "(" << this->x << " " << this->y << ")\n";
	}

	double hallatala() {
		return this->y / this->x;
	}

	double stefnuhorn() {
		return atan(this->hallatala()) * (180/M_PI);
	}

	double horn(Vigur v2){
		return acos(((this->x*this->y)+(v2.x*v2.y))/(this->lengd()*v2.lengd())) * (180 / M_PI);
	}

	Vigur summa(Vigur v2){
		return Vigur(this->x + v2.x, this->y + v2.y);
	}
};

int main(void)
{
	Vigur v1(1,3);
	v1.prenta();
	printf("Lengd: %f\n", v1.lengd());
	printf("Halli: %f\n", v1.hallatala());
	Vigur thv = v1.thvervigur();
	printf("Thervigur: ");
	thv.prenta();
	printf("Stefnuhorn: %f\n", v1.stefnuhorn());
	Vigur v2(-3, 1);
	printf("Horn milli vigra: %f\n", v2.horn(v1));
	Vigur v3 = v1.summa(v2);
	printf("Summa: ");
	v3.prenta();
	return 0;
}