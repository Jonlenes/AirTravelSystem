#include "Date.h"
//#include <QMessageBox>
using namespace myTime;

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

Date::Date(int hours, int minutes) :
    hours(hours), minutes(minutes)
{
    if(h < 0 || h > 23 || m < 0 || m > 59) throw string("date invalide!");

    time[0] = hours / 10 + 48;
    time[1] = hours % 10 + 48;
    time[2] = ':';
    time[3] = minutes / 10 + 48;
    time[4] = minutes % 10 + 48;

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
