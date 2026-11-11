#include <iostream>
#include <string>
using namespace std;
class Person{
protected:string name;int id;string phone;
public:Person(string n,int i,string p):name(n),id(i),phone(p){}
};
class Student:virtual public Person{
protected:string programme;double cgpa;
public:Student(string n,int i,string p,string pr,double c):Person(n,i,p),programme(pr),cgpa(c){}
};
class Staff:virtual public Person{
protected:string department;double salary;
public:Staff(string n,int i,string p,string d,double s):Person(n,i,p),department(d),salary(s){}
};
class ResearchScholar:public Student{
    double fellowship;
public:
    ResearchScholar(string n,int i,string p,string pr,double c,double f):Person(n,i,p),Student(n,i,p,pr,c),fellowship(f){}
    void showFellowship()const{cout<<"Fellowship: "<<fellowship<<'\n';}
};
class TeachingAssistant:public Student,public Staff{
public:TeachingAssistant(string n,int i,string p,string pr,double c,string d,double s):
Person(n,i,p),Student(n,i,p,pr,c),Staff(n,i,p,d,s){}
void show()const{cout<<name<<" "<<id<<" "<<programme<<" "<<department<<" "<<cgpa<<" "<<salary<<'\n';}
};
int main(){TeachingAssistant t("Kavya",101,"9876543210","CSE",8.5,"IT",25000);t.show();}
