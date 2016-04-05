#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;
const int maxn = 1000000;

int main(int argc, char *argv[])
{	
    map<string, int> mp;
    for (int i = 0; i < maxn; i++) {
        string str  = "";
        for (int j = 0; j < 32; j++) {
            char c = '0' + rand() % 10;
            str+= c;
        }
        mp[str] = rand() % 10;
    }
    int n;
    cout<<"finish"<<endl;
    cin>>n;
    return 0;
}
