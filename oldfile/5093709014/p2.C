#include<iostream>
#include <stdlib.h>
#include<string>
#include"two-three-tree.h"
//#include"two-three-tree.C"
#include<fstream>
using namespace std;



class Base{
public:
	int population;
	int economy;
	int count;
	string *name;
	//string info;
	Base(){
		population = 0;
		economy = 0;
		count = 0;
		name = NULL;
	}
	~Base(){
		//cout<<"aaa"<<endl;
	}
	friend ostream& operator<<(ostream& out,const Base& p);
};
ostream& operator<<(ostream& out,const Base& p){
	out<<p.population<<" "<<p.economy<<" "<<*(p.name);
	return out;
}

int main(int argc, char* argv[]){
	string category;
	string first_arg;
	string second_arg;
	string third_arg;
	int poplist[10000]={0};
	int ecolist[10000]={0};
	string namelist[10000];
	Tree<int,Base> population;
	Tree<int,Base> economy;
	Tree<string,Base> name;
	int count=0;
	int rtime = 0;
	while(!cin.eof()){
		cin>>category;
		if(cin.eof()) break;
		if(category=="insert"){
			cin>>first_arg;
			cin>>second_arg;
			cin>>third_arg;
			poplist[count] = atoi(first_arg.c_str());
			ecolist[count] = atoi(second_arg.c_str());
			namelist[count] = third_arg;
			int *pop = poplist+count;
			int *eco = ecolist+count;
			string *namekey = namelist+count;
			//for values
			Base *base = new Base;
			base->population = *pop;
			base->economy = *eco;
			base->name = namekey;
			base->count = count;
			cout<<"insert "<<first_arg<<" "<<second_arg<<" "<<third_arg<<endl;
			bool p = population.insert(pop,base);
			if(p){
				bool e = economy.insert(eco,base);
				if(e){
					bool n = name.insert(namekey,base);
					if(n){
						count++;
						cout<<"Insertion successful"<<endl;
					}else{
						cout<<"Insertion failed"<<endl;
						Base *temps = population.remove(*pop);
						delete temps;
						economy.remove(*eco);
					}
				}
				else{
					cout<<"Insertion failed"<<endl;
					Base* temps = population.remove(*pop);
					delete temps;
				}
			}else{
				delete base;
				cout<<"Insertion failed"<<endl;
			}
		}else if(category=="search"){
			cin>>first_arg;
			cin>>second_arg;
			cout<<"search "<<first_arg<<" "<<second_arg<<endl;
			if(first_arg=="1"){
				int key = atoi(second_arg.c_str());
				Base *base = population.search(key);
				if(base!=NULL){
					cout<<"Record found: "<<base->population<<" "<<base->economy<<" "<<*(base->name)<<endl;
				}
				else{
					cout<<"No record found"<<endl;
				}
			}else if(first_arg=="2"){
				int key = atoi(second_arg.c_str());
				Base *base = economy.search(key);
				if(base!=NULL){
					cout<<"Record found: "<<base->population<<" "<<base->economy<<" "<<*(base->name)<<endl;
				}
				else{
					cout<<"No record found"<<endl;
				}
			}else if(first_arg=="3"){
				string key = second_arg;
				Base *base = name.search(key);
				if(base!=NULL){
					//int *po = economy.search(*ec);
					cout<<"Record found: "<<base->population<<" "<<base->economy<<" "<<*(base->name)<<endl;
				}else{
					cout<<"No record found"<<endl;
				}
			}else
				return 0;
		}else if(category=="remove"){
			cin>>first_arg;
			cin>>second_arg;
			cout<<"remove "<<first_arg<<" "<<second_arg<<endl;
			if(first_arg=="1"){
				int key = atoi(second_arg.c_str());
				Base *base = population.remove(key);
				if(base!=NULL){
					cout<<"Remove record: "<<base->population<<" "<<base->economy<<" "<<*(base->name)<<endl;
					name.remove(*base->name);
					economy.remove(base->economy);
					poplist[base->count]=0;
					ecolist[base->count]=0;
					namelist[base->count]="";
					rtime++;
					delete base;
				}
				else{
					cout<<"Removal failed"<<endl;
				}
			}else if(first_arg=="2"){
				int key = atoi(second_arg.c_str());
				Base *base = economy.remove(key);
				if(base!=NULL){
					cout<<"Remove record: "<<base->population<<" "<<base->economy<<" "<<*(base->name)<<endl;
					population.remove(base->population);
					name.remove(*base->name);
					poplist[base->count]=0;
					ecolist[base->count]=0;
					namelist[base->count]="";
					rtime++;
					delete base;
				}
				else{
					cout<<"Removal failed"<<endl;
				}
			}else if(first_arg=="3"){
				string key = second_arg;
				Base *base = name.remove(key);
				if(base!=NULL){
					cout<<"Remove record: "<<base->population<<" "<<base->economy<<" "<<*(base->name)<<endl;
					economy.remove(base->economy);
					population.remove(base->population);
					poplist[base->count]=0;
					ecolist[base->count]=0;
					namelist[base->count]="";
					rtime++;
					delete base;
				}else{
					cout<<"Removal failed"<<endl;
				}
			}else
				return 0;
		}else if(category=="list"){
			cin>>first_arg;
			cout<<"list "<<first_arg<<endl;
			if(first_arg=="1"){
				population.inOrderPrint(cout);
			}else if(first_arg=="2"){
				economy.inOrderPrint(cout);
			}else if(first_arg=="3"){
				name.inOrderPrint(cout);
			}else
				return 0;
		}else
			return 0;
	}
	int count_del = count-rtime;
	int x = 0;
	while(count_del>0){
		if(poplist[x]!=0){
			count_del--;
			Base *base = population.search(poplist[x]);
			poplist[x]=0;
			ecolist[x]=0;
			namelist[x]="";
			delete base;
		}
		x++;
	}
}
