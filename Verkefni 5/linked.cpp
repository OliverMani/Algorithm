#include <string>
#include <iostream>

using namespace std;

template <class T> struct Node {
	T data;
	Node* next;
	Node* prev;

	Node(T data){
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
};

template <class T> class DDL {
private:
	Node<T>* root;
public:
	DDL(Node<T>* root){
		this->root = root;
	}
	DDL() {
		this->root = nullptr;
	};

	DDL(T str) {
		this->root = new Node<T>(str);
	}

	void print_list(){
		print_list(endl);
	}
	void print_list(string end){
		Node<T>* current = this->root;
		while(current) {
			cout << current->data << end;
			current = current->next;
		}
	}

	void push(T data){
		if(!this->root) {
			this->root = new Node<T>(data);
			return;
		}
		Node<T>* node = new Node<T>(data);
		node->next = this->root;
		this->root->prev = node;
		this->root = node;
	}

	void append(T data){
		if(!this->root) {
			this->root = new Node<T>(data);
			return;
		}
		Node<T>* current = this->root;
		while(current->next)
			current = current->next;
		current->next = new Node<T>(data);
		current->next->prev = current;

	}

	void del(T data) {
		Node<T>* current = this->root;
		while(current) {
			Node<T>* next = current->next;
			if(current->data == data) {
				current->prev->next = current->next;
				current->next->prev = current->prev;
				delete current;
			}
			current = next;
		}
	}

	bool find(T data){
		Node<T>* current = this->root;
		while(current) {
			if(current->data == data)
				return true;
			current = current->next;
		}
		return false;
	}

	~DDL(){
		Node<T>* current = this->root;
		while(current) {
			Node<T>* next = current->next;
			delete current;
			current = next;
		}
	}


};

int main(){
	DDL<int> list;
	list.append(5);
	list.append(7);
	list.push(1);
	list.push(0);
	list.append(10);
	list.print_list(" ");
	list.del(5);
	cout << endl;
	list.print_list(" ");
	cout << endl;
	cout << list.find(5) << endl;
	cout << list.find(7) << endl;
}