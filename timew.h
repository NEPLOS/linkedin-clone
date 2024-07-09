#ifndef TIMEW_H
#define TIMEW_H

#include <QString>
#include <QTime>
#include <QDateTime>

class timew
{
    QString year;
    QString month;
    QString day;
    QString hour;
    QString minute;
    QString second;


public:
    timew();
    QString get_second();
    QString get_minute();
    QString get_hour();
    QString get_day();
    QString get_month();
    QString get_year();
};


#endif // TIMEW_H
