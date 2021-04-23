#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>

using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main()
{
    cout << "Welcome to our conversions program!" << endl;

    ofstream File("File.txt");

    File << "1 km = 1000 m" << endl;
    File << "1 m = 100 cm" << endl;
    File << "1 kg = 1000 g" << endl;
    File << "1 ton = 1000 kg" << endl;
    File << "1 hour = 60 min" << endl;
    File << "1 min = 60 sec" << endl;
    File << "1 USD = 3.33 ILS ";
    File.close();

    string file = "File.txt";
    ifstream units_MyFile{file};
    NumberWithUnits::read_units(units_MyFile);
    usleep(100000);
    cout << endl
         << "This is the types of conversions:" << endl
         << endl;

    ifstream MyReadFile(file);

    cout << "{km, m, cm}" << endl;
    usleep(100000);
    cout << "{ton, kg, g}" << endl;
    usleep(100000);
    cout << "{hour, min, sec}" << endl;
    usleep(100000);
    cout << "{USD, ILS}" << endl;
    usleep(100000);
    cout << endl
         << "you can create objects and do on them operators functions" << endl;
    cout << "create 2 objects: <here write the type from the file>[<here write the num>]" << endl;
    NumberWithUnits a{1, "m"};
    NumberWithUnits b{1, "m"};
    cin >> a >> b;
    cout<<endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout<<endl;
    cout << "choose one of the option: \n1:/a+b \n2:a-b \n3:a+=b \n4:a-=b \n5:a*num \n6:b*num" << endl;
    int num;
    cin >> num;
    NumberWithUnits temp = 1 * a;
    double x = 0;
    try
    {
        switch (num)
        {
        case 1:
            cout << a << "+" << b << "=" << (a + b) << endl;
            break;

        case 2:
            cout << a << "-" << b << "=" << (a - b) << endl;
            break;
        case 3:
            (a += b);
            cout << temp << "+=" << b << "-> a=" << a << endl;
            break;
        case 4:
            (a -= b);
            cout << temp << "-=" << b << "-> a=" << a << endl;
            break;
        case 5:
            cout << "enter the number you want to multiply by ";
            cin >> x;
            cout << a << "*" << x << "=" << (a * x) << endl;

            break;
        case 6:
            cout << "enter the number you want to multiply by ";
            cin >> x;
            cout << b << "*" << x << "=" << (b * x) << endl;
            break;

        default:
            cin >> num;
        }
    }
    catch (exception &ex)
    {
        cout << ex.what() << endl;
        cout << "exit" << endl;
    }
    return 0;
}