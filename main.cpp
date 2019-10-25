#include<iostream>
#include<fstream>
#include<cstring>
#include <bits/stdc++.h>
using namespace std;


struct Index
{
	char id[10];
	int offset;
};

int hash1(string id)
{
	return ((int) id[0] + (int) id[1]) % 100;
}

void initializeFile(fstream& ofile)
{
	Index s;
	s.offset = -1;
	for(int i = 0 ;  i < 100 ; i++)
		ofile.write((char*)&s,sizeof(Index));
}

void addStudent(Index s, fstream& ofile)
{
	int RRN = hash1(s.id);
	//cout<<endl<<s.id<<"  " << RRN;
	ofile.seekp(RRN*sizeof(Index));
	ofile.write((char*)&s,sizeof(Index));
}

int searchStudent(char id[], fstream& ifile)
{
	Index s;
	int RRN = hash1(id);

	ifile.seekg(RRN*sizeof(Index));
	//cout<<endl<<id<<"  " << ifile.tellg();
	ifile.read((char*)&s,sizeof(Index));

	if(strcmp(s.id,id) ==0)
    	return s.offset;
    else
    	return -1;
}

int main()
{
	fstream file;
	file.open("index.txt",ios::in|ios::out|ios::binary);
	initializeFile(file);
	int numRec;

	cout<<"Enter Number Of Input Records:";
    cin>>numRec;

    for(int i =0;i<numRec;i++)
	{
        Index tmp;
        cout<<endl<<"Enter Student "<<i+1<<" ID (Max 10 Letters):";
        cin>>tmp.id;

		cout<<"Enter Student "<<i+1<<" Offset:";
        cin>>tmp.offset;

        addStudent(tmp,file);
    }

	char id[10];
	cout<<endl<<"Enter Target Stundent ID: ";
    cin>>id;
	int offset = searchStudent(id,file);
	if(offset !=  -1)
    	cout<<endl<<"Student ID : "<<id<<"  Offset: "<<offset<<endl;
    else
    	cout<<"Student not found.";
	file.close();

}
