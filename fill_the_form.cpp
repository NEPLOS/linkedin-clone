#include "fill_the_form.h"
#include "ui_fill_the_form.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include <QFileInfo>
#include <QPixmap>
#include "QSqlQueryModel"
#include "person.h"
#include "mainwindow.h"
#include <QIntValidator>
#include "QMessageBox"
#include "main_page.h"
#include <direct.h>
#include <QDebug>
#include <QSqlError>
#include <sys/stat.h>
#include <QDir>
#include <qstring.h>
#include <fstream>
#include <QDirIterator>

bool save_data = 0;

QString user_mail;

bool dark_mode_fill_the_form = false;

QStringList company = {"google" , "Microsoft" , "amazon" , "apple" , "Samsung" , "IBM" , "Tesla" , "Intel" , "Netflix"  , "Meta" ,
                       "yahoo" , "NVIDIA" , "Visa" , "Adobe" , "Walmart" , "other"};

QStringList university = {"sharif" , "amirkabir", "tehran" , "tabriz" , "golestan" , "ferdowsi mashhad" , "isfahan" , "noshirvani" , "other"};

QStringList jobs = {"Web Developer" , "UI/UX Designer" , "AI/ML Engineer" , "Data Scientist" , "Software Engineer" , "Video Game Developer" ,
                   "AR/VR Developer" , "DataBase Developer" , "DataBase Administrator" , "Backend Developer" , "System Analyst" , "Cloud Engineer"
                   , "Robotic Engineer" , "Computer Support Specialist" , "Cybersecurity Specialist" , "Computer Network Architect" , "other"};

bool jobch = false;
bool unich = false;
bool comch = false;

inline void res_c(std::string addrs)
{
    _mkdir((addrs + "\\pic").c_str());
    _mkdir((addrs + "\\vid").c_str());
    _mkdir((addrs + "\\audio").c_str());

    QString path = QDir::currentPath();

    path = path + "/icons/person-profile-image-icon.png";

    QString if_pic = QString::fromStdString(addrs + "/pic/0.png");
    QFile::copy(path,if_pic);

}

inline void make_Dm_c(std::string addres)
{
    _mkdir((addres + "\\res" ).c_str());
    res_c(addres + "\\res");
    addres = addres + "\\user.db";
    std::ofstream jj(addres);
    jj.close();
}

inline void make_content_c(std::string addres)
{
    _mkdir((addres + "\\res" ).c_str());
    res_c(addres + "\\res");
    std::ofstream j((addres + "\\like.db").c_str());
    j.close();
    std::ofstream h((addres + "\\comment.db").c_str());
    h.close();
    std::ofstream f((addres + "\\post.db").c_str());
    f.close();
}

inline void make_data_c(std::string addres)
{
    //std::ofstream a((addres + "\\i_follow.db").c_str());
    //a.close();
    //std::ofstream b((addres + "\\they_follow.db").c_str());
    //b.close();
    std::ofstream c((addres + "\\personal.db").c_str());
    c.close();
    std::ofstream s((addres + "\\connections.db").c_str());
    s.close();

    QSqlDatabase dat = QSqlDatabase::addDatabase("QSQLITE");
    dat.setDatabaseName(QString::fromStdString(addres) + "/connections.db");
    dat.open();

    QSqlQuery temp_q(dat);

    if (!temp_q.exec("CREATE TABLE IF NOT EXISTS pending(user_id TEXT)"))
    {
        qDebug() << "Failed to create pending table:" << temp_q.lastError().text();
    }
    if (!temp_q.exec("CREATE TABLE IF NOT EXISTS connected(user_id TEXT)"))
    {
        qDebug() << "Failed to create connected table:" << temp_q.lastError().text();
    }
    if (!temp_q.exec("CREATE TABLE IF NOT EXISTS follow(user_id TEXT)"))
    {
        qDebug() << "Failed to create follow table:" << temp_q.lastError().text();
    }
}

void file_C(std::string a , std::string path , std::string ID)
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
        make_Dm_c(content);
      }
      else if(a=="content")
      {
        make_content_c(content);
      }
      else
      {
        make_data_c(content);
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

void make_all(std::string ID, std::string path)
{
    file_C("DM" , path , ID);
    file_C("data" , path , ID);
    file_C("content" , path , ID);
}

fill_the_form::fill_the_form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fill_the_form)
{
    ui->setupUi(this);

    if(dark_mode_fill_the_form)
    {
        set_color();
    }

    ui->job_box->addItems(jobs);

    ui->uni_box->addItems(university);

    ui->company_box->addItems(company);

    ui->phoneNumber->setValidator(new QIntValidator);

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
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

    QString skills = ui->skills->text();

    QString phone_number = ui->phoneNumber->text();

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
        return;
    }
    if(ln.length() < 1)
    {
        QMessageBox::warning(this,"","enter your last name" , "ok");
        return;
    }

    if(phone_number.size() < 5)
    {
        QMessageBox::warning(this,"","enter your phone number" , "ok");
        return;
    }

    set_dark_mode_main_page(dark_mode_fill_the_form);

    QString file_path = QDir::currentPath();

    QString folderPath = file_path + "/content";

    QDirIterator it(folderPath, QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    QString numFiles;

    QSqlQuery qqq;
    qqq.prepare("SELECT COUNT(*) FROM USER");

    if (!qqq.exec())
    {

    }
    int numRows = 0;
    if (qqq.next()) {
        numRows = qqq.value(0).toInt();
    }

    numFiles = QString::number(numRows);

    QString bio = "";

    Person person(ln,fn,skills,numFiles,phone_number,user_mail);

    q.exec("UPDATE USER SET first_name='"+person.get_first_name()+"' WHERE email='"+user_mail+"'");
    q.exec("UPDATE USER SET last_name='"+person.get_last_name()+"' WHERE email='"+user_mail+"'");
    q.exec("UPDATE USER SET birthday='"+date+"' WHERE email='"+user_mail+"'");
    q.exec("UPDATE USER SET ID='"+person.get_Account_ID()+"' WHERE email='"+user_mail+"'");
    q.exec("UPDATE USER SET Bio='"+bio+"' WHERE email='"+user_mail+"'");
    q.exec("UPDATE USER SET Phone_number='"+person.get_Phone_number()+"' WHERE email='"+user_mail+"'");
    if(!q.exec("UPDATE USER SET skill='"+person.get_skills()+"' WHERE email='"+user_mail+"'"))
    {
        qDebug() << "faild : " << q.lastError().text();
    }

    if(save_data == true)
    {
        q.exec("UPDATE userdb SET ID='"+numFiles+"' WHERE email='"+user_mail+"'");
    }

    make_all(numFiles.toStdString(),file_path.toStdString());

    main_page *k = new main_page;
    k->show();
    this->close();


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

void set_bool_save_r(bool b)
{
    save_data = b;
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
    ui->skills->setStyleSheet("color: rgb(255, 255, 255);");
    ui->phoneNumber->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_7->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_8->setStyleSheet("color: rgb(255, 255, 255);");
}
