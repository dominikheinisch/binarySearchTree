#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <vector>
#include <sstream>

namespace DataStructures
{
	template <class T>
	class BinarySearchTree
	{
	private:
		class Node
		{
		friend class BinarySearchTree;
		private:
			T value;
			Node * left;
			Node * right;

			Node() :
				left(nullptr), right(nullptr) {}
			Node(const T & val) :
				left(nullptr), right(nullptr), value(val) {}
		};

		Node * root;
		bool insert(const T & val, Node *& node);
		bool remove(const T & val, Node *& node);
		bool contains(const T & val, Node *& node);
		Node * succesorParent(Node *& node) const;
		size_t size(const Node * node) const;
		void deleteTree(Node *& node);
		typedef typename std::vector<T>::iterator T_itera_type;
		static void toVectorInOrder(Node * node, T_itera_type & iter);
		static void toVectorPreOrder(Node * node, T_itera_type & iter);
		static void toVectorPostOrder(Node * node, T_itera_type & iter);
		typedef typename std::vector<typename BinarySearchTree<T>::Node *>::iterator p_node_iter_type;
		static void toVectorLevelOrder(p_node_iter_type node_iter, p_node_iter_type add_iter, p_node_iter_type end_iter);

	public:
		BinarySearchTree() : root(nullptr) {}
		~BinarySearchTree();
		T* getRoot() const;
		bool contains(const T & val);
		bool insert(const T & val);
		bool remove(const T & val);
		int size() const;
		std::vector<T> toVectorInOrder() const;
		std::vector<T> toVectorPreOrder() const;
		std::vector<T> toVectorPostOrder() const;
		std::vector<T> toVectorLevelOrder() const;
		std::string toString() const;
			template <typename U>
		friend std::ostream& operator<<(std::ostream& out, const BinarySearchTree<U>& bst);
	};

	template<class T>
	bool BinarySearchTree<T>::insert(const T & val, Node *& node)
	{
		if (node == nullptr)
		{
			node = new Node(val);
			return true;
		}
		else
		{
			if (node->value == val)
			{
				return false;
			}
			else if (val < node->value)
			{
				return insert(val, node->left);
			}
			else
			{
				return insert(val, node->right);
			}
		}
	}

	template<class T>
	bool BinarySearchTree<T>::remove(const T & val, Node *& node)
	{
		if (node == nullptr)
		{
			return false;
		}
		else if (val < node->value)
		{
			remove(val, node->left);
		}
		else if (val > node->value)
		{
			remove(val, node->right);
		}
		else
		{
			if (node->left == nullptr && node->right == nullptr)
			{
				delete node;
				node = nullptr;
			}
			else if (node->left == nullptr)
			{
				Node *ptr = node->right;
				delete node;
				node = ptr;
			}
			else if (node->right == nullptr)
			{
				Node *ptr = node->left;
				delete node;
				node = ptr;
			}
			else
			{
				Node *parent = succesorParent(node->right);
				parent->left->left = node->left;
				parent->left->right = node->right;
				delete node;
				node = parent->left;
				parent->left = nullptr;
			}
			return true;
		}
	}

	template<class T>
	bool BinarySearchTree<T>::contains(const T & val, Node *& node)
	{
		if (node == nullptr)
		{
			return false;
		}
		else if (val < node->value)
		{
			contains(val, node->left);
		}
		else if (val > node->value)
		{
			contains(val, node->right);
		}
		else return true;
	}

	template<class T>
	typename BinarySearchTree<T>::Node * BinarySearchTree<T>::succesorParent(Node *& node) const
	{
		if (node == nullptr || node->left == nullptr)
		{
			return nullptr;
		}
		else
		{
			while (node->left->left != nullptr)
			{
				node = node->left;
			}
			return node;
		}
	}

	template<class T>
	size_t BinarySearchTree<T>::size(const Node * node) const
	{
		return node == nullptr ? 0 : 1 + size(node->left) + size(node->right);
	}

	template<class T>
	void BinarySearchTree<T>::deleteTree(Node *& node)
	{
		if (node != nullptr)
		{
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
	}

	template<class T>
	void BinarySearchTree<T>::toVectorInOrder(Node * node, T_itera_type & iter)
	{
		if (node != nullptr)
		{
			toVectorInOrder(node->left, iter);
			*iter++ = node->value;
			toVectorInOrder(node->right, iter);
		}
	}

	template<class T>
	void BinarySearchTree<T>::toVectorPreOrder(Node * node, T_itera_type & iter)
	{
		if (node != nullptr)
		{
			*(iter++) = node->value;
			toVectorPreOrder(node->left, iter);
			toVectorPreOrder(node->right, iter);
		}
	}

	template<class T>
	void BinarySearchTree<T>::toVectorPostOrder(Node * node, T_itera_type & iter)
	{
		if (node != nullptr)
		{
			toVectorPostOrder(node->left, iter);
			toVectorPostOrder(node->right, iter);
			*iter++ = node->value;
		}
	}

	template<class T>
	void BinarySearchTree<T>::toVectorLevelOrder(p_node_iter_type node_iter, p_node_iter_type add_iter, p_node_iter_type end_iter)
	{
		if ((*node_iter)->left != nullptr)
		{
			*(++add_iter) = (*node_iter)->left;
		}
		if ((*node_iter)->right != nullptr)
		{
			*(++add_iter) = (*node_iter)->right;
		}
		if (node_iter + 1 != end_iter)
		{
			toVectorLevelOrder(++node_iter, add_iter, end_iter);
		}
	}

	template<class T>
	BinarySearchTree<T>::~BinarySearchTree()
	{
		deleteTree(root);
	}

	template<class T>
	T * BinarySearchTree<T>::getRoot() const
	{
		if (root != nullptr)
		{
			return &(root->value);
		}
		else return nullptr;
	}

	template<class T>
	bool BinarySearchTree<T>::contains(const T & val)
	{
		return contains(val, root);
	}

	template<class T>
	bool BinarySearchTree<T>::insert(const T & val)
	{
		return insert(val, root);
	}

	template<class T>
	bool BinarySearchTree<T>::remove(const T & val)
	{
		return remove(val, root);
	}

	template<class T>
	int BinarySearchTree<T>::size() const
	{
		return size(root);
	}

	template<class T>
	std::vector<T> BinarySearchTree<T>::toVectorInOrder() const
	{
		size_t size = this->size();
		std::vector<T> vect(size > 0 ? size : 1);
		toVectorInOrder(root, vect.begin());
		return vect;
	}

	template<class T>
	std::vector<T> BinarySearchTree<T>::toVectorPreOrder() const
	{
		size_t size = this->size();
		std::vector<T> vect(size > 0 ? size : 1);
		toVectorPreOrder(root, vect.begin());
		return vect;
	}

	template<class T>
	std::vector<T> BinarySearchTree<T>::toVectorPostOrder() const
	{
		size_t size = this->size();
		std::vector<T> vect(size > 0 ? size : 1);
		toVectorPostOrder(root, vect.begin());
		return vect;
	}

	template<class T>
	std::vector<T> BinarySearchTree<T>::toVectorLevelOrder() const
	{
		size_t size = this->size();
		std::vector<T> vect(size > 0 ? size : 1);
		std::vector<T>::iterator vect_iter = vect.begin();
		std::vector<BinarySearchTree<T>::Node *> accumulator(size > 0 ? size : 1);
		if (root != nullptr) {
			*accumulator.begin() = root;
			toVectorLevelOrder(accumulator.begin(), accumulator.begin(), accumulator.end());
			for (auto it = accumulator.begin(); it != accumulator.end(); ++it)
			{
				*vect_iter++ = (*it)->value;
			}
		}
		return vect;
	}

	template<class T>
	std::string BinarySearchTree<T>::toString() const
	{
		std::vector<T> vect(toVectorInOrder());
		std::stringstream ss;
		ss << '[';
		if (vect.size() > 0)
			ss << (vect[0]);
		for (auto it = vect.begin() + 1; it != vect.end(); ++it)
		{
			ss << ", ";
			ss << (*it);
		}
		ss << ']';
		return ss.str();
	}

	template<typename U>
	std::ostream & operator<<(std::ostream & out, const BinarySearchTree<U>& bst)
	{
		out << bst.toString();
		return out;
	}
}
#endif