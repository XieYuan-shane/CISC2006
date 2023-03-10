#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

//Implement a BST without height balance property
class BST
{
private:
	struct Node { //node of a BST tree
		int key; //key stored in the node
		Node* left; //link to the left child
		Node* right;  //link to the right child
		Node(int x) //initialize a new node
		{
			key = x;
			left = NULL;
			right = NULL;
		}
	};

public:
	Node* root; //store the root of BST
	BST() { //initialize an empty BST with a null root
		root = NULL;
	}
	int number = 0;
	void insert(int k)
	{
		Node* newNode = new Node(k);
		if (root == NULL)
			root = newNode;
		else {
			Node* temp = root;
			while (true) {
				if (k < temp->key) {
					if (temp->left != NULL) {
						temp = temp->left;
					}
					else {
						temp->left = newNode;
						break;
					}
				}
				else {
					if (temp->right != NULL) {
						temp = temp->right;
					}
					else {
						temp->right = newNode;
						break;
					}
				}
			}
		}
		number++;
	}
	Node* find_parent(Node* node, Node* temp) {
		if (temp == NULL || node == temp) {
			return NULL;
		}
		else if (temp->right == node || temp->left == node) {
			return temp;
		}
		else {
			if (temp->key > node->key && temp->left != NULL)
				return find_parent(node, temp->left);
			else
				return find_parent(node, temp->right);
		}
	}

	Node* find(Node* newnode, int k)
	{
		if (NULL != newnode) {
			if (newnode->key == k) {
				return newnode;
			}
			else if (newnode->key < k) {
				if (newnode->right == NULL)
					return NULL;
				else
					return find(newnode->right, k);
			}
			else {
				if (newnode->left == NULL)
					return NULL;
				else
					return find(newnode->left, k);
			}
		}
		else
		{
			return NULL;
		}
	}

	Node* find(int k)
	{
		return find(root, k);
	}

	Node* deleteNode(Node* root, int k)
	{
		// Base case
		if (find(root, k)){
			Node* temp = find(root, k);
			Node* parent = find_parent(temp, root);
				if (temp->left == NULL && temp->right == NULL) {
					if (parent == NULL) {
						    delete temp;
							root = NULL;
					}
					else {
						if (parent->left == temp) {
							parent->left = NULL;
								delete temp;
							temp = NULL;
						}
						else {
							parent->right = NULL;
							delete temp;
							temp = NULL;
						}
					}
				}
				else if (temp->left == NULL && temp->right != NULL) {
					if (temp == root) {
						root = temp->right;
						delete temp;
					}
					else {
						if (parent->left == temp) {
							parent->left = temp->right;
							delete temp;
							temp = NULL;
						}
						else {
							parent->right = temp->right;
							delete temp;
							temp = NULL;
						}
					}
				}
				else if (temp->left != NULL && temp->right == NULL) {
					if (temp == root) {
						root = temp->left;
						delete temp;
					}
					else {

						if (parent->left == temp) {
							parent->left = temp->left;
							delete temp;
							temp = NULL;
						}
						else {
							parent->right = temp->left;
							delete temp;
							temp = NULL;
						}
					}
				}
				else {
					Node* x = temp->right;
					while (true) {
						if (x->left == NULL)
							break;
						else {
							x = x->left;
						}
					}
					temp->key = x->key;
					Node *px = find_parent(x, root);
					if (x->right != NULL) px->left = x->right;
					else px->left = NULL;
					delete x;
					x = NULL;
				}
			number--;
		}
		else
			cout << "Fail to delete" << endl;
		return root;
	}

	void remove(int k)
	{
		if (find(k))
			root = deleteNode(root, k);
		else
			cout << "Deletion failed: no such element is found!" << endl;
	}

	void remove(Node* p)
	{
		if (p != NULL)
			root = deleteNode(root, p->key);
		else
			cout << "Deletion failed: empty pointer!" << endl;
	}

	int size()
	{
		return number;
	}

	bool isEmpty()
	{
		return number == 0;
	}

	void printTree(string prefix, Node* node, bool isRight)
	{
		if (node != NULL) {
			cout << prefix; //print the blank space before the node
			cout << (isRight ? "---" : "|__"); //depend on whether the node is a right child, print different labels
			cout << node->key << endl; // print the value of the node
			// enter the next tree level - left and right branch
			printTree(prefix + (isRight ? "|   " : "    "), node->right, true);
			printTree(prefix + (isRight ? "|   " : "    "), node->left, false);
		}
	}

	void printTree()
	{ //print the tree from the root
		printTree("", root, false);
	}
};

//Implement a AVL tree.
class AVL
{
private:
	struct Node { //node of a BST tree
		int key; //key stored in the node
		Node* left; //link to the left child
		Node* right;  //link to the right child
		int height; //store the height of node
		Node(int x) //initialize a new node
		{
			key = x;
			left = NULL;
			right = NULL;
			height = 0;
		}
	};

public:
	Node* root; //store the root of BST
	int number = 0;
	AVL()
	{ //initialize an empty BST with a null root
		root = NULL;
	}
	//LL型调整函数,执行右旋
	Node* LL_rotate(Node* root) {
		Node* temp;
		temp = root->left;
		root->left = temp->right;
		temp->right = root;
		return temp;
	}
	//RR型调整函数,执行左旋 
	Node* RR_rotate(Node* root) {
		Node* temp;
		temp = root->right;
		root->right = temp->left;
		temp->left = root;
		return temp;
	}
	//LR型调整函数，先左旋转，再右旋转
	Node* LR_rotate(Node* root) {
		Node* temp;
		temp = root->left;
		root->left = RR_rotate(temp);
		return LL_rotate(root);
	}
	//RL型调整函数，先右旋转，再左旋转
	Node* RL_rotate(Node* root) {
		Node* temp;
		temp = root->right;
		root->right = LL_rotate(temp);
		return RR_rotate(root);
	}
	//树高
	int height(Node* root)
	{
		if (root == NULL)
			return 0;
		int max;
		int left = height(root->left);
		int right = height(root->right);
		if (left >= right)
			max = left;
		else
			max = right;
		return max + 1;
	}
	//求叶子节点个数
	int  GetSumOfLeafNode(Node* root)
	{
		if (root == NULL)
			return 0;

		if (root->left == NULL && root->right == NULL)
			return 1;
		else
		{
			return GetSumOfLeafNode(root->left)
				+ GetSumOfLeafNode(root->right);
		}
	}
	//平衡因子，即当前节点左右子树的差
	int diff(Node* root)
	{
		return height(root->left) - height(root->right);
	}
	//平衡操作
	Node* Balance(Node* root)
	{
		int balanceFactor = diff(root);//平衡因子（左右子树高度差）
		if (balanceFactor > 1)//左子树高于右子树
		{
			if (diff(root->left) > 0)
				//LL的情况 
				root = LL_rotate(root);
			else
				//LR的情况 
				root = LR_rotate(root);
		}
		else if (balanceFactor < -1)//右子树高于左子树
		{
			if (diff(root->right) > 0)
				//RL的情况 
				root = RL_rotate(root);
			else
				//RR的情况 
				root = RR_rotate(root);
		}
		return root;
	}
	//平衡二叉树最大值 
	int tree_max(Node* node) {
		int key;
		key = node->key;
		if (node->right != NULL)
			return tree_max(node->right);
		else
			return key;

	}
	//平衡二叉树最小值 
	int tree_min(Node* node) {
		int key;
		key = node->key;
		if (node->left != NULL)
			return tree_min(node->left);
		else
			return key;
	}
	Node* insert(Node* node, int k)
	{
		Node* newnode = new Node(k);
		if (node == NULL) {
			node = newnode;
		}
		else if (k < node->key) {
			node->left = insert(node->left, k);
			node = Balance(node);
		}
		else if (k > node->key) {
			node->right = insert(node->right, k);
			node = Balance(node);
		}
		return node;
	}
	void insert(int k)
	{
		root = insert(root, k);
		number++;
	}

	Node* find(Node* node, int k)
	{
		if (node) {
			if (node->key == k)
				return node;
			else if (node->key < k)
				return find(node->right, k);
			else
				return find(node->left, k);
		}
		else {
			cout << "Searching failed: no element is found!" << endl;
			return NULL;
		}
	}

	Node* find(int k)
	{
		return find(root, k);
	}

	Node* find_parent(Node* node,Node * temp) {
		if (temp->right == node || temp->left == node) {
			return temp;
		}
		else {
			if (temp->key > node->key)
				return find_parent(node, temp->left);
			else
				return find_parent(node, temp->right);
		}
	}
	Node* deleteNode(Node* node, int k)
	{
		if (NULL == node)
			return NULL;
		else if (!(find(node, k))) {
			cout << "fail to remove." << endl;
			return NULL;
		}
		else {
			if (k == node->key)//根节点
			{
				if (node->left != NULL && node->right != NULL)//左右子树都非空
				{
					if (diff(node) > 0)//左子树更高，在左边删除
					{
						node->key = tree_max(node->left);//以左子树的最大值替换当前值
						node->left = deleteNode(node->left, node->key);//删除左子树中已经替换上去的节点
					}
					else//右子树更高，在右边删除
					{
						node->key = tree_min(node->right);//以右子树的最小值替换当前值
						node->right = deleteNode(node->right, node->key);//删除右子树中已经替换上去的节点
					}
				}
				else//有一个孩子、叶子节点的情况合并
				{
					Node* tmp = node;
					node = (node->left) ? (node->left) : (node->right);
					delete tmp;
					tmp = NULL;
				}
			}
			//往左边删 
			else if (k < node->key)
			{
				node->left =deleteNode(node->left, k);
				//不满足平衡条件
				if (diff(node) < -1)
				{
					if (diff(node->right) > 0)
					{
						node = RL_rotate(node);
					}
					else
					{
						node = RR_rotate(node);
					}
				}
			}
			//往右边删 
			else
			{
				node->right = deleteNode(node->right, k);
				//不满足平衡 条件 
				if (diff(node) > 1)
				{
					if (diff(node->left) < 0)
					{
						node = LR_rotate(node);
					}
					else
					{
						node = LL_rotate(node);
					}
				}
			}
			return node;
		}
	}

	void remove(int k)
	{
		if (find(k) != NULL) {
			root = deleteNode(root, k);
			number--;
		}

		else
			cout << "Deletion failed: no such element is found!" << endl;
	}

	void remove(Node* p)
	{
		if (p != NULL)
			root = deleteNode(root, p->key);
		else
			cout << "Deletion failed: empty pointer!" << endl;
	}

	int size()
	{
		return number;
	}

	bool isEmpty()
	{
		return number == 0;
	}

	void printTree(string prefix, Node* node, bool isRight)
	{
		if (node != NULL) {
			cout << prefix;
			cout << (isRight ? "---" : "|__");
			// print the value of the node
			cout << node->key << endl;
			// enter the next tree level - left and right branch
			printTree(prefix + (isRight ? "|   " : "    "), node->right, true);
			printTree(prefix + (isRight ? "|   " : "    "), node->left, false);
		}
	}

	void printTree()
	{
		printTree("", root, false);
	}
};

int main() {
	BST bstree; //build an empty BST 
	AVL avltree; //build an empty AVL tree

	cout << "The AVL tree is empty: " << boolalpha << avltree.isEmpty() << endl; //check if the three is empty
	cout << "The BST tree is empty: " << boolalpha << bstree.isEmpty() << endl; //check if the three is empty

	int a; //insert elements in A to the BST and the AVL tree
	ifstream arrA;
	arrA.open("testA.txt");
	if (!arrA) {
		cout << "Unable to open file!" << endl;
	}
	while (arrA >> a) {
		bstree.insert(a);
		avltree.insert(a);
	}

	cout << "The insertions of elements are done!" << endl;

	cout << "The BST is printed as follows:" << endl; //print BST tree
	bstree.printTree();
	cout << "The AVL tree is printed as follows:" << endl; //print AVL tree
	avltree.printTree();
	//The constructed AVL tree would be
	//	|__15
	//		---30
	//		|   ---40
	//		|   |   ---81
	//		|   |__25
	//		|__6
	//		    ---8
	//		    |	---12
	//		    |__2
	//				---4

	int b; //remove all the elements in array B from the BST and the AVL tree
	ifstream arrB;
	arrB.open("E:\\testB.txt");
	if (!arrB) {
		cout << "Unable to open file!" << endl;
	}
	while (arrB >> b) {
		bstree.remove(b);
		avltree.remove(b);
	}
	cout << "The removals of elements are done!" << endl;
	cout << "The BST is printed as follows:" << endl; //print BST after removals
	bstree.printTree();
	cout << "The AVL tree is printed as follows:" << endl; //print AVL tree after removals
	avltree.printTree();

	cout << "Next we find the element with key=6 in both trees, and remove it:" << endl;
	bstree.remove(bstree.find(6)); //removal of element by pointer
	avltree.remove(6);	//removal of element by key

	cout << "The BST is printed as follows:" << endl; //print BST after the removal
	bstree.printTree();
	cout << "The AVL tree is printed as follows:" << endl; //print AVL tree after the removal
	avltree.printTree();

	cout << "The size of the BST is " << bstree.size() << endl;
	cout << "The size of the AVL tree is " << avltree.size() << endl;
	cout << "The BST tree is empty: " << boolalpha << bstree.isEmpty() << endl;
	cout << "The AVL tree is empty: " << boolalpha << avltree.isEmpty() << endl;
	return 0;
};