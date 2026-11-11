#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Staff {
protected: string name; int id; double basic;
public: Staff(string n,int i,double b):name(n),id(i),basic(b){}
virtual ~Staff()=default; virtual double pay()const=0;
void show()const{cout<<name<<" ("<<id<<"): "<<pay()<<'\n';}
};
class Professor:public Staff{
double research;
public:Professor(string n,int i,double b,double r):Staff(n,i,b),research(r){}
double pay()const override{return basic+basic*0.42+research;}
};
class LabAssistant:public Staff{
public:LabAssistant(string n,int i,double b):Staff(n,i,b){}
double pay()const override{return basic+basic*0.42;}
};
class GuestFaculty:public Staff{
double hours,rate;
public:GuestFaculty(string n,int i,double h,double r):Staff(n,i,0),hours(h),rate(r){}
double pay()const override{return hours*rate;}
};
int main(){vector<Staff*> v={new Professor("Anu",1,50000,5000),new LabAssistant("Bala",2,30000),new GuestFaculty("Ravi",3,20,1000)};
for(Staff* s:v) { s->show(); }
for(Staff* s:v) { delete s; }}
