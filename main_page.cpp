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
#include <fstream>
#include <qfileinfo.h>
#include "welcome.h"
#include <qdebug.h>
#include <QDir>
#include "send_post.h"
#include "like.h"
#include "view_profile.h"
#include "message_contact.h"
#include "QMessageBox"



QString HOME_ID = "1";
QString POST_ID = "1";
QString MY_ID_HOME_PAGE;
bool temp_for_audio = true;

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
    ui->comment->setIcon(QIcon("icons/speech-bubble-line-icon.png"));
    ui->profile->setFlat(1);

    std::ifstream dark_mode("is_dark.txt");
    std::string mode;
    dark_mode >> mode;

    set_color(mode[0]);

    ui->audio->setEnabled(false);
    ui->audio->hide();

    if(QFile::exists("content/"+HOME_ID+"/res/pic/0.png"))
    {
         ui->profile->setIcon(QIcon("content/"+HOME_ID+"/res/pic/0.png"));
    }
    else
    {
        ui->profile->setIcon(QIcon("content/"+HOME_ID+"/res/pic/0.jpg"));
    }
    ui->profile->setIconSize(QSize{64,64});

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
    QString pic_cap;
    QString Audio_cap;

    if(!qu.exec("SELECT ContentText , ContentPicture , ContentAudio FROM postdata WHERE PostID='"+POST_ID+"'")) {qDebug() << qu.lastError().text();}

    if(qu.first())
    {
        caption = qu.value("ContentText").toString();
        pic_cap = qu.value("ContentPicture").toString();
        Audio_cap = qu.value("ContentAudio").toString();
    }

    QSqlDatabase test_the_like = QSqlDatabase::addDatabase("QSQLITE","the_like_area");
    test_the_like.setDatabaseName(QDir::currentPath() + "/content/" + HOME_ID + "/like.db");
    test_the_like.open();

    QSqlQuery q_like(test_the_like);

    if(!q_like.exec("SELECT Who_like_id FROM '"+POST_ID+"' WHERE Who_like_id='"+MY_ID_HOME_PAGE+"'"))
    {
        qDebug() << "can't select the like database : " << q_like.lastError().text();
    }
    if(q_like.first())
    {
        ui->like_button->setIcon(QIcon("icons/heart-icon.png"));
    }

    if(pic_cap != "Empty")
    {
        QString e;
        if(QFile::exists(QDir::currentPath() + "/content/" + HOME_ID + "/res/pic/" + POST_ID + ".png"))
        {
            e = QDir::currentPath() + "/content/" + HOME_ID + "/res/pic/" + POST_ID + ".png";
        }
        else
        {
            e = QDir::currentPath() + "/content/" + HOME_ID + "/res/pic/" + POST_ID + ".jpg";
        }
        QPixmap ui_res(e);
        QPixmap scaled_pixmap = ui_res.scaled(551, 171, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->post->setPixmap(scaled_pixmap);
    }
    else if(Audio_cap != "Empty")
    {
        QString e = QDir::currentPath() + "/content/" + HOME_ID + "/res/audio/" + POST_ID;

        if(QFile::exists(e + ".mp3"))
        {
            e = e + ".mp3";
        }
        else
        {
            e = e + ".wav";
        }
        mediaPlayer = new QMediaPlayer(this);
        mediaPlayer->setMedia(QUrl::fromLocalFile(e));
        mediaPlayer->setVolume(40);
        mediaPlayer->play();
        ui->audio->setEnabled(true);
        ui->audio->show();
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

void main_page::set_color(char c)
{
    if(c == '1')
    {
        main_page::setStyleSheet("background-color: rgb(66, 69, 73);");
        ui->pushButton->setStyleSheet("color: rgb(0, 0, 0);");
        ui->pushButton->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->job_button->setStyleSheet("color: rgb(0, 0, 0);");
        ui->job_button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->comment->setStyleSheet("color: rgb(0, 0, 0);");
        ui->comment->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->notif_button->setStyleSheet("color: rgb(0, 0, 0);");
        ui->notif_button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->home_button->setStyleSheet("color: rgb(0, 0, 0);");
        ui->home_button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->like_button->setStyleSheet("color: rgb(0, 0, 0);");
        ui->like_button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->next_pushbutton->setStyleSheet("color: rgb(0, 0, 0);");
        ui->next_pushbutton->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->pushButton_2->setStyleSheet("color: rgb(0, 0, 0);");
        ui->pushButton_2->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->previous_pushbutton->setStyleSheet("color: rgb(0, 0, 0);");
        ui->previous_pushbutton->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->message_button->setStyleSheet("color: rgb(0, 0, 0);");
        ui->message_button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->mynetwork_button->setStyleSheet("color: rgb(0, 0, 0);");
        ui->mynetwork_button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->share_button->setStyleSheet("color: rgb(0, 0, 0);");
        ui->share_button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->serach_button->setStyleSheet("color: rgb(0, 0, 0);");
        ui->serach_button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->me_button->setStyleSheet("color: rgb(0, 0, 0);");
        ui->me_button->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->name->setStyleSheet("color: rgb(255, 255, 255);");
        ui->capshion->setStyleSheet("color: rgb(255, 255, 255);");
        ui->Date->setStyleSheet("color: rgb(255, 255, 255);");
        ui->search->setStyleSheet("color: rgb(255, 255, 255);");

    }
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

    //----------------------------------------------------------------------------------------------------------------

    ui->post->clear();

    if(ui->audio->isEnabled())
    {
        delete mediaPlayer;
    }
    ui->audio->setEnabled(false);
    ui->audio->hide();

    QSqlDatabase new_data = QSqlDatabase::addDatabase("QSQLITE", "postDB");

    new_data.setDatabaseName(QDir::currentPath() + "/content/" + HOME_ID + "/post.db");
    if (!new_data.open())
    {
        qDebug() << "Failed to open post database:" << final.lastError().text();
        return;
    }

    QSqlQuery ww(new_data);

    if (!ww.exec("SELECT ContentText , ContentPicture , ContentAudio FROM postdata WHERE PostID='" + POST_ID + "'"))
    {
        qDebug() << "Failed to get content text:" << ww.lastError().text();
        return;
    }
    QString caption;
    QString pic_cap;
    QString Audio_cap;

    if (ww.first())
    {
        caption = ww.value("ContentText").toString();
        pic_cap = ww.value("ContentPicture").toString();
        Audio_cap = ww.value("ContentAudio").toString();
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

    if(pic_cap != "Empty")
    {
        QString e;
        if(QFile::exists(QDir::currentPath() + "/content/" + HOME_ID + "/res/pic/" + POST_ID + ".png"))
        {
            e = QDir::currentPath() + "/content/" + HOME_ID + "/res/pic/" + POST_ID + ".png";
        }
        else
        {
            e = QDir::currentPath() + "/content/" + HOME_ID + "/res/pic/" + POST_ID + ".jpg";
        }
        QPixmap ui_res(e);
        QPixmap scaled_pixmap = ui_res.scaled(551, 171, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->post->setPixmap(scaled_pixmap);
    }
    else if(Audio_cap != "Empty")
    {
        QString e = QDir::currentPath() + "/content/" + HOME_ID + "/res/audio/" + POST_ID;

        if(QFile::exists(e + ".mp3"))
        {
            e = e + ".mp3";
        }
        else
        {
            e = e + ".wav";
        }
        mediaPlayer = new QMediaPlayer(this);
        mediaPlayer->setMedia(QUrl::fromLocalFile(e));
        mediaPlayer->setVolume(40);
        mediaPlayer->play();
        ui->audio->setEnabled(true);
        ui->audio->show();
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

    //----------------------------------------------------------------------------------------------------------------

    ui->post->clear();

    if(ui->audio->isEnabled())
    {
        delete mediaPlayer;
    }
    ui->audio->setEnabled(false);
    ui->audio->hide();

    QSqlQuery qu(final);

    QString caption;
    QString pic_cap;
    QString Audio_cap;

    if(!qu.exec("SELECT ContentText , ContentPicture , ContentAudio FROM postdata WHERE PostID='"+POST_ID+"'")) {qDebug() << qu.lastError().text();}

    if(qu.first())
    {
        caption = qu.value("ContentText").toString();
        pic_cap = qu.value("ContentPicture").toString();
        Audio_cap = qu.value("ContentAudio").toString();
    }

    if(pic_cap != "Empty")
    {
        QString e;
        if(QFile::exists(QDir::currentPath() + "/content/" + HOME_ID + "/res/pic/" + POST_ID + ".png"))
        {
            e = QDir::currentPath() + "/content/" + HOME_ID + "/res/pic/" + POST_ID + ".png";
        }
        else
        {
            e = QDir::currentPath() + "/content/" + HOME_ID + "/res/pic/" + POST_ID + ".jpg";
        }
        QPixmap ui_res(e);
        QPixmap scaled_pixmap = ui_res.scaled(551, 171, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->post->setPixmap(scaled_pixmap);
    }
    else if(Audio_cap != "Empty")
    {
        QString e = QDir::currentPath() + "/content/" + HOME_ID + "/res/audio/" + POST_ID;

        if(QFile::exists(e + ".mp3"))
        {
            e = e + ".mp3";
        }
        else
        {
            e = e + ".wav";
        }
        mediaPlayer = new QMediaPlayer(this);
        mediaPlayer->setMedia(QUrl::fromLocalFile(e));
        mediaPlayer->setVolume(40);
        mediaPlayer->play();
        ui->audio->setEnabled(true);
        ui->audio->show();
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
        if(ui->audio->isEnabled())
        {
            delete mediaPlayer;
        }
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
    if(ui->audio->isEnabled())
    {
        delete mediaPlayer;
    }
    send_post *vcode = new send_post;
    vcode->show();
    this->close();
}


void main_page::on_me_button_clicked()
{
    if(ui->audio->isEnabled())
    {
        delete mediaPlayer;
    }
    profile* t = new profile;
    t->show();
    this->close();
}


void main_page::on_profile_clicked()
{
    if(ui->audio->isEnabled())
    {
        delete mediaPlayer;
    }
    get_the_ID(HOME_ID);
    view_profile* page = new view_profile;
    page->show();
    this->close();
}


void main_page::on_mynetwork_button_clicked()
{
    if(ui->audio->isEnabled())
    {
        delete mediaPlayer;
    }
    get_user_id_my_network(MY_ID_HOME_PAGE);
    my_network* n = new my_network;
    n->show();
    this->close();
}


void main_page::on_job_button_clicked()
{
    if(ui->audio->isEnabled())
    {
        delete mediaPlayer;
    }
    job_form* job_page_open = new job_form;

    job_page_open->show();

    this->close();
}


void main_page::on_message_button_clicked()
{
    if(ui->audio->isEnabled())
    {
        delete mediaPlayer;
    }
    get_the_user_ID(MY_ID_HOME_PAGE);
    message_contact* n = new message_contact;
    n->show();
    this->close();
}


void main_page::on_comment_clicked()
{
    get_the_id(POST_ID,HOME_ID , MY_ID_HOME_PAGE);
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
    QSqlDatabase test_the_like = QSqlDatabase::addDatabase("QSQLITE","the_like_area_bool");
    test_the_like.setDatabaseName(QDir::currentPath() + "/content/" + HOME_ID + "/like.db");
    test_the_like.open();

    QSqlQuery q_like(test_the_like);

    if(!q_like.exec("SELECT Who_like_id FROM '"+POST_ID+"' WHERE Who_like_id='"+MY_ID_HOME_PAGE+"'"))
    {
        qDebug() << "can't select the like database : " << q_like.lastError().text();
        return;
    }
    if(q_like.first())
    {
        if(!q_like.exec("DELETE FROM '"+POST_ID+"' WHERE Who_like_id='"+MY_ID_HOME_PAGE+"'"))
        {
            qDebug() << "can't delete the like database : " << q_like.lastError().text();
            return;
        }
        ui->like_button->setIcon(QIcon("icons/heart-thin-icon.png"));
    }
    else
    {
        QString like_id;
        q_like.prepare("SELECT COUNT(*) FROM '"+POST_ID+"'");
        if(!q_like.exec())
        {
            qDebug() << "can't count the like database : " << q_like.lastError().text();
            return;
        }
        if(q_like.first())
        {
            like_id = q_like.value(0).toString();
        }

        LIKE like(MY_ID_HOME_PAGE,like_id);
        if(!q_like.exec("INSERT INTO '"+POST_ID+"'(Who_like_id,like_id,day,month,year,hour,minute,second)VALUES('"+like.get_who_liked_ID()+"' , '"+like.get_Like_ID()+"' , '"+like.get_time().get_day()+"' , '"+like.get_time().get_month()+"' , '"+like.get_time().get_year()+"' , '"+like.get_time().get_hour()+"' , '"+like.get_time().get_minute()+"' , '"+like.get_time().get_second()+"')"))
        {
            qDebug() << "can't insert in the like database : " << q_like.lastError().text();
            return;
        }
        ui->like_button->setIcon(QIcon("icons/heart-icon.png"));
    }
}


void main_page::on_audio_clicked()
{
    if(temp_for_audio)
    {
        mediaPlayer->pause();
    }
    else
    {
        mediaPlayer->play();
    }
    temp_for_audio = !temp_for_audio;
}

