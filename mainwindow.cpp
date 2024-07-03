#include "verify_code.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include <ctime>
#include "fill_the_form.h"
#include "main_page.h"
#include <QDir>


bool have_an_ac = true;
bool dark_mode = false;
bool is_hide = true;

QString test;

QString capgenerator();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    srand(time(0));

    ui->setupUi(this);
    ui->AC->hide();

    ui->email_box->setPlaceholderText(" enter your email address...");
    ui->Passbox->setPlaceholderText(" enter your password...");
    ui->Passbox->setEchoMode(QLineEdit::Password);
    ui->captcha_input->setPlaceholderText(" enter the captcha...");
    ui->captcha->setText(capgenerator());
    ui->captcha->setEnabled(false);
    ui->checkBox->setChecked(true);

    if(dark_mode)
    {
        set_color();
    }

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString capgenerator()
{
    QString Cd = "";

    int min;

    for(int i = 0 ; i < 6 ; i++)
    {
        int number = rand() % 3;

        if(number == 0)
        {
            Cd = Cd + (char)(rand() % 10 + 48);
        }
        else
        {
            bool upper = rand() % 2;

            upper? min = 65 : min = 97;

            int temp = rand() % 26 + min;

            Cd = Cd + (char)temp;
        }
    }

    test = Cd;

    return Cd;
}

void MainWindow::on_DC_clicked()
{
    ui->DC->hide();
    ui->AC->show();
    ui->pushButton->setText("Join now");
    ui->captcha_input->setText("");
    ui->captcha->setText(capgenerator());
    have_an_ac = false;
}


void MainWindow::on_AC_clicked()
{
    ui->AC->hide();
    ui->DC->show();
    ui->pushButton->setText("Login");
    ui->captcha_input->setText("");
    ui->captcha->setText(capgenerator());
    have_an_ac = true;
}

void MainWindow::on_pushButton_clicked()
{

    bool r = ui->checkBox->checkState();

    if(ui->captcha_input->text() != test)
    {
        ui->WARNING->setText("!!! WRONG CAPTCHA !!!");
        ui->WARNING->setStyleSheet("color: rgb(199, 0, 57);");
        ui->captcha_input->setText("");
        ui->captcha->setText(capgenerator());
    }
    else
    {

        QString Uemail  = ui->email_box->text();

        QString Pass = ui->Passbox->text();

        QSqlQuery check;

        check.exec("SELECT email FROM USER WHERE email='"+Uemail+"'");

        if(!have_an_ac)
        {
            if(check.first())
            {
                ui->WARNING->setText("!!! EMAIL ALREADY EXIST !!!");
                ui->WARNING->setStyleSheet("color: rgb(199, 0, 57);");
                ui->captcha_input->setText("");
                ui->captcha->setText(capgenerator());
            }
            else
            {
                if(Pass.length() < 7)
                {
                    ui->WARNING->setText("!!! PASSWORD IS LESS THAN 8 CHAR !!!");
                    ui->WARNING->setStyleSheet("color: rgb(199, 0, 57);");
                    ui->captcha_input->setText("");
                    ui->captcha->setText(capgenerator());
                }
                else
                {
                    check.exec("INSERT INTO USER(email,password)VALUES('"+Uemail+"' , '"+Pass+"')");

                    QSqlQuery v;

                    if(r)
                    {
                        v.exec("DELETE FROM userdb");
                        v.exec("INSERT INTO userdb(email,password)VALUES('"+Uemail+"' , '"+Pass+"')");
                    }
                    else
                    {
                        v.exec("DELETE FROM userdb");
                    }

                    verify_code *vcode = new verify_code;
                    set_bool_dark_mode_verify_code(dark_mode);

                    set_bool_save_r(r);

                    mailmail(Uemail);
                    vcode->show();
                    this->close();

                }
            }
        }
        else
        {
            if(!check.first())
            {
                ui->WARNING->setText("!!! EMAIL DOES NOT EXIST !!!");
                ui->WARNING->setStyleSheet("color: rgb(199, 0, 57);");
                ui->captcha_input->setText("");
                ui->captcha->setText(capgenerator());
            }
            else
            {

                check.exec("SELECT password,ID FROM USER WHERE email='"+Uemail+"' AND password='"+Pass+"'");

                if(check.first())
                {
                    QString temp_temp_ID = check.value("ID").toString();

                    QSqlQuery v;

                    if(r)
                    {
                        v.exec("DELETE FROM userdb");
                        v.exec("INSERT INTO userdb(email,password,ID)VALUES('"+Uemail+"' , '"+Pass+"' , '"+temp_temp_ID+"')");
                    }
                    else
                    {
                        v.exec("DELETE FROM userdb");
                    }

                    set_ID_from_LOGIN(temp_temp_ID);
                    set_dark_mode_main_page(dark_mode);
                    main_page *mainp = new main_page;

                    mailmail(Uemail);
                    mainp->show();
                    this->close();
                }
                else
                {
                    ui->WARNING->setText("!!! WRONG PASSWORD!!!");
                    ui->WARNING->setStyleSheet("color: rgb(199, 0, 57);");
                    ui->captcha_input->setText("");
                    ui->captcha->setText(capgenerator());
                }
            }
        }
    }
}

void MainWindow::set_color()
{
    MainWindow::setStyleSheet("background-color: rgb(66, 69, 73);");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->pushButton->setStyleSheet("color: rgb(0, 0, 0);");
    ui->pushButton->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->AC->setStyleSheet("color: rgb(0, 0, 0);");
    ui->AC->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->DC->setStyleSheet("color: rgb(0, 0, 0);");
    ui->DC->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->hide_pass->setStyleSheet("color: rgb(0, 0, 0);");
    ui->hide_pass->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->email_box->setStyleSheet("color: rgb(255, 255, 255);");
    ui->Passbox->setStyleSheet("color: rgb(255, 255, 255);");
    ui->captcha->setStyleSheet("color: rgb(255, 255, 255);");
    ui->captcha_input->setStyleSheet("color: rgb(255, 255, 255);");
    ui->checkBox->setStyleSheet("color: rgb(255, 255, 255);");
}

void set_bool_dark_mode_mainwindows(bool n)
{
    dark_mode = n;
}

void MainWindow::on_hide_pass_clicked()
{
    is_hide = -is_hide + 1;

    if(is_hide)
    {
        ui->Passbox->setEchoMode(QLineEdit::Password);
        ui->hide_pass->setText("show");
    }
    else
    {
        ui->Passbox->setEchoMode(QLineEdit::Normal);
        ui->hide_pass->setText("hide");
    }
}

