#ifndef PERSON_H
#define PERSON_H

#include "account.h"

class Person : public Account
{
private:
    QString last_name;
    QString first_name;
    QString skills;
public:
    Person(QString last_name , QString first_name , QString skills , QString Account_ID , QString Phone_number , QString email);
    QString get_last_name();
    QString get_first_name();
    QString get_skills();

};

#endif // PERSON_H
