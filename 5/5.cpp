/*
   Write a C++ program to implement simple index on primary key
   for a file of student objects.
   Implement add(),search(),delete() using the index.
 */

 #include <iostream>
 #include <string>
 #include <fstream>
 #include <stdlib.h>

 using namespace std;

 class student {
 public:
   string usn, name, sem;
   void enter_data();
   void pack();
 }s1;

 struct index {
   string usn;
   int addr;
 }il[100], temp;

 int cnt;
 fstream fp;

 void create_index();
 void sort_index();
 void search();
 int bin_srch(string);
 void del();
 void error(int);

 int main(){
   int choice;
   system("clear");
   fp.open("record5.txt", ios::out|ios::app);
   fp.close();
   create_index();
   while (1) {
     cout<<"1.To add record\n2.To search for a record\n3.To delete a record\n4.Exit \n\nEnter choice : ";
     cin>>choice;
     switch (choice) {
       case 1: s1.enter_data();
               fp.open("record5.txt", ios::out|ios::app);
               if (!fp) {
                 error(1);
               }
               s1.pack();
               fp.close();
               break;
       case 2: search();
               break;
       case 3: del();
               break;
       default:exit(0);
     }
   }
 }

 void create_index(){
   int pos,i;
   string seg, usnbuf;
   cnt = -1;
   fp.open("record5.txt", ios::in);
   if (!fp) {
     error(1);
   }
   while (fp) {
     usnbuf.erase();
     pos = fp.tellg();
     getline(fp, usnbuf, '|');
     getline(fp, seg);
     if (usnbuf[0] == '*' || usnbuf.length() == 0) {
       continue;
     }
     cnt++;
     il[cnt].usn = usnbuf;
     il[cnt].addr = pos;
   }
   fp.close();
   sort_index();
 }

 void sort_index(){
   for (int i = 0; i <=cnt; i++) {
     for (int j = i+1; j <= cnt; j++) {
       if (il[i].usn>il[j].usn) {
         temp.usn = il[i].usn;
         temp.addr = il[i].addr;
         il[i].usn = il[j].usn;
         il[i].addr = il[j].addr;
         il[j].usn = temp.usn;
         il[j].addr = temp.addr;
       }
     }
   }
 }

 void student::enter_data(){
   cout<<"\nEnter usn : ";
   cin>>usn;
   cout<<"\nEnter name : ";
   cin>>name;
   cout<<"\nEnter sem : ";
   cin>>sem;
 }

 void student::pack(){
   int pos=fp.tellg();
   string buf = usn + "|" + name + "|" + sem + "|";
   fp<<buf<<endl;
   cnt++;
   il[cnt].usn = usn;
   il[cnt].addr = pos;
   sort_index();
 }

 int bin_srch(string usn_srch){
   int l=0, h=cnt, mid;
   while (l<=h) {
     mid = (l+h)/2;
     if (il[mid].usn == usn_srch) {
       return mid;
     }
     if (il[mid].usn<usn_srch) {
       l=mid+1;
     }
     if (il[mid].usn>usn_srch) {
       h=mid-1;
     }
   }
   return -1;
 }

 void search(){
   string usn_srch, buf;
   cout<<"Enter the USN of the student to be found : ";
   cin>>usn_srch;
   int pos = bin_srch(usn_srch);
   if (pos == -1) {
     cout<<"Record not found\n";
     return;
   }
   cout<<"Record found\n";
   cout<<"Usn|Name|Sem"<<endl;
   fp.open("record5.txt",ios::in);
   if (!fp) {
     error(1);
   }
   fp.seekg(il[pos].addr, ios::beg);
   getline(fp, buf);
   fp.close();
   cout<<buf<<endl;
 }

 void del(){
   string usn_srch;
   cout<<"Enter the USN of the student to be deleted : ";
   cin>>usn_srch;
   int pos = bin_srch(usn_srch);
   if (pos == -1) {
     cout<<"\nRecord not found";
     return;
   }
   cout<<"\nRecord found and deleted\n";
   fp.open("record5.txt", ios::out|ios::in);
   fp.seekp(il[pos].addr, ios::beg);
   fp.put('*');
   fp.close();
   for (int i = 0; i < cnt; i++) {
     il[i].usn = il[i+1].usn;
     il[i].addr = il[i+1].addr;
   }
   cnt--;
 }

 void error(int error_type){
   switch (error_type) {
     case 1: cout<<"\nFATAL ERROR! : Unable to open the record file\n";
             exit(0);
   }
 }
