#include "job_form_company.h"
#include "job_form.h"
#include "ui_job_form_company.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "job_form_company.h"
#include "QSqlQuery"
#include "job_form.h"
#include <qpixmap.h>
#include "QSqlQueryModel"
#include "my_network.h"
#include "QSqlError"
#include "profile.h"
#include <qpixmap.h>
#include "error.h"
#include <qfile.h>
#include "make_job.h"
#include <qfileinfo.h>
#include "welcome.h"
#include <qdebug.h>
#include <QDir>
#include "main_page.h"
#include "message_contact.h"
#include "QMessageBox"
#include "view_profile.h"

QString ma_com_ID;
QString current_user;

QString Glonal_job_title = "none";
QString Glonal_first_name = "none";
QString Glonal_last_name = "none";
QString Glonal_skills = "none";
QString Glonal_bio = "none";
QString Glonal_email = "none";
QString Glonal_salary = "none";
QString Glonal_company = "none";

void search_job_form_com();

job_form_company::job_form_company(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::job_form_company)
{
    ui->setupUi(this);

    ui->mod->addItem("Normal user");
    ui->mod->addItem("company");
    ui->mod->setCurrentIndex(1);

    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton_2->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));

    QString database_path = QDir::currentPath() + "/linkedin_C.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main_db");
    db.setDatabaseName(database_path);

    if (db.open())
    {
        QSqlQuery q(db);
        QString job_page_com_ID;
        if (q.exec("SELECT IDC FROM userdb") && q.first())
        {
            job_page_com_ID = q.value(0).toString();
            ma_com_ID = job_page_com_ID;
        }

        QString iconPath = "content/" + job_page_com_ID + "/res/pic/0.png";
        if (!QFile::exists(iconPath))
        {
            iconPath = "content/" + job_page_com_ID + "/res/pic/0.jpg";
        }
        ui->me_button->setIcon(QIcon(iconPath));
    }
    else
    {
        qDebug() << "faild to open database:" << db.lastError().text();
    }

    search_job_form_com();

    ui->email->setText(Glonal_email);
    ui->bio->setText(Glonal_bio);
    ui->name->setText(Glonal_first_name);
    ui->last_name->setText(Glonal_last_name);
    ui->skills->setText(Glonal_skills);
    ui->job_exp->setText(Glonal_company);
    ui->job_title->setText(Glonal_job_title);

}

job_form_company::~job_form_company()
{
    delete ui;
}

void job_form_company::on_mod_currentIndexChanged(int index)
{
    if (index == 0)
    {
        job_form* j = new job_form;
        this->close();
        j->show();
    }
}

void job_form_company::on_pushButton_clicked()
{
    make_job* d = new make_job;
    this->close();
    d->show();
}

void job_form_company::on_Accept_clicked()
{
    QString SALARY;

    QSqlDatabase data_base_job_company = QSqlDatabase::addDatabase("QSQLITE", "job_db");
    data_base_job_company.setDatabaseName(QDir::currentPath() + "/job.db");

    if (data_base_job_company.open())
    {
        QSqlQuery q(data_base_job_company);
        if (q.exec("SELECT salary FROM USER WHERE job_title='" + Glonal_job_title + "'") && q.first())
        {
            SALARY = q.value("salary").toString();
        }
        else
        {
            qDebug() << "Can't select salary FROM USER:" << q.lastError().text();
        }
    }
    else
    {
        qDebug() << "faild to open job database:" << data_base_job_company.lastError().text();
    }


    QSqlDatabase data_base_job_company_employee = QSqlDatabase::addDatabase("QSQLITE", "employee_db");
    data_base_job_company_employee.setDatabaseName(QDir::currentPath() + "/content/" + ma_com_ID + "/employee.db");

    if (data_base_job_company_employee.open())
    {
        QSqlQuery employee(data_base_job_company_employee);

        employee.prepare("INSERT INTO emp(user_id, job_title, first_name, last_name, salary, email) VALUES (:user_id, :job_title, :first_name, :last_name, :salary, :email)");
        employee.bindValue(":user_id", current_user);
        employee.bindValue(":job_title", Glonal_job_title);
        employee.bindValue(":first_name", Glonal_first_name);
        employee.bindValue(":last_name", Glonal_last_name);
        employee.bindValue(":salary", SALARY);
        employee.bindValue(":email", Glonal_email);

        if (!employee.exec())
        {
            qDebug() << "Can't INSERT INTO emp:" << employee.lastError().text();
        }
    }
    else
    {
        qDebug() << "Failed to open employee database:" << data_base_job_company_employee.lastError().text();
    }


    QSqlDatabase temp_data_base = QSqlDatabase::addDatabase("QSQLITE", "personal_db");
    temp_data_base.setDatabaseName(QDir::currentPath() + "/content/" + current_user + "/job.db");

    if (temp_data_base.open())
    {
        QSqlQuery f(temp_data_base);
        if (!f.exec("DELETE FROM job_db WHERE job_title='" + Glonal_job_title + "'"))
        {
            qDebug() << "Can't DELETE FROM pending:" << f.lastError().text();
        }
    }
    else
    {
        qDebug() << "Failed to open job database:" << temp_data_base.lastError().text();
    }


    QSqlDatabase jooooob = QSqlDatabase::addDatabase("QSQLITE", "job_db_delete");
    jooooob.setDatabaseName(QDir::currentPath() + "/job.db");

    if (jooooob.open())
    {
        QSqlQuery d(jooooob);
        if (!d.exec("DELETE FROM USER WHERE job_title='" + Glonal_job_title + "'"))
        {
            qDebug() << "Can't DELETE FROM job_db:" << d.lastError().text();
        }
    }
    else
    {
        qDebug() << "cant open job database :" << jooooob.lastError().text();
    }


    search_job_form_com();


    ui->email->setText(Glonal_email);
    ui->bio->setText(Glonal_bio);
    ui->name->setText(Glonal_first_name);
    ui->last_name->setText(Glonal_last_name);
    ui->skills->setText(Glonal_skills);
    ui->job_exp->setText(Glonal_company);
    ui->job_title->setText(Glonal_job_title);
}

void job_form_company::on_Deny_clicked()
{

    QSqlDatabase temp_data_base = QSqlDatabase::addDatabase("QSQLITE", "personal_db_deny");
    temp_data_base.setDatabaseName(QDir::currentPath() + "/content/" + current_user + "/job.db");

    if (temp_data_base.open())
    {
        QSqlQuery f(temp_data_base);
        if (!f.exec("DELETE FROM job_db WHERE job_title='" + Glonal_job_title + "'"))
        {
            qDebug() << "Can't DELETE FROM job_db:" << f.lastError().text();
        }
    }
    else
    {
        qDebug() << "Failed to open job database:" << temp_data_base.lastError().text();
    }


    search_job_form_com();


    ui->email->setText(Glonal_email);
    ui->bio->setText(Glonal_bio);
    ui->name->setText(Glonal_first_name);
    ui->last_name->setText(Glonal_last_name);
    ui->skills->setText(Glonal_skills);
    ui->job_exp->setText(Glonal_company);
    ui->job_title->setText(Glonal_job_title);
}


void search_job_form_com()
{

    QSqlDatabase data_base_job_company = QSqlDatabase::addDatabase("QSQLITE", "company_job_db");
    QString jobDbPath = QDir::currentPath() + "/content/" + ma_com_ID + "/job.db";
    data_base_job_company.setDatabaseName(jobDbPath);

    if (data_base_job_company.open())
    {
        qDebug() << "Opened job database at:" << jobDbPath;

        QSqlQuery qqq(data_base_job_company);
        if (qqq.exec("SELECT user_id, job_title FROM job_db LIMIT 1"))
        {
            if (qqq.first())
            {
                Glonal_job_title = qqq.value("job_title").toString();
                current_user = qqq.value("user_id").toString();
                qDebug() << "Job title:" << Glonal_job_title << ", User ID:" << current_user;
            }
            else
            {
                qDebug() << "No rows returned from job_db.";
            }
        }
        else
        {
            qDebug() << "Can't SELECT user_id FROM job_db:" << qqq.lastError().text();
        }

        data_base_job_company.close();
    }
    else
    {
        qDebug() << "Failed to open company job database:" << data_base_job_company.lastError().text();
    }

    QSqlDatabase search_the_job = QSqlDatabase::addDatabase("QSQLITE", "linkedin_db");
    QString linkedinDbPath = QDir::currentPath() + "/linkedin_c.db";
    search_the_job.setDatabaseName(linkedinDbPath);

    if (search_the_job.open())
    {
        qDebug() << "Opened LinkedIn database at:" << linkedinDbPath;

        QSqlQuery stj(search_the_job);
        if (stj.exec("SELECT first_name, last_name, email, skill, company, Bio FROM user WHERE ID='" + current_user + "'") && stj.first())
        {
            if(stj.first())
            {
                Glonal_first_name = stj.value("first_name").toString();
                Glonal_last_name = stj.value("last_name").toString();
                Glonal_skills = stj.value("skill").toString();
                Glonal_email = stj.value("email").toString();
                Glonal_bio = stj.value("Bio").toString();
                Glonal_company = stj.value("company").toString();
                qDebug() << "User info retrieved. First name:" << Glonal_first_name;
            }
            else
            {
                Glonal_first_name = "none";
                Glonal_last_name = "none";
                Glonal_skills = "none";
                Glonal_email = "none";
                Glonal_bio = "none";
                Glonal_company = "none";
            }
        }
        else
        {
            qDebug() << "Can't SELECT user info FROM user:" << stj.lastError().text();
        }

        search_the_job.close();
    }
    else
    {
        qDebug() << "Failed to open LinkedIn database:" << search_the_job.lastError().text();
    }
}


void job_form_company::on_home_button_clicked()
{
    main_page* t = new main_page;
    t->show();
    this->close();
}


void job_form_company::on_me_button_clicked()
{
    profile* t = new profile;
    t->show();
    this->close();
}


void job_form_company::on_pushButton_2_clicked()
{
    QSqlQuery q;
    q.exec("DELETE FROM userdb");

    welcome *t = new welcome;
    t->show();
    this->close();
}


void job_form_company::on_message_button_clicked()
{
    message_contact* n = new message_contact;
    n->show();
    this->close();
}


void job_form_company::on_mynetwork_button_clicked()
{
    my_network* n = new my_network;
    n->show();
    this->close();
}


void job_form_company::on_serach_button_clicked()
{
    QString search = ui->search->text();
    QString s;

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q(db);

    q.exec("SELECT ID FROM USER WHERE first_name='"+search+"'");
    if(q.first())
    {
        s = q.value(0).toString();
        get_the_ID(s);
        view_profile* page = new view_profile;
        page->show();
        this->close();
    }
    else
    {
        QMessageBox::information(this,"Search name ","The name is not exsict " , "ok");
        ui->search->setText("");
    }
}

