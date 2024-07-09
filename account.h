#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <vector>
#include "post.h"

class Account
{

    QString Account_ID;
    QString Phone_number;
    QString email;
    std::vector<std::string> Connections;
    std::vector<std::string> following;
    std::vector<Post> posts;

public:
    Account( QString Account_ID,QString Phone_number , QString email);
    QString get_Account_ID();
    QString get_Phone_number();
    QString get_email();
};

#endif // ACCOUNT_H
