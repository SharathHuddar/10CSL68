// TODO : rewrite the whole thing

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

char st_no[5];

int no;

class record {
public:
char usn[20];
char name[20];
char sem[2];
} rec[20];

void retrieve_details() {
        fstream file2;
        char name[20], usn[20], rrn[5], sem[5];
        file2.open("record.txt", ios::in);
        for (int i = 0; i < no; i++) {
                file2.getline(rrn, 5, '|');
                file2.getline(usn, 20, '|');
                file2.getline(name, 20, '|');
                file2.getline(sem, 5, '\n');
                if (strcmp(rrn, st_no) == 0) {
                        cout<<"\n\nStudent details are : ";
                        cout<<"\n\nUSN : "<<usn<<"\nName : "<<name<<"\nSem : "<<sem<<"\n";
                }
        }
        file2.close();
}

int main() {
        fstream file1, file2;
        int ch;
        char rt_usn[20], st_rrn[20];
        char ind[2], name[20], sem[5];
        int i, flag, flag1;
        for(;; ) {
                cout<<"\n1.Add record \n2.Search record\n";
                cin>>ch;
                switch (ch) {
                case 1: cout<<"Enter the details";
                        file1.open("index.txt", ios::out|ios::app);
                        file2.open("record.txt", ios::out|ios::app);
                        if(!file1 || !file2) {
                                cout<<"File creation error!\n";
                                exit(0);
                        }
                        for (i = 0; i <=no; i++) {
                                cout<<"\nName : ";
                                cin>>rec[i].name;
                                cout<<"USN : ";
                                cin>>rec[i].usn;
                                cout<<"Sem : ";
                                cin>>rec[i].sem;
                                file1<<rec[i].usn<<"|"<<i<<"\n";
                                file2<<i<<"|"<<rec[i].usn<<"|"<<rec[i].name<<"|"<<rec[i].sem<<"\n";
                        }
                        file1.close();
                        file2.close();
                        break;

                case 2: cout<<"Enter RRN whose record is to be displayed : ";
                        cin>>st_rrn;
                        file1.open("index.txt", ios::in);
                        file2.open("record.txt", ios::in);
                        if (!file1 || !file2) {
                                cout<<"\nError!\n";
                                exit(0);
                        }
                        flag1=0;
                        for (i = 0; i < no; i++) {
                                file1.getline(rt_usn, 20, '|');
                                file2.getline(st_no, 4, '\n');
                                if (strcmp(st_rrn, st_no) == 0) {
                                        retrieve_details();
                                        flag1 = 1;
                                }
                        }
                        if (!flag1) {
                                cout<<"Record search failed!\n";
                        }
                        file1.close();
                        break;

                default: cout<<"Invalid choice";
                        exit(0);
                        break;
                }
        }
}