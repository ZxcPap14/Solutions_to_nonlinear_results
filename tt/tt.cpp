#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
struct Peremen
{
    double epsilon = 0.001;
    double x = 0.5;
    double xk;
    double eps;
    int count = 0;
};

static double x(double result)
{
    return (1-log10(result)-result);
}



int main()
{
    Peremen per;
    cout << setw(2) << " count" << " | "
        << setw(10) << fixed << setprecision(4) << "X(K)" << " | "
        << setw(10) << fixed << setprecision(4) << "X(k)-X(k-1)" << "| "
        << endl;
    do {
        if (per.count != 0) {
            per.xk = per.x; 
            per.x = x(per.x);
            per.eps = abs(per.xk - per.x);
            //cout << per.xk << " " << per.x<< " "<<per.eps<<endl;
            cout << setw(6) << per.count << " | "
                << setw(10) << fixed << setprecision(4) << per.x << " | "
                << setw(10) << fixed << setprecision(4) << per.eps << " | "
                << endl;
           
            
        }
        else
        {
            //cout << per.xk;
            cout << setw(6) << per.count << " | "
                << setw(10) << fixed << setprecision(4) << per.x << " | "
                << setw(10) << fixed << setprecision(4) << "-" << " | "
                << endl;
        }
        per.count++;



    } 
    while (abs(per.eps)>=per.epsilon);
    
    return 0;
}