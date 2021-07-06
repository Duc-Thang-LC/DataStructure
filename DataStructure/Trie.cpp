//this is code example of Trie Implement 
//including Insertion, Searching and Deletion

#include <iostream>

using namespace std;

const int alphabetSize = 26;

class Node
{
public:
	//the next character
	Node* child[alphabetSize];

	//check if this character is end of word
	bool isLeaf;

	//constructor
	Node()
	{
		for (int i = 0; i < alphabetSize; ++i)
		{
			child[i] = NULL;
		}
		isLeaf = 0;
	}

	//destructor
	~Node()
	{
		for (int i = 0; i < alphabetSize; ++i)
		{
			delete child[i];
		}
	}
};

class Trie
{
public:
	Node* root;

	//constructor
	Trie()
	{
		root = new Node;
	}

	~Trie()
	{
		delete root;
	}

	void Insert(string str)
	{
		Node* p = root;
		for (int i = 0; i < str.size(); ++i)
		{
			int x = str[i] - 'a';
			if (!p->child[x])
			{
				p->child[x] = new Node;
			}
			p = p->child[x];
		}
		p->isLeaf = 1;
	}

	bool Search(string str)
	{
		Node* p = root;
		for (int i = 0; i < str.size(); ++i)
		{
			int x = str[i] - 'a';
			if (!p->child[x])
			{
				return false;
			}
			p = p->child[x];
		}

		if (!p->isLeaf)return false;
		return true;
	}

	void RecurDel(Node* (&p), int i, string str)
	{
		cout << str[i];
		if (i < str.size() - 1)
		{
			int x = str[i + 1] - 'a';
			RecurDel(p->child[x], i + 1, str);
			if (!p->child[x])delete p->child[x];
		}
		if (p->isLeaf != 0 && i == str.size() - 1)
		{
			int dem = 0;
			for (int i = 0; i < alphabetSize; ++i)
			{
				if (p->child[i])dem++;
			}
			if (!dem)p = NULL;
			else p->isLeaf = 0;
		}
		else if (p->isLeaf == 0)
		{
			int dem = 0;
			for (int i = 0; i < alphabetSize; ++i)
			{
				if (p->child[i])dem++;
			}
			if (!dem)p = NULL;
		}
	}

	void Delete(string str)
	{
		int x = str[0] - 'a';
		RecurDel(root->child[x], 0, str);
	}
};

int main()
{
	Trie x;
	string keys[] = { "a","b", "b" };
	for (int i = 0; i < 3; ++i)
	{
		x.Insert(keys[i]);
	}

	for (int i = 2; i >= 2; --i)
	{
		x.Delete(keys[i]);
		cout << endl;
	}

	cout << x.Search("b");

	return 0;
}