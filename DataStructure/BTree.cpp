// This code is a example of implement BTree
// including Insertion + Searching + Deletion

#include<iostream>

using namespace std;

//class Node in BTree
class Node
{
public:

	int* key; // arr of key
	Node** child; // arr of child
	int current_key; // num of current key
	int min_size; // min of child
	bool leaf; // check if this node is leaf or not
	Node* fa; // father 

	// construction
	Node()
	{
		leaf = 1;
		current_key = 0;
	}

	Node(int min_size1, bool leaf1)
	{
		min_size = min_size1;
		leaf = leaf1;
		child = new Node * [2 * min_size + 10];
		key = new int[2 * min_size + 10];
	}

	// find
	Node* Find(int val)
	{
		for (int i = current_key - 1; i >= 0; --i)
		{
			if (val >= key[i])
			{
				if (val == key[i])return this;
				else
				{
					if (leaf == 0)return child[i + 1]->Find(val);
					else return NULL;
				}
			}
		}

		return child[0]->Find(val);
	}

	void Print()
	{
		if (leaf == 0)
		{
			for (int i = 0; i < current_key; ++i)
			{
				child[i]->Print();
				cout << key[i] << " ";
			}
			child[current_key]->Print();
		}

		else
		{
			for (int i = 0; i < current_key; ++i)
			{
				cout << key[i] << " ";
			}
		}
	}

	//insert new val
	void Insert(int val, Node*& root)
	{
		if (leaf == 0)
		{
			int i = 0;
			while (i < current_key - 1 && key[i] < val)
			{
				i++;
			}

			if (key[i] < val)child[i + 1]->Insert(val, root);
			else child[i]->Insert(val, root);
		}

		if (leaf == 1)
		{
			int i = 0;
			while (i < current_key - 1 && key[i] < val)
			{
				i++;
			}

			if (key[i] < val)
			{
				key[current_key] = val;
			}
			else

			{
				for (int j = current_key; j >= i + 1; --j)
				{
					key[j] = key[j - 1];
				}
				key[i] = val;
			}

			current_key += 1;

			if (current_key > min_size * 2 - 1)
			{
				Rotate(root);
			}
		}
	}

	// rotate to balance tree
	void Rotate(Node*& root)
	{
		if (fa)
		{
			//find middle member
			int i = min_size - 1;
			int val = key[i];

			//add middle member to fa
			int j = 0;
			while (j < fa->current_key && fa->key[j] < val)j++;
			fa->current_key += 1;

			for (int k = fa->current_key - 1; k >= j + 1; --k)
			{
				fa->key[k] = fa->key[k - 1];
				fa->child[k + 1] = fa->child[k];
			}
			fa->key[j] = val;

			//add new node to fa
			fa->child[j + 1] = new Node(min_size, leaf);
			int dem = 0;
			for (int k = i + 1; k < current_key; ++k)
			{
				fa->child[j + 1]->current_key++;
				if (leaf == 0)
				{
					child[k]->fa = fa->child[j + 1];
					fa->child[j + 1]->child[dem] = child[k];
				}
				fa->child[j + 1]->key[dem] = key[k];
				dem++;
			}
			if (leaf == 0)
			{
				child[current_key]->fa = fa->child[j + 1];
				fa->child[j + 1]->child[dem] = child[current_key];
			}
			fa->child[j + 1]->fa = fa;

			//resize current key size
			current_key = min_size - 1;

			// rotate fa
			if (fa->current_key > min_size * 2 - 1)fa->Rotate(root);
		}

		else
		{
			//find middle member
			int i = min_size - 1;
			int val = key[i];

			//create new fa and add current node
			fa = new Node(min_size, 0);
			fa->current_key = 1;
			fa->key[0] = val;
			fa->child[0] = this;
			this->fa = fa;

			//add new node to fa
			fa->child[1] = new Node(min_size, leaf);
			int dem = 0;
			for (int k = i + 1; k < current_key; ++k)
			{
				fa->child[1]->current_key++;
				if (leaf == 0)
				{
					child[k]->fa = fa->child[1];
					fa->child[1]->child[dem] = child[k];
				}
				fa->child[1]->key[dem] = key[k];
				dem++;
			}
			if (leaf == 0)
			{
				child[current_key]->fa = fa->child[1];
				fa->child[1]->child[dem] = child[current_key];
			}
			fa->child[1]->fa = fa;

			//resize current key size
			current_key = min_size - 1;

			if (root == this)root = fa;
		}
	}

};

//class BTree
class BTree
{
public:

	Node* root;

	int min_size;

	//construction
	BTree(int n)
	{
		min_size = n;
		root = NULL;
	}

	//find value in BTree
	Node* Find(int val)
	{
		return root->Find(val);
	}

	void Print()
	{
		root->Print();
	}

	//insertion
	void Insert(int val)
	{
		if (root == NULL)
		{
			root = new Node(min_size, 1);
			root->key[0] = val;
			root->current_key = 1;
		}

		else
		{
			root->Insert(val, root);
		}
	}

	Node* Successor(Node* x)
	{
		if (x->leaf == 1)
		{
			return x;
		}
		else return Successor(x->child[x->current_key]);
	}

	void Delete(int val)
	{
		// x is the key need to delete
		Node* x = Find(val);

		int Case = 0;
		int last_val = val;

		// Case 1: x is the internal node
		if (x->leaf == 0)
		{
			Case = 1;

			//Find successor node
			int point = 0;
			for (int i = 0; i < x->current_key; ++i)
			{
				if (x->key[i] == val)point = i;
			}
			Node* suc = Successor(x->child[point]);
			int suc_val = suc->key[suc->current_key - 1];
			x = suc;
			val = suc_val;
		}

		// Case 2: x is leaf node 
		if (x->leaf == 1)
		{
			if (Case == 0)Case = 2;

			// if x's current key > min key
			if (x->current_key > min_size - 1)
			{
				x->current_key -= 1;
				for (int i = 0; i < x->current_key; ++i)
				{
					if (x->key[i] >= val)
					{
						x->key[i] = x->key[i + 1];
					}
				}
			}

			// if x's current key = min key
			else
			{
				x->current_key -= 1;
				for (int i = 0; i < x->current_key; ++i)
				{
					if (x->key[i] >= val)
					{
						x->key[i] = x->key[i + 1];
					}
				}

				if (x != root)Merge(x);
			}
		}

		if (Case == 1)
		{
			Node* x = Find(last_val);
			for (int i = 0; i < x->current_key; ++i)
			{
				if (x->key[i] == last_val)
				{
					x->key[i] = val;
					return;
				}
			}
		}

		return;
	}

	void Merge(Node* x);
};

void BTree::Merge(Node* x)
{
	//if x is the root
	if (x == root)
	{
		if (x->current_key == 0)
		{
			root = x->child[0];
			return;
		}
		else return;
	}

	Node* fax = x->fa;  // is father of x

	//else 
	int point = 0;// which fa->child[point] = x;
	while (point <= fax->current_key - 1 && fax->child[point] != x)
	{
		point++;
	}

	if (point > 0) // borrow from left sibling 
	{
		if (fax->child[point - 1]->current_key > min_size - 1)
		{
			int left_child_key = fax->child[point - 1]->current_key;
			Node* newnode = fax->child[point - 1]->child[left_child_key]; //new child of x
			int newval = fax->child[point - 1]->key[left_child_key - 1]; //new key of x
			fax->child[point - 1]->current_key -= 1; // delete key and child from left sibling

			//add new child and key to x
			x->current_key += 1;
			for (int i = x->current_key - 1; i >= 1; --i)
			{
				x->key[i] = x->key[i - 1];
			}

			for (int i = x->current_key; i >= 1; --i)
			{
				x->child[i] = x->child[i - 1];
			}
			x->key[0] = fax->key[point - 1];
			x->child[0] = newnode;
			if (!x->leaf)newnode->fa = x;
			fax->key[point - 1] = newval;

			for (int i = 0; i <= x->current_key; ++i)if (!x->leaf)x->child[i]->fa = x;
			for (int i = 0; i <= fax->child[point - 1]->current_key; ++i)if (!fax->child[point - 1]->leaf)fax->child[point - 1]->child[i]->fa = fax->child[point - 1];

			return;
		}
	}

	if (point < fax->current_key)// borrow from right sibling 
	{
		if (fax->child[point + 1]->current_key > min_size - 1)
		{
			Node* newnode = fax->child[point + 1]->child[0]; // new child of x
			int newval = fax->child[point + 1]->key[0]; // new key of x

			//delete node and child from right sibling
			fax->child[point + 1]->current_key -= 1;
			for (int i = 0; i < fax->child[point + 1]->current_key; ++i)
			{
				fax->child[point + 1]->key[i] = fax->child[point + 1]->key[i + 1];
			}
			for (int i = 0; i <= fax->child[point + 1]->current_key; ++i)
			{
				fax->child[point + 1]->child[i] = fax->child[point + 1]->child[i + 1];
			}

			//add new child and key to x
			x->current_key += 1;
			x->key[x->current_key - 1] = fax->key[point];
			x->child[x->current_key] = newnode;
			if (!x->leaf)newnode->fa = x;
			fax->key[point] = newval;

			for (int i = 0; i <= x->current_key; ++i)if (!x->leaf)x->child[i]->fa = x;
			for (int i = 0; i <= fax->child[point + 1]->current_key; ++i)if (!fax->child[point + 1]->leaf)fax->child[point + 1]->child[i]->fa = fax->child[point + 1];

			return;
		}
	}

	//merge to left sibling
	if (point > 0)
	{

		//increase left sibling's current key
		int left_child_key = fax->child[point - 1]->current_key;
		int new_current_key = left_child_key + x->current_key + 1;
		for (int i = left_child_key + 1; i < new_current_key; ++i)
		{
			fax->child[point - 1]->key[i] = x->key[i - left_child_key - 1];
		}
		fax->child[point - 1]->key[left_child_key] = fax->key[point - 1];
		for (int i = left_child_key + 1; i <= new_current_key; ++i)
		{
			fax->child[point - 1]->child[i] = x->child[i - left_child_key - 1];
			if (!x->leaf)x->child[i - left_child_key - 1]->fa = fax->child[point - 1];
		}
		fax->child[point - 1]->current_key = new_current_key;

		//delete x from fax;
		for (int i = point; i < fax->current_key; ++i)
		{
			fax->child[i] = fax->child[i + 1];
		}
		for (int i = point - 1; i < fax->current_key - 1; ++i)
		{
			fax->key[i] = fax->key[i + 1];
		}
		fax->current_key -= 1;

		for (int i = 0; i <= fax->current_key; ++i)fax->child[i]->fa = fax;
		//for (int i = 0; i <= x->current_key; ++i)if (!x->leaf)x->child[i]->fa = x;
		for (int i = 0; i <= fax->child[point - 1]->current_key; ++i)if (!fax->child[point - 1]->leaf)fax->child[point - 1]->child[i]->fa = fax->child[point - 1];

	}

	//merge to right sibling 
	else if (point < fax->current_key)
	{

		//increase x's current key
		int right_child_key = fax->child[point + 1]->current_key;
		int new_current_key = right_child_key + x->current_key + 1;
		for (int i = x->current_key + 1; i < new_current_key; ++i)
		{
			x->key[i] = fax->child[point + 1]->key[i - x->current_key - 1];
		}
		for (int i = x->current_key + 1; i <= new_current_key; ++i)
		{
			x->child[i] = fax->child[point + 1]->child[i - x->current_key - 1];
			if (!fax->child[point + 1]->leaf)fax->child[point + 1]->child[i - x->current_key - 1]->fa = x;
		}
		x->key[x->current_key] = fax->key[point];
		x->current_key = new_current_key;

		//delete right child from fax;
		for (int i = point + 1; i < fax->current_key; ++i)
		{
			fax->child[i] = fax->child[i + 1];
		}
		for (int i = point; i < fax->current_key - 1; ++i)
		{
			fax->key[i] = fax->key[i + 1];
		}
		fax->current_key -= 1;

		for (int i = 0; i <= fax->current_key; ++i)fax->child[i]->fa = fax;
		for (int i = 0; i <= x->current_key; ++i)if (!x->leaf)x->child[i]->fa = x;
		//for (int i = 0; i <= fax->child[point + 1]->current_key; ++i)if (!fax->child[point + 1]->leaf)fax->child[point + 1]->child[i]->fa = fax->child[point + 1];
	}

	//if num node of fax is enough => return
	if (x->fa->current_key >= min_size - 1)return;
	Merge(x->fa);

	return;
}

int main()
{
	
}