#include "main_file_first.h"
#include "welcome_page.h"
#include "mainwindow.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

main_file_first::main_file_first(QObject *parent)
    : QAbstractItemModel(parent)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("h:\\linkedin_C.db");
    db.open();

    QSqlQuery q;
    QSqlQuery f;

    q.exec("SELECT password FROM userdb");

    if(q.first())
    {
        QString g = q.value(0).toString();

        f.exec("SELECT email FROM USER WHERE password");
        if(f.first())
        {
            MainWindow *y = new MainWindow;
            y->show();
        }
        else
        {
            Wellcome_page *i = new Wellcome_page;
            i->show();
        }
    }
    else
    {
        Wellcome_page *i = new Wellcome_page;
        i->show();
    }

}
