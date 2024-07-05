#ifndef LIKE_H
#define LIKE_H

#include "timew.h"

class LIKE
{

    QString who_liked_ID;

    QString Like_ID;

    timew time;

public:
    LIKE(QString who_liked_ID , QString Like_ID);
    QString get_who_liked_ID();
    QString get_Like_ID();
    timew get_time();
};

#endif // LIKE_H
