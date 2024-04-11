#include "main_page.h"
#include "ui_main_page.h"
#include "QString"
#include <QFileInfo>
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include "welcome.h"

bool dark_mode_main_page = false;

main_page::main_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_page)
{
    ui->setupUi(this);

    this->setWindowTitle("Main page");

    if(dark_mode_main_page)
    {
        set_color();
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("h:/Project/data/linkedin_C.db");
    db.open();
}

main_page::~main_page()
{
    delete ui;
}

void main_page::on_pushButton_clicked()
{
    QSqlQuery q;
    q.exec("DELETE FROM userdb");

    welcome *t = new welcome;
    t->show();
    this->close();
}

void set_dark_mode_main_page(bool g)
{
    dark_mode_main_page = g;
}

void main_page::set_color()
{
    main_page::setStyleSheet("background-color: rgb(66, 69, 73);");
    ui->pushButton->setStyleSheet("color: rgb(0, 0, 0);");
    ui->pushButton->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");
}

