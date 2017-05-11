#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
        string name, rev;
        int cnt, len, i, j;
        cout<<"\n\nHow many?";
        cin>>cnt;
        while (cnt--) {
                cout<<"\nName : ";
                cin>>name;
                rev.erase();
                for (i = name.length(); i >= 0; i--) {
                        rev+=name[i];
                }
                cout<<"\nReverse : "<<"\t"<<rev;
        }
        return 0;
}