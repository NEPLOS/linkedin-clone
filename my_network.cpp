#include "my_network.h"
#include "ui_my_network.h"
#include "profile.h"
#include "main_page.h"
#include "welcome.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include <QFileInfo>
#include "QSqlError"
#include <QPixmap>
#include "QSqlQueryModel"
#include "job_form.h"
#include "QDir"
#include <QPixmap>
#include <QFile>
#include "qdebug.h"
#include "view_profile.h"
#include "QMessageBox"
#include <qfile.h>
#include <qfileinfo.h>
#include "message_contact.h"


QString usre_id_my_network;
QString current_user_id_re;
int r=0;

void get_user_id_my_network(QString id)
{
    usre_id_my_network = id;
}

my_network::my_network(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::my_network)
{
    ui->setupUi(this);
    ui->next_pushbutton->hide();
    ui->previous_pushbutton->hide();
    ui->request_groupbox->hide();
    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));
    ui->me_button->setIcon(QIcon("icons/person-profile-image-icon.png"));

    if(QFile::exists("content/"+usre_id_my_network+"/res/pic/0.png"))
    {
        ui->me_button->setIcon(QIcon("content/"+usre_id_my_network+"/res/pic/0.png"));
    }
    else
    {
        ui->me_button->setIcon(QIcon("content/"+usre_id_my_network+"/res/pic/0.jpg"));
    }

}

my_network::~my_network()
{
    delete ui;
}
void my_network::on_request_button_clicked()
{
    r++;
    if(r%2!=0)
    {
        ui->next_pushbutton->show();
        ui->previous_pushbutton->show();
        ui->suggest_groupBox->hide();
        ui->request_groupbox->show();
        ui->request_button->setText("Back");

        QSqlDatabase my_network_db = QSqlDatabase::addDatabase("QSQLITE","MyNetWork_DB");
        my_network_db.setDatabaseName(QDir::currentPath() + "/data/" + usre_id_my_network + "/connections.db");
        my_network_db.open();

        QSqlQuery q(my_network_db);

        if(!q.exec("SELECT user_id FROM pending"))
        {
            qDebug() << "can't select from pending " <<  q.lastError().text();
        }
        if(q.first())
        {
            current_user_id_re = q.value("user_id").toString();
            QSqlDatabase main_db = QSqlDatabase::addDatabase("QSQLITE","main_db_QDIR");
            main_db.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");
            main_db.open();

            QSqlQuery p(main_db);

            if(!p.exec("SELECT first_name , last_name , email from USER WHERE ID='"+current_user_id_re+"'"))
            {
                qDebug() << "can't select from first_name , last_name , email " <<  p.lastError().text();
            }

            if(p.first())
            {
                QString fn = p.value("first_name").toString();
                QString ln = p.value("last_name").toString();
                QString email = p.value("email").toString();

                ui->name_r->setText(fn);
                ui->last_name_r->setText(ln);
                ui->email_r->setText(email);

                if(QFile::exists("content/"+current_user_id_re+"/res/pic/0.png"))
                {
                    QPixmap ui_res("content/"+current_user_id_re+"/res/pic/0.png");
                    QPixmap scaled_pixmap = ui_res.scaled(81, 81, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ui->profile_6->setPixmap(scaled_pixmap);
                }
                else
                {
                    QPixmap ui_res("content/"+current_user_id_re+"/res/pic/0.jpg");
                    QPixmap scaled_pixmap = ui_res.scaled(81, 81, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    ui->profile_6->setPixmap(scaled_pixmap);
                }

            }
        }
        else
        {
            current_user_id_re = "none";
            ui->name_r->setText("none");
            ui->last_name_r->setText("none");
            ui->email_r->setText("none");
            ui->profile_6->clear();
        }

    }
    else
    {
        ui->next_pushbutton->hide();
        ui->previous_pushbutton->hide();
        ui->suggest_groupBox->show();
        ui->request_groupbox->hide();
        ui->request_button->setText("Requests");
    }
}


void my_network::on_me_button_clicked()
{
    profile* t = new profile;
    t->show();
    this->close();
}


void my_network::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec("DELETE FROM userdb");

    welcome *t = new welcome;
    t->show();
    this->close();
}


void my_network::on_home_button_clicked()
{
    main_page* t = new main_page;
    t->show();
    this->close();
}


void my_network::on_job_button_clicked()
{
    job_form* job_page_open = new job_form;

    job_page_open->show();

    this->close();
}


void my_network::on_serach_button_clicked()
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


void my_network::on_message_button_clicked()
{
    get_the_user_ID(usre_id_my_network);
    message_contact* n = new message_contact;
    n->show();
    this->close();
}


void my_network::on_accept_button_1_clicked()
{

    if(current_user_id_re == "none")
    {
        return;
    }
    QSqlDatabase my_network_db = QSqlDatabase::addDatabase("QSQLITE","accepted");
    my_network_db.setDatabaseName(QDir::currentPath() + "/data/" + usre_id_my_network + "/connections.db");
    my_network_db.open();

    QSqlDatabase my_network_db_current = QSqlDatabase::addDatabase("QSQLITE","accepted_for_him");
    my_network_db_current.setDatabaseName(QDir::currentPath() + "/data/" + current_user_id_re + "/connections.db");
    my_network_db_current.open();

    QSqlQuery q(my_network_db);

    if(!q.exec("DELETE FROM pending WHERE user_id = '"+current_user_id_re+"'"))
    {
        qDebug() << "can't delete from pending " <<  q.lastError().text();
    }

    q.exec("INSERT INTO connected(user_id)VALUES('"+current_user_id_re+"')");

    QSqlQuery qq(my_network_db_current);

    qq.exec("INSERT INTO connected(user_id)VALUES('"+usre_id_my_network+"')");

    q.exec("SELECT user_id FROM pending");
    if(q.first())
    {
        current_user_id_re = q.value("user_id").toString();
        QSqlDatabase main_db = QSqlDatabase::addDatabase("QSQLITE","main_db_QDIR_a");
        main_db.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");
        main_db.open();

        QSqlQuery p(main_db);

        p.exec("SELECT first_name , last_name , email from USER WHERE ID='"+current_user_id_re+"'");
        if(p.first())
        {
            QString fn = p.value("first_name").toString();
            QString ln = p.value("last_name").toString();
            QString email = p.value("email").toString();

            ui->name_r->setText(fn);
            ui->last_name_r->setText(ln);
            ui->email_r->setText(email);

            if(QFile::exists("content/"+current_user_id_re+"/res/pic/0.png"))
            {
                QPixmap ui_res("content/"+current_user_id_re+"/res/pic/0.png");
                QPixmap scaled_pixmap = ui_res.scaled(81, 81, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->profile_6->setPixmap(scaled_pixmap);
            }
            else
            {
                QPixmap ui_res("content/"+current_user_id_re+"/res/pic/0.jpg");
                QPixmap scaled_pixmap = ui_res.scaled(81, 81, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->profile_6->setPixmap(scaled_pixmap);
            }

        }
    }
    else
    {
        current_user_id_re = "none";
        ui->name_r->setText("none");
        ui->last_name_r->setText("none");
        ui->email_r->setText("none");
        ui->profile_6->clear();
    }

}


void my_network::on_decline_button_1_clicked()
{
    if(current_user_id_re == "none")
    {
        return;
    }
    QSqlDatabase my_network_db = QSqlDatabase::addDatabase("QSQLITE","denied");
    my_network_db.setDatabaseName(QDir::currentPath() + "/data/" + usre_id_my_network + "/connections.db");
    my_network_db.open();

    QSqlQuery q(my_network_db);

    if(!q.exec("DELETE FROM pending WHERE user_id='"+current_user_id_re+"'"))
    {
        qDebug() << "can't delete from pending " <<  q.lastError().text();
    }

    q.exec("SELECT user_id FROM pending");
    if(q.first())
    {
        current_user_id_re = q.value("user_id").toString();
        QSqlDatabase main_db = QSqlDatabase::addDatabase("QSQLITE","main_db_QDIR_d");
        main_db.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");
        main_db.open();

        QSqlQuery p(main_db);

        p.exec("SELECT first_name , last_name , email from USER WHERE ID='"+current_user_id_re+"'");
        if(q.first())
        {
            QString fn = p.value("first_name").toString();
            QString ln = p.value("last_name").toString();
            QString email = p.value("email").toString();

            ui->name_r->setText(fn);
            ui->last_name_r->setText(ln);
            ui->email_r->setText(email);

            if(QFile::exists("content/"+current_user_id_re+"/res/pic/0.png"))
            {
                QPixmap ui_res("content/"+current_user_id_re+"/res/pic/0.png");
                QPixmap scaled_pixmap = ui_res.scaled(81, 81, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->profile_6->setPixmap(scaled_pixmap);
            }
            else
            {
                QPixmap ui_res("content/"+current_user_id_re+"/res/pic/0.jpg");
                QPixmap scaled_pixmap = ui_res.scaled(81, 81, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->profile_6->setPixmap(scaled_pixmap);
            }

        }
    }
    else
    {
        current_user_id_re = "none";
        ui->name_r->setText("none");
        ui->last_name_r->setText("none");
        ui->email_r->setText("none");
        ui->profile_6->clear();
    }


}
