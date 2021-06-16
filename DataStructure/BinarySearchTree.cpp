// Đây là code Binary Search Tree

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
const int oo = 1000000007;

class BST
{
public:
	int val;
	BST* left;
	BST* right;

	// khai báo có val = 0;
	BST();

	// khai báo có val;
	BST(int);

	// Insert Function
	BST* Insert(BST*, int);

	// Inorder traversal
	void Inorder(BST*);

	// Searching a key
	bool Search(BST*, int);

	// Delete value
	BST* Delete(BST*, int);
};

BST::BST()
{
	val = 0;
	left = right = nullptr;
}

BST::BST(int value)
{
	val = value;
	left = right = nullptr;
}

BST* BST::Insert(BST* node, int value)
{
	if (node == nullptr)
	{
		return new BST(value);
	}
	if (value > node->val)
	{
		node->right = Insert(node->right, value);
	}
	if (value <= node->val)
	{
		node->left = Insert(node->left, value);
	}
	return node;
}

bool BST::Search(BST* root, int value)
{
	if (!root) return 0;
	if (value > root->val)
	{
		return Search(root->right, value);
	}
	else if (value < root->val)return Search(root->left, value);
	return 1;
}

void BST::Inorder(BST* root)
{
	if (!root)return;
	Inorder(root->left);
	cout << root->val << " ";
	Inorder(root->right);
}

BST* BST::Delete(BST* root, int value)
{
	if (root == nullptr)return root;
	if (root->val == value)
	{
		BST* l = root->left;
		BST* r = root->right;
		if (l == nullptr && r == nullptr)
		{
			free(root);
			return NULL;
		}
		else if (l == nullptr)
		{
			free(root);
			return r;
		}
		else if (r == nullptr)
		{
			free(root);
			return l;
		}
		else
		{
			free(root);
			BST* point = l;
			while (point->right != nullptr)
			{
				point = point->right;
			}
			point->right = r;
			return l;
		}
	}
	else if (value > root->val)
	{
		root->right = Delete(root->right, value);
	}
	else root->left = Delete(root->left, value);
	return root;
}

int main()
{
	BST b;
	BST* root = nullptr;
	root = b.Insert(root, 50);
	b.Insert(root, 30);
	b.Insert(root, 20);
	b.Insert(root, 40);
	b.Insert(root, 70);
	b.Insert(root, 60);
	b.Insert(root, 80);

	cout << "Inorder traversal of the given tree \n";
	b.Inorder(root);

	cout << "\nDelete 60\n";
	root = b.Delete(root, 60);
	cout << "Inorder traversal of the modified tree \n";
	b.Inorder(root);

	cout << "\nDelete 30\n";
	root = b.Delete(root, 30);
	cout << "Inorder traversal of the modified tree \n";
	b.Inorder(root);

	cout << "\nDelete 50\n";
	root = b.Delete(root, 50);
	cout << "Inorder traversal of the modified tree \n";
	b.Inorder(root);

	return 0;
}
