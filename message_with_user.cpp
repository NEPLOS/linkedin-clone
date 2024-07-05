
#include "message_with_user.h"
#include "ui_message_with_user.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include <QFileInfo>
#include <QPixmap>
#include <QDir>
#include "QSqlQueryModel"
#include "person.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <qlabel.h>
#include "qsqlerror.h"
#include <QIntValidator>
#include "QMessageBox"
#include "qdebug.h"

QString me_me_me_ID;
QString user_user_user_ID;

void get_the_ideas_chat_screen(QString me , QString user)
{
    me_me_me_ID = me;
    user_user_user_ID = user;
}

void message_with_user::add_scroll_area()
{
    QSqlDatabase db = QSqlDatabase::database("main_db_chat_creen_lkdnal");
    if (!db.isValid())
    {
        db = QSqlDatabase::addDatabase("QSQLITE", "main_db_chat_creen_lkdnal");
        db.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");
        if (!db.open())
        {
            qDebug() << db.lastError().text();
            return;
        }
    }

    QSqlDatabase me_db = QSqlDatabase::database("main_db_chat_creen_lkdfsddsdfdnal");
    if (!me_db.isValid())
    {
        me_db = QSqlDatabase::addDatabase("QSQLITE", "main_db_chat_creen_lkdfsddsdfdnal");
        me_db.setDatabaseName(QDir::currentPath() + "/DM/" + me_me_me_ID + "/user.db");
        if (!me_db.open())
        {
            qDebug() << me_db.lastError().text();
            return;
        }
    }

    QSqlDatabase user_db = QSqlDatabase::database("main_fsdsfdb_chat_creen_lkdfsddsdfdnal");
    if (!user_db.isValid())
    {
        user_db = QSqlDatabase::addDatabase("QSQLITE", "main_fsdsfdb_chat_creen_lkdfsddsdfdnal");
        user_db.setDatabaseName(QDir::currentPath() + "/DM/" + user_user_user_ID + "/user.db");
        if (!user_db.open())
        {
            qDebug() << user_db.lastError().text();
            return;
        }
    }

    QWidget *scrollAreaContent = ui->chat_screen->widget();
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(scrollAreaContent->layout());
    if (!layout)
    {
        layout = new QVBoxLayout(scrollAreaContent);
        scrollAreaContent->setLayout(layout);
    }
    else
    {
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr)
        {
            delete child->widget();
            delete child;
        }
    }

    QSqlQuery me_db_q(me_db);
    if (me_db_q.exec("SELECT user_id, message FROM '" + user_user_user_ID + "'"))
    {
        while (me_db_q.next())
        {
            QString sender_id = me_db_q.value("user_id").toString();
            QString content_text = me_db_q.value("message").toString();

            QSqlQuery qLinkedIn(db);
            qLinkedIn.prepare("SELECT first_name, last_name FROM USER WHERE ID = :sender_id");
            qLinkedIn.bindValue(":sender_id", sender_id);
            if (qLinkedIn.exec() && qLinkedIn.next())
            {
                QString first_name = qLinkedIn.value("first_name").toString();
                QString last_name = qLinkedIn.value("last_name").toString();

                QLabel *label = new QLabel(QString(" %1 %2 : %3").arg(first_name).arg(last_name).arg(content_text), this);
                layout->addWidget(label);
            }
        }
    }
}




message_with_user::message_with_user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::message_with_user)
{
    ui->setupUi(this);

    //user_user_user_ID

    QString e;
    if(QFile::exists(QDir::currentPath() + "/content/" + user_user_user_ID + "/res/pic/0.png"))
    {
        e = QDir::currentPath() + "/content/" + user_user_user_ID + "/res/pic/0.png";
    }
    else
    {
        e = QDir::currentPath() + "/content/" + user_user_user_ID + "/res/pic/0.jpg";
    }
    QPixmap ui_res(e);
    QPixmap scaled_pixmap = ui_res.scaled(41, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->profile->setPixmap(scaled_pixmap);

    QSqlDatabase database_username = QSqlDatabase::addDatabase("QSQLITE", "message_for_username_2_0");
    database_username.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");
    database_username.open();
    if(!database_username.isOpen())
    {
        qDebug() << "database is not open ";
    }
    QSqlQuery d(database_username);

    if(!d.exec("SELECT first_name , last_name FROM USER WHERE ID='"+user_user_user_ID+"'"))
    {
        qDebug() << "cant select : " << d.lastError().text();
    }

    QString fn;
    QString ln;

    if(d.first())
    {
        fn = d.value("first_name").toString();
        ln = d.value("last_name").toString();
    }

    ui->user_name->setText(fn + ' ' + ln);

    add_scroll_area();

}

message_with_user::~message_with_user()
{
    delete ui;
}

void message_with_user::on_send_clicked()
{
    QString message = ui->user_input->text();

    if (message.isEmpty())
    {
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "hghghjhhg");
    db.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");
    if (!db.open())
    {
        qDebug() << "Failed to open main database:" << db.lastError().text();
        return;
    }

    QSqlDatabase me_db = QSqlDatabase::addDatabase("QSQLITE", "fddsfsdfsd");
    me_db.setDatabaseName(QDir::currentPath() + "/DM/" + me_me_me_ID + "/user.db");
    if (!me_db.open())
    {
        qDebug() << me_db.lastError().text();
        return;
    }

    QSqlDatabase user_db = QSqlDatabase::addDatabase("QSQLITE", "fddfdsfgsdfsd");
    user_db.setDatabaseName(QDir::currentPath() + "/DM/" + user_user_user_ID + "/user.db");
    if (!user_db.open())
    {
        qDebug()  << user_db.lastError().text();
        return;
    }

    QSqlQuery one(me_db);
    if (!one.exec("INSERT INTO '"+user_user_user_ID+"'(user_id, message)VALUES('"+me_me_me_ID+"','"+message+"')"))
    {
        qDebug() << one.lastError().text();
        return;
    }

    QSqlQuery two(user_db);
    if (!two.exec("INSERT INTO '"+ me_me_me_ID +"'(user_id, message)VALUES('"+me_me_me_ID+"','"+message+"')"))
    {
        qDebug() << two.lastError().text();
        return;
    }

    QSqlQuery qqq(db);
    QString fn, ln;
    if (!qqq.exec("SELECT first_name, last_name FROM USER WHERE ID='" + me_me_me_ID + "'"))
    {
        qDebug() << qqq.lastError().text();
        return;
    }
    if (qqq.first())
    {
        fn = qqq.value("first_name").toString();
        ln = qqq.value("last_name").toString();
    }

    QWidget *scrollAreaContent = ui->chat_screen->widget();
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(scrollAreaContent->layout());
    if (!layout)
    {
        layout = new QVBoxLayout(scrollAreaContent);
        scrollAreaContent->setLayout(layout);
    }
    QLabel *label = new QLabel(QString(" %1 %2 : %3").arg(fn).arg(ln).arg(message), this);
    layout->addWidget(label);

    ui->user_input->clear();
}
