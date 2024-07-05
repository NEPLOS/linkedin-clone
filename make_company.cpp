#include "make_company.h"
#include "ui_make_company.h"
#include "QString"
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

QString ID_C;


inline void res(std::string addrs)
{
    _mkdir((addrs + "\\pic").c_str());
    _mkdir((addrs + "\\vid").c_str());
    _mkdir((addrs + "\\audio").c_str());

    QString path = QDir::currentPath();

    path = path + "/icons/person-profile-image-icon.png";

    QString if_pic = QString::fromStdString(addrs + "/pic/0.png");
    QFile::copy(path,if_pic);

}

inline void make_content(std::string addres)
{
    _mkdir((addres + "\\res" ).c_str());
    res(addres + "\\res");
    std::ofstream j((addres + "\\like.db").c_str());
    j.close();
    std::ofstream h((addres + "\\comment.db").c_str());
    h.close();
    std::ofstream f((addres + "\\post.db").c_str());
    f.close();
    std::ofstream a((addres + "\\job.db").c_str());
    a.close();
    std::ofstream b((addres + "\\employee.db").c_str());
    b.close();
}

inline void make_data(std::string addres)
{
    std::ofstream b((addres + "/connections.db").c_str());
    b.close();
    std::ofstream c((addres + "/personal.db").c_str());
    c.close();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","make_the_follow");

    db.setDatabaseName(QString::fromStdString(addres) + "/connections.db");
    db.open();

    QSqlQuery q(db);

    if (!q.exec("CREATE TABLE IF NOT EXISTS follow(user_id TEXT)"))
    {
        qDebug() << "Failed to create pending table:" << q.lastError().text();
    }

}

void file(std::string a , std::string path , std::string ID)
{
  struct stat sd;
  a_file:
  if(stat((path + "\\" + a).c_str(), &sd) == 0)
  {
    id_file:
    std::string content = path + "\\" + a + "\\" + ID;
    if(stat(content.c_str(), &sd) == 0)
    {
      if(a=="DM")
      {

      }
      else if(a=="content")
      {
        make_content(content);
      }
      else
      {
        make_data(content);
      }
    }
    else
    {
      _mkdir(content.c_str());
      goto id_file;
    }
  }
  else
  {
    _mkdir((path + "\\" + a).c_str());
    goto a_file;
  }
}

make_company::make_company(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::make_company)
{
    ui->setupUi(this);

    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->me_button->setIcon(QIcon("icons/person-profile-image-icon.png"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q;

    q.exec("SELECT ID FROM userdb");
    if(q.first())
    {
        ID_C = q.value(0).toString();
    }

    if(QFile::exists("content/"+ID_C+"/res/pic/0.png"))
    {
        ui->me_button->setIcon(QIcon("content/"+ID_C+"/res/pic/0.png"));
    }
    else
    {
        ui->me_button->setIcon(QIcon("content/"+ID_C+"/res/pic/0.jpg"));
    }

    ui->company_phone_number->setValidator(new QIntValidator);


}

make_company::~make_company()
{
    delete ui;
}

void make_company::on_pushButton_2_clicked()
{
    QString name = ui->company_name->text();
    QString email = ui->company_email->text();
    QString phone_number = ui->company_phone_number->text();

    if(phone_number.size() < 5)
    {
        QMessageBox::warning(this,"","enter your phone number" , "ok");
        return;
    }

    if(name.size() < 1)
    {
        QMessageBox::warning(this,"","enter your company name" , "ok");
        return;
    }

    if(email.size() < 6)
    {
        QMessageBox::warning(this,"","enter your email address" , "ok");
        return;
    }

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q(db);

    QString user_comapny_id = ID_C + "C";

    QString Uemail;

    q.exec("SELECT email FROM userdb");
    if(q.first())
    {
        Uemail = q.value(0).toString();
    }

    if(Uemail == email)
    {
        QMessageBox::warning(this,"","U CAN'T USE THIS EMAIL FOR YOUR COMAPNY","ok");
        return;
    }

    q.exec("UPDATE userdb SET IDC='"+user_comapny_id+"' WHERE ID='"+ID_C+"'");

    if(!q.exec("INSERT INTO USER(email,first_name,Phone_number,ID)VALUES('"+email+"' , '"+name+"' , '"+phone_number+"' , '"+user_comapny_id+"')"))
    {
        qDebug() << q.lastError().text();
    }
    file("content", QDir::currentPath().toStdString() ,user_comapny_id.toStdString());
    file("data" , QDir::currentPath().toStdString() ,user_comapny_id.toStdString());
    profile* fd = new profile;
    fd->show();
    this->close();
}

