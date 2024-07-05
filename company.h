#ifndef COMPANY_H
#define COMPANY_H

#include "person.h"
#include "job.h"
#include <vector>

class company
{
private:
    QString company_name;
    std::vector<job> jobs;
    std::vector<Person> employee;
public:
    company(QString company_name);
    QString get_company_name();
    void create_job();
};

#endif // COMPANY_H
