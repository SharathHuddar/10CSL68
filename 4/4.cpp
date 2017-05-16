/*
   Write a c++ program to write student objects with variable-length records
   using any suitable record structure and to read from this file a
   student record using RRN.
 */


#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

class records {
public:
void addRecord(string, string, string);
void search(int);
};

void records::addRecord(string usn, string name, string sem) {
        fstream fp;
        fp.open("records.txt", ios::out|ios::app);
        if (!fp) {
                cout<<"File creation error!\n";
                exit(0);
        }
        fp<<usn<<"|"<<name<<"|"<<sem<<"\n";
        fp.close();
}

void records::search(int rrn) {
        char line[100];
        int flag;
        fstream fp;
        char usn[25], name[25], sem[4];
        fp.open("records.txt", ios::in);
        fp.seekg(ios::beg);
        for (int i = 0; i < rrn; i++) {
                if (fp.peek() != EOF) {
                        flag=0;
                        fp.getline(line, 101,  '\n');
                } else {
                        flag=1;
                }
        }
        if (flag) {
                cout<<"\nRecord not found\n";
        } else {
                cout<<"\nRecord found : \n";
                strcpy(usn, strtok(line, "|"));
                strcpy(name, strtok(NULL, "|"));
                strcpy(sem, strtok(NULL, "\n"));
                cout<<"\nUSN : "<<usn<<endl;
                cout<<"\nName : "<<name<<endl;
                cout<<"\nSem : "<<sem<<endl;
        }
}

int main() {
        int ch, rrn;
        string usn, name, sem;
        records r;
        do {
                cout<<"\n1.Add a record\n2.Search for a record by RRN\nEnter your choice : ";
                cin>>ch;
                switch (ch) {
                case 1: cout<<"Enter USN : ";
                        cin>>usn;
                        cout<<"Enter Name : ";
                        cin>>name;
                        cout<<"Enter Sem : ";
                        cin>>sem;
                        r.addRecord(usn, name, sem);
                        break;
                case 2: cout<<"Enter RRN to search record : ";
                        cin>>rrn;
                        r.search(rrn);
                }
        } while(ch==1 || ch==2);
        exit(0);
        return 0;
}
