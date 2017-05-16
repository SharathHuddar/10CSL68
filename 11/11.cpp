/*
   Write a C++ program to store and retrieve student data from file using
   hashing. Use any collision resolution technique
 */


#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define LEN 40
#define N 5

using namespace std;

class student {
char name[25], usn[11], age[4], str[LEN];
int fd;
unsigned int hash(char*);
void pack();
void unpack();
public:
student();
~student();
void add();
void search();
};

student::student(){
        if((fd=open("./student",O_RDWR))==-1) {
                char buf[(LEN+1)*N];
                int i;
                for(i=0; i<(LEN+1)*N; i++)
                        buf[i]='/';
                fd=open("./student",O_RDWR|O_CREAT|O_EXCL, 0666);
                write(fd, buf, (LEN+1)*N);
        }
}

void student::pack(){
        strcpy(str, usn);
        strcat(str, "|");
        strcat(str, name);
        strcat(str, "|");
        strcat(str, age);
        for (int i = strlen(str); i<LEN-1; i++)
                strcat(str, "#");
}

void student::unpack(){
        strcpy(usn, strtok(str, "|"));
        strcpy(name, strtok(NULL, "|"));
        strcpy(age, strtok(NULL, "#"));
}

unsigned int student::hash(char *str){
        unsigned int hash=0;
        int c;
        while(c=*str++)
                hash=hash*33+c;
        return hash%N;
}

void student::add(){
        int home_address, i=0;
        char test;
        char test_buf[2];
        cout<<"Enter USN : ";
        cin>>usn;
        cout<<"Enter name : ";
        cin>>name;
        cout<<"Enter age : ";
        cin>>age;
        pack();
        home_address=hash(name);
        while(1) {
                if(i==N) {
                        cout<<"Overflow!\n";
                        return;
                }
                lseek(fd, (LEN+1)*home_address, SEEK_SET);
                read(fd, &test, sizeof(test));
                if(test=='/')
                        break;
                home_address=(home_address+1)%N;
                i++;
        }
        lseek(fd, (LEN+1)*home_address, SEEK_SET);
        write(fd, str, LEN);
        write(fd, "\n", 1);
}

void student::search(){
        char key[25];
        int home_address, i=0;
        cout<<"Enter key : ";
        cin>>key;
        home_address=hash(key);
        do
        {
                lseek(fd, (LEN+1)*home_address, SEEK_SET);
                read(fd, str, LEN);
                unpack();
                home_address=(home_address+1)%N;
                i++;
        } while(strcmp(name, key)&& i<N);
        if(strcmp(name, key))
                cout<<"Not found!\n";
        else {
                cout<<"Student found \n";
                cout<<"Name = "<<name;
                cout<<"\nUsn = "<<usn;
                cout<<"\nAge = "<<age<<endl;
        }
}

student::~student(){
        close(fd);
}

int main(){
        int ch;
        student s;
        do
        {
                cout<<"\n1.Add\n2.Search\n3.Exit\n\nEnter choice : ";
                cin>>ch;
                switch(ch) {
                case 1: s.add();
                        break;
                case 2: s.search();
                        break;
                case 3: break;
                default: cout<<"Wrong choice!";
                }
        } while(ch!=3);
}
