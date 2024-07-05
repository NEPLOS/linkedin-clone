#include "job_form.h"
#include "ui_job_form.h"
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
#include <qfileinfo.h>
#include "welcome.h"
#include <qdebug.h>
#include <QDir>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include "main_page.h"
#include "message_contact.h"
#include "view_profile.h"
#include "QMessageBox"


QString job_page_user_ID = "None";
QString com_id_jf = "None";
QString com_name_jf = "None";
QString job_name_jf = "None";
QString salary_jf = "None";
QString skills_rec_jf = "None";
QString workplace_type_jf = "None";
QString location_jf = "None";
QString type_jf = "None";

QString num_jf = "0";

void select_jf(QString num);

job_form::job_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::job_form)
{

    ui->setupUi(this);

    ui->comboBox->addItem("Normal user");
    ui->comboBox->addItem("Company");
    ui->comboBox->setCurrentIndex(0);

    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->me_button->setIcon(QIcon("icons/person-profile-image-icon.png"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));

    QString database_path = QDir::currentPath() + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    if (!db.open())
    {
        qDebug() << "Error: Failed to connect to database:" << db.lastError().text();
        return;
    }

    QSqlQuery q;
    if (q.exec("SELECT ID FROM userdb"))
    {
        if (q.first())
        {
            job_page_user_ID = q.value(0).toString();
        }
    }
    else
    {
        qDebug() << "Error executing query:" << q.lastError().text();
    }

    if (QFile::exists("content/" + job_page_user_ID + "/res/pic/0.png"))
    {
        ui->me_button->setIcon(QIcon("content/" + job_page_user_ID + "/res/pic/0.png"));
    }
    else
    {
        ui->me_button->setIcon(QIcon("content/" + job_page_user_ID + "/res/pic/0.jpg"));
    }

    select_jf(num_jf);

    ui->com_name->setText(com_name_jf);
    ui->salary->setText(salary_jf);
    ui->job_t->setText(job_name_jf);
    ui->j_t->setText(type_jf);
    ui->w_t->setText(workplace_type_jf);
}

job_form::~job_form()
{
    delete ui;
}

void job_form::on_comboBox_currentIndexChanged(int index)
{
    if (index == 1)
    {
        job_form_company* jfc = new job_form_company;
        jfc->show();
        this->close();
    }
}

void job_form::on_apply_clicked()
{
    QSqlDatabase job_base_send = QSqlDatabase::addDatabase("QSQLITE", "job_base_send");
    job_base_send.setDatabaseName(QDir::currentPath() + "/content/" + com_id_jf + "/job.db");
    if (!job_base_send.open())
    {
        qDebug() << "Error: Failed to open job database:" << job_base_send.lastError().text();
        return;
    }

    QSqlQuery query(job_base_send);
    if (!query.exec("CREATE TABLE IF NOT EXISTS job_db (user_id TEXT, job_title TEXT)"))
    {
        qDebug() << "Error: Failed to create job_db table:" << query.lastError().text();
    }

    // Insert into job_db table
    if (!query.exec("INSERT INTO job_db (user_id, job_title) VALUES ('" + job_page_user_ID + "', '" + job_name_jf + "')"))
    {
        qDebug() << "Error: Failed to insert into job_db table:" << query.lastError().text();
    }

    QSqlDatabase emp_db = QSqlDatabase::addDatabase("QSQLITE", "emp_db");
    emp_db.setDatabaseName(QDir::currentPath() + "/content/" + com_id_jf + "/employee.db");
    if (!emp_db.open())
    {
        qDebug() << "Error: Failed to open employee database:" << emp_db.lastError().text();
        return;
    }

    QSqlQuery q_emp(emp_db);
    if (!q_emp.exec("CREATE TABLE IF NOT EXISTS emp (user_id TEXT, job_title TEXT , first_name TEXT , last_name TEXT , salary TEXT , email TEXT)"))
    {
        qDebug() << "Error: Failed to create emp table:" << q_emp.lastError().text();
    }

    QSqlDatabase apply = QSqlDatabase::addDatabase("QSQLITE", "apply");
    apply.setDatabaseName(QDir::currentPath() + "/data/" + job_page_user_ID + "/personal.db");
    if (!apply.open())
    {
        qDebug() << "Error: Failed to open personal database:" << apply.lastError().text();
        return;
    }

    QSqlQuery ff(apply);

    if (!ff.exec("INSERT INTO pending (com_name, job_title) VALUES ('" + com_name_jf + "', '" + job_name_jf + "')"))
    {
        qDebug() << "Error: Failed to insert into pending table:" << ff.lastError().text();
    }

    ui->ignore->setEnabled(false);
    ui->apply->setEnabled(false);
    ui->ignore->setText("Pending");
    ui->apply->setText("Pending");

    job_base_send.close();
    emp_db.close();
    apply.close();
}

void job_form::on_ignore_clicked()
{
    QSqlDatabase job_base = QSqlDatabase::addDatabase("QSQLITE", "job_base");
    job_base.setDatabaseName(QDir::currentPath() + "/data/" + job_page_user_ID + "/personal.db");
    if (!job_base.open())
    {
        qDebug() << "Error: Failed to open personal database:" << job_base.lastError().text();
        return;
    }

    QSqlQuery queryqqqq(job_base);
    if (!queryqqqq.exec("CREATE TABLE IF NOT EXISTS ignored (comp_name TEXT, job_title TEXT)"))
    {
        qDebug() << "Error: Failed to create ignored table:" << queryqqqq.lastError().text();
    }

    if (!queryqqqq.exec("INSERT INTO ignored (comp_name, job_title) VALUES ('" + com_name_jf + "', '" + job_name_jf + "')"))
    {
        qDebug() << "Error: Failed to insert into ignored table:" << queryqqqq.lastError().text();
    }

    ui->ignore->setEnabled(false);
    ui->apply->setEnabled(false);
    ui->ignore->setText("Ignored");
    ui->apply->setText("Ignored");

    job_base.close();
}


void select_jf(QString num)
{
    QSqlDatabase job_base = QSqlDatabase::addDatabase("QSQLITE", "job_base");
    job_base.setDatabaseName(QDir::currentPath() + "/job.db");
    if (!job_base.open())
    {
        qDebug() << "Error: Failed to open job database:" << job_base.lastError().text();
        return;
    }

    QSqlQuery query(job_base);
    QString sqlQuery = "SELECT company_id, company_name, job_name, salary, skills_required, workplace_type, location, type FROM USER LIMIT 1 OFFSET " + num;

    if (query.exec(sqlQuery))
    {
        if (query.next())
        {
            com_id_jf = query.value("company_id").toString();
            com_name_jf = query.value("company_name").toString();
            job_name_jf = query.value("job_name").toString();
            salary_jf = query.value("salary").toString();
            skills_rec_jf = query.value("skills_required").toString();
            workplace_type_jf = query.value("workplace_type").toString();
            location_jf = query.value("location").toString();
            type_jf = query.value("type").toString();
        }
        else
        {
            qDebug() << "No rows returned.";
        }
    }
    else
    {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}

void job_form::on_pushButton_3_clicked()
{
    int temp = num_jf.toInt();
    temp++;
    num_jf = QString::number(temp);

    select_jf(num_jf);
    ui->com_name->setText(com_name_jf);
    ui->salary->setText(salary_jf);
    ui->job_t->setText(job_name_jf);
    ui->j_t->setText(type_jf);
    ui->w_t->setText(workplace_type_jf);

    bool is_pending = false;
    bool is_ignored = false;

    QSqlDatabase job_base = QSqlDatabase::addDatabase("QSQLITE", "job_base");
    job_base.setDatabaseName(QDir::currentPath() + "/data/" + job_page_user_ID + "/personal.db");

    if (!job_base.open())
    {
        qDebug() << "Error: Failed to open personal database:" << job_base.lastError().text();
        return;
    }

    QSqlQuery temp_q(job_base);

    if (!temp_q.exec("SELECT comp_name FROM ignored WHERE job_title='" + job_name_jf + "'"))
    {
        qDebug() << "Error at selecting from ignored:" << temp_q.lastError().text();
    }
    else if (temp_q.first())
    {
        is_ignored = true;
    }

    if (!temp_q.exec("SELECT com_name FROM pending WHERE job_title='" + job_name_jf + "'"))
    {
        qDebug() << "Error at selecting from pending:" << temp_q.lastError().text();
    }
    else if (temp_q.first())
    {
        is_pending = true;
    }

    if (is_ignored)
    {
        ui->ignore->setEnabled(false);
        ui->apply->setEnabled(false);
        ui->ignore->setText("ignored");
        ui->apply->setText("ignored");
    }
    else if (is_pending)
    {
        ui->ignore->setEnabled(false);
        ui->apply->setEnabled(false);
        ui->ignore->setText("pending");
        ui->apply->setText("pending");
    }
    else
    {
        ui->ignore->setEnabled(true);
        ui->apply->setEnabled(true);
        ui->ignore->setText("ignore");
        ui->apply->setText("apply");
    }

    job_base.close();
}

void job_form::on_pushButton_2_clicked()
{
    int temp = num_jf.toInt();
    temp--;
    if (temp >= 0)
    {
        num_jf = QString::number(temp);

        select_jf(num_jf);
        ui->com_name->setText(com_name_jf);
        ui->salary->setText(salary_jf);
        ui->job_t->setText(job_name_jf);
        ui->j_t->setText(type_jf);
        ui->w_t->setText(workplace_type_jf);

        bool is_pending = false;
        bool is_ignored = false;

        QSqlDatabase job_base = QSqlDatabase::addDatabase("QSQLITE", "job_base_2");
        job_base.setDatabaseName(QDir::currentPath() + "/data/" + job_page_user_ID + "/personal.db");

        if (!job_base.open())
        {
            qDebug() << "Error: Failed to open personal database:" << job_base.lastError().text();
            return;
        }

        QSqlQuery temp_q(job_base);

        if (!temp_q.exec("SELECT comp_name FROM ignored WHERE job_title='" + job_name_jf + "'"))
        {
            qDebug() << "Error at selecting from ignored:" << temp_q.lastError().text();
        }
        else if (temp_q.first())
        {
            is_ignored = true;
        }

        if (!temp_q.exec("SELECT com_name FROM pending WHERE job_title='" + job_name_jf + "'"))
        {
            qDebug() << "Error at selecting from pending:" << temp_q.lastError().text();
        }
        else if (temp_q.first())
        {
            is_pending = true;
        }

        if (is_ignored)
        {
            ui->ignore->setEnabled(false);
            ui->apply->setEnabled(false);
            ui->ignore->setText("ignored");
            ui->apply->setText("ignored");
        }
        else if (is_pending)
        {
            ui->ignore->setEnabled(false);
            ui->apply->setEnabled(false);
            ui->ignore->setText("pending");
            ui->apply->setText("pending");
        }
        else
        {
            ui->ignore->setEnabled(true);
            ui->apply->setEnabled(true);
            ui->ignore->setText("ignore");
            ui->apply->setText("apply");
        }

        job_base.close();
    }
}


void job_form::on_home_button_clicked()
{
    main_page* t = new main_page;
    t->show();
    this->close();
}


void job_form::on_me_button_clicked()
{
    profile* t = new profile;
    t->show();
    this->close();
}


void job_form::on_pushButton_clicked()
{

    QSqlDatabase data_base_job_company = QSqlDatabase::addDatabase("QSQLITE", "job_message_company_job_db");
    data_base_job_company.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");
    QSqlQuery q(data_base_job_company);
    q.exec("DELETE FROM userdb");

    welcome *t = new welcome;
    t->show();
    this->close();
}


void job_form::on_mynetwork_button_clicked()
{
    my_network* n = new my_network;
    n->show();
    this->close();
}


void job_form::on_message_button_clicked()
{
    get_the_user_ID(job_page_user_ID);
    //job_page_user_ID
    message_contact* n = new message_contact;
    n->show();
    this->close();
}


void job_form::on_serach_button_clicked()
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

