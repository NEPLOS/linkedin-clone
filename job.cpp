#include "job.h"

job::job(QString salary,QString job_name,QString company_name,QString skill_required,QString workplace_type,QString location,QString type)
{
    this->salary = salary;
    this->job_name = job_name;
    this->company_name = company_name;
    this->skill_required = skill_required;
    this->workplace_type = workplace_type;
    this->location = location;
    this->type = type;
}


QString job::get_salary()
{
    return salary;
}
QString job::get_job_name()
{
    return  job_name;
}
QString job::get_company_name()
{
    return company_name;
}
QString job::get_skill_required()
{
    return skill_required;
}
QString job::get_workplace_type()
{
    return workplace_type;
}
QString job::get_location()
{
    return location;
}
QString job::get_type()
{
    return type;
}
void job::set_location(QString new_location)
{
    location = new_location;
}
void job::set_salary(QString new_salary)
{
    salary = new_salary;
}


