#include "make_job.h"
#include "ui_make_job.h"
#include <QString>
#include <QSqlDatabase>
#include <fstream>
#include <QDirIterator>
#include <direct.h>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <sys/stat.h>
#include <QFileInfo>
#include "send_post.h"
#include "job_form_company.h"
#include <QPixmap>
#include <QSqlQueryModel>
#include "profile.h"
#include <QIntValidator>

QString id_company_name;

make_job::make_job(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::make_job)
{
    ui->setupUi(this);
    ui->workplace_type->addItems(QStringList({"On-site","Remote","Hybird"}));
    ui->job_type->addItems(QStringList({"Full-time","Part-time","Contract","Temporary","Other","Volunteer","Internship"}));
    ui->workplace_type->setCurrentIndex(0);
    ui->job_type->setCurrentIndex(0);

    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->me_button->setIcon(QIcon("icons/person-profile-image-icon.png"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));

    QString database_path = QDir::currentPath();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main_connection");
    db.setDatabaseName(database_path + "/linkedin_C.db");
    if (!db.open())
    {
        QMessageBox::warning(this, "Error", "Can't connect to the Database", "OK");
        return;
    }

    QSqlQuery query(db);

    query.prepare("SELECT IDC FROM userdb");
    if(!query.exec())
    {
        qDebug() << "Error executing query1: " << query.lastError().text();
    }

    if (query.next())
    {
        id_company_name = query.value(0).toString();
    }

    if(QFile::exists("content/" + id_company_name + "/res/pic/0.png"))
    {
        ui->me_button->setIcon(QIcon("content/" + id_company_name + "/res/pic/0.png"));
    }
    else
    {
        ui->me_button->setIcon(QIcon("content/" + id_company_name + "/res/pic/0.jpg"));
    }

    QString com_name;

    QSqlQuery q2(db);

    q2.prepare("SELECT first_name FROM USER WHERE ID='"+id_company_name+"'");

    if(!q2.exec())
    {
        qDebug() << "Error executing query:2 " << q2.lastError().text();
    }

    if (q2.next())
    {
        com_name = q2.value(0).toString();
    }

    ui->company->setText(com_name);
}

make_job::~make_job()
{
    delete ui;
}

void make_job::on_pushButton_2_clicked()
{
    QString comp_name = ui->company->text();
    QString workplaceType = ui->workplace_type->currentText();
    QString jobType = ui->job_type->currentText();
    QString Location = ui->job_location->text();
    QString jobTitle = ui->job_title->text();
    QString salary = ui->salary_line->text();

    QString database_path = QDir::currentPath();

    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE", "job_connection");
    dataBase.setDatabaseName(database_path + "/job.db");
    if (!dataBase.open())
    {
        QMessageBox::warning(this, "Error", "Can't connect to the Database", "OK");
        return;
    }

    QSqlQuery query_2(dataBase);
    query_2.prepare("INSERT INTO USER (company_id, company_name, job_name, salary, skills_required, workplace_type, location, type) "
                    "VALUES (:id_company_name, :comp_name, :jobTitle, :salary, :jobTitle, :workplaceType, :Location, :jobType)");
    query_2.bindValue(":id_company_name", id_company_name);
    query_2.bindValue(":comp_name", comp_name);
    query_2.bindValue(":jobTitle", jobTitle);
    query_2.bindValue(":salary", salary);
    query_2.bindValue(":workplaceType", workplaceType);
    query_2.bindValue(":Location", Location);
    query_2.bindValue(":jobType", jobType);

    if(!query_2.exec())
    {
        qDebug() << "Failed to insert a new job:" << query_2.lastError().text();
    }

    job_form_company* jfk = new job_form_company;
    jfk->show();
    this->close();
}
