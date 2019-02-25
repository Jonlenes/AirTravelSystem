#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;
    class Date
    {
    public:
        Date();
        Date(string time);
        Date(int hours, int minutes);

        int getHours();
        int getMinutes();
        string toString();

        double operator - (Date date);

    private:
        int hours;
        int minutes;
        string time;
    };
#endif // DATE_H
