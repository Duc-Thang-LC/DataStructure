// Đây là code Red-Black Tree

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;
const int oo = 1000000007;

class RBT {
public:
	int value;
	bool color;
	RBT* left, * right, * father;

	// khai báo nullptr
	RBT();

	// khai báo có giá trị value và color
	RBT(int, int);

	// insert
	RBT* Insert(RBT*, int);

	//delete
	RBT* Delete(RBT*, int);

	//dãy theo order
	void Inorder(RBT*);

	//level Order
	void LevelOrder(RBT*);

	//xuli Delete
	RBT* xuli(RBT*, int);

	//Double_Black_Case
	RBT* Double_Black_Case(RBT*, int, bool);
};

RBT::RBT()
{
	value = 0;
	father = left = right = nullptr;
}

RBT::RBT(int val, int col)
{
	value = val;
	color = col;
	father = left = right = nullptr;
}

RBT* RBT::Insert(RBT* node, int val)
{
	if (node == nullptr)
	{
		RBT* neww = new RBT;
		neww->value = val;
		neww->color = 0;
		return neww;
	}

	if (val > node->value)
	{
		if (node->right)
		{
			node->right = Insert(node->right, val);
		}
		else
		{
			RBT* x = new RBT;
			x->value = val;
			x->color = 1;
			x->father = node;
			node->right = x;
		}
	}

	if (val < node->value)
	{
		if (node->left)
		{
			node->left = Insert(node->left, val);
		}
		else
		{
			RBT* x = new RBT;
			x->value = val;
			x->color = 1;
			x->father = node;
			node->left = x;
		}
	}

	// cha ở bên phải ông nội
	if ((node->right) && (node->right->color) == 1)
	{
		// chú bằng null hoặc đen
		if ((node->left == NULL) || (node->left->color == 0))
		{
			// trường hợp tam giác
			RBT* bo = node->right;
			RBT* conleft = bo->left;
			RBT* conright = bo->right;
			RBT* chu = node->left;
			RBT* ong = node;
			if ((conleft) && (conleft->color == 1))
			{
				bo->left = nullptr;
				conleft->father = node;
				node->right = conleft;
				node->right->right = bo;
				bo->father = conleft;
			}

			// trường hợp line
			chu = node->left;
			ong = node;
			bo = node->right;
			conleft = bo->left;
			conright = bo->right;
			if ((conright) && (conright->color == 1))
			{
				bo->father = ong->father;
				ong->father = bo;
				ong->right = bo->left;
				bo->left = ong;
				bo->color = 0;
				ong->color = 1;
				node = bo;
			}
		}

		// chú bằng đỏ
		else if ((node->left->color) == 1)
		{
			RBT* bo = node->right;
			RBT* conleft = bo->left;
			RBT* conright = bo->right;
			RBT* chu = node->left;
			RBT* ong = node;
			if ((conleft) && (conleft->color == 1))
			{
				bo->color = 0;
				chu->color = 0;
				ong->color = 1;
				node = ong;
			}
			else if ((conright) && (conright->color == 1))
			{
				bo->color = 0;
				chu->color = 0;
				ong->color = 1;
				node = ong;
			}
		}
	}

	// cha ở bên trái ông nội
	if ((node->left) && (node->left->color) == 1)
	{
		// chú bằng null hoặc đen
		if ((node->right == NULL) || (node->right->color == 0))
		{
			// trường hợp tam giác
			RBT* bo = node->left;
			RBT* conleft = bo->left;
			RBT* conright = bo->right;
			RBT* chu = node->right;
			RBT* ong = node;
			if ((conright) && (conright->color == 1))
			{
				bo->right = nullptr;
				conright->father = node;
				node->left = conright;
				node->left->left = bo;
				bo->father = conright;
			}

			// trường hợp line
			bo = node->left;
			conleft = bo->left;
			conright = bo->right;
			chu = node->right;
			ong = node;
			if ((conleft) && (conleft->color == 1))
			{
				bo->father = ong->father;
				ong->father = bo;
				ong->left = bo->right;
				bo->right = ong;
				bo->color = 0;
				ong->color = 1;
				node = bo;
			}
		}

		// chú bằng đỏ
		else if ((node->right) && (node->right->color == 1))
		{
			RBT* bo = node->left;
			RBT* conleft = bo->left;
			RBT* conright = bo->right;
			RBT* chu = node->right;
			RBT* ong = node;
			if ((conleft) && (conleft->color == 1))
			{
				bo->color = 0;
				chu->color = 0;
				ong->color = 1;
				node = ong;
			}
			else if ((conright) && (conright->color == 1))
			{
				bo->color = 0;
				chu->color = 0;
				ong->color = 1;
				node = ong;
			}
		}
	}

	if (node->father == nullptr)
	{
		node->color = 0;
	}

	return node;
}

RBT* RBT::Delete(RBT* node, int val)
{
	if (node->value == val)
	{
		//tim phan thay the
		RBT* x = node;
		if (node->left)
		{
			x = node->left;
			while (x->right)
			{
				x = x->right;
			}
		}
		else if (node->right)
		{
			x = node->right;
			while (x->left)
			{
				x = x->left;
			}
		}
		node->value = x->value;

		//xu li phan thay the
		if (!x->father)
		{
			return nullptr;
		}
		int loai;
		if (x->father->left == x)loai = 1;
		else loai = 2;
		x->father = xuli(x->father, loai);
	}

	if (val < (node->value))
	{
		node->left = Delete(node->left, val);
	}

	if (val > (node->value))
	{
		node->right = Delete(node->right, val);
	}

	return node;
}

RBT* RBT::xuli(RBT* bo, int loai)
{
	// truong hop con1 ben trai bo
	if (loai == 1)
	{
		RBT* con1 = bo->left;
		if (con1->color == 1)
		{
			if (con1->left)
			{
				RBT* cleft = con1->left;
				bo->left = cleft;
				cleft->father = bo;
				return bo;
			}
			con1 = nullptr;
			return bo;
		}
		else
		{
			if (con1->left)
			{
				RBT* cleft = con1->left;
				bo->left = cleft;
				cleft->father = bo;
				if (cleft->color == 1)
				{
					cleft->color = 0;
					return bo;
				}
				else
				{
					bo = Double_Black_Case(bo, loai, 0);
					return bo;
				}
			}
			else
			{
				bo = Double_Black_Case(bo, loai, 1);
				return bo;
			}
		}
	}

	//truong hop con1 ben phai bo
	else
	{
		RBT* con1 = bo->right;
		if (con1->color == 1)
		{
			if (con1->right)
			{
				RBT* cright = con1->right;
				bo->right = cright;
				cright->father = bo;
				return bo;
			}
			con1 = nullptr;
			return bo;
		}
		else
		{
			if (con1->right)
			{
				RBT* cright = con1->right;
				bo->right = cright;
				cright->father = bo;
				if (cright->color == 1)
				{
					cright->color = 0;
					return bo;
				}
				else
				{
					bo = Double_Black_Case(bo, loai, 0);
					return bo;
				}
			}
			else
			{
				bo = Double_Black_Case(bo, loai, 1);
				return bo;
			}
		}
	}
}

RBT* RBT::Double_Black_Case(RBT* G, int loai, bool null)
{
	//truong hop x ben trai G
	if (loai == 1)
	{
		RBT* x = G->left;
		RBT* y = G->right;
		if (null)x = nullptr;

		//truong hop c2 do
		if (y)
		{
			RBT* c2 = y->right;
			RBT* c1 = y->left;
			if ((c2) && (c2->color == 1))
			{
				y->father = G->father;
				y->left = G;
				G->father = y;
				G->right = c1;
				y->color = G->color;
				G->color = 0;
				c2->color = 0;
				return y;
			}
		}

		//truong hop c2 den, c1 do
		if (y)
		{
			RBT* c2 = y->right;
			RBT* c1 = y->left;
			if (c2 == NULL || (c2 && c2->color == 0))
			{
				if (c1 && c1->color == 1)
				{
					c1->father = G;
					y->father = c1;
					y->left = c1->right;
					c1->right = y;
					c1->color = 0;
					y->color = 1;

					c1->father = G->father;
					G->father = c1;
					G->right = c1->left;
					c1->left = G;
					c1->color = G->color;
					G->color = 0;
					y->color = 0;
					return c1;
				}
			}
		}

		//truong hop c2 den, c1 den
		if (y)
		{
			RBT* c2 = y->right;
			RBT* c1 = y->left;
			if (c2 == NULL || (c2 && c2->color == 0))
			{
				if (c1 == NULL || (c1 && c1->color == 0))
				{
					// truong hop G den, y den
					if (G->color == 0 && y->color == 0)
					{
						y->color = 1;
						return G;
						// *can phai sua* //
					}

					// truong hop G den, y do
					else if (G->color == 0 && y->color == 1)
					{
						y->father = G->father;
						y->left = G;
						G->father = y;
						G->right = c1;
						y->color = 0;
						c1->color = 1;
						return G;
					}

					// truong hop G do, y den
				}
			}
		}
	}
}

void RBT::Inorder(RBT* node)
{
	if (node == NULL)
		return;

	Inorder(node->left);
	cout << node->value << "  ";
	Inorder(node->right);
}

void RBT::LevelOrder(RBT* node)
{
	if (node == NULL)
		return;

	std::queue<RBT*> q;
	q.push(node);

	while (!q.empty())
	{
		RBT* temp = q.front();
		cout << temp->value << "  ";
		q.pop();

		if (temp->left != NULL)
			q.push(temp->left);

		if (temp->right != NULL)
			q.push(temp->right);
	}
}

int main()
{
	RBT x;
	RBT* root = nullptr;
	root = x.Insert(root, 7);
	root = x.Insert(root, 6);
	root = x.Insert(root, 5);
	root = x.Insert(root, 4);
	root = x.Insert(root, 3);
	root = x.Insert(root, 2);
	root = x.Insert(root, 1);

	cout << root->value << endl;
	cout << "Inoder Traversal of Created Tree\n";
	x.Inorder(root);

	cout << "\n\nLevel Order Traversal of Created Tree\n";
	x.LevelOrder(root);

	return 0;
}
