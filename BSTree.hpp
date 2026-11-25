#include <iostream>
#include <stdlib.h>
#include <string>

namespace BSTree {
	class BST {
	private:
		struct Node {
			Node* right;
			Node* left;
			void* value;
			int key;
		};		
		
		Node* root;
		
		Node* create(int key);

		void _free(Node* self); 

		Node* copy(Node* self); 
		
		void _push(Node* self, int key);

		void _serialize(Node* self, std::ostream& os) const;
		
		Node* _deserialize(std::istream& is);

		Node* _find(Node* self, int key); 

		// inline? 
		Node* _get_succesor(Node* self);

		Node* _remove(Node* self, int key);
		
		// L-N-R
		void _in_order(Node* self, std::ostream& os);

		// L-R-N
		void _post_order(Node* self, std::ostream& os);

		// N-L-R
		void _pre_order(Node* self, std::ostream& os);

		void _merge(Node* src);

	public:
		BST() : root(nullptr) {}
		BST(int key) : root(create(key)) {}
		BST(const BST& other) : root(copy(other.root)) { }
		BST(BST&& other) noexcept : root(other.root) {
			other.root = nullptr;
		}
		BST& operator=(const BST& other);
		BST& operator=(BST&& other) noexcept;

		~BST() {
			_free(root);
		} 

		void clear();
		bool empty() const { return root == nullptr; }

		void push(int key);
		
		friend std::ostream& operator<<(std::ostream& os, const BST& tree);

		void serialize(const std::string& file);

		void deserialize(const std::string& file);

		void remove(int key);

		Node* find(int key);

		void in_order(std::ostream& os);
		void post_order(std::ostream& os);
		void pre_order(std::ostream& os);

		void merge(const BST& other);
		static BST merge(const BST trees[], size_t n);

	};
}