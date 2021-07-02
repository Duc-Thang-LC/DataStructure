// This code is an example of implement of B Plus 
// Include Isertion, Finding and Visualization of B Plus Tree

#include<iostream>
#include <time.h>
#include<map>

using namespace std;

class Node
{
public:

	int current_key;

	int min_child;

	int max_child;

	Node* right, * fa, * left;

	int height;

	int* key;

	Node** child;

	bool leaf;

	Node();

	Node(int Min, bool m_leaf)
	{
		min_child = Min;
		max_child = Min * 2;
		child = new Node * [max_child + 10];
		key = new int[max_child + 10];
		leaf = m_leaf;
		right = NULL;
		left = NULL;
		fa = NULL;
	}

	~Node()
	{
		if (key)delete key;
		for (int i = 0; i < max_child + 10; ++i)
		{
			if (child[i])delete child[i];
		}
		if (child)delete child;
		if (right)delete right;
		if (fa)delete fa;
	}

	Node* Find(int val)
	{
		if (leaf == 1)return this;
		int i = 0;
		while (i < current_key)
		{
			if (key[i] > val)break;
			i++;
		}
		return child[i]->Find(val);
	}

	void Vi(Node* root, int& kc, int& h, map<int, int>* mp)
	{
		if (this == root)height = 1;
		else height = fa->height + 2;

		h = max(h, height);

		if (leaf == 1)
		{
			for (int i = 0; i < current_key; ++i)
			{
				if (key[i] >= 10)
				{
					mp[height][kc] = key[i] / 10 + 1;
					++kc;
					mp[height][kc] = key[i] % 10 + 1;
				}
				else
				{
					mp[height][kc] = key[i] + 1;
				}

				kc += 1;
			}
			return;
		}

		for (int i = 0; i <= current_key; ++i)
		{
			child[i]->Vi(root, kc, h, mp);
			if (i < current_key)
			{
				if (key[i] >= 10)
				{
					mp[height][kc] = key[i] / 10 + 1;
					++kc;
					mp[height][kc] = key[i] % 10 + 1;
				}
				else
				{
					mp[height][kc] = key[i] + 1;
				}

				kc += 1;
			}
		}
	}

	void Insert(Node*& root, int val)
	{
		//adding new key to this 
		int point = 0;
		while (point < current_key)
		{
			if (key[point] > val)break;
			point++;
		}
		current_key++;
		for (int i = current_key - 1; i >= point + 1; --i)
		{
			key[i] = key[i - 1];
		}
		key[point] = val;

		//if this has more key than max
		if (current_key > max_child - 1)
		{
			Divine(root);
		}
	}

	void Divine(Node*& root)
	{
		Node* new_fa;
		if (this == root)new_fa = new Node(min_child, 0);
		else new_fa = fa;
		Node* child_left = new Node(min_child, leaf);
		Node* child_right = new Node(min_child, leaf);

		//Case 1: leaf = 1
		if (leaf == 1)
		{
			int val = key[min_child];

			//add new members to left child
			for (int i = 0; i < min_child; ++i)
			{
				child_left->current_key++;
				child_left->key[i] = key[i];
			}

			//add new members to right child
			for (int i = min_child; i < current_key; ++i)
			{
				child_right->current_key++;
				child_right->key[i - min_child] = key[i];
			}

			//add new node to fa
			int point = 0;
			while (point < new_fa->current_key)
			{
				if (new_fa->key[point] > val)
				{
					break;
				}
				point++;
			}
			new_fa->current_key++;
			for (int i = new_fa->current_key - 1; i >= point + 1; --i)
			{
				new_fa->key[i] = new_fa->key[i - 1];
			}
			new_fa->key[point] = val;
			for (int i = new_fa->current_key; i >= point; --i)
			{
				new_fa->child[i] = new_fa->child[i - 1];
			}
			new_fa->child[point] = child_left;
			new_fa->child[point + 1] = child_right;

			//finish relationship fa, left and right child
			child_left->fa = new_fa;
			child_right->fa = new_fa;
			child_left->right = child_right;
			child_right->right = right;
			child_right->left = child_left;
			child_left->left = left;
			if (left)left->right = child_left;
			if (right)right->left = child_right;
		}

		//Case 2: leaf = 0
		else
		{
			int val = key[min_child];

			//add new members to left child
			for (int i = 0; i < min_child; ++i)
			{
				child_left->current_key++;
				child_left->key[i] = key[i];
				child_left->child[i] = child[i];
				child_left->child[i]->fa = child_left;
			}
			child_left->child[min_child] = child[min_child];
			child_left->child[min_child]->fa = child_left;

			//add new members to right child
			for (int i = min_child + 1; i < current_key; ++i)
			{
				child_right->current_key++;
				child_right->key[i - min_child - 1] = key[i];
				child_right->child[i - min_child - 1] = child[i];
				child_right->child[i - min_child - 1]->fa = child_right;
			}
			child_right->child[current_key - min_child - 1] = child[current_key];
			child_right->child[current_key - min_child - 1]->fa = child_right;

			//add new members to new fa
			int point = 0;
			while (point < new_fa->current_key)
			{
				if (new_fa->key[point] > val)
				{
					break;
				}
				point++;
			}
			new_fa->current_key++;
			for (int i = new_fa->current_key - 1; i >= point + 1; --i)
			{
				new_fa->key[i] = new_fa->key[i - 1];
			}
			new_fa->key[point] = val;
			for (int i = new_fa->current_key; i >= point; --i)
			{
				new_fa->child[i] = new_fa->child[i - 1];
			}
			new_fa->child[point] = child_left;
			new_fa->child[point + 1] = child_right;

			//finish relationship fa, left and right child
			child_left->fa = new_fa;
			child_right->fa = new_fa;
		}

		if (root == this)root = new_fa;
		if (new_fa->current_key > max_child - 1)
		{
			new_fa->Divine(root);
		}
	}

	int FindSuccessor()
	{
		if (leaf == 1)return key[0];
		return child[0]->FindSuccessor();
	}

	void DeleteDouble(int val)
	{
		if (leaf == 1)return;
		int point = 0;
		while (point < current_key)
		{
			if (key[point] == val)
			{
				key[point] = child[point + 1]->FindSuccessor();
				return;
			}
			if (key[point] > val)
			{
				child[point]->DeleteDouble(val);
				return;
			}
			point++;
		}
		return child[point]->DeleteDouble(val);
	}

	void Delete(int val, Node*& root)
	{
		Node* x = Find(val);

		if (x != this)
		{
			x->Delete(val, root);
			return;
		}

		//Delete val from node x
		int point = 0;
		for (int i = 0; i < current_key; ++i)
		{
			if (key[i] == val)
			{
				point = i;
				break;
			}
		}
		current_key--;
		for (int i = point; i < current_key; ++i)
		{
			key[i] = key[i + 1];
		}

		//handling case current_key < min key
		if (current_key < min_child - 1)
		{
			Handling(root);
		}
	}

	void Handling(Node*& root)
	{
		//if this is root
		if (this == root)
		{
			if (current_key == 0)
			{
				if (leaf == 0) root = child[0];
				else root = NULL;
			}
			return;
		}

		//if this is not root 
		int point = 0; // which fa->child[point] = this
		while (fa->child[point] != this)
		{
			point++;
		}

		//borrow from left sibling
		if (point > 0)
		{
			if (fa->child[point - 1]->current_key > min_child - 1)
			{
				// case leaf = 1
				if (leaf == 1)
				{
					fa->child[point - 1]->current_key--;
					int lcurrent_key = fa->child[point - 1]->current_key;
					int val = fa->child[point - 1]->key[lcurrent_key];
					current_key++;

					for (int i = current_key - 1; i >= 1; --i)
					{
						key[i] = key[i - 1];
					}
					key[0] = val;

					fa->key[point - 1] = val;
				}

				//case leaf = 0
				else
				{
					fa->child[point - 1]->current_key--;
					int lcurrent_key = fa->child[point - 1]->current_key;
					int val = fa->child[point - 1]->key[lcurrent_key];

					current_key++;
					for (int i = current_key - 1; i >= 1; --i)
					{
						key[i] = key[i - 1];
					}
					for (int i = current_key; i >= 1; --i)
					{
						child[i] = child[i - 1];
					}
					key[0] = fa->key[point - 1];
					child[0] = fa->child[point - 1]->child[lcurrent_key + 1];
					child[0]->fa = this;

					fa->key[point - 1] = val;
				}

				return;
			}
		}

		//borrow from right sibling 
		if (point < fa->current_key)
		{
			if (fa->child[point + 1]->current_key > min_child - 1)
			{
				//case leaf = 1
				if (leaf == 1)
				{
					fa->child[point + 1]->current_key--;
					int rcurrent_key = fa->child[point + 1]->current_key;
					int val = fa->child[point + 1]->key[0];
					for (int i = 0; i < rcurrent_key; ++i)
					{
						fa->child[point + 1]->key[i] = fa->child[point + 1]->key[i + 1];
					}

					current_key++;
					key[current_key - 1] = val;

					fa->key[point] = fa->child[point + 1]->key[0];
				}

				//case leaf = 0
				else
				{
					fa->child[point + 1]->current_key--;
					int rcurrent_key = fa->child[point + 1]->current_key;
					int val = fa->child[point + 1]->key[0];
					Node* rnode = fa->child[point + 1]->child[0];
					for (int i = 0; i < rcurrent_key; ++i)
					{
						fa->child[point + 1]->key[i] = fa->child[point + 1]->key[i + 1];
					}
					for (int i = 0; i <= rcurrent_key; ++i)
					{
						fa->child[point + 1]->child[i] = fa->child[point + 1]->child[i + 1];
					}

					current_key++;
					key[current_key - 1] = fa->key[point];
					child[current_key] = rnode;
					child[current_key]->fa = this;

					fa->key[point] = val;
				}

				return;
			}
		}

		//merge to left sibling
		if (point > 0)
		{
			//case leaf = 1
			if (leaf == 1)
			{
				Node* new_child = new Node(min_child, leaf);
				Node* rright = right;
				Node* lleft = fa->child[point - 1]->left;

				//add members to newchild
				int lcurrent_key = fa->child[point - 1]->current_key;
				for (int i = 0; i < lcurrent_key; ++i)
				{
					new_child->key[i] = fa->child[point - 1]->key[i];
					new_child->current_key++;
				}
				for (int i = 0; i < current_key; ++i)
				{
					new_child->key[i + lcurrent_key] = key[i];
					new_child->current_key++;
				}

				//add newchild to fa
				fa->current_key--;
				for (int i = point - 1; i < fa->current_key; ++i)
				{
					fa->key[i] = fa->key[i + 1];
				}
				for (int i = point; i <= fa->current_key; ++i)
				{
					fa->child[i] = fa->child[i + 1];
				}
				fa->child[point - 1] = new_child;
				fa->child[point - 1]->fa = fa;
				fa->child[point - 1]->right = rright;
				fa->child[point - 1]->left = lleft;
				if (rright)rright->left = fa->child[point - 1];
				if (lleft)lleft->right = fa->child[point - 1];
			}

			//case leaf = 0
			else
			{
				Node* new_child = new Node(min_child, leaf);

				// add new members to new child
				int lcurrent_key = fa->child[point - 1]->current_key;
				for (int i = 0; i <= lcurrent_key; ++i)
				{
					new_child->child[i] = fa->child[point - 1]->child[i];
					new_child->child[i]->fa = new_child;
				}
				for (int i = 0; i <= current_key; ++i)
				{
					new_child->child[i + lcurrent_key + 1] = child[i];
					new_child->child[i + lcurrent_key + 1]->fa = new_child;
				}
				for (int i = 0; i < lcurrent_key; ++i)
				{
					new_child->key[i] = fa->child[point - 1]->key[i];
					new_child->current_key++;
				}
				new_child->key[lcurrent_key] = fa->key[point - 1];
				new_child->current_key++;
				for (int i = 0; i < current_key; ++i)
				{
					new_child->key[i + lcurrent_key + 1] = key[i];
					new_child->current_key++;
				}

				//add newchild to fa
				fa->current_key--;
				for (int i = point - 1; i < fa->current_key; ++i)
				{
					fa->key[i] = fa->key[i + 1];
				}
				for (int i = point; i <= fa->current_key; ++i)
				{
					fa->child[i] = fa->child[i + 1];
				}
				fa->child[point - 1] = new_child;
				fa->child[point - 1]->fa = fa;
			}
		}

		//merge to right sibling 
		else
		{
			//case leaf = 1
			if (leaf == 1)
			{
				Node* new_child = new Node(min_child, leaf);
				Node* rright = fa->child[point + 1]->right;
				Node* lleft = left;

				//add new members to new_child
				int rcurrent_key = fa->child[point + 1]->current_key;
				for (int i = 0; i < current_key; ++i)
				{
					new_child->key[i] = key[i];
					new_child->current_key++;
				}
				for (int i = 0; i < rcurrent_key; ++i)
				{
					new_child->key[current_key + i] = fa->child[point + 1]->key[i];
					new_child->current_key++;
				}

				//add new child to fa
				fa->current_key--;
				for (int i = point; i < fa->current_key; ++i)
				{
					fa->key[i] = fa->key[i + 1];
				}
				for (int i = point + 1; i <= fa->current_key; ++i)
				{
					fa->child[i] = fa->child[i + 1];
				}
				fa->child[point] = new_child;
				fa->child[point]->fa = fa;
				fa->child[point]->right = rright;
				fa->child[point]->left = lleft;
				if (rright)rright->left = fa->child[point];
				if (lleft)lleft->right = fa->child[point];
			}

			//case leaf = 0
			else
			{
				Node* new_child = new Node(min_child, leaf);

				//add new members to new child
				int rcurrent_key = fa->child[point + 1]->current_key;
				for (int i = 0; i <= current_key; ++i)
				{
					new_child->child[i] = child[i];
					new_child->child[i]->fa = new_child;
				}
				for (int i = 0; i <= rcurrent_key; ++i)
				{
					new_child->child[i + current_key + 1] = fa->child[point + 1]->child[i];
					new_child->child[i + current_key + 1]->fa = new_child;
				}
				for (int i = 0; i < current_key; ++i)
				{
					new_child->key[i] = key[i];
					new_child->current_key++;
				}
				new_child->key[current_key] = fa->key[point];
				new_child->current_key++;
				for (int i = 0; i < rcurrent_key; ++i)
				{
					new_child->key[i + current_key + 1] = fa->child[point + 1]->key[i];
					new_child->current_key++;
				}

				//add new child to fa
				fa->current_key--;
				for (int i = point; i < fa->current_key; ++i)
				{
					fa->key[i] = fa->key[i + 1];
				}
				for (int i = point + 1; i <= fa->current_key; ++i)
				{
					fa->child[i] = fa->child[i + 1];
				}
				fa->child[point] = new_child;
				fa->child[point]->fa = fa;
			}
		}

		if (fa->current_key < min_child - 1)
		{
			fa->Handling(root);
		}

		return;
	}
};

class BPlusTree
{
public:

	Node* root;

	int min_child;

	BPlusTree(int Min)
	{
		min_child = Min;
		root = NULL;
	}

	void Insert(int val)
	{
		//If there are no member in the root
		if (root == NULL)
		{
			root = new Node(min_child, 1);
			root->key[0] = val;
			root->current_key++;
			return;
		}

		//Else 
		//Step 1: Find the leaf
		Node* x = root->Find(val);
		//Step 2: Adding new key to that node
		x->Insert(root, val);
	}

	void Print()
	{
		Node* x = root;
		while (x->leaf == 0)
		{
			x = x->child[0];
		}

		while (x)
		{
			for (int i = 0; i < x->current_key; ++i)
			{
				cout << x->key[i] << " ";
			}
			x = x->right;
		}
	}

	void Delete(int val)
	{
		root->Delete(val, root);
		//delete the double-value of val
		if (!root || root->current_key == 0)return;
		root->DeleteDouble(val);
	}

	void Vi()
	{
		map<int, int>* mp;
		mp = new map<int, int>[100002];
		int kc = 0;
		int h = 0;
		root->Vi(root, kc, h, mp);
		for (int i = 0; i <= h; ++i)
		{
			for (int j = 0; j <= kc; ++j)
			{
				if (mp[i][j] - 1 == -1)cout << " ";
				else cout << mp[i][j] - 1;
			}
			cout << endl;
		}
	}
};

int main()
{
	int min_size = 2;
	BPlusTree x(min_size);
	int a[30] = { 13,15,11,19,20,3,24,23,7,18,12,9,21,17,14,6,10,8,2,1,4,16,25,5,22 };
	for (int i = 0; i < 25; ++i)
	{
		x.Insert(a[i]);
		cout << "Insert " << a[i] << endl;
		x.Vi();
		cout << endl << endl;
	}

	int b[30] = { 3,25,14,22,4,17,18,6,23,24,11,7,1,10,16,8,9,13,12,5,20,2,15 };

	for (int i = 0; i < 23; ++i)
	{
		x.Delete(b[i]);
		cout << "Delete " << b[i] << endl;
		x.Vi();
		cout << endl;
		cout << x.root->current_key << endl;
		cout << endl;
	}

	return 0;
}