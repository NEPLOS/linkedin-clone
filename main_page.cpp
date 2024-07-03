#include "main_page.h"
#include "ui_main_page.h"
#include "QString"
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QSqlQuery"
#include "job_form.h"
#include <qpixmap.h>
#include "QSqlQueryModel"
#include "my_network.h"
#include "QSqlError"
#include "profile.h"
#include "comments.h"
#include <qpixmap.h>
#include "error.h"
#include <qfile.h>
#include <qfileinfo.h>
#include "welcome.h"
#include <qdebug.h>
#include <QDir>
#include "send_post.h"
#include "view_profile.h"
#include "message_contact.h"
#include "QMessageBox"



QString HOME_ID = "1";
QString POST_ID = "1";
QString MY_ID_HOME_PAGE;

bool dark_mode_main_page = false;

void color_the_theme();

main_page::main_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_page)
{
    ui->setupUi(this);


    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->me_button->setIcon(QIcon("icons/person-profile-image-icon.png"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->next_pushbutton->setIcon(QIcon("icons/down.png"));
    ui->previous_pushbutton->setIcon(QIcon("icons/hand-finger-up-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));
    ui->share_button->setIcon(QIcon("icons/paper-plane-icon.png"));
    ui->like_button->setIcon(QIcon("icons/heart-thin-icon.png"));

    if(QFile::exists("content/"+HOME_ID+"/res/pic/0.png"))
    {
         ui->profile->setIcon(QIcon("content/"+HOME_ID+"/res/pic/0.png"));
    }
    else
    {
        ui->profile->setIcon(QIcon("content/"+HOME_ID+"/res/pic/0.jpg"));
    }
    ui->profile->setIconSize(QSize{64,64});
    if(dark_mode_main_page)
    {
        set_color();
    }

    QString database_path = QDir::currentPath();

    database_path = database_path + "/content/"+HOME_ID+"/post.db";

    QString name_path = QDir::currentPath();

    name_path = name_path + "/linkedin_C.db";

    QSqlDatabase data_base = QSqlDatabase::addDatabase("QSQLITE");
    data_base.setDatabaseName(name_path);
    data_base.open();

    QString Name;

    QSqlQuery v(data_base);

    QString ID;

    v.exec("SELECT ID FROM userdb");
    if(v.first())
    {
        ID = v.value(0).toString();
    }

    MY_ID_HOME_PAGE = ID;

    if(QFile::exists("content/"+ID+"/res/pic/0.png"))
    {
        ui->me_button->setIcon(QIcon("content/"+ID+"/res/pic/0.png"));
    }
    else
    {
        ui->me_button->setIcon(QIcon("content/"+ID+"/res/pic/0.jpg"));
    }

    v.exec("SELECT first_name FROM USER WHERE ID='"+HOME_ID+"'");
    if(v.first())
    {
        Name = v.value(0).toString();
    }
    data_base.close();
    QSqlDatabase final = QSqlDatabase::addDatabase("QSQLITE");
    final.setDatabaseName(database_path);
    final.open();

    QSqlQuery qu(final);

    QString caption;

    if(!qu.exec("SELECT ContentText FROM postdata WHERE PostID='"+POST_ID+"'")) {qDebug() << qu.lastError().text();}

    if(qu.first())
    {
        caption = qu.value(0).toString();
    }


    ui->name->setText(Name);
    ui->capshion->setText(caption);
}

main_page::~main_page()
{
    delete ui;
}

void main_page::on_pushButton_clicked()
{

    QSqlDatabase data_base_remove = QSqlDatabase::addDatabase("QSQLITE","delete_the_database");
    data_base_remove.setDatabaseName(QDir::currentPath() + "/linkedin_C.db");
    data_base_remove.open();


    QSqlQuery q(data_base_remove);
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
    //ui->label->setStyleSheet("color: rgb(255, 255, 255);");
}




void main_page::on_next_pushbutton_clicked()
{
    int t = POST_ID.toInt();
    t++;
    POST_ID = QString::number(t);

    QString path = QDir::currentPath() + "/linkedin_C.db";

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "mainDB");
    database.setDatabaseName(path);
    if (!database.open())
    {
        qDebug() << "Failed to open main database :( :" << database.lastError().text();
        return;
    }

    QSqlQuery qqq(database);
    if (!qqq.exec("SELECT COUNT(*) FROM USER"))
    {
        qDebug() << "Failed to execute query on main database:" << qqq.lastError().text();
        return;
    }

    int numRows = 0;
    if (qqq.next())
    {
        numRows = qqq.value(0).toInt();
    }
    QString amount_of_users = QString::number(numRows);

    QString database_path = QDir::currentPath() + "/content/" + HOME_ID + "/post.db";

    QSqlDatabase final = QSqlDatabase::addDatabase("QSQLITE", "postDB");

    final.setDatabaseName(database_path);
    if (!final.open())
    {
        qDebug() << "Failed to open post database:" << final.lastError().text();
        return;
    }

    QSqlQuery qu(final);
    if (!qu.exec("SELECT COUNT(*) FROM postdata"))
    {
        qDebug() << "Failed to execute query on post database:" << qu.lastError().text();
        return;
    }

    int numRows_2 = 0;
    if (qu.next())
    {
        numRows_2 = qu.value(0).toInt();
    }
    QString amount_of_post = QString::number(numRows_2);

    if (POST_ID.toInt() - 1 >= amount_of_post.toInt())
    {
        if (HOME_ID.toInt() < amount_of_users.toInt())
        {
            int temp = HOME_ID.toInt();
            temp++;
            HOME_ID = QString::number(temp);
            POST_ID = "1";
        }
        else
        {
            return;
        }
    }


    QSqlDatabase new_data = QSqlDatabase::addDatabase("QSQLITE", "postDB");

    new_data.setDatabaseName(QDir::currentPath() + "/content/" + HOME_ID + "/post.db");
    if (!new_data.open())
    {
        qDebug() << "Failed to open post database:" << final.lastError().text();
        return;
    }

    QSqlQuery ww(new_data);

    if (!ww.exec("SELECT ContentText FROM postdata WHERE PostID='" + POST_ID + "'"))
    {
        qDebug() << "Failed to get content text:" << ww.lastError().text();
        return;
    }
    QString caption;
    if (ww.first())
    {
        caption = ww.value(0).toString();
    }

    final.close();
    QSqlDatabase::removeDatabase("postDB");

    if (!qqq.exec("SELECT first_name FROM USER WHERE ID='" + HOME_ID + "'"))
    {
        qDebug() << "Failed to get user name:" << qqq.lastError().text();
        return;
    }
    QString name;
    if (qqq.first())
    {
        name = qqq.value(0).toString();
    }

    QString imagePath = "content/" + HOME_ID + "/res/pic/0.png";
    if (!QFile::exists(imagePath))
    {
        imagePath = "content/" + HOME_ID + "/res/pic/0.jpg";
    }
    if (QFile::exists(imagePath))
    {
        ui->profile->setIcon(QIcon(imagePath));
    } else {
        qDebug() << "Profile image does not exist:" << imagePath;
    }

    ui->capshion->setText(caption);

    database.close();
    QSqlDatabase::removeDatabase("mainDB");
}



void main_page::on_previous_pushbutton_clicked()
{
    int t = POST_ID.toInt();
    t--;

    if(t <= 0 && HOME_ID == "1")
    {
        t = 1;
        POST_ID = QString::number(t);
        return;
    }

    POST_ID = QString::number(t);

    QString database_path = QDir::currentPath();

    database_path = database_path + "/content/"+HOME_ID+"/post.db";

    QSqlDatabase final = QSqlDatabase::addDatabase("QSQLITE");
    final.setDatabaseName(database_path);
    final.open();

    QSqlQuery qu(final);

    QString caption;

    if(!qu.exec("SELECT ContentText FROM postdata WHERE PostID='"+POST_ID+"'")) {qDebug() << qu.lastError().text();}

    if(qu.first())
    {
        caption = qu.value(0).toString();
    }

    ui->capshion->setText(caption);
}


void main_page::on_serach_button_clicked()
{
    QString search = ui->search->text();
    QString s;

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q(db);

    q.exec("SELECT ID FROM USER WHERE first_name='"+search+"'");
    if(q.first())
    {
        s = q.value(0).toString();
        get_the_ID(s);
        view_profile* page = new view_profile;
        page->show();
        this->close();
    }
    else
    {
        QMessageBox::information(this,"Search name ","The name is not exsict " , "ok");
        ui->search->setText("");
    }
}


void main_page::on_pushButton_2_clicked()
{
    send_post *vcode = new send_post;
    vcode->show();
    this->close();
}


void main_page::on_me_button_clicked()
{
    profile* t = new profile;
    t->show();
    this->close();
}


void main_page::on_profile_clicked()
{
    get_the_ID(HOME_ID);
    view_profile* page = new view_profile;
    page->show();
    this->close();
}


void main_page::on_mynetwork_button_clicked()
{
    get_user_id_my_network(MY_ID_HOME_PAGE);
    my_network* n = new my_network;
    n->show();
    this->close();
}


void main_page::on_job_button_clicked()
{
    job_form* job_page_open = new job_form;

    job_page_open->show();

    this->close();
}


void main_page::on_message_button_clicked()
{
    get_the_user_ID(MY_ID_HOME_PAGE);
    message_contact* n = new message_contact;
    n->show();
    this->close();
}


void main_page::on_comment_clicked()
{
    get_the_id(HOME_ID,POST_ID , MY_ID_HOME_PAGE);
    comments* d = new comments;
    d->show();
}

void color_the_theme()
{

    if(false)
    {

    }
}

void set_ID_from_LOGIN(QString g)
{
    MY_ID_HOME_PAGE = g;
}

void main_page::on_like_button_clicked()
{

}

