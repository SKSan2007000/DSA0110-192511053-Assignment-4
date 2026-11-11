#include <iostream>
#include <string>
using namespace std;
class Address{string city;int pin;public:Address(string c,int p):city(c),pin(p){}string show()const{return city+"-"+to_string(pin);}};
class Course{string name;public:Course(string n):name(n){}string show()const{return name;}};
class Person{protected:string name;int age;Address home;public:Person(string n,int a,string c,int p):name(n),age(a),home(c,p){cout<<"Person constructed\n";}virtual ~Person(){cout<<"Person destroyed\n";}};
class Student:public Person{long long reg;Course course;public:Student(string n,int a,long long r,string c,int p,string co):Person(n,a,c,p),reg(r),course(co){cout<<"Student constructed\n";}~Student(){cout<<"Student destroyed\n";}void show()const{cout<<reg<<" "<<name<<" ("<<age<<") "<<home.show()<<" "<<course.show()<<'\n';}};
int main(){{Student s("Kavya",19,192311001,"Salem",636001,"CSE");s.show();}cout<<"Block ended\n";}
