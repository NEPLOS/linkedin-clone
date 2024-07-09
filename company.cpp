#include "company.h"

company::company(QString company_name)
{
    this->company_name = company_name;
}


QString company::get_company_name()
{
    return company_name;
}
