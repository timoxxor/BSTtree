#include <fstream>
#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include <string>

#define todo(...) ((void)0)
#define len(arr) sizeof(arr) / sizeof(arr[0]) 

// Прямой обход (N - L - R)
// Симметричный обход (L - N - R)
// Обратный обход (L - R - N)

struct Node {
	Node* right;
	Node* left;
	int key;
	void* value;
};

Node* create_node(int key) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->left = nullptr;
	node->right = nullptr;

	return node;
}

void push_data(Node* self, int key) {
	if (key > self->key) 
		(self->right == nullptr) ? (void)(self->right = create_node(key)) : push_data(self->right, key);
	else if (key < self-> key) 
		(self->left == nullptr) ? (void)(self->left = create_node(key)) : push_data(self->left, key);
	else return;
}

void free_BST(Node* self) {
	if (!self) return;

	free_BST(self->left);
	free_BST(self->right);

	free(self);
}

Node* copy_BST(Node* src) {
	if (!src) return nullptr;

	Node* dst = create_node(src->key);

	dst->left = copy_BST(src->left);
	dst->right = copy_BST(src->right);

	return dst;
}

void serialize_BST(Node* self, std::ostream& os) {
	if (!self) return;

	os << self->key << ": ";
	if (self->left)
		os << self->left->key << " ";
	else
		os << "null ";

	if (self->right) 
		os << self->right->key << "\n";
	else
		os << "null \n";		

	serialize_BST(self->left, os);
	serialize_BST(self->right, os);
}

Node* deserialize_BST(std::istream& is) {
	std::string line;
	if (!std::getline(is, line) || line.empty()) return nullptr;

	Node* root = create_node(std::stoi(line));

	while (std::getline(is, line)) {
		if (!line.empty()) push_data(root, std::stoi(line));
	}

	return root;
}

int main(int argc, char* argv[]) {
	Node* root = create_node(10);

	int arr[] = {4, 8, 3, 19, 21, 7, 18};
	for (int i = 0; i < len(arr); i++) {
		push_data(root, arr[i]);
	}	

	std::string file = "tree.bst";
	std::ifstream os(file);
	Node* test = deserialize_BST(os);

	serialize_BST(test, std::cout);

	free_BST(root);
	return 0;
}

