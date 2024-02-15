#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>
#include <cctype>
#include <stdio.h>
#include <ctime>
#include <iomanip>
using namespace std;

struct Variables
{
    double Fxx;
    double a;
    double b;
    double x_n;
    double x;
    double x_pred;
    double epslion;
    double Fa;
    double Fb;
    double Fdxa2;
    double Fdxb2;
    double Fdxa1;
    double Fdxb1;
    double newPer;
    double newPerF;
    string Fx;
    string Fdx1;
    string Fdx2;
    int count = 0;
    int method = 0;
};
static void Input(Variables& per) {
   // cout << "Exeple :\nx^3-x+1 \n"<<"Cos(x)+2*x-3  => 2*x-3+Cos(x)" <<"\n" << endl;
    if (per.method != 2) {
        cout << "Exeple : \nf(x) = x^3-3*x+5 \nf'(x)=3*x^2-3\nf''(x) = 6*x \n a = -2.5 \n b = -2\n Epsilon = 0.001" << endl;
        cout << "\n\n\n";

        cout << "Enter f(x) = ";
        cin >> per.Fx;

        if (per.method != 1) {
            cout << "Enter f'(x) = ";
            cin >> per.Fdx1;

            cout << "Enter f''(x) = ";
            cin >> per.Fdx2;
        }

        cout << "Enter a = ";
        cin >> per.a;

        cout << "Enter b = ";
        cin >> per.b;

        cout << "Enter Epsilon = ";
        cin >> per.epslion;
        cout << "\n\n\n";
    }

}
static void ChoseyOurChampion(Variables& per) {
    cout << "Please choose a method : \n 1:Dichotomy\n 2:Simple iteration \n 3:Chords\n 4:NewtonNewton\n=> ";
    cin >> per.method;
    cout << endl;

}
vector<int> FindAllYmnoj(const string& input) {
    vector<int> digitIndices3;
    for (int i = 0; i < input.length(); ++i) {
        if (input[i] == '*') {
            digitIndices3.push_back(i);
        }
    }
    return digitIndices3;
}
vector<int> Findop(const string& input) {
    vector<int> digitIndices1;
    for (int i = 0; i < input.length(); ++i) {

        if (isdigit(input[i])) {

        }
        else if (input[i] != '.')
        {
            digitIndices1.push_back(i);
        }
    }
    return digitIndices1;
}
vector<double> splitExpression(string& expression) {
    vector<double> elements;
    string currentElement = "";

    for (char& c : expression) {
        if (isdigit(c) || c == '.' || c == '-') {
            currentElement += c;
        }
        else {
            if (!currentElement.empty()) {
                // Преобразование строки в тип double и добавление в вектор
                elements.push_back(stod(currentElement));
                currentElement = "";
            }
        }
    }

    if (!currentElement.empty()) {
        elements.push_back(stod(currentElement));
    }

    return elements;
}
static string Razlojenie(string fx) {

    int i = 0;
    int ii = 0;
    string zxc = fx;
    const char* str = zxc.c_str();
    const size_t length = strlen(str);
    const int ss = strlen(str);
    char charArray[100];
    
    strcpy_s(charArray, str);
    while (i < length) {
        if (str[i] == '^')
        {
            int zxc = str[i + 1] - '0';
            for (int f = 0; f < zxc - 1;f++) {
                charArray[ii] = '*';
                ii++;
                charArray[ii] = 'x';
                ii++;
            }
            i++; ii--;
        }
        else
        {
            charArray[ii] = str[i];
        }
        i++;
        ii++;
    }
    charArray[ii] = '\0';
    return string(charArray);
    
}
static double Slojenye(string stroka) {
    string zxc = stroka;
    istringstream expression_stream(zxc);
    double result = 0;
    char op;
    double operand;
    expression_stream >> ws; // Skip whitespaces
    if (isdigit(expression_stream.peek()) || expression_stream.peek() == '-') {
        expression_stream >> operand;
        result = operand;
    }
    while (expression_stream >> op >> operand) {

        if (op == '+') {
            result += operand;
        }
        else if (op == '-') {
            result -= operand;
        }
    }
    //cout << result << endl;
    return result;
}
static double f(string stroka, double x) {
    string zxc = Razlojenie(stroka);
    size_t cosDash = zxc.find("Cos(x)");
    while (cosDash != string::npos) {
        zxc.replace(cosDash, 6, to_string(cos(x)));
        cosDash = zxc.find("Cos(x)", cosDash + 1);
    }

    size_t sinDash = zxc.find("Sin(x)");
    while (sinDash != string::npos) {
        zxc.replace(sinDash, 6, to_string(sin(x)));
        sinDash = zxc.find("Sin(x)", sinDash + 1);
    }

    size_t tgDash = zxc.find("tg(x)");
    while (tgDash != string::npos) {
        zxc.replace(tgDash, 5, to_string(tan(x)));
        tgDash = zxc.find("tg(x)", tgDash + 1);
    }

    size_t pos = zxc.find("x");
    while (pos != string::npos) {
        zxc.replace(pos, 1, to_string(x));
        pos = zxc.find("x", pos + 1);
    }

    size_t posDash = zxc.find("--");
    while (posDash != string::npos) {
        zxc.replace(posDash, 2, "+");
        posDash = zxc.find("--", posDash + 1);
    }

    //cout << zxc << "\n\n";

    
    
    char OperMas[100];                  // массив цифр
    double ciferkiMas[100];             // массив операторов
    int OperMasIndex[100];              // Массив индексов цифр
    int ciferkiMasIndex[100];           // Массив индексов операторов
    int AllYmnojIndex[100];             // Масств Индексов умножения 
    vector<double> elements = splitExpression(zxc);
    int numi = 0;
    for (double& element : elements) {
        ciferkiMas[numi] = element;
        //cout << ciferkiMas[numi] << "  ";
    }
    //cout << endl;
    numi = 0;

    vector<int> indices = Findop(zxc);

    for (int index : indices) {
        ciferkiMasIndex[numi] = index;
        //cout << ciferkiMasIndex[numi] << " ";
        numi++;
    }
    ciferkiMasIndex[numi] = '\0';
   
    //cout << endl;
    numi = 0;

    //cout << "\t\n All(index) * = ";
    vector<int> AllYmnoj = FindAllYmnoj(zxc);
    int yazaebalsiapishyetoeje3dna = 0;
    for (int index : AllYmnoj) {
        AllYmnojIndex[numi] = index;
        //cout << AllYmnojIndex[numi] << " ";
        numi++;
        yazaebalsiapishyetoeje3dna++;
    }
   
    
    if (yazaebalsiapishyetoeje3dna == 0) {
        double result = Slojenye(zxc);
        return result;
    }

    //cout << " \n\n\n\ " << endl;
    numi = 0;

    double newproiz;
    int proverka = size(AllYmnoj);
    //cout << proverka;
    int doge = 0;
    int nazhalo = 0;
    int konez = 0;
    int count = 0;
    size_t test;
        try {
            size_t test = AllYmnoj[doge];
            while (test != string::npos) {
                //cout << "\t \t \t count = " << count << endl;
                
                //cout << "pervyi element  - " << ciferkiMasIndex[0] << " \t perv  * = " << test << endl;
                for (int a = 0; a < size(AllYmnoj);a++) {
                    if (test == AllYmnojIndex[a]) {
                        //cout << "Ymnojene v tochke " << AllYmnojIndex[a] << endl;
                    }
                    //cout << size(elements) << endl;
                    for (int aa = 0; aa < size(elements);aa++) {
                        //cout << zxc[ciferkiMasIndex[0]] << endl;
                        //cout << zxc[ciferkiMasIndex[1]] << endl;
                        if (ciferkiMasIndex[0] == test) {
                            if (zxc[ciferkiMasIndex[0 + 1]] == '-') {
                                nazhalo = 0;
                                konez = ciferkiMasIndex[1+1] - 1;
                            }
                            else {
                                konez = ciferkiMasIndex[1] - 1;
                                nazhalo = 0;
                            }
                        }

                        else if (test == ciferkiMasIndex[aa]) {
                            
                             if (zxc[ciferkiMasIndex[0]] == '-' && zxc[ciferkiMasIndex[1]]=='*') {
                                konez = ciferkiMasIndex[aa + 2] - 1;
                                nazhalo = 0;
                            }
                             else if(zxc[test + 1]=='-') {
                                 nazhalo = ciferkiMasIndex[aa - 1] + 1;
                                 konez = ciferkiMasIndex[aa + 2] - 1;
                             }
                            else {
                                nazhalo = ciferkiMasIndex[aa - 1] + 1;
                                konez = ciferkiMasIndex[aa + 1] - 1;
                            }


                        }

                        // cout << aa << endl;

                    }
                    /*cout << test << endl;
                    cout << " na4alo  = " << nazhalo << endl;
                    cout << " konez = " << konez << endl;
                    cout << "indices = " << indices[0] << endl;
                    cout << "Test = " << test << endl;
                    cout << " ciferkiMasIndex[0] = " << ciferkiMasIndex[0] << endl;*/
                    string secondd = zxc.substr(test + 1, konez - test);
                    //cout << zxc<<endl;
                    string firstt = zxc.substr(nazhalo, test - nazhalo);
                    //cout << " \t perv peremen = " << firstt << " \t secon peremen = " << secondd << "\n\n";

                    double yra = stod(secondd) * stod(firstt);

                   //cout << zxc << endl;

                    zxc.replace(nazhalo, konez - nazhalo + 1, to_string(yra));
                    size_t posDash = zxc.find("--");
                    while (posDash != string::npos) {
                        zxc.replace(posDash, 2, "+");
                        posDash = zxc.find("--", posDash + 1);
                    }
                    //cout << zxc << endl;
                    vector<double> elements = splitExpression(zxc);

                    for (double& element : elements) {
                        ciferkiMas[numi] = element;
                        //cout << ciferkiMas[numi] << " ";
                        numi++;
                    }
                    //cout << endl;
                    numi = 0;

                    vector<int> AllYmnoj = FindAllYmnoj(zxc);

                    numi = 0;
                    for (int index : AllYmnoj) {
                        AllYmnojIndex[numi] = index;
                        //cout << AllYmnojIndex[numi] << " ";
                        numi++;
                    }
                    vector<int> indices = Findop(zxc);
                    numi = 0;
                    for (int index : indices) {
                        ciferkiMasIndex[numi] = index;
                        //cout << index << " ";
                        numi++;
                    }
                    //cout << size(AllYmnoj) << endl;
                    if (size(AllYmnoj) != 0) {
                        test = AllYmnoj[doge];
                    }
                    int numi = 0;
                    count++;
                    //cout << proverka << " " << count;
                    if (count == proverka) {
                        break;
                    }

                }



                break;
            }
        }
        catch(string exepsion){
            double result = Slojenye(zxc);
            return result;
        }
        
    
    //cout << zxc << endl;
      double result = Slojenye(zxc);
      return result;
}

static void FindF(Variables& per) {
   
    per.Fa = f(per.Fx, per.a);
    per.Fb = f(per.Fx, per.b);
    //cout << "\n\n\n\n\n\n\n " << per.Fdx2;
    per.Fdxa1 = f(per.Fdx1, per.a);
    per.Fdxb1 = f(per.Fdx1, per.b);
    per.Fdxa2 = f(per.Fdx2, per.a);
    per.Fdxb2 = f(per.Fdx2, per.b);
}

int main()
{
    Variables per;
    ChoseyOurChampion(per);
    Input(per);
    clock_t t0 = clock();

    FindF(per);
    system("cls");
    cout << "F(a) = " << per.Fa << "\nF(b) = " << per.Fb << endl;;

    switch (per.method)
    {
    case 1:
        cout << "\n"
            << setw(6) << "Count" << " "
            << "| " << setw(10) << "Fa" << " "
            << "| " << setw(10) << "A" << " "
            << "| " << setw(10) << "B" << " "
            << "| " << setw(10) << "Fb" << " "
            << "| " << setw(10) << "C" << " "
            << "| " << setw(10) << "Fc" << " "
            << "| " << setw(10) << "B-A" << "\n";

        while (fabs(per.a - per.b) > per.epslion)
        {
            per.x = (per.a + per.b) / 2;
            per.Fxx = f(per.Fx, per.x);
            if (per.count > 0)
            {
                if ((per.a / per.Fxx) > (per.b / per.Fxx))
                {
                    per.a = per.x;
                }
                else
                {
                    per.b = per.x;
                }

            }
            per.Fa = f(per.Fx, per.a);
            per.Fb = f(per.Fx, per.b);

            cout << setw(6) << per.count << " | "
                << setw(10) << fixed << setprecision(3) << per.Fa << " | "
                << setw(10) << fixed << setprecision(3) << per.a << " | "
                << setw(10) << fixed << setprecision(3) << per.b << " | "
                << setw(10) << fixed << setprecision(3) << per.Fb << " | "
                << setw(10) << fixed << setprecision(3) << per.x << " | "
                << setw(10) << fixed << setprecision(3) << per.Fxx << " | "
                << setw(10) << fixed << setprecision(3) << (per.b - per.a)
                << endl;
            per.count++;
        }
        cout << "Otvet:" << "\n" << "c= " << per.x;
        break;
    case 2:


        cout << "Temporarily not working ;(";



        break;
    case 3:
        if (per.Fa > 0 || per.Fdxa2 < 0) {
            per.x_pred = per.a;
            per.newPer = per.b;
            per.newPerF = per.Fb;
        }
        else {
            per.x_pred = per.b;
            per.newPer = per.a;
            per.newPerF = per.Fa;
        }
        do {
            if (per.count != 0) {
                per.x_pred = per.x_n;
            }
            double qqx = f(per.Fx, per.x_pred);
            
            per.x_n = per.x_pred - (qqx * (per.x_pred - per.newPer) / (f(per.Fx, per.x_pred) - f(per.Fx, per.newPer)));
            per.Fxx = f(per.Fx, per.x_n);
               if (abs(per.x_n - per.x_pred) >= per.epslion) {
                   per.count++;
                cout << setw(5) << per.count << " | "
                    << setw(10) << fixed << setprecision(4) << per.x_n << " | "
                    << setw(10) << fixed << setprecision(4) << per.Fxx << " | "
                    << endl;
            }
            
        } while (abs(per.x_n - per.x_pred) >= per.epslion);
        cout << "ANSWER X(" << per.count << ")= " << per.x_n;
        break;
    case 4:
        if (per.Fa > 0 || per.Fdxa2 < 0) {
            per.x_pred = per.a;
        }
        else {
            per.x_pred = per.b;
        }
        cout << setw(2) << "count" << " | "
            << setw(10) << fixed << setprecision(4) << "x" << " | "
            << setw(10) << fixed << setprecision(4) << "F(x)" << " | "
            << setw(10) << fixed << setprecision(4) << "Epsilon"
            << endl;
        do {
            if (per.count != 0) {
                per.x_pred = per.x_n;

            }

            per.x_n = per.x_pred - (f(per.Fx, per.x_pred) / f(per.Fdx1, per.x_pred));
            per.Fxx = f(per.Fx, per.x_n);
            double mmmm = f(per.Fx, per.x_n) / f(per.Fdx1, per.x_n);
            
            if (abs(per.x_n - per.x_pred) >= per.epslion){
                cout << setw(5) << per.count << " | "
                    << setw(10) << fixed << setprecision(4) << per.x_n << " | "
                    << setw(10) << fixed << setprecision(4) << per.Fxx << " | "
                    << setw(10) << fixed << setprecision(4) << mmmm
                    << endl;
                      }

        } 
        while (abs(per.x_n - per.x_pred) >= per.epslion);
        cout << "ANSWER X(" << per.count << ")= " << per.x_n;
        break;
    }
    
    
    clock_t t1 = clock();
    cout << "\n\ttime: " << (double)(t1 - t0) / CLOCKS_PER_SEC << endl;
    int sdgdfg;
    system("PAUSE");
    cin >> sdgdfg;
    return 0;
}








