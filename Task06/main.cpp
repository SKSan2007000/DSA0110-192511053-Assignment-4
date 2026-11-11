#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;
class Vehicle{
protected:string reg;double daily;bool rented=false;
public:Vehicle(string r,double d):reg(r),daily(d){}virtual ~Vehicle()=default;
virtual double charge(int days)const=0;virtual string kind()const=0;
bool rent(){if(rented)return false;rented=true;return true;}
double returnVehicle(int daysLate){rented=false;return daysLate*200.0;}
void show()const{cout<<kind()<<" "<<reg<<" daily="<<daily<<" rented="<<boolalpha<<rented<<'\n';}
};
class Bicycle:public Vehicle{public:Bicycle(string r,double d):Vehicle(r,d){}double charge(int n)const override{return daily*n;}string kind()const override{return "Bicycle";}};
class TwoWheeler:public Vehicle{double fuel;public:TwoWheeler(string r,double d,double f):Vehicle(r,d),fuel(f){}double charge(int n)const override{return daily*n+(fuel<2?100:0);}string kind()const override{return "TwoWheeler";}};
class Car:public Vehicle{int seats;public:Car(string r,double d,int s):Vehicle(r,d),seats(s){}double charge(int n)const override{return daily*n+(seats>5?300:0);}string kind()const override{return "Car";}};
class ElectricCar:public Vehicle{double kwh;public:ElectricCar(string r,double d,double k):Vehicle(r,d),kwh(k){}double charge(int n)const override{return daily*n+kwh*8;}string kind()const override{return "ElectricCar";}};
class ElectricBus:public Vehicle{int capacity;public:ElectricBus(string r,double d,int c):Vehicle(r,d),capacity(c){}double charge(int n)const override{return daily*n+capacity*20;}string kind()const override{return "ElectricBus";}};
int main(){vector<unique_ptr<Vehicle>> fleet;fleet.push_back(make_unique<Bicycle>("BI-01",100));fleet.push_back(make_unique<TwoWheeler>("TW-02",250,1));fleet.push_back(make_unique<Car>("CA-03",1200,7));fleet.push_back(make_unique<ElectricCar>("EV-04",1500,40));fleet.push_back(make_unique<ElectricBus>("EB-05",3000,30));for(auto& v:fleet){v->rent();v->show();cout<<"3-day charge: "<<v->charge(3)<<", late fee: "<<v->returnVehicle(1)<<'\n';}}
