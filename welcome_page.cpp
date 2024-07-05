#include "welcome_page.h"
#include "ui_wellcome_page.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"
#include "mainwindow.h"

welcome_page::welcome_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::welcome_page)
{
    ui->setupUi(this);
}

welcome_page::~welcome_page()
{
    delete ui;
}

void welcome_page::on_pushButton_clicked()
{
    MainWindow *y = new MainWindow;
    y->show();
    this->close();

}

