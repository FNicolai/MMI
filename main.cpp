#include "graphcontroller.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphView w;

    w.show();

    return a.exec();
}


// ##### CONVENTION #####

//class A {
//  void foo(int age_) { //parameter
//    int age = 18; //local scope
//    if (age_ > age) cout << legal << endl;
//  }
//  int _age; //member
//};

//In the above example:

//    _variable - means this is a class member variable
//    variable_ - means this is a parameter to a function
//    variable - means this is just a regular variable local to the function scope
