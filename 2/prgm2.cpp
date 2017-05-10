#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include <iostream.h>
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
