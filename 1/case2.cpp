/*  Write a C++ program to read series of names, one per line, from standard input and write these names
   spelled in reverse order to the standard output using I/O redirection and pipes. Repeat the exercise using
   an input file specified by the user instead of the standard input and using an output file specified by the
   user instead of the standard output.
 */

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;
int main()
{
		string name,rev;
		char infile[30],outfile[30];
		fstream fpinp,fpoutp;
		int j;
		cout<<"enter the input file name:\n";
		cin>>infile;
		cout<<"enter output filename:\n";
		cin>>outfile;
		fpinp.open(infile,ios::in);
		fpoutp.open(outfile,ios::out);
		if(!fpinp||!fpoutp)
		{
				cout<<"FATAL ERROR!:UNABLE TO OPEN THE FILE(S)";
				exit(0);
		}
		while(fpinp)
		{
				getline(fpinp,name);
				rev.erase();
				for(j=name.length()-1; j>=0; j--)
						rev+=name[j];
				fpoutp<<rev<<endl;
		}
		fpinp.close();
		fpoutp.close();
		return 0;
}
