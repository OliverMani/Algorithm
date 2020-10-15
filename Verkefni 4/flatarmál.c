#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct part {
	char* number;
	char next_action;
	struct part* next;
};

char char_in(char ch, char* str) {
	for(int i = 0; str[i]; i++)
		if(ch == str[i])
			return 1;
	return 0;
}



char* int_to_str(int num){
	int size = ceil(log10(num));
	char* result = malloc(size+1);
	result[size] = 0;
	for(int i = size - 1; i >= 0; i--) {
		result[i] = (num % 10) | 48;
		num /= 10;
	}

	return result;
}

int str_to_int(char* str) {
	int i = 0;
	int number = 0;
	while(str[i]) {
		number *= 10;
		number += str[i] - 48;
		i++;
	}
	return number;
}

double reikna_tolur(char* tolur) {
	double number = 0;
	double tmp = 0;
	int i = 0;
	while(tolur[i]) {
		tmp = 0;
		while(char_in(tolur[i], "0123456789")) {
			tmp *= 10;
			tmp += tolur[i] - 48;
			i++;
		}

		switch(tolur[i]) {
			case '+':
				number += tmp;
				break;
			case '-':
				number -= tmp;
				break;
			case '*':
				number *= tmp;
				break;
			case '/':
				number /= tmp;
				break;
			case '^':
				number = pow(number, tmp);
				break;
		}


		i++;
	}

	return number;
}

struct part* parse(char* formula) {
	int i = 0;

	char read_number = 0;
	char read_variable = 0;
	char read_action = 0;

	int last_number = 0;
	char ch;

	struct part* root = malloc(sizeof(struct part));
	root->number = "";
	root->next_action = 0;
	root->next = NULL;
	struct part* last = root;

	while((ch = formula[i++])) {

		if(char_in(ch, "0123456789")) {
			
			if(!read_number) {
				read_number = 1;
				last_number = 0;
			}

			last_number *= 10;
			last_number += (ch - 48);

			last->number = int_to_str(last_number);

		} else if(char_in(ch, "+-/*^R")) {
			
			read_number = 0;
			if(ch == '-' && last == root) {
				struct part* new = malloc(sizeof(struct part));
				new->number = "0";
				new->next_action = ch;
				new->next = root;
				root = new;
			} else {
				last->next_action = ch;
				struct part* new = malloc(sizeof(struct part));
				new->number = NULL;
				new->next_action = 0;
				new->next = NULL;
				last->next = new;
				last = last->next;
			}
		} else {
			
			read_number = 0;
			last->number = "x";
			if(char_in(formula[i], "+-/*^R")) {
				last->next_action = formula[i++];
				
			} else {
				last->next_action = char_in(formula[i], "0123456789") ? '^' : '*';
			}
			struct part* new = malloc(sizeof(struct part));
			new->number = NULL;
			new->next_action = 0;
			new->next = NULL;
			last->next = new;
			last = last->next;
			
		}
	}

	return root;
}

void heilda(struct part* root) {
	struct part* last = root;
	while(last) {
		char* number = last->number;
		char action = last->next_action;

		if(number != "x" && last != root) {

			struct part* new = malloc(sizeof(struct part));
			new->number = "A";
			new->next_action = last->next_action;
			new->next = last->next;
			last->next_action = '*';
			last->next = new;
			
			last = last->next;
		} else switch (action) {
			case '^':
				// Við viljum setja parta fyrir aftan, byrjum á að býa þá til
				struct part* tmp = malloc(sizeof(struct part));
				tmp->number = last->number;
				tmp->next = last->next;
				tmp->next_action = last->next_action;

				// Hoppa yfir í næsta
				last = last->next;

				// Við viljum breyta veldinu...
				int inum = str_to_int(last->number);
				inum++;
				last->number = int_to_str(inum);
				break;
			default:break;
		}

		last = last->next;
	}
}

int main() {
	//printf("Int i streng: %s\n", int_to_str(1234565));
	
	char input[1024];
	for(int i = 0; i < 1024; i++)
		input[i] = 0;
	gets(input);

	struct part* parsed = parse(input);
	struct part* last = parsed;

	while(last) {
		printf("%s %c ", last->number, last->next_action);
		last = last->next;
	}

	printf("\nHeildað: ");

	heilda(parsed);
	last = parsed;

	while(last) {
		printf("%s %c ", last->number, last->next_action);
		last = last->next;
	}
	printf("\n");
}