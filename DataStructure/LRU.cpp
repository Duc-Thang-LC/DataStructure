//Problem:
//Implement methods of LRU cache
//get(x) : return the value of key x if key exist in the cache
//set(x,y) : set the value of x to y and put it on the first of cache


#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class LN
{
public:
    LN* fa;
    LN* child;
    int val;
    int k;

    LN()
    {
        fa = NULL;
        child = NULL;
        val = 0;
    }
};

class LRUCache
{
private:
    int csize;

    LN* ans;

    LN* last;

    unordered_map<int, LN*> ma;

public:
    //Constructor for initializing the cache capacity with the given value.
    LRUCache(int cap)
    {
        csize = cap;
        ans = NULL;
        last = NULL;
        
        ma.clear();
    }

    //Function to return value corresponding to the key.
    int get(int key)
    {
        if (ma.find(key) != ma.end())
        {
            LN* x = ma[key];

            int value = x->val;
            if (x == ans)
            {
                ans = x->child;
                if (ans == NULL)last = NULL;
                else ans->fa = NULL;
            }
            else if (!x->child)
            {
                x->fa->child = NULL;
                last = x->fa;
            }
            else
            {
                x->fa->child = x->child;
                x->child->fa = x->fa;
            }

            LN* neww = new LN;
            neww->val = value;
            neww->k = key;
            neww->child = ans;
            if (ans)ans->fa = neww;
            ans = neww;
            ma[key] = ans;

            if (ma.size() == 1)last = ans;
            return value;
        }

        else return -1;
    }

    //Function for storing key-value pair.
    void set(int key, int value)
    {
        if (ma.find(key) != ma.end())
        {
            LN* x = ma[key];
            if (x == ans)
            {
                ans = x->child;
                if (ans == NULL)last = NULL;
                else ans->fa = NULL;
            }
            else if (!x->child)
            {
                x->fa->child = NULL;
                last = x->fa;
            }
            else
            {
                x->fa->child = x->child;
                x->child->fa = x->fa;
            }

            LN* neww = new LN;
            neww->val = value;
            neww->child = ans;
            neww->k = key;
            if (ans)ans->fa = neww;
            ans = neww;

            ma[key] = ans;

            if (ma.size() == 1)last = ans;
        }

        else
        {
            if (ma.size() == csize)
            {
                ma.erase(last->k);
                last = last->fa;
                if (last) last->child = NULL;
            }

            LN* neww = new LN;
            neww->val = value;
            neww->child = ans;
            neww->k = key;
            if (ans)ans->fa = neww;
            ans = neww;
            ma.insert({ key, ans });

            if (ma.size() == 1)last = ans;
        }
    }
};

int main()
{
    return 0;
}