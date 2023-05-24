// BINARY SEARCH TREE FILE

#include <iostream>
#include <algorithm>

using namespace std;

template<typename TKey, typename TValue>
class binarysearchtree
{
private:
	// initialize bst as linked list
	struct Node
	{
		TKey Key;
		TValue Value;
		Node* Left;
		Node* Right;
	};
	
	Node* Root;
	int Size;
	
	
	// helper height function computes height of bst recursively
	int _height (Node* curNode)
	{
		if (curNode == nullptr) 
			return -1;
		else
		{
			int leftHeight = _height(curNode->Left);
			int rightHeight = _height(curNode->Right);
			
			return 1 + max(leftHeight, rightHeight);
		}
	}
	
	// helper order function tranverses bst in order recursively
	void _inorder(Node* curNode)
	{
		if (curNode == nullptr)
			return;
		else
		{
			_inorder(curNode->Left);
			cout << "Key: " << curNode->Key << " ";
			cout << "Value: " << curNode->Value << endl;
			_inorder(curNode->Right);
		}
	}
	
	// helper delete function for deleting bst
	void _delete(Node* curNode)
	{
		if (curNode == nullptr)
			return;
		
		_delete(curNode->Left);
		_delete(curNode->Right);
		
		delete curNode;
	}
	
	// helper order copy function to create bst copy
	void _inordercopy(Node* curNode)
	{
		if (curNode == nullptr)
			return;
		
		insert(curNode->Key, curNode->Value);
		_inordercopy(curNode->Left);
		_inordercopy(curNode->Right);
	}


public:
	// default constructor, creates empty tree
	binarysearchtree()
	{
		Root = nullptr;
		Size = 0;
	}
	
	// copy constructor, create copy of existing bst
	binarysearchtree (binarysearchtree& other)
	{
		Root = nullptr;
		_inordercopy(other.Root);
		
		Size = other.Size;
	}
	
	// destructor, free memory when tree is destroyed
	virtual ~binarysearchtree()
	{
		_delete(Root);
	}
	
	// size function, returns size/number of nodes in bst
	int size()
	{
		return Size;
	}
	
	// height function, computes height of bst (empty = -1)
	int height()
	{
		return _height(Root);
	}
	
	// search function, searches bst for given key
	TValue* search(TKey key)
	{
		Node* curNode = Root;
		
		while (curNode != nullptr)
		{
			if (key == curNode->Key)
				return &(curNode->Value);
				
			// search if key < cur (left) or key > cur (right)
			if (key < curNode->Key)
				curNode = curNode->Left;
			else
				curNode = curNode->Right;
		}
		
		return nullptr; // null if key not found (key never = cur key)
	}
	
	// insert function, insert value in appropriate spot in bst
	void insert(TKey key, TValue value)
	{
		Node* prevNode = nullptr;
		Node* curNode = Root;
	
		while (curNode != nullptr)
		{
			if (key == curNode->Key) // no insert if already in tree
				return;
			
			// search if key < cur (left) or key > cur (right)
			if (key < curNode->Key)
			{
				prevNode = curNode;
				curNode = curNode->Left;
			}
			else
			{
				prevNode = curNode;
				curNode = curNode->Right;
			}
		}
		
		// declare new node to be inserted
		Node* newNode = new Node();
		newNode->Key = key;
		newNode->Value = value;
		newNode->Left = nullptr;
		newNode->Right = nullptr;
		
		// insert new node where appropriate
		if (prevNode == nullptr)
			Root = newNode;
		else if (key < prevNode->Key)
			prevNode->Left = newNode;
		else
			prevNode->Right = newNode;
			
		Size++;
	}
	
	// inorder function, prints out bst values in order
	void inorder()
	{
		cout << "Inorder: " << endl;
		
		_inorder(Root);
		
		cout << endl;
	}
	
	// clear function, clear/free bst memory
	void clear()
	{
		_delete(Root);
		
		// re-initialize root pointer and size to default
		Root = nullptr;
		Size = 0;
	}
};