#include "Date.h"
//#include <QMessageBox>


Date::Date()
{

}

Date::Date(string time) :
    time(time)
{
    int h = (time[0] - 48) * 10 + (time[1] - 48);
    int m = (time[3] - 48) * 10 + (time[4] - 48);

    //QMessageBox::information(NULL, "tESTE", QString::fromStdString(time));

    if(h < 0 || h > 23 || m < 0 || m > 59) throw string("date invalide!");

    this->hours = h;
    this->minutes = m;
}

Date::Date(int hours, int minutes)
{
    if(hours < 0 || hours > 23 || minutes < 0 || minutes > 59) throw string("date invalide!");

    time += hours / 10 + 48;
    time += hours % 10 + 48;
    time += ':';
    time += minutes / 10 + 48;
    time += minutes % 10 + 48;
    time[5] += 0;


    //QMessageBox::information(NULL, "tESTE", QString::fromStdString(time));
}

int Date::getHours()
{
    return this->hours;
}

int Date::getMinutes()
{
    return this->minutes;
}

string Date::toString()
{
    return this->time;
}

double Date::operator - (Date date)
{
    return (this->hours - date.hours) + ((this->minutes - date.minutes) / 60.0);
}
