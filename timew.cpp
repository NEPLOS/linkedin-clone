#include "timew.h"

timew::timew()
{
    QDateTime current = QDateTime::currentDateTime();


    second = QString::number(current.time().second());
    minute = QString::number(current.time().minute());
    hour = QString::number(current.time().hour());
    day = QString::number(current.date().day());
    month = QString::number(current.date().month());
    year = QString::number(current.date().year());
}

QString timew::get_second()
{
    return second;
}
QString timew::get_minute()
{
    return minute;
}
QString timew::get_hour()
{
    return hour;
}
QString timew::get_day()
{
    return day;
}
QString timew::get_month()
{
    return month;
}
QString timew::get_year()
{
    return year;
}
