#include <stdio.h>
#include <malloc.h>

struct tree {
	int number;
	struct tree* left;
	struct tree* right;
};

struct tree* init(int number) {
	struct tree* root = malloc(sizeof(struct tree));
	root->number = number;
	root->left = NULL;
	root->right = NULL;
	return root;
}

void insert(struct tree* root, int number) {
	if(number < root->number) {
		if(root->left) {
			insert(root->left, number);
		} else {
			root->left = init(number);
		}
	} else if (number > root->number) {
		if(root->right) {
			insert(root->right, number);
		} else {
			root->right = init(number);
		}
	}
}

struct tree* find(struct tree* root, int number) {
	if(!root)
		return NULL;
	if(number < root->number) {
		if(!root->left)
			return NULL;
		return find(root->left, number);
	} else if(number > root->number) {
		if(!root->right)
			return NULL;
		return find(root->right, number);
	}
	return root;
}

char delete(struct tree* root, int number) {
	struct tree* top = root;
	struct tree* prev = top;
	while(top->number != number) {
		prev = top;
		if(number < top->number) {
			top = top->left;
		} else {
			top = top->right;
		}
	}
	if(!top)
		return 0;
	if(!top->right) {
		if(!top->left) {
			free(top);
			if(prev->left == top)
				prev->left = NULL;
			else if(prev->right == top) 
				prev->right = NULL;
		} else {
			top->number = top->left->number;
			struct tree* tmp = top->left;
			top->left = tmp->left;
			top->right = tmp->right;
			free(tmp);
		}
	} else {
		struct tree* right = top->right;
		struct tree* current = right;
		struct tree* prev = current;
		int min;
		while(current->left) {
			prev = current;
			min = current->number;
			current = current->left;
		}

		top->number = min;
		free(current);
		prev->left = NULL;
	}
	

	return 1;
}

void preOrderPrint(struct tree* root) {

}

void postOrderPrint(struct tree* root) {
	printf("from %i: ", root->number);
	if(root->left)
		printf("%i, ", root->left->number);
	else
		printf("(null), ");
	if(root->right)
		printf("%i\n", root->right->number);
	else
		printf("(null)\n");
	
	if(root->left)
		postOrderPrint(root->left);
	if(root->right)
		postOrderPrint(root->right);
}

int main(){
	struct tree* root = init(16);
	insert(root, 5);
	insert(root, 18);
	char found = find(root, 5) != NULL;
	printf("Fann 5: %i\n", found);
	printf("Fann 6: %i\n", find(root, 6) != NULL);
	insert(root, 3);
	insert(root, 12);
	printf("Fann 12: %i\n", find(root, 12) != NULL);
	delete(root, 12);
	printf("Fann 12: %i\n", find(root, 12) != NULL);
	printf("\n\n\n");
	postOrderPrint(root);
}