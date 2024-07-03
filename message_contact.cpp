#include "message_contact.h"
#include "ui_message_contact.h"
#include "my_network.h"
#include "job_form.h"
#include "qlabel.h"
#include "main_page.h"
#include "welcome.h"
#include "QString"
#include "message_with_user.h"
#include "QSqlDatabase"
#include <fstream>
#include <QDirIterator>
#include <direct.h>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QMessageBox"
#include <qsqlerror.h>
#include <qdebug.h>
#include <QDir>
#include <sys/stat.h>
#include <QFileInfo>
#include "send_post.h"
#include <QPixmap>
#include "QSqlQueryModel"
#include "profile.h"
#include <QIntValidator>
#include "QSqlQuery"
#include "profile.h"
#include "QDir"
#include "view_profile.h"
#include "QMessageBox"


QString MY_ID_conntacts_;
QString Current_Row = "0";

void get_the_user_ID(QString ID_ID_ID)
{
    MY_ID_conntacts_ = ID_ID_ID;
}

message_contact::message_contact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::message_contact)
{
    ui->setupUi(this);
    loadDataFromDatabase();

    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->me_button->setIcon(QIcon("icons/person-profile-image-icon.png"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));

    if(QFile::exists("content/"+MY_ID_conntacts_+"/res/pic/0.png"))
    {
         ui->me_button->setIcon(QIcon("content/"+MY_ID_conntacts_+"/res/pic/0.png"));
    }
    else
    {
        ui->me_button->setIcon(QIcon("content/"+MY_ID_conntacts_+"/res/pic/0.jpg"));
    }

}

void message_contact::loadDataFromDatabase()
{
    QSqlDatabase dbConnections = QSqlDatabase::addDatabase("QSQLITE", "connections_db");
    dbConnections.setDatabaseName(QDir::currentPath() + "/data/" + MY_ID_conntacts_ + "/connections.db");

    if (!dbConnections.open())
    {
        qDebug() << "cant open connections database:" << dbConnections.lastError().text();
        return;
    }

    QSqlQuery qConnections(dbConnections);
    qConnections.prepare("SELECT user_id FROM connected LIMIT 1 OFFSET " + Current_Row);

    if (!qConnections.exec())
    {
        qDebug() << qConnections.lastError().text();
        return;
    }

    if (qConnections.first())
    {
        QString id = qConnections.value("user_id").toString();

        QSqlDatabase dbMainServer = QSqlDatabase::addDatabase("QSQLITE", "main_server_db_linkedin");
        dbMainServer.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");

        if (!dbMainServer.open())
        {
            qDebug() << "cant open database:" << dbMainServer.lastError().text();
            return;
        }

        QSqlQuery qMainServer(dbMainServer);
        qMainServer.prepare("SELECT first_name, last_name FROM USER WHERE ID = :id");
        qMainServer.bindValue(":id", id);

        if (!qMainServer.exec())
        {
            qDebug() << "cant : "<< qMainServer.lastError().text();
            return;
        }

        if (qMainServer.first())
        {
            QString fn = qMainServer.value("first_name").toString();
            QString ln = qMainServer.value("last_name").toString();
            ui->name->setText(fn);
            ui->last_name->setText(ln);

            QString imagePath = QDir::currentPath() + "/content/" + id + "/res/pic/0.png";
            if (QFile::exists(imagePath))
            {
                QPixmap ui_res(imagePath);
                QPixmap scaled_pixmap = ui_res.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->picture->setPixmap(scaled_pixmap);
            }
            else
            {
                imagePath = QDir::currentPath() + "/content/" + id + "/res/pic/0.jpg";
                if (QFile::exists(imagePath))
                {
                    QPixmap ui_res(imagePath);
                    QPixmap scaled_pixmap = ui_res.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ui->picture->setPixmap(scaled_pixmap);
                }
                else
                {
                    qDebug() << "picture not found";
                    ui->picture->clear();
                }
            }
        }
    }
}

void message_contact::on_next_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "count_umm_yeah");
    db.setDatabaseName(QDir::currentPath() + "/data/" + MY_ID_conntacts_ + "/connections.db");

    if (!db.open())
    {
        qDebug() << "cant open connections database:" << db.lastError().text();
        return;
    }

    QSqlQuery q(db);
    q.exec("SELECT COUNT(*) FROM connected");

    int amount = 0;

    if (q.next())
    {
        amount = q.value(0).toInt();
    }

    amount--;

    if (amount > MY_ID_conntacts_.toInt())
    {
        int temp = MY_ID_conntacts_.toInt() + 1;
        MY_ID_conntacts_ = QString::number(temp);
    }

    Current_Row = QString::number(MY_ID_conntacts_.toInt());
    loadDataFromDatabase();
}

void message_contact::on_previous_clicked()
{
    if (MY_ID_conntacts_.toInt() > 0)
    {
        int temp = MY_ID_conntacts_.toInt() - 1;
        MY_ID_conntacts_ = QString::number(temp);
    }

    Current_Row = QString::number(MY_ID_conntacts_.toInt());
    loadDataFromDatabase();
}


message_contact::~message_contact()
{
    delete ui;
}

void message_contact::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec("DELETE FROM userdb");

    welcome *t = new welcome;
    t->show();
    this->close();
}


void message_contact::on_me_button_clicked()
{
    profile* t = new profile;
    t->show();
    this->close();
}


void message_contact::on_home_button_clicked()
{
    main_page* t = new main_page;
    t->show();
    this->close();
}


void message_contact::on_job_button_clicked()
{
    job_form* job_page_open = new job_form;

    job_page_open->show();

    this->close();
}


void message_contact::on_mynetwork_button_clicked()
{
    my_network* n = new my_network;
    n->show();
    this->close();
}


void message_contact::on_serach_button_clicked()
{
    QString search = ui->search->text();
    QString s;

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","numnumnum");
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


void message_contact::on_pushButton_2_clicked()
{
    QSqlDatabase dbConnections = QSqlDatabase::addDatabase("QSQLITE", "count_umm_yeah_2_2");
    dbConnections.setDatabaseName(QDir::currentPath() + "/data/" + MY_ID_conntacts_ + "/connections.db");

    if (!dbConnections.open())
    {
        qDebug() << "can't " << dbConnections.lastError().text();
        return;
    }

    QSqlQuery q(dbConnections);
    if (!q.exec("SELECT user_id FROM connected LIMIT 1 OFFSET " + Current_Row))
    {
        qDebug() << "can't " << q.lastError().text();
        return;
    }

    QString id;
    if (q.first())
    {
        id = q.value("user_id").toString();
    }

    QSqlDatabase dbUser1 = QSqlDatabase::addDatabase("QSQLITE", "make_dn_table_1_1");
    dbUser1.setDatabaseName(QDir::currentPath() + "/DM/" + MY_ID_conntacts_ + "/user.db");

    if (!dbUser1.open())
    {
        qDebug() << "can't open database for user " << MY_ID_conntacts_ << ":" << dbUser1.lastError().text();
        return;
    }

    QSqlQuery t1(dbUser1);
    QString table1 = id;
    if (!t1.exec("CREATE TABLE IF NOT EXISTS '" + table1 + "'(user_id TEXT, message TEXT)"))
    {
        qDebug() << "can't create table " << table1 << ":" << t1.lastError().text();
    }

    QSqlDatabase dbUser2 = QSqlDatabase::addDatabase("QSQLITE", "make_dn_table_1_2");
    dbUser2.setDatabaseName(QDir::currentPath() + "/DM/" + id + "/user.db");

    if (!dbUser2.open())
    {
        qDebug() << "can't open database for user " << id << ":" << dbUser2.lastError().text();
        return;
    }

    QSqlQuery t2(dbUser2);
    QString table2 = MY_ID_conntacts_;
    if (!t2.exec("CREATE TABLE IF NOT EXISTS '" + table2 + "' (user_id TEXT, message TEXT)"))
    {
        qDebug() << "can't create table " << table2 << ":" << t2.lastError().text();
    }

    get_the_ideas_chat_screen(MY_ID_conntacts_, id);
    message_with_user* fff = new message_with_user;
    fff->show();
}



