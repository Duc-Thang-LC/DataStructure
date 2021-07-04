//this is the example code of K-D Tree
//including Search, Insert, Find Minimum Val and Deletion  

#include <iostream>

using namespace std;

const int k = 2;

//a structure present node of kd tree
class Node
{
public:
	int point[k]; // to store k dimension point 

	Node* left, * right; // point to left or right child 

	Node()//construction
	{
		left = right = NULL;
	}

	Node(int arr[]) // construction
	{
		for (int i = 0; i < k; ++i)
		{
			point[i] = arr[i];
		}

		left = right = NULL;
	}

	//insert arr[] in tree
	void Insert(int arr[], unsigned depth)
	{
		int cd = depth % k;
		if (arr[cd] < point[cd])
		{
			if (!left)left = new Node(arr);
			else left->Insert(arr, depth + 1);
		}
		else
		{
			if (!right)right = new Node(arr);
			else right->Insert(arr, depth + 1);
		}
	}

	//search arr[] in the tree
	bool Search(int arr[], unsigned depth)
	{
		bool same = true;

		for (int i = 0; i < k; ++i)
		{
			if (arr[i] != point[i])same = false;
		}

		if (!same)
		{
			int cd = depth % k;
			if (arr[cd] < point[cd])
			{
				if (!left)return false;
				return left->Search(arr, depth + 1);
			}
			else
			{
				if (!right)return false;
				return right->Search(arr, depth + 1);
			}
		}

		return true;
	}

	//find the min node at coordinate x 
	Node* FindMin(int x, unsigned depth)
	{
		if (depth % k == x)
		{
			if (left)
			{
				Node* minLeft = left->FindMin(x, depth + 1);
				if (minLeft->point[x] < point[x])
				{
					return minLeft;
				}
				return this;
			}
			return this;
		}

		else
		{
			Node* ans = this;
			if (right)
			{
				Node* minRight = right->FindMin(x, depth + 1);
				if (minRight->point[x] < point[x])
				{
					ans = minRight;
				}
			}
			if (left)
			{
				Node* minLeft = left->FindMin(x, depth + 1);
				if (minLeft->point[x] < point[x])
				{
					ans = minLeft;
				}
			}
			return ans;
		}
	}

	//check if p1 = p2 ?
	bool CheckTheSame(int p1[], int p2[])
	{
		for (int i = 0; i < k; ++i)
		{
			if (p1[i] != p2[i])return false;
		}
		return true;
	}

	//return p1 = p2
	void Copy(int p1[], int p2[])
	{
		for (int i = 0; i < k; ++i)
		{
			p1[i] = p2[i];
		}
	}

	//delete arr[]
	Node* Deletion(int arr[], unsigned int depth)
	{
		int cd = depth % k;

		//if arr[] = point[]
		if (CheckTheSame(arr, point))
		{
			if (right)
			{
				Node* min = right->FindMin(cd, depth + 1);
				Copy(point, min->point);
				right = right->Deletion(point, depth + 1);
			}
			else if (left)
			{
				Node* min = left->FindMin(cd, depth + 1);
				Copy(point, min->point);
				right = left->Deletion(point, depth + 1);
				left = NULL;
			}
			else
			{
				return NULL;
			}
		}

		//else
		else if (arr[cd] < point[cd])
		{
			left = left->Deletion(arr, depth + 1);
		}
		else right = right->Deletion(arr, depth + 1);

		//return...
		return this;
	}
};

class KDTree
{
public:
	Node* root;

	KDTree()
	{
		root = NULL;
	}

	//insert arr[] in the tree
	void Insert(int arr[])
	{
		if (root == NULL)
		{
			root = new Node(arr);
			return;
		}
		else
		{
			root->Insert(arr, 0);
		}
	}

	//search arr[] in the tree
	bool Search(int arr[])
	{
		if (root == NULL)
		{
			return false;
		}
		return root->Search(arr, 0);
	}

	// Find min value in the coordination 
	int FindMin(int x)
	{
		if (!root)return -1e9 + 7;
		return root->FindMin(x, 0)->point[x];
	}

	//deletion arr[] int the tree
	void Deletion(int arr[])
	{
		root = root->Deletion(arr, 0);
	}
};

int main()
{
	KDTree x;

	int arr[][k] = { { 30, 40 }, { 5, 25 },{ 70, 70 }, { 10, 12 }, { 50, 30 }, { 35, 45  } };

	int n = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < n; ++i)
	{
		x.Insert(arr[i]);
	}

	x.Deletion(arr[2]);

	return 0;
}