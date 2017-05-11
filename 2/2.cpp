#include <fstream>
#include <string.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
class student
{
public:
string usn;
string name;
string sem;
string Buf;
char buf[46];
int pack();
void write_f(fstream &);
void unpack();
void print(ostream &);
void read_f(fstream &);
};
int student::pack()
{
								Buf=usn+"|"+name+"|"+sem+"|";
								if(Buf.length()>45)
																return 0;
								else
								{
																while(Buf.length()<45)
																								Buf=Buf+'_';
																Buf=Buf+'\n';
																return 1;
								}
}
void student::write_f(fstream &fp)
{
								fp<<Buf;
}
void student::print(ostream &stream)
{
								stream<<"student:"<<"\tusn"<<usn<<"\n"<<"\tname"<<name<<"\n"<<"\t sem"<<sem<<"\n";
}
void student::unpack()
{
								char stg[100];
								int pos=0,count=0,k;
								while(count<3)
								{
																k=0;
																for(int i=pos; i<strlen(buf); i++,k++)
																{
																								stg[k]=buf[i];
																								pos++;
																								if(buf[i]=='|')
																																break;
																}
																stg[k]='\0';
																count++;
																if(count==1) usn=stg;
																if(count==2) name=stg;
																if(count==3) sem=stg;
								}
}
void student::read_f(fstream &fp)
{
								char sg[55];
								fp.getline(buf,46,'_');
								fp.getline(sg,50,'\n');
}
main()
{
								int ch,k;
								fstream fp;
								void search();
								student s;
								system("clear");
								do
								{
																cout<<"\nenter your choice\n";
																cout<<"1.insert a record\n"<<"2.search and modify a record\n"<<"3.exit";
																cin>>ch;
																switch(ch)
																{
																case 1: fp.open("in.txt",ios::out|ios::app);
																								cout<<"enter usn:";
																								cin>>s.usn;
																								cout<<"enter name:";
																								cin>>s.name;
																								cout<<"enter sem:";
																								cin>>s.sem;
																								k=s.pack();
																								if(k==0)
																								{
																																cout<<"invalid data\n";
																																break;
																								}
																								else
																																s.write_f(fp);
																								fp.close();
																								break;
																case 2: search();
																								break;
																case 3: exit(1);
																}
								}
								while(ch<=3);
}
void search()
{
								int c=0,choice;
								string usn;
								student s[100];
								fstream fp1;
								fp1.open("in.txt",ios::in);
								cout<<"enter usn of student to be searched and modified\n";
								cin>>usn;
								int cnt=0;
								int i=0;
								while(fp1)
								{
																s[i].read_f(fp1);
																s[i].unpack();
																i++;
								}
								fp1.close();
								cnt=i-1;
								for(i=0; i<cnt; i++)
								{
																if(s[i].usn==usn)
																{
																								c++;
																								break;
																}
								}
								if(c==0)
								{
																cout<<"record not found\n";
																return;
								}
								else
								{
																cout<<"record found\n";
																s[i].print(cout);
																do
																{
																								cout<<"\n\t enter your choice of the field to be modified";
																								cout<<"\n\n\tusn=>\t"<<s[i].usn<<"\n\n\t1.name=>\t"<<s[i].name<<"\n\n\t2.semester=>\t"<<s[i].sem<<"\n\n\t3.exit";
																								cout<<"\n\n\tchoice=>";
																								cin>>choice;
																								switch(choice)
																								{
																								case 1: cout<<"enter the name=>";
																																cin>>s[i].name;
																																break;
																								case 2: cout<<"enter the semester=>";
																																cin>>s[i].sem;
																																break;
																								case 3: break;
																								default: cout<<"\n\t\t invalid entry!"<<endl;
																																break;
																								}
																} while(choice!=3);

																fp1.open("in.txt",ios::out);
																for(i=0; i<cnt; i++)
																{
																								s[i].pack();
																								s[i].write_f(fp1);
																}
																fp1.close();
								}
}

