#include "fill_the_form.h"
#include "ui_fill_the_form.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include <QFileInfo>
#include "QSqlQueryModel"
#include "QMessageBox"
#include "main_page.h"


QString user_mail;

bool dark_mode_fill_the_form = false;

QStringList company = {"google" , "Microsoft" , "amazon" , "apple" , "Samsung" , "IBM" , "Tesla" , "Intel" , "Netflix"  , "Meta" ,
                       "yahoo" , "NVIDIA" , "Visa" , "Adobe" , "Walmart"};

QStringList university = {"sharif" , "amirkabir", "tehran" , "tabriz" , "golestan" , "ferdowsi mashhad" , "isfahan" , "noshirvani" , "athers"};

QStringList jobs = {"Web Developer" , "UI/UX Designer" , "AI/ML Engineer" , "Data Scientist" , "Software Engineer" , "Video Game Developer" ,
                   "AR/VR Developer" , "DataBase Developer" , "DataBase Administrator" , "Backend Developer" , "System Analyst" , "Cloud Engineer"
                   , "Robotic Engineer" , "Computer Support Specialist" , "Cybersecurity Specialist" , "Computer Network Architect"};

bool jobch = false;
bool unich = false;
bool comch = false;


fill_the_form::fill_the_form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fill_the_form)
{
    ui->setupUi(this);

    this->setWindowTitle("Fill the form");

    if(dark_mode_fill_the_form)
    {
        set_color();
    }

    ui->job_box->addItems(jobs);

    ui->uni_box->addItems(university);

    ui->company_box->addItems(company);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("h:/Project/data/linkedin_C.db");
    db.open();


}

fill_the_form::~fill_the_form()
{
    delete ui;
}

void mailmail(QString hmm)
{
    user_mail = hmm;
}

void fill_the_form::on_Done_clicked()
{
    QString fn = ui->first_name_input->text();

    QString ln = ui->last_name_input->text();

    QString date = ui->dateEdit->text();

    QSqlQuery q;

    if(!jobch)
    {
        QString jt = jobs[0];

        q.exec("UPDATE USER SET job='"+jt+"' WHERE email='"+user_mail+"'");
    }

    if(!unich)
    {
        QString ut = university[0];

        q.exec("UPDATE USER SET mahal_tahsil='"+ut+"' WHERE email='"+user_mail+"'");
    }

    if(!comch)
    {
        QString ct = company[0];

        q.exec("UPDATE USER SET company='"+ct+"' WHERE email='"+user_mail+"'");
    }

    if(fn.length() < 1)
    {
        QMessageBox::warning(this,"","enter your first name" , "ok");
    }
    else if(ln.length() < 1)
    {
        QMessageBox::warning(this,"","enter your last name" , "ok");
    }
    else
    {
        q.exec("UPDATE USER SET first_name='"+fn+"' WHERE email='"+user_mail+"'");
        q.exec("UPDATE USER SET last_name='"+ln+"' WHERE email='"+user_mail+"'");
        q.exec("UPDATE USER SET birthday='"+date+"' WHERE email='"+user_mail+"'");

        set_dark_mode_main_page(dark_mode_fill_the_form);

        main_page *k = new main_page;
        k->show();
        this->close();
    }

}

void fill_the_form::on_company_box_activated(int index)
{
    comch = true;

    QSqlQuery q;

    QString c = company[index];

    q.exec("UPDATE USER SET company='"+c+"' WHERE email='"+user_mail+"'");
}


void fill_the_form::on_job_box_activated(int index)
{
    jobch = true;

    QSqlQuery q;

    QString j = jobs[index];

    q.exec("UPDATE USER SET job='"+j+"' WHERE email='"+user_mail+"'");
}


void fill_the_form::on_uni_box_activated(int index)
{
    unich = true;

    QSqlQuery q;

    QString u = university[index];

    q.exec("UPDATE USER SET mahal_tahsil='"+u+"' WHERE email='"+user_mail+"'");
}

void set_dark_mode_fill_the_form(bool n)
{
    dark_mode_fill_the_form = n;
}

void fill_the_form::set_color()
{
    fill_the_form::setStyleSheet("background-color: rgb(66, 69, 73);");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_4->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_5->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_6->setStyleSheet("color: rgb(255, 255, 255);");
    ui->first_name_input->setStyleSheet("color: rgb(255, 255, 255);");
    ui->last_name_input->setStyleSheet("color: rgb(255, 255, 255);");
    ui->job_box->setStyleSheet("color: rgb(255, 255, 255);");
    ui->company_box->setStyleSheet("color: rgb(255, 255, 255);");
    ui->uni_box->setStyleSheet("color: rgb(255, 255, 255);");
    ui->dateEdit->setStyleSheet("color: rgb(255, 255, 255);");
    ui->Done->setStyleSheet("color: rgb(0, 0, 0);");
    ui->Done->setStyleSheet("background-color: rgb(255, 255, 255);");
}
