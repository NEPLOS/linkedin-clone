#include "view_profile.h"
#include "ui_view_profile.h"
#include <qlabel.h>
#include <QDir>
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QMessageBox"
#include "QSqlQuery"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include "QSqlError"
#include <QFile>
#include "qdebug.h"
#include "profile.h"
#include <string>
#include "welcome.h"
#include "QSqlError"
#include <QWidget>
#include "main_page.h"
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include "my_network.h"
#include "job_form.h"
#include "message_contact.h"






QString global_ID;
QString ma_id;

view_profile::view_profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::view_profile)
{

    ui->setupUi(this);

    ui->connect_button->show();

    QString path = QDir::currentPath();

    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->me_button->setIcon(QIcon("icons/person-profile-image-icon.png"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton_3->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));

    path = path + "/content/" + global_ID + "/res/pic/0.";
    QFileInfo file_info(path + "png");
    if(file_info.exists())
    {
        path = path + "png";
    }
    else
    {
        path = path + "jpg";
    }

    QPixmap ui_res(path);
    QPixmap scaled_pixmap = ui_res.scaled(130, 130, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->picture->setPixmap(scaled_pixmap);

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q(db);

    QString first_name;
    QString bio;
    QString last_name;
    QString email;

    q.exec("SELECT ID FROM userdb");
    if(q.first())
    {
        ma_id = q.value(0).toString();
    }

    if(QFile::exists("content/"+ma_id+"/res/pic/0.png"))
    {
        ui->me_button->setIcon(QIcon("content/"+ma_id+"/res/pic/0.png"));
    }
    else
    {
        ui->me_button->setIcon(QIcon("content/"+ma_id+"/res/pic/0.jpg"));
    }

    q.exec("SELECT first_name FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        first_name = q.value(0).toString();
    }
    qDebug() << q.lastError().text();

    q.exec("SELECT last_name FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        last_name = q.value(0).toString();
    }
    qDebug() << q.lastError().text();

    q.exec("SELECT email FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        email = q.value(0).toString();
    }
    qDebug() << q.lastError().text();

    q.exec("SELECT Bio FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        bio = q.value(0).toString();
    }
    qDebug() << q.lastError().text();

    QString skills;

    q.exec("SELECT skill FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        skills = q.value(0).toString();
    }

    ui->bio->setText(bio);
    ui->name->setText(first_name);
    ui->lastname->setText(last_name);
    ui->email->setText(email);
    ui->my_skills->setText(skills);

    if(global_ID != ma_id)
    {
        database_path = database_path + "/linkedin_C.db";

        QSqlDatabase data_base_button_check = QSqlDatabase::addDatabase("QSQLITE");
        data_base_button_check.setDatabaseName(QDir::currentPath() + "/data/" +global_ID+ "/connections.db");
        data_base_button_check.open();

        QSqlQuery qee(data_base_button_check);

        qee.exec("SELECT user_id FROM pending WHERE user_id='"+ma_id+"'");
        if(qee.first())
        {
            ui->connect_button->setEnabled(false);
            ui->connect_button->setText("pendig");
        }
    }
    else
    {
        ui->connect_button->setEnabled(false);
        ui->connect_button->hide();
    }

}


view_profile::~view_profile()
{
    delete ui;
}

void view_profile::on_home_button_clicked()
{
    main_page* t = new main_page;
    t->show();
    this->close();
}


void view_profile::on_me_button_clicked()
{
    profile* t = new profile;
    t->show();
    this->close();
}

//quit account
void view_profile::on_pushButton_3_clicked()
{

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q(db);
    q.exec("DELETE FROM userdb");

    welcome *t = new welcome;
    t->show();
    this->close();

}

void get_the_ID(QString ID)
{
    global_ID = ID;
}

void view_profile::on_serach_button_clicked()
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
        QMessageBox::information(this,"Search name ","The name is not exist " , "ok");
        ui->search->setText("");
    }
}


void view_profile::on_message_button_clicked()
{
    message_contact* n = new message_contact;
    n->show();
    this->close();
}


void view_profile::on_mynetwork_button_clicked()
{
    my_network* n = new my_network;
    n->show();
    this->close();
}


void view_profile::on_job_button_clicked()
{
    job_form* job_page_open = new job_form;
    job_page_open->show();
    this->close();
}


void view_profile::on_connect_button_clicked()
{

    QSqlDatabase db_connect = QSqlDatabase::addDatabase("QSQLITE","connect_stuff");
    db_connect.setDatabaseName(QDir::currentPath() + "/data/" +global_ID+ "/connections.db");
    db_connect.open();

    QSqlQuery q(db_connect);

    if(!q.exec("INSERT INTO pending(user_id)VALUES('"+ma_id+"')"))
    {
        qDebug() << "failed to insert data into pending : " << q.lastError().text();
    }

    ui->connect_button->setEnabled(false);
    ui->connect_button->setText("pendig");

}

