#include "welcome.h"
#include "ui_welcome.h"
#include "mainwindow.h"
#include "fill_the_form.h"
#include "main_page.h"
#include <fstream>
#include "verify_code.h"
#include "QDate"
#include <QDir>

bool have_dark_mode_welcome = false;

welcome::welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Light");
    ui->comboBox->addItem("Dark");
    setMaximumSize(1167,600);
    setMinimumSize(1167,600);
    QString s= QDate::currentDate().toString();
    ui->date_lable->setText(s);
    std::string color;
    std::ifstream color_theme("is_dark.txt");
    color_theme >> color;
    if(color == "1")
    {
        on_comboBox_activated(1);
    }
    else
    {
        on_comboBox_activated(0);
    }

}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_pushButton_clicked()
{
    MainWindow *j = new MainWindow;

    j->show();
    this->close();
}


void welcome::on_comboBox_activated(int index)
{

    if(index == 1)
    {
        ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
        ui->label_3->setStyleSheet("color: rgb(255, 255, 255);");
        ui->label_4->setStyleSheet("color: rgb(255, 255, 255);");
        ui->label_5->setStyleSheet("color: rgb(255, 255, 255);");
        ui->label_6->setStyleSheet("color: rgb(255, 255, 255);");
        ui->label_7->setStyleSheet("color: rgb(255, 255, 255);");
        ui->label_8->setStyleSheet("color: rgb(255, 255, 255);");
        ui->pushButton->setStyleSheet("color: rgb(255, 255, 255);");
        ui->pushButton->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->comboBox->setStyleSheet("color: rgb(255, 255, 255);");
        ui->date_lable->setStyleSheet("color: rgb(255, 255, 255);");

        welcome::setStyleSheet("background-color: rgb(66, 69, 73);");
        have_dark_mode_welcome = true;
        set_bool_dark_mode_mainwindows(true);
        set_bool_dark_mode_verify_code(true);
        std::ofstream color_them("is_dark.txt");
        color_them  << 1;

    }
    else
    {

        ui->label_2->setStyleSheet("color: rgb(0, 0, 0);");
        ui->label_3->setStyleSheet("color: rgb(0, 0, 0);");
        ui->label_4->setStyleSheet("color: rgb(0, 0, 0);");
        ui->label_5->setStyleSheet("color: rgb(0, 0, 0);");
        ui->label_6->setStyleSheet("color: rgb(0, 0, 0);");
        ui->label_7->setStyleSheet("color: rgb(0, 0, 0);");
        ui->label_8->setStyleSheet("color: rgb(0, 0, 0);");
        ui->pushButton->setStyleSheet("color: rgb(0, 0, 0);");
        ui->pushButton->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->comboBox->setStyleSheet("color: rgb(0, 0, 0);");
        ui->date_lable->setStyleSheet("color: rgb(0, 0, 0);");

        welcome::setStyleSheet("");
        have_dark_mode_welcome = false;
        set_bool_dark_mode_mainwindows(false);
        set_bool_dark_mode_verify_code(false);
        std::ofstream color_them("is_dark.txt");
        color_them  << 0;
    }

}

