#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

class student{
	public:
		string usn;
		string name;
		string sem;
		string buf;
		void get_data();
		void pack();
		void write_f();
		void unpack(int);
		void search(string);
		int hash(string);
};

int student::hash(string key){
	int t;
	t = (((key[7]-48)*100 + ((key[8]-48)*10) + (key[9] - 48))%9);
	if (t==0) return 9;
	else return t;
}

void student::get_data(){
	cout<<"\nUSN : ";
	cin>>usn;
	cout<<"\nName : ";
	cin>>name;
	cout<<"\nSem : ";
	cin>>sem;
}

void student::pack(){
	string s,temp;
	stringstream out;
	out<<sem;
	s = out.str();
	buf.erase();
	temp.erase();
	temp+=usn+'|'+name+'|'+s;
	for(; temp.size() < 40;)temp+='_';
	buf+=temp+'\n';
}

void student::write_f(){
	fstream fp;
	string temp;
	int cnt, pos;
	pos = hash(usn);
	pos--;
	pos = pos*304;
	fp.open("hash1.txt");
	fp.seekp(pos, ios::beg);
	getline(fp, temp);
	fp.close();
	cnt = temp[0] - 48;
	fp.open("hash1.txt");
	if (cnt<0){
		fp.seekp(pos, ios::beg);
		fp.put('1');
		pos = pos +1;
	} else if (cnt ==1 ) {
		fp.seekp(pos, ios::beg);
		fp.put('2');
		pos=pos+42;
	} else if (cnt==2) {
		fp.seekp(pos, ios::beg);
		fp.put('3');
		pos = pos + 83;
	}
	cout<<"Inserting at : "<<pos;
	fp.seekp(pos, ios::beg);
	fp<<buf;
	fp.close();
	if (cnt == 3) cout<<"\nCannot insert ";
}

void student::unpack(int flag){
	string s;
	int ch=1, i=0;
	usn.erase();
	if(flag==1) i++;
	buf.erase();
	while(buf[i]!='|')
		usn+=buf[i++];
	name.erase();
	i++;
	while(buf[i]!='|')
		name+=buf[i++];
	s.erase();
	i++;
	while(buf[i]!='_')
		s+=buf[i++];
	istringstream out(s);
	out>>sem;
}

void student::search(string key){
	fstream fp;
	int flag=0, pos=1, cnt, i=1;
	string temp;
	pos = pos*304;
	fp.open("hash1.txt");
	fp.seekp(pos, ios::beg);
	getline(fp, temp);
	cnt = temp[0]-48;
	fp.seekp(pos, ios::beg);
	while (i<=cnt){
		buf.erase();
		getline(fp, buf);
		unpack(i++);
		if (key==usn) flag=1;
	}
	if(!flag) cout<<"\nKey not found ";
	else {
		cout<<"\nThe rec details are - ";
		cout<<"\nUSN : "<<usn<<"\nName : "<<name<<"\nSem : "<<sem;
	}
	fp.close();
}

int main(){
	int ch;
	student s1;
	string key;
	while(1){
		cout<<"\nMain Menu \n1.Add\n\n2.Search\n\n3.Exit\n\nEnter the choice:";
		cin>>ch;
		switch(ch){
			case 1: cout<<"Data \n";
				s1.get_data();
				s1.pack();
				s1.write_f();
				break;
			case 2: cout<<"\nEnter the key";
				cin>>key;
				s1.search(key);
				break;
			case 3: return 0;
			default:cout<<"\nWrong choice ";
		}
	}
}
