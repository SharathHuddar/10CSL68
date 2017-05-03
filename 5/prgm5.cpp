#include<fstream.h>
#include<string>
#include<iostream>
#include<stdlib.h>
using namespace std;
char st_no[5];
int no;
//record specification
class record
{
	public:
		char usn[20];
		char name[20];
		char sem[2];
}rec[20];
void retrieve_details()
{
	fstream file2;
	char name[20],usn[20],rrn[5],sem[5];
	file2.open("record.txt",ios::in);
	for(int i=0;i<no;i++)
	{
		file2.getline(rrn,5,'|');
		file2.getline(usn,20,'|');
		file2.getline(name,20,'|');
		file2.getline(sem,5,'\n');
		
		
