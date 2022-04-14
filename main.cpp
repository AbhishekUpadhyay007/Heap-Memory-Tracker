#include <iostream>
#include "./include/heaptracker.h"

using namespace std;

class Employee{
    public:
        string name;

        Employee(){
            
        }

        Employee(string name){
            this->name = name;
        }

        string getName(){
            return name;
        }    
};

int main(){

    heap_track_init();

    Employee * e1 = new Employee;
    Employee * e2 = new Employee("Abhishek");
    Employee * e3 = new Employee("Abhishek");

    float * f = new float;
    
     delete e1;
     delete e2;
     delete e3;
     delete f;    
    heap_track_stats();

}
