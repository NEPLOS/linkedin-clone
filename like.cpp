#include "like.h"

LIKE::LIKE(QString who_liked_ID , QString Like_ID)
{
    this->who_liked_ID = who_liked_ID;
    this->Like_ID = Like_ID;
}

QString LIKE::get_who_liked_ID()
{
    return who_liked_ID;
}
QString LIKE::get_Like_ID()
{
    return Like_ID;
}
timew LIKE::get_time()
{
    return time;
}
