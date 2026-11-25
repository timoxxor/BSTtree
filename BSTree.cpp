#include "BSTree.hpp"
#include <fstream>

namespace BSTree {
	BST::Node* BST::create(int key) {
		Node* node = (Node*)malloc(sizeof(Node));

		node->key = key;
		node->left = nullptr;
		node->right = nullptr;

		return node;
	}

	void BST::_free(Node* self) {
		if (!self) return;

		_free(self->left);
		_free(self->right);

		free(self);
	}

	BST::Node* BST::copy(Node* self) {
		if (!self) return nullptr;

		Node* dst = create(self->key);

		dst->left = copy(self->left);
		dst->right = copy(self->right);

		return dst;
	}

	void BST::_push(Node* self, int key) {
		if (key > self->key) 
			(self->right == nullptr) ? (void)(self->right = create(key)) : _push(self->right, key);
		else if (key < self-> key) 
			(self->left == nullptr) ? (void)(self->left = create(key)) : _push(self->left, key);
		else return;
	}

	void BST::_serialize(Node* self, std::ostream& os) const {
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
	
		_serialize(self->left, os);
		_serialize(self->right, os);
	}
	
	BST::Node* BST::_deserialize(std::istream& is) {
		std::string line;
		if (!std::getline(is, line) || line.empty()) return nullptr;
	
		Node* root = create(std::stoi(line));
	
		while (std::getline(is, line)) {
			if (!line.empty()) _push(root, std::stoi(line));
		}
	
		return root;
	}

	BST::Node* BST::_find(Node* self, int key) {
		if (!self || self->key == key) return self;

		return (self->key > key) ? _find(self->left, key) : _find(self->right, key);
	}

	BST::Node* BST::_get_succesor(Node* self) {
		self = self->right;
		while (self && self->left) {
			self = self->left;
		}
		return self;
	}

	BST& BST::operator=(const BST& other) {
		if (this != &other) {
			_free(root);
			root = copy(other.root);
		}
		return *this;
	}

	BST& BST::operator=(BST&& other) noexcept {
		if (this != &other) {
			_free(root);
			root = other.root;
			other.root = nullptr;
		}
		return *this;
	}

	void BST::clear() {
		_free(root);
		root = nullptr;
	}

	BST::Node* BST::_remove(Node* self, int key) {
		if (!self) return nullptr;

		if (key < self->key) self->left = _remove(self->left, key);
		else if (key > self->key) self->right = _remove(self->right, key);
		else {
			// 1  
			if (!self->left) {
				Node* temp = self->right;
				free(self);
				return temp;
			}

			if (!self->right) {
				Node* temp = self->left;
				free(self);
				return temp;
			}

			// 2
			Node* temp = _get_succesor(self); 
			self->key = temp->key;
			self->right = _remove(self->right, temp->key);
		}

		return self;
	}
	
	// L-N-R (In order)
	void BST::_in_order(Node* self, std::ostream& os) {
		if (!self) return;

		_in_order(self->left, os);
		os << self->key << " ";
		_in_order(self->right, os);
	}

	// L-R-N (Post-order)
	void BST::_post_order(Node* self, std::ostream& os) {
		if (!self) return; 

		_post_order(self->left, os);
		_post_order(self->right, os);
		os << self->key << " ";
	}

	// N-L-R (Pre-order)
	void BST::_pre_order(Node* self, std::ostream& os) {
		if (!self) return; 

		os << self->key << " ";
		_pre_order(self->left, os);
		_pre_order(self->right, os);
	}

	void BST::push(int key) {
		if (!root) root = create(key);
		else _push(root, key);
	}
	
	std::ostream& operator<<(std::ostream& os, const BST& tree) {
		tree._serialize(tree.root, os);
		return os;
	}

	void BST::serialize(const std::string& file) {
		std::ofstream ofs(file);
		if (ofs.is_open()) {
			_serialize(root, ofs);
		} 
	}

	void BST::deserialize(const std::string& file) {
		std::ifstream ifs(file);
		if (ifs.is_open()) {
			_free(root);
			root = nullptr; 

			root = _deserialize(ifs);
		}
	}

	void BST::remove(int key) {
		root = _remove(root, key);
	}

	BST::Node* BST::find(int key) {
		return _find(root, key);	
	}

	void BST::in_order(std::ostream& os) { _in_order(root, os); }
	void BST::post_order(std::ostream& os) { _post_order(root, os); }
	void BST::pre_order(std::ostream& os) { _pre_order(root, os); }

	void BST::_merge(Node* src) {
		if (!src) return;
		push(src->key);
		_merge(src->left);
		_merge(src->right);
	}

	void BST::merge(const BST& other) {
		_merge(other.root);
	}

	BST BST::merge(const BST trees[], size_t n) {
		BST result;
		for (size_t i = 0; i < n; ++i) {
			result.merge(trees[i]);
		}
		return result;
	}
}
