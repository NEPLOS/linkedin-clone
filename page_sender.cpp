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


page_sender::page_sender(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::page_sender)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("h:/Project/data/linkedin_C.db");
    db.open();

    if(!db.open())
    {
        QMessageBox::warning(this," " , " can't connect to the Database ", "OK");
    }

    QSqlQuery q;

    QString temp_mail;

    q.exec("SELECT email FROM userdb");
    if(q.first())
    {
        temp_mail = q.value(0).toString();
    }

    q.exec("SELECT password FROM userdb");

    QString temp_pass;

    if(q.first())
    {
        temp_pass = q.value(0).toString();
    }

    q.exec("SELECT password FROM USER WHERE email='"+temp_mail+"'");
    if(q.first())
    {
        QString pass_in_db = q.value(0).toString();

        if(temp_pass == pass_in_db)
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

page_sender::~page_sender()
{
    delete ui;
}
