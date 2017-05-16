/*  Write a C++ program to read series of names, one per line, from standard input and write these names
   spelled in reverse order to the standard output using I/O redirection and pipes. Repeat the exercise using
   an input file specified by the user instead of the standard input and using an output file specified by the
   user instead of the standard output.
 */

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
