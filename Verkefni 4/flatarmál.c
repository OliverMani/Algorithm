#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct part {
	char* number;
	char next_action;
	struct part* next;
};

char char_in(char ch, char* str) {
	int i = 0;
	while(str[i++])
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

		printf("ch = %c\n", ch);

		if(char_in(ch, "0123456789")) {
			if(!read_number) {
				read_number = 1;
				last_number = 0;
			}
			if(read_variable) {
				read_variable = 0;
				printf("Number is NULL: %i (%s -> '%i')\n", last->number == NULL, last->number, last->next_action == 0);
				struct part* next = malloc(sizeof(struct part));
				next->number = "0";
				next->next_action = 0;
				next->next = NULL;
				last->next_action = '^';
				last->next = next;
				last = last->next;
				
				
			}
			
			
			
			
			read_action = 0;
			last_number *= 10;
			last_number += ch - 48;

			last->number = int_to_str(last_number);
		} else if(char_in(ch, "+-*/^R")) {
			if(root == last && ch == '-')
				root->number = "0";
			//printf("Last next NOT exists: %i\n", last->next == NULL);
			last->next_action = ch;
			struct part* new = malloc(sizeof(struct part));
			new->number = NULL;
			new->next_action = 0;
			new->next = NULL;
			last->next = new;
			
			last = last->next;

			read_action = 1;
		} else if(char_in(ch, "()")) {

		} else {
			// X for example...
			//printf("?? Formula + 1: %c\n", formula[i+1]);

			char* new_ch = malloc(sizeof(char)*2);
			new_ch[0] = ch;
			new_ch[1] = 0;

			if(read_number) {
				read_number = 0;
				if(!last->next_action)
					last->next_action = '*';
				
			}
			
			last->number = new_ch;
			if(formula[i + 1] && !char_in(formula[i + 1], "+-/*^R")) {
				last->next_action = char_in(formula[i+1], "0123456789") ? 'A' : 'B';
			} else {
				struct part* new = malloc(sizeof(struct part));
				new->next_action = 0;
				last->next = new;
				last = last->next;
			}

			read_variable = 1;


			
		}
	}

	return root;
}

int main() {
	//printf("Int i streng: %s\n", int_to_str(1234565));

	char input[1024];
	for(int i = 0; i < 1024; i++)
		input[i] = 0;
	gets(input);

	struct part* parsed = parse(input);

	while(parsed) {
		printf("%s %c ", parsed->number, parsed->next_action);
		parsed = parsed->next;
	}

	printf("\n");
}