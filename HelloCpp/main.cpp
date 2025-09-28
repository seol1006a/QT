#include <iostream>
#include <vector>
using namespace std;

void vector_print(vector<int>& v);
int main()
{
    vector<int> v={1, 2, 3};
    vector<int>::iterator it;
    cout << "Hello World!" << endl;

    v.push_back(4);
    v.push_back(5);

    for(unsigned long long i = 0; i<v.size(); i++)
    {
       cout << "v[" << i << "]:" << v[i] << endl;
    }
    int i=0;
    for(it=v.begin(); it !=v.end(); it++)
    {
        cout << "it v[" << i++ << "]:" << *it << endl;
    }
    // it=v.end()-1;
    // for(int i = v.size()-1; i>=0; i--)
    // {

    //     cout << "it v[" << i << "]:" << v[i] << endl;
    //     v.erase(it);
    // }
    vector_print(v);

   // for(int i = 0; i<v.size(); i++)
   //  {

   //     cout << "rease v[" << i << "]:" << v[i] << endl;
   //  }
    return 0;
}
void vector_print(vector<int>& v)
{
    vector<int>::iterator it;
    it=v.end()-1;
    for(int i = v.size()-1; i>=0; i--)
    {
        cout << "it v[" << i << "]:" << v[i] << endl;
        v.erase(it);
    }
}
