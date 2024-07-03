#include "person.h"

Person::Person(QString last_name , QString first_name , QString skills , QString Account_ID , QString Phone_number , QString email)
    : Account(Account_ID,Phone_number,email)
{
    this->last_name = last_name;
    this->first_name = first_name;
    this->skills = skills;
}

QString Person::get_last_name()
{
    return last_name;
}

QString Person::get_first_name()
{
    return first_name;
}

QString Person::get_skills()
{
    return skills;
}
