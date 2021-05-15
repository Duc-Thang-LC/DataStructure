#include <iostream>

using namespace std;

class MinHeap
{
public:
	// constructor 
	MinHeap(int mmax);

    // return parent node 
	int parent(int i) { return (i - 1) / 2; }

	//return left child node
	int left(int i) { return i * 2 + 1; }

	//return right child node
	int right(int i) { return i * 2 + 2; }

	//delete root with minium value
	int extractMin();

	// fix to right definition
	void MinHeapify(int i);

	// return the root with minium value
	int getMin() { return arr[0]; }

	//adding new value
	void insertKey(int val);

private:
	int* arr; // pointer to array of elements in heap

	int max_size; 

	int current_size;
};

MinHeap::MinHeap(int mmax)
{
	current_size = 0;

	max_size = mmax;

	arr = new int [mmax];
}

void MinHeap::insertKey(int val)
{
	if (current_size == max_size)
	{
		cout << "Overflow: Could not insert Key \n";
	}

	current_size++;
	int i = current_size - 1;
	arr[i] = val;

	while (i != 0 && arr[parent(i)] > arr[i])
	{
		swap(arr[i], arr[parent(i)]);
		i = parent(i);
	}
}

int MinHeap::extractMin()
{
	if (current_size == 0)
	{
		return 10000007;
	}

	if (current_size == 1)
	{
		current_size--;
		return arr[0];
	}
	current_size--;
	arr[0] = arr[current_size];
	MinHeapify(0);

	return arr[0];
}

void MinHeap::MinHeapify(int i)
{
	int smallest = i;
	int l = left(i);
	int r = right(i);
	if (l < current_size && arr[i] > arr[l])
	{
		smallest = l;
	}
	if (r < current_size && arr[smallest] > arr[r])
	{
		smallest = r;
	}
	if (smallest != i)
	{
		swap(arr[i], arr[smallest]);
		MinHeapify(smallest);
	}
}

void MinHeap::deleteKey(int i)
{

}

int main()
{
	MinHeap x(10);
	x.insertKey(10);
	x.insertKey(2);
	x.insertKey(5);
	x.insertKey(6);
	x.insertKey(1);
    cout << x.extractMin() << endl;
    cout << x.extractMin() << endl;
    cout << x.extractMin() << endl;
    cout << x.extractMin() << endl;
}