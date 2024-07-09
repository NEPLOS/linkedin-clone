#ifndef JOB_H
#define JOB_H

#include <qstring.h>

class job
{
private:
    QString salary;
    QString job_name;
    QString company_name;
    QString skill_required;
    QString workplace_type;
    QString location;
    QString type;
public:
    job(QString salary,QString job_name,QString company_name,QString skill_required,QString workplace_type,QString location,QString type);
    QString get_salary();
    QString get_job_name();
    QString get_company_name();
    QString get_skill_required();
    QString get_workplace_type();
    QString get_location();
    QString get_type();
    void set_location(QString new_location);
    void set_salary(QString new_salary);
};

#endif // JOB_H
