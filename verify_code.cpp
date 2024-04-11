#include "verify_code.h"
#include "ui_verify_code.h"
#include "QMessageBox"
#include "QString"
#include <ctime>
#include <QIntValidator>
#include <fill_the_form.h>
#include <main_page.h>

int a;
bool acc_have;
bool dark_mode_2 = false;

verify_code::verify_code(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::verify_code)
{

    ui->setupUi(this);

    this->setWindowTitle("Verify code");

    srand(time(NULL));

    if(dark_mode_2)
    {
        set_color_verify_code();
    }

    ui->code_input->setValidator(new QIntValidator);
}

verify_code::~verify_code()
{
    delete ui;
}

void verify_code::on_get_the_code_clicked()
{
    a = rand() % 9000 + 1000;

    QMessageBox::information(this,"Verify your email","to verify your email , enter ths code : " + QString::number(a), "ok");

    ui->get_the_code->setEnabled(false);

}

void haveacc(bool t)
{
    acc_have = t;
}

void verify_code::on_done_clicked()
{
    QString user_input = ui->code_input->text();

    int user_input_int;

    if(user_input == "" || user_input == "+" || user_input == "-" || user_input.length() != 4)
    {
        goto warn;
    }
    else
    {
        user_input_int = user_input.toInt();
    }

    if(user_input_int != a)
    {
        warn:

        QMessageBox::warning(this,"WRONG" , "WRONG CODE");
        ui->get_the_code->setEnabled(true);
        a = 0;
    }
    else
    {
        if(acc_have)
        {
            main_page *p = new main_page;
            p->show();
            this->close();
        }
        else
        {
            set_dark_mode_fill_the_form(dark_mode_2);

            fill_the_form *p = new fill_the_form;
            p->show();
            this->close();
        }
    }
}

void verify_code::set_color_verify_code()
{
    verify_code::setStyleSheet("background-color: rgb(66, 69, 73);");
    ui->code_input->setStyleSheet("color: rgb(255, 255, 255);");
    ui->done->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);");
    ui->get_the_code->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(255, 255, 255);");

}

void set_bool_dark_mode_verify_code(bool n)
{
    dark_mode_2 = n;
}


