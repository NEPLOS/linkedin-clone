#include "profile.h"
#include "ui_profile.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include <QFileInfo>
#include "send_post.h"
#include <QPixmap>
#include "QSqlQueryModel"
#include <QVariant>
#include "make_company.h"
#include "welcome.h"
#include "mainwindow.h"
#include "main_page.h"
#include "message_contact.h"
#include "message_with_user.h"
#include "QMessageBox"
#include "main_page.h"
#include <direct.h>
#include "fstream"
#include <sys/stat.h>
#include <QPixmap>
#include <QDir>
#include <qstring.h>
#include <QFileDialog>
#include <QIcon>
#include <fstream>
#include <QDirIterator>
#include "my_network.h"
#include "job_form.h"
#include "view_profile.h"
QString ID;
bool is_new_bio;

profile::profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Light");
    ui->comboBox->addItem("Dark");

    std::ifstream dd("is_dark.txt");
    std::string ddd;
    dd >> ddd;
    if(ddd == "1")
    {
        ui->comboBox->setCurrentIndex(1);
    }
    else
    {
        ui->comboBox->setCurrentIndex(0);
    }

    ui->switch_mode->addItem("Normal user");
    ui->switch_mode->addItem("company");

    ui->switch_mode->setCurrentIndex(0);

    ui->make_company->hide();

    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton_3->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));


    ui->new_bio->hide();
    ui->new_bio_l->hide();
    ui->submit->hide();

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q(db);

    q.exec("SELECT ID FROM userdb");
    if(q.first())
    {
        ID = q.value(0).toString();
    }

    if(QFile::exists("content/"+ID+"/res/pic/0.png"))
    {
        ui->me_button->setIcon(QIcon("content/"+ID+"/res/pic/0.png"));
    }
    else
    {
        ui->me_button->setIcon(QIcon("content/"+ID+"/res/pic/0.jpg"));
    }

    QString path = QDir::currentPath();

    path = path + "/content/" + ID + "/res/pic/0.";
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

    QString firstName;
    QString lastName;
    QString bio;
    QString Skill;

    q.exec("SELECT first_name FROM USER WHERE ID='"+ID+"'");
    if(q.first())
    {
        firstName = q.value(0).toString();
    }

    q.exec("SELECT last_name FROM USER WHERE ID='"+ID+"'");
    if(q.first())
    {
        lastName = q.value(0).toString();
    }

    q.exec("SELECT Bio FROM USER WHERE ID='"+ID+"'");
    if(q.first())
    {
        bio = q.value(0).toString();
    }

    q.exec("SELECT skill FROM USER WHERE ID='"+ID+"'");
    if(q.first())
    {
        Skill = q.value(0).toString();
    }

    ui->name->setText(firstName);
    ui->lastname->setText(lastName);
    ui->bio->setText(bio);
    ui->skill->setText(Skill);

}

profile::~profile()
{
    delete ui;
}

void profile::on_pushButton_2_clicked()
{
    send_post* t = new send_post;
    t->show();
    this->close();
}


void profile::on_pushButton_clicked()
{
    ui->new_bio->show();
    ui->new_bio_l->show();
    ui->submit->show();
    is_new_bio = true;
    ui->new_bio_l->setText("new bio : ");
}


void profile::on_Edit_profile_button_clicked()
{
    QString file_path = QFileDialog::getOpenFileName();

    QFileInfo info(file_path);

    if(info.suffix() == "png" || info.suffix() == "jpg")
    {
        QString path = QDir::currentPath();
        path = path + "/content/" + ID + "/res/pic/0.";
        QFile::remove(path + "png");
        QFile::remove(path + "jpg");
        path = path + info.suffix();
        QFile::copy(file_path,path);
        QPixmap ui_res(path);
        QPixmap scaled_pixmap = ui_res.scaled(130, 130, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->picture->setPixmap(scaled_pixmap);
        ui->me_button->setIcon(QIcon(path));
    }
    else
    {
         QMessageBox::warning(this,"invalid","invalid file format (only png and jpg is acceptable)", "ok");
    }
}

void profile::on_home_button_clicked()
{
    main_page* t = new main_page;
    t->show();
    this->close();
}


void profile::on_submit_clicked()
{

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q(db);
    if(is_new_bio)
    {
        QString new_bio = ui->new_bio->text();

        q.exec("UPDATE USER SET Bio='"+new_bio+"' WHERE ID='"+ID+"'");
        ui->bio->setText(new_bio);
    }
    else
    {
        QString new_skill = ui->new_bio->text();

        q.exec("UPDATE USER SET skill='"+new_skill+"' WHERE ID='"+ID+"'");
        ui->skill->setText(new_skill);
    }

    ui->new_bio->hide();
    ui->new_bio->setText("");
    ui->new_bio_l->hide();
    ui->submit->hide();

}


void profile::on_pushButton_3_clicked()
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


void profile::on_pushButton_4_clicked()
{
    ui->new_bio->show();
    ui->new_bio_l->show();
    ui->submit->show();
    is_new_bio = false;
    ui->new_bio_l->setText("new skill : ");
}


void profile::on_switch_mode_currentIndexChanged(int index)
{

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    if(index == 1)
    {
        QSqlQuery q(db);

        q.exec("SELECT IDC FROM userdb");
        if(q.next())
        {
            QVariant result = q.value(0);
            if (result.isNull())
            {

                QMessageBox::warning(this,"Error","you don't have any company rn , u can make one by pressing the \"make company\" button");

                ui->make_company->show();

                return;
            }
            else
            {
                qDebug() << "The value is:" << result.toString();
            }
        }

        ID = ID + "C";

        q.exec("SELECT ID FROM USER WHERE ID='"+ID+"'");
        if(q.first())
        {

        }


        if(QFile::exists("content/"+ID+"/res/pic/0.png"))
        {
            ui->me_button->setIcon(QIcon("content/"+ID+"/res/pic/0.png"));
        }
        else
        {
            ui->me_button->setIcon(QIcon("content/"+ID+"/res/pic/0.jpg"));
        }

        QString path = QDir::currentPath();

        path = path + "/content/" + ID + "/res/pic/0."; // 0.png";
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

        QString name_company;
        QString lastName;
        QString bio;
        QString Skill;

        q.exec("SELECT first_name FROM USER WHERE ID='"+ID+"'");
        if(q.first())
        {
            name_company = q.value(0).toString();
        }

        q.exec("SELECT last_name FROM USER WHERE ID='"+ID+"'");
        if(q.first())
        {
            lastName = q.value(0).toString();
        }

        q.exec("SELECT Bio FROM USER WHERE ID='"+ID+"'");
        if(q.first())
        {
            bio = q.value(0).toString();
        }

        q.exec("SELECT skill FROM USER WHERE ID='"+ID+"'");
        if(q.first())
        {
            Skill = q.value(0).toString();
        }

        ui->name->setText(name_company);
        ui->label_5->hide();
        ui->lastname->setText("");
        ui->bio->setText(bio);
        ui->skill->setText(Skill);
    }
    else
    {
        QSqlQuery q(db);

        q.exec("SELECT ID FROM userdb");
        if(q.first())
        {
            ID = q.value(0).toString();
        }

        if(QFile::exists("content/"+ID+"/res/pic/0.png"))
        {
            ui->me_button->setIcon(QIcon("content/"+ID+"/res/pic/0.png"));
        }
        else
        {
            ui->me_button->setIcon(QIcon("content/"+ID+"/res/pic/0.jpg"));
        }

        QString path = QDir::currentPath();

        path = path + "/content/" + ID + "/res/pic/0.";
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

        QString firstName;
        QString lastName;
        QString bio;
        QString Skill;

        q.exec("SELECT first_name FROM USER WHERE ID='"+ID+"'");
        if(q.first())
        {
            firstName = q.value(0).toString();
        }

        q.exec("SELECT last_name FROM USER WHERE ID='"+ID+"'");
        if(q.first())
        {
            lastName = q.value(0).toString();
        }

        q.exec("SELECT Bio FROM USER WHERE ID='"+ID+"'");
        if(q.first())
        {
            bio = q.value(0).toString();
        }

        q.exec("SELECT skill FROM USER WHERE ID='"+ID+"'");
        if(q.first())
        {
            Skill = q.value(0).toString();
        }

        ui->label_5->show();
        ui->name->setText(firstName);
        ui->lastname->setText(lastName);
        ui->bio->setText(bio);
        ui->skill->setText(Skill);
    }
}


void profile::on_make_company_clicked()
{
    ui->make_company->hide();
    make_company* comp = new make_company;
    comp->show();
    this->hide();
}


void profile::on_mynetwork_button_clicked()
{
    my_network* n = new my_network;
    n->show();
    this->close();
}


void profile::on_job_button_clicked()
{
    job_form* job_page_open = new job_form;

    job_page_open->show();

    this->close();
}


void profile::on_serach_button_clicked()
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


void profile::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {
        std::ofstream d("is_dark.txt");
        d << '0';
    }
    else
    {
        std::ofstream d("is_dark.txt");
        d << '1';
    }
}


void profile::on_message_button_clicked()
{
    get_the_user_ID(ID);
    message_contact* n = new message_contact;
    n->show();
    this->close();
}

