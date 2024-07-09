#include "account.h"

Account::Account( QString Account_ID,QString Phone_number , QString email)
{
    this->Account_ID = Account_ID;
    this->Phone_number = Phone_number;
    this->email = email;
}

QString Account::get_Account_ID()
{
    return Account_ID;
}
QString Account::get_Phone_number()
{
    return Phone_number;
}
QString Account::get_email()
{
    return email;
}
