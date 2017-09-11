#include <iostream>
#include "BinarySearchTree.h"
#include <vector>

using DataStructures::BinarySearchTree;

#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>

template<class T>
void printVector(std::vector<T> vect)
{
	for (auto i = vect.begin(); i != vect.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::cout << "\n....BinarySearchTree<int> test" << std::endl;
	BinarySearchTree<int> bst;

	std::cout << "\n.....test add" << std::endl;
	int i = 8;
	bst.insert(i);
	bst.insert(3);
	std::cout << (bst.insert(6) == 1) << std::endl;
	bst.insert(31);
	bst.insert(1);
	bst.insert(7);
	std::cout << (bst.insert(2) == 1) << std::endl;
	std::cout << (bst.insert(6) == 0) << std::endl;
	bst.insert(0);
	bst.insert(42);
	bst.insert(34);
	bst.insert(32);
	bst.insert(1);
	bst.insert(45);
	bst.insert(43);
	bst.insert(49);
	std::cout << (bst.insert(2) == 0) << std::endl;
	bst.insert(4);
	
	std::cout << "\n.....test size" << std::endl;
	std::cout << bst.size() << std::endl;

	std::cout << "\n.....test getRoot" << std::endl;
	std::cout << *bst.getRoot() << std::endl;

	std::cout << "\n.....test contains" << std::endl;
	std::cout << (bst.contains(2) == 1) << std::endl;
	std::cout << (bst.contains(7) == 1) << std::endl;
	std::cout << (bst.contains(42) == 1) << std::endl;
	std::cout << (bst.contains(8) == 1) << std::endl;
	std::cout << (bst.contains(100) == 0) << std::endl;

	std::cout << "\n.....test in-order" << std::endl;
	printVector(bst.toVectorInOrder());

	std::cout << "\n.....test pre-order" << std::endl;
	printVector(bst.toVectorPreOrder());

	std::cout << "\n.....test post-order" << std::endl;
	printVector(bst.toVectorPostOrder());

	std::cout << "\n.....test level-order" << std::endl;
	printVector(bst.toVectorLevelOrder());

	std::cout << "\n.....test remove" << std::endl;
	std::cout << ".....level-order" << std::endl;
	printVector(bst.toVectorLevelOrder());
	std::cout << (bst.remove(2) == 1) << std::endl;
	std::cout << (bst.remove(2) == 0) << std::endl;
	printVector(bst.toVectorLevelOrder());
	std::cout << (bst.remove(31) == 1) << std::endl;
	printVector(bst.toVectorLevelOrder());
	std::cout << (bst.remove(34) == 1) << std::endl;
	printVector(bst.toVectorLevelOrder());
	std::cout << (bst.remove(3) == 1) << std::endl;
	printVector(bst.toVectorLevelOrder());
	std::cout << (bst.remove(8) == 1) << std::endl;
	printVector(bst.toVectorLevelOrder());

	std::cout << "\n.....test operator <<" << std::endl;
	std::cout << bst << std::endl;

	std::cout << "\n....empty tree test" << std::endl;
	BinarySearchTree<int> empty;
	std::cout << empty.size() << std::endl;
	std::cout << empty.getRoot() << std::endl;
	std::cout << empty.contains(3) << std::endl;
	printVector(empty.toVectorInOrder());
	printVector(empty.toVectorLevelOrder());
	std::cout << bst.remove(3) << std::endl;

	system("pause");
	return 0;
}