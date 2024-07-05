#include "comments.h"
#include "ui_comments.h"
#include "post.h"
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
#include <QLabel>
#include <QVBoxLayout>
#include "main_page.h"
#include <direct.h>
#include <QDebug>
#include <QSqlError>
#include <sys/stat.h>
#include <QDir>
#include <qstring.h>
#include <fstream>
#include <QDirIterator>
#include <QSqlError>
#include <QScrollBar>

QString post_sender_id;
QString my_id_comment;
QString post_id_comment;

void comments::add_scroll_area()
{

    if (!QSqlDatabase::contains("comment_page"))
    {
        QSqlDatabase dbComments = QSqlDatabase::addDatabase("QSQLITE", "comment_page");
        dbComments.setDatabaseName(QDir::currentPath() + "/content/" + post_sender_id + "/comment.db");
    }

    if (!QSqlDatabase::contains("linkedin_page"))
    {
        QSqlDatabase dbLinkedIn = QSqlDatabase::addDatabase("QSQLITE", "linkedin_page");
        dbLinkedIn.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");
    }

    QSqlDatabase dbComments = QSqlDatabase::database("comment_page");
    QSqlDatabase dbLinkedIn = QSqlDatabase::database("linkedin_page");

    if (!dbComments.open())
    {
        qDebug() << "cant 1 : " << dbComments.lastError().text();
        return;
    }

    if (!dbLinkedIn.open())
    {
        qDebug() << "cant 2 : " << dbLinkedIn.lastError().text();
        return;
    }

    QSqlQuery qComments(dbComments);
    qComments.prepare("SELECT senderID, contenttext FROM '" + post_id_comment + "'");

    if (!qComments.exec())
    {
        qDebug() << "cant 3 : " << qComments.lastError().text();
        return;
    }

    QWidget *scrollAreaContent = ui->scrollArea->widget();
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(scrollAreaContent->layout());
    if (!layout)
    {
        layout = new QVBoxLayout(scrollAreaContent);
        scrollAreaContent->setLayout(layout);
    }

    while (qComments.next())
    {
        QString sender_id = qComments.value("senderID").toString();
        QString content_text = qComments.value("contenttext").toString();

        QSqlQuery linkedin_db_q_3(dbLinkedIn);
        linkedin_db_q_3.prepare("SELECT first_name, last_name FROM USER WHERE ID='"+sender_id+"'");
        QString fn, ln;
        if (linkedin_db_q_3.exec() && linkedin_db_q_3.next())
        {
            fn = linkedin_db_q_3.value("first_name").toString();
            ln = linkedin_db_q_3.value("last_name").toString();
        }
        else
        {
            qDebug() << linkedin_db_q_3.lastError().text();
        }

        QLabel *label = new QLabel(QString(" %1 %2 : %3").arg(fn).arg(ln).arg(content_text), this);
        layout->addWidget(label);
    }

    QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

comments::comments(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comments)
{
    ui->setupUi(this);
    add_scroll_area();
}

comments::~comments()
{
    delete ui;
}

void get_the_id(QString post_id, QString sender_id, QString my_id)
{
    post_sender_id = sender_id;
    my_id_comment = my_id;
    post_id_comment = post_id;
}

void comments::on_send_clicked()
{
    QString m_comment = ui->comment_input->text();

    if (m_comment.trimmed().isEmpty()) {
        return;
    }

    if (!QSqlDatabase::contains("comment_page_2"))
    {
        QSqlDatabase dbComments = QSqlDatabase::addDatabase("QSQLITE", "comment_page_2");
        dbComments.setDatabaseName(QDir::currentPath() + "/content/" + post_sender_id + "/comment.db");
    }

    QSqlDatabase dbComments = QSqlDatabase::database("comment_page_2");

    QSqlQuery dbComments_query(dbComments);
    dbComments_query.prepare("SELECT COUNT(*) FROM '" + post_id_comment + "'");

    if (!dbComments_query.exec())
    {
        qDebug() << dbComments_query.lastError().text();
        return;
    }

    int temp = 0;
    if (dbComments_query.next())
    {
        temp = dbComments_query.value(0).toInt();
    }
    temp++;
    QString comment_id = QString::number(temp);

    Comment commet(my_id_comment, m_comment, "Empty", "Empty", "Empty", post_id_comment, comment_id);

    dbComments_query.prepare("INSERT INTO '" + post_id_comment + "' (senderID, Contenttext, ContentPicture, ContentVideo, ContentAudio, PostID, commentID, hour, minute, second, year, month, day) VALUES (:sender_id, :content_text, :content_picture, :content_video, :content_audio, :post_id, :comment_id, :hour, :minute, :second, :year, :month, :day)");
    dbComments_query.bindValue(":sender_id", commet.get_sender_ID());
    dbComments_query.bindValue(":content_text", commet.get_content_text());
    dbComments_query.bindValue(":content_picture", commet.get_content_Picture());
    dbComments_query.bindValue(":content_video", commet.get_content_Video());
    dbComments_query.bindValue(":content_audio", commet.get_content_Audio());
    dbComments_query.bindValue(":post_id", commet.get_Post_ID());
    dbComments_query.bindValue(":comment_id", commet.get_comment_ID());
    dbComments_query.bindValue(":hour", commet.get_time_send().get_hour());
    dbComments_query.bindValue(":minute", commet.get_time_send().get_minute());
    dbComments_query.bindValue(":second", commet.get_time_send().get_second());
    dbComments_query.bindValue(":year", commet.get_time_send().get_year());
    dbComments_query.bindValue(":month", commet.get_time_send().get_month());
    dbComments_query.bindValue(":day", commet.get_time_send().get_day());

    if (!dbComments_query.exec())
    {
        qDebug() << "can't insert: " << dbComments_query.lastError().text();
        return;
    }

    QWidget *scrollAreaContent = ui->scrollArea->widget();
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(scrollAreaContent->layout());

    if (!layout)
    {
        layout = new QVBoxLayout(scrollAreaContent);
        scrollAreaContent->setLayout(layout);
    }

    QSqlDatabase dbLinkedIn = QSqlDatabase::database("linkedin_page");

    if (!dbLinkedIn.open())
    {
        qDebug() << "cant";
        return;
    }

    QSqlQuery qLinkedIn(dbLinkedIn);
    qLinkedIn.prepare("SELECT first_name, last_name FROM USER WHERE ID = :sender_id");
    qLinkedIn.bindValue(":sender_id", commet.get_sender_ID());

    QString first_name, last_name;
    if (qLinkedIn.exec() && qLinkedIn.next())
    {
        first_name = qLinkedIn.value("first_name").toString();
        last_name = qLinkedIn.value("last_name").toString();
    }
    else
    {
        qDebug() << "cant select";
        return;
    }

    QLabel *label = new QLabel(QString(" %1 %2 : %3").arg(first_name).arg(last_name).arg(m_comment), this);
    layout->addWidget(label);

    QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());

    ui->comment_input->clear();
}
