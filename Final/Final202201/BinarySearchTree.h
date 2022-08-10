//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 16-4.

/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
//#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
#include <queue>
#include <stack>

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
   BinaryNode<ItemType>* rootPtr;
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   // Recursively finds where the given node should be placed and
   // inserts it in a leaf at that point.
   BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr,
                                       BinaryNode<ItemType>* newNode);
   
   // Removes the leftmost node in the left subtree of the node
   // pointed to by nodePtr.
   // Sets inorderSuccessor to the value in this node.
   // Returns a pointer to the revised subtree.
   
   void inorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const;
   void levelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const;
   bool isParentNode(BinaryNode<ItemType>* subTreePtr, const ItemType target);
   int countParentNodes(BinaryNode<ItemType>* subTreePtr);
   ItemType inorderSuccessor(BinaryNode<ItemType>* subTreePtr, const ItemType target);
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   BinarySearchTree();
   BinarySearchTree(const ItemType& rootItem);
   BinarySearchTree(const BinarySearchTree<ItemType>& tree);
   virtual ~BinarySearchTree();
   
   //------------------------------------------------------------
   // Public Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const;
   //int getHeight() const;
   //int getNumberOfNodes() const;
   //ItemType getRootData() const throw(PrecondViolatedExcep);
   //void setRootData(const ItemType& newData) const  throw(PrecondViolatedExcep);
   bool add(const ItemType& newEntry);
   void clear();
//   ItemType getEntry(const ItemType& anEntry) const;
//   throw(NotFoundException);
//   bool contains(const ItemType& anEntry) const;
   bool isParent(const ItemType target);
   int countParents();
   ItemType find(const ItemType target);
   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------
   //void preorderTraverse(void visit(ItemType&)) const;
   void inorderTraverse(void visit(BinaryNode<ItemType>&)) const;
   //void postorderTraverse(void visit(ItemType&)) const;
   void levelorderTraverse(void visit(BinaryNode<ItemType>&)) const;
   
   //------------------------------------------------------------
   // Overloaded Operator Section.
   //------------------------------------------------------------
   BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);   
}; // end BinarySearchTree

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr)
{
}  // end default constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
{
   rootPtr = new BinaryNode<ItemType>( rootItem, nullptr, nullptr );
}  // end constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& treePtr)
{
   rootPtr = copyTree( treePtr.rootPtr );
}  // end copy constructor

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
	this->destroyTree( rootPtr );
}  // end destructor

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const
{
	if ( subtreePtr != nullptr )
   {
		inorder( visit, subtreePtr->getLeftChildPtr() );
		visit( *subtreePtr );
		inorder( visit, subtreePtr->getRightChildPtr() );
   }  // end if
}  // end inorder

template<class ItemType>
void BinarySearchTree<ItemType>::levelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const
{
	// the data structures that may be useful
	queue<BinaryNode<ItemType>*> nodeQueue;
	stack<BinaryNode<ItemType>*> nodeStack;
	BinaryNode<ItemType> *tmpPtr = subtreePtr;

	
	// add your code here


}  // end levelorder


//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////


template<class ItemType>
void BinarySearchTree<ItemType>:: clear(){
	this->destroyTree( rootPtr );
	rootPtr = nullptr;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
   return ( rootPtr == nullptr ) ;
} 

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
   BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
   rootPtr = insertInorder(rootPtr, newNodePtr);
   return true;
}  // end add

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr,
                                                            BinaryNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;

	if ( subTreePtr->getItem() == newNodePtr->getItem() ) {
		

		// add some code here


		return subTreePtr;
	}

	BinaryNode<ItemType>* tempPtr;

	if ( subTreePtr->getItem() > newNodePtr->getItem() ) {
		tempPtr = insertInorder( subTreePtr->getLeftChildPtr(), newNodePtr );
		subTreePtr->setLeftChildPtr( tempPtr );
	}
	else {
		tempPtr = insertInorder( subTreePtr->getRightChildPtr(), newNodePtr );
		subTreePtr->setRightChildPtr( tempPtr );
	}
	
	return subTreePtr;
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(BinaryNode<ItemType>&)) const
{
   inorder(visit, rootPtr);
}  

template<class ItemType>
void BinarySearchTree<ItemType>::levelorderTraverse(void visit(BinaryNode<ItemType>&)) const
{
   levelorder(visit, rootPtr);
}  

template<class ItemType>
int BinarySearchTree<ItemType>::countParents()
{
	return countParentNodes( rootPtr );
}

template<class ItemType>
int BinarySearchTree<ItemType>::countParentNodes(BinaryNode<ItemType>* subtreePtr)
{


	// add your code here


	return 0;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isParent(const ItemType target)
{
	return (isParentNode(rootPtr, target));
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isParentNode(BinaryNode<ItemType>* subtreePtr, const ItemType target)
{


	// add your code here


	return false;
} // end findValue

template<class ItemType>
ItemType BinarySearchTree<ItemType>::find(const ItemType target)
{
	return inorderSuccessor(rootPtr, target);
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::inorderSuccessor(BinaryNode<ItemType>* subtreePtr, const ItemType target)
{


	// add your code here


	return target;
} // end findImmediateSuccessor
#endif
