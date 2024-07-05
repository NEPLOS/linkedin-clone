#include "page_sender.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include "ui_page_sender.h"
#include "QMessageBox"
#include "welcome.h"
#include "main_page.h"
#include <direct.h>
#include "QSqlError"
#include <sys/stat.h>
#include <string>
#include <QDir>
#include <fstream>
#include <QDebug>

page_sender::page_sender(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::page_sender)
{
    ui->setupUi(this);

    QString database_path = QDir::currentPath();

    std::string folders = database_path.toStdString();

    _mkdir((folders + "\\content").c_str());
    _mkdir((folders + "\\data" ).c_str());
    _mkdir((folders + "\\DM").c_str());

    std::ifstream file("linkedin_C.db");
    file.close();

    std::ifstream dde("is_dark.txt");
    dde.close();

    std::ifstream jobs_data_base_make("job.db");
    jobs_data_base_make.close();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main_connection");
    db.setDatabaseName(database_path + "/linkedin_C.db");
    if (!db.open())
    {
        QMessageBox::warning(this, "Error", "Can't connect to the Database", "OK");
        return;
    }

    QSqlQuery databaseQuery(db);
    if (!databaseQuery.exec("CREATE TABLE IF NOT EXISTS USER (email TEXT, password TEXT, first_name TEXT, last_name TEXT, job TEXT, company TEXT, birthday TEXT, Bio TEXT, Phone_number TEXT, skill TEXT, mahal_tahsil TEXT, ID INTEGER)"))
    {
        qDebug() << "Failed to create USER table:" << databaseQuery.lastError().text();
    }
    if (!databaseQuery.exec("CREATE TABLE IF NOT EXISTS userdb (email TEXT , password TEXT, ID TEXT, IDC TEXT)"))
    {
        qDebug() << "Failed to create userdb table:" << databaseQuery.lastError().text();
    }

    QSqlDatabase job_db = QSqlDatabase::addDatabase("QSQLITE", "job_connection");
    job_db.setDatabaseName(database_path + "/job.db");
    if (!job_db.open())
    {
        qDebug() << "Failed to open job database:" << job_db.lastError().text();
    }
    else
    {
        QSqlQuery job_q(job_db);
        if (!job_q.exec("CREATE TABLE IF NOT EXISTS USER (company_id TEXT, company_name TEXT, job_name TEXT, salary TEXT, skills_required TEXT, workplace_type TEXT, location TEXT, type TEXT)"))
        {
            qDebug() << "Failed to create job USER table:" << job_q.lastError().text();
        }
        job_q.clear();
        job_db.close();
    }

    QString temp_mail;
    databaseQuery.prepare("SELECT email FROM userdb");
    if (!databaseQuery.exec())
    {
        qDebug() << "cant select email from userdb:" << databaseQuery.lastError().text();
    }
    else if (databaseQuery.first())
    {
        temp_mail = databaseQuery.value(0).toString();

        QString temp_pass;
        databaseQuery.prepare("SELECT password FROM userdb WHERE email = :email");
        databaseQuery.bindValue(":email", temp_mail);
        if (!databaseQuery.exec())
        {
            qDebug() << "cant select password from userdb:" << databaseQuery.lastError().text();
        }
        else if (databaseQuery.first())
        {
            temp_pass = databaseQuery.value(0).toString();

            databaseQuery.prepare("SELECT password FROM USER WHERE email = :email");
            databaseQuery.bindValue(":email", temp_mail);
            if (!databaseQuery.exec())
            {
                qDebug() << "cant to select password:" << databaseQuery.lastError().text();
            }
            else if (databaseQuery.first())
            {
                QString pass_in_db = databaseQuery.value(0).toString();
                if (temp_pass == pass_in_db)
                {
                    main_page *y = new main_page;
                    y->show();
                }
                else
                {
                    welcome *y = new welcome;
                    y->show();
                }
            }
            else
            {
                welcome *y = new welcome;
                y->show();
            }
        }
        else
        {
            qDebug() << "No password found in userdb for email:" << temp_mail;
            welcome *y = new welcome;
            y->show();
        }
    }
    else
    {
        qDebug() << "No email found in userdb";
        welcome *y = new welcome;
        y->show();
    }
}

page_sender::~page_sender()
{
    delete ui;
}
