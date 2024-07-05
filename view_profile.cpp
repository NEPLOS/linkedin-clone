#include "view_profile.h"
#include "ui_view_profile.h"
#include <qlabel.h>
#include <QDir>
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QMessageBox"
#include "QSqlQuery"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include "QSqlError"
#include "comments.h"
#include <QFile>
#include "qdebug.h"
#include "profile.h"
#include <string>
#include "welcome.h"
#include "QSqlError"
#include <QWidget>
#include "main_page.h"
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "like.h"
#include <QtMultimedia/QMediaPlayer>
#include "my_network.h"
#include "job_form.h"
#include "message_contact.h"


QString global_ID;
QString ma_id;
int amount_of_post;
int what_post_i_am;
bool play_or_pause = false;

view_profile::view_profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::view_profile)
{

    ui->setupUi(this);

    ui->connect_button->show();

    QString path = QDir::currentPath();

    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->me_button->setIcon(QIcon("icons/person-profile-image-icon.png"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton_3->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));
    ui->share->setIcon(QIcon("icons/paper-plane-icon.png"));
    ui->like->setIcon(QIcon("icons/heart-thin-icon.png"));
    ui->comment->setIcon(QIcon("icons/speech-bubble-line-icon.png"));

    path = path + "/content/" + global_ID + "/res/pic/0.";
    QFileInfo file_info(path + "png");
    if(file_info.exists())
    {
        path = path + "png";
    }
    else
    {
        path = path + "jpg";
    }

    if(global_ID[global_ID.size() - 1] == 'C')
    {
        ui->connect_button->setText("follow");
        ui->bio_label->hide();
        ui->label_10->hide();
        ui->lastname_label->hide();
    }

    QPixmap ui_res(path);
    QPixmap scaled_pixmap = ui_res.scaled(130, 130, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->picture->setPixmap(scaled_pixmap);

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q(db);

    QString first_name;
    QString bio;
    QString last_name;
    QString email;

    q.exec("SELECT ID FROM userdb");
    if(q.first())
    {
        ma_id = q.value(0).toString();
    }

    if(QFile::exists("content/"+ma_id+"/res/pic/0.png"))
    {
        ui->me_button->setIcon(QIcon("content/"+ma_id+"/res/pic/0.png"));
    }
    else
    {
        ui->me_button->setIcon(QIcon("content/"+ma_id+"/res/pic/0.jpg"));
    }

    q.exec("SELECT first_name FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        first_name = q.value(0).toString();
    }
    qDebug() << q.lastError().text();

    q.exec("SELECT last_name FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        last_name = q.value(0).toString();
    }
    qDebug() << q.lastError().text();

    q.exec("SELECT email FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        email = q.value(0).toString();
    }
    qDebug() << q.lastError().text();

    q.exec("SELECT Bio FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        bio = q.value(0).toString();
    }
    qDebug() << q.lastError().text();

    QString skills;

    q.exec("SELECT skill FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        skills = q.value(0).toString();
    }

    QString number;

    q.exec("SELECT Phone_number FROM USER WHERE ID='"+global_ID+"'");
    if(q.first())
    {
        number = q.value(0).toString();
    }

    ui->bio->setText(bio);
    ui->name->setText(first_name);
    ui->lastname->setText(last_name);
    ui->email->setText(email);
    ui->my_skills->setText(skills);

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase data_base_button_check = QSqlDatabase::addDatabase("QSQLITE");
    data_base_button_check.setDatabaseName(QDir::currentPath() + "/data/" +global_ID+ "/connections.db");
    data_base_button_check.open();
    QSqlQuery qee(data_base_button_check);

    if(global_ID[global_ID.size() - 1] == 'C')
    {
        if(global_ID != ma_id)
        {
            qee.exec("SELECT user_id FROM follow WHERE user_id='"+ma_id+"'");
            if(qee.first())
            {
                ui->connect_button->setEnabled(false);
                ui->connect_button->hide();
            }
        }
        else
        {
            ui->connect_button->show();
        }

        ui->lastname_label->setText("phone number :");
        ui->lastname->setText(number);
        ui->lastname_label->setEnabled(true);
        ui->lastname_label->show();
    }
    else
    {
        if(global_ID != ma_id)
        {
            qee.exec("SELECT user_id FROM pending WHERE user_id='"+ma_id+"'");
            if(qee.first())
            {
                ui->connect_button->setEnabled(false);
                ui->connect_button->setText("pendig");
            }
        }
        else
        {
            ui->connect_button->setEnabled(false);
            ui->connect_button->hide();
        }
    }

    QSqlDatabase db_for_view_page = QSqlDatabase::addDatabase("QSQLITE","db_for_view_page_2");
    db_for_view_page.setDatabaseName(QDir::currentPath() + "/content/" + global_ID + "/post.db");
    db_for_view_page.open();

    QSqlQuery db_for_view_page_query(db_for_view_page);

    if(!db_for_view_page_query.exec("SELECT COUNT(*) FROM postdata"))
    {
        qDebug() << "can't count : " << db_for_view_page_query.lastError().text();
    }
    if(db_for_view_page_query.first())
    {
        amount_of_post = db_for_view_page_query.value(0).toInt();
    }

    what_post_i_am = 0;

    ui->audio->setEnabled(false);
    ui->audio->hide();

    if(amount_of_post != 0)
    {
        ui->previous->setEnabled(0);
        if(!db_for_view_page_query.exec("SELECT ContentText , ContentPicture , ContentAudio FROM postdata WHERE PostID=1"))
        {
            qDebug() << "can't select from postdata : " << db_for_view_page_query.lastError().text();
        }
        if(db_for_view_page_query.first())
        {
            QString temp_for_pic = db_for_view_page_query.value("ContentPicture").toString();
            QString temp = db_for_view_page_query.value("ContentText").toString();
            QString audio_path = db_for_view_page_query.value("ContentAudio").toString();
            ui->text_label->setText(temp);
            what_post_i_am++;
            if(temp_for_pic != "Empty")
            {
                QString e;
                QString ee = QString::number(what_post_i_am);
                if(QFile::exists(QDir::currentPath() + "/content/" + global_ID + "/res/pic/" + what_post_i_am + ".png"))
                {
                    e = QDir::currentPath() + "/content/" + global_ID + "/res/pic/" + ee + ".png";
                }
                else
                {
                    e = QDir::currentPath() + "/content/" + global_ID + "/res/pic/" + ee + ".jpg";
                }
                QPixmap ui_res(e);
                QPixmap scaled_pixmap = ui_res.scaled(551, 171, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->image->setPixmap(scaled_pixmap);
            }
            else if(audio_path != "Empty")
            {
                QString e = QDir::currentPath() + "/content/" + global_ID + "/res/audio/" + what_post_i_am;

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

            QString POST_ID = QString::number(what_post_i_am);

            QSqlDatabase test_the_like = QSqlDatabase::addDatabase("QSQLITE","the_like_area_like_view_prof");
            test_the_like.setDatabaseName(QDir::currentPath() + "/content/" + global_ID + "/like.db");
            test_the_like.open();

            QSqlQuery q_like(test_the_like);

            if(!q_like.exec("SELECT Who_like_id FROM '"+POST_ID+"' WHERE Who_like_id='"+ma_id+"'"))
            {
                qDebug() << "can't select the like database : " << q_like.lastError().text();
            }
            if(q_like.first())
            {
                ui->like->setIcon(QIcon("icons/heart-icon.png"));
            }

        }
    }
    else
    {
        ui->text_label->setText("sorry , no post :(( ");
        ui->next->setEnabled(0);
        ui->comment->setEnabled(0);
        ui->share->setEnabled(0);
        ui->like->setEnabled(0);
        ui->previous->setEnabled(0);
    }
}


view_profile::~view_profile()
{
    delete ui;
}

void view_profile::on_home_button_clicked()
{
    main_page* t = new main_page;
    t->show();
    this->close();
}


void view_profile::on_me_button_clicked()
{
    profile* t = new profile;
    t->show();
    this->close();
}

void view_profile::on_pushButton_3_clicked()
{

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();

    QSqlQuery q(db);
    q.exec("DELETE FROM userdb");

    welcome *t = new welcome;
    t->show();
    this->close();

}

void get_the_ID(QString ID)
{
    global_ID = ID;
}

void view_profile::on_serach_button_clicked()
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
        QMessageBox::information(this,"Search name ","The name is not exist " , "ok");
        ui->search->setText("");
    }
}


void view_profile::on_message_button_clicked()
{
    get_the_user_ID(ma_id);
    message_contact* n = new message_contact;
    n->show();
    this->close();
}


void view_profile::on_mynetwork_button_clicked()
{
    my_network* n = new my_network;
    n->show();
    this->close();
}


void view_profile::on_job_button_clicked()
{
    job_form* job_page_open = new job_form;
    job_page_open->show();
    this->close();
}



void view_profile::on_connect_button_clicked()
{

    QSqlDatabase db_connect = QSqlDatabase::addDatabase("QSQLITE","connect_stuff");
    db_connect.setDatabaseName(QDir::currentPath() + "/data/" +global_ID+ "/connections.db");
    db_connect.open();

    QSqlQuery q(db_connect);

    if(global_ID[global_ID.size() - 1] == 'C')
    {
        if(!q.exec("INSERT INTO follow(user_id)VALUES('"+ma_id+"')"))
        {
            qDebug() << "failed to insert data into follow (com): " << q.lastError().text();
        }

        QSqlDatabase db_connect_2 = QSqlDatabase::addDatabase("QSQLITE","connect_stuff_2");
        db_connect_2.setDatabaseName(QDir::currentPath() + "/data/" +ma_id+ "/connections.db");
        db_connect_2.open();

        QSqlQuery q_2(db_connect_2);

        if(!q_2.exec("INSERT INTO follow(user_id)VALUES('"+global_ID+"')"))
        {
            qDebug() << "failed to insert data into follow (user): " << q_2.lastError().text();
        }
        ui->connect_button->setEnabled(false);
        ui->connect_button->hide();
        return;
    }

    if(!q.exec("INSERT INTO pending(user_id)VALUES('"+ma_id+"')"))
    {
        qDebug() << "failed to insert data into pending : " << q.lastError().text();
    }

    ui->connect_button->setEnabled(false);
    ui->connect_button->setText("pendig");

}


void view_profile::on_comment_clicked()
{
    QString post_ID = QString::number(what_post_i_am);
    get_the_id( post_ID, global_ID, ma_id);
    comments* d = new comments;
    d->show();
}


void view_profile::on_next_clicked()
{
    if (what_post_i_am >= amount_of_post)
    {
        what_post_i_am = amount_of_post;
        ui->next->setEnabled(false);
        return;
    }
    else
    {
        ui->next->setEnabled(true);
    }
    ui->previous->setEnabled(true);
    what_post_i_am++;

    if(what_post_i_am == amount_of_post)
    {
        ui->next->setEnabled(false);
    }

    QSqlDatabase db_for_view_page = QSqlDatabase::database("db_for_view_page_2_4_7");
    if (!db_for_view_page.isValid())
    {
        db_for_view_page = QSqlDatabase::addDatabase("QSQLITE", "db_for_view_page_2_4_7");
        db_for_view_page.setDatabaseName(QDir::currentPath() + "/content/" + global_ID + "/post.db");
    }
    if (!db_for_view_page.open())
    {
        qDebug() << "Failed to open database: " << db_for_view_page.lastError().text();
        return;
    }

    QSqlQuery db_for_view_page_query(db_for_view_page);

    QString temp_for_selecting_the_post = QString::number(what_post_i_am);

    if (!db_for_view_page_query.exec("SELECT ContentText, ContentPicture, ContentAudio FROM postdata WHERE PostID='" + temp_for_selecting_the_post + "'"))
    {
        qDebug() << "can't select from postdata : " << db_for_view_page_query.lastError().text();
        return;
    }

    if(ui->audio->isEnabled())
    {
        delete  mediaPlayer;
    }

    ui->audio->setEnabled(false);
    ui->audio->hide();

    if (db_for_view_page_query.next())
    {
        ui->image->clear();
        QString temp_for_pic = db_for_view_page_query.value("ContentPicture").toString();
        ui->text_label->setText(db_for_view_page_query.value("ContentText").toString());
        QString audio_path = db_for_view_page_query.value("ContentAudio").toString();

        if(temp_for_pic != "Empty")
        {
            QString e;
            QString ee = QString::number(what_post_i_am);
            if(QFile::exists(QDir::currentPath() + "/content/" + global_ID + "/res/pic/" + ee + ".png"))
            {
                e = QDir::currentPath() + "/content/" + global_ID + "/res/pic/" + ee + ".png";
            }
            else
            {
                e = QDir::currentPath() + "/content/" + global_ID + "/res/pic/" + ee + ".jpg";
            }
            QPixmap ui_res(e);
            QPixmap scaled_pixmap = ui_res.scaled(551, 171, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->image->setPixmap(scaled_pixmap);
        }
        else if(audio_path != "Empty")
        {
            QString ee = QString::number(what_post_i_am);
            QString e = QDir::currentPath() + "/content/" + global_ID + "/res/audio/" + ee;

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

        QString POST_ID = QString::number(what_post_i_am);

        QSqlDatabase test_the_like = QSqlDatabase::addDatabase("QSQLITE","the_like_area_like_view_prof_2");
        test_the_like.setDatabaseName(QDir::currentPath() + "/content/" + global_ID + "/like.db");
        test_the_like.open();

        QSqlQuery q_like(test_the_like);

        if(!q_like.exec("SELECT Who_like_id FROM '"+POST_ID+"' WHERE Who_like_id='"+ma_id+"'"))
        {
            qDebug() << "can't select the like database : " << q_like.lastError().text();
        }
        if(q_like.first())
        {
            ui->like->setIcon(QIcon("icons/heart-icon.png"));
        }
        else
        {
            ui->like->setIcon(QIcon("icons/heart-thin-icon.png"));
        }
    }
    else
    {
        qDebug() << "No record found for PostID: " << temp_for_selecting_the_post;
    }
}

void view_profile::on_previous_clicked()
{
    if (what_post_i_am <= 1)
    {
        what_post_i_am = 1;
        ui->previous->setEnabled(false);
        return;
    }
    else
    {
        ui->previous->setEnabled(true);
    }
    ui->next->setEnabled(true);

    what_post_i_am--;

    if(what_post_i_am == 1)
    {
        ui->previous->setEnabled(false);
    }

    QSqlDatabase db_for_view_page = QSqlDatabase::database("db_for_view_page_2_4_7_2");
    if (!db_for_view_page.isValid())
    {
        db_for_view_page = QSqlDatabase::addDatabase("QSQLITE", "db_for_view_page_2_4_7_2");
        db_for_view_page.setDatabaseName(QDir::currentPath() + "/content/" + global_ID + "/post.db");
    }
    if (!db_for_view_page.open())
    {
        qDebug() << "Failed to open database: " << db_for_view_page.lastError().text();
        return;
    }

    QSqlQuery db_for_view_page_query(db_for_view_page);

    QString temp_for_selecting_the_post = QString::number(what_post_i_am);

    if (!db_for_view_page_query.exec("SELECT ContentText, ContentPicture, ContentAudio FROM postdata WHERE PostID='" + temp_for_selecting_the_post + "'"))
    {
        qDebug() << "can't select from postdata : " << db_for_view_page_query.lastError().text();
        return;
    }

    if(ui->audio->isEnabled())
    {
        delete  mediaPlayer;
    }

    ui->audio->setEnabled(false);
    ui->audio->hide();

    if (db_for_view_page_query.next())
    {
        ui->image->clear();
        QString temp_for_pic = db_for_view_page_query.value("ContentPicture").toString();
        ui->text_label->setText(db_for_view_page_query.value("ContentText").toString());
        QString audio_path = db_for_view_page_query.value("ContentAudio").toString();

        if(temp_for_pic != "Empty")
        {
            QString e;
            QString ee = QString::number(what_post_i_am);
            if(QFile::exists(QDir::currentPath() + "/content/" + global_ID + "/res/pic/" + ee + ".png"))
            {
                e = QDir::currentPath() + "/content/" + global_ID + "/res/pic/" + ee + ".png";
            }
            else
            {
                e = QDir::currentPath() + "/content/" + global_ID + "/res/pic/" + ee + ".jpg";
            }
            QPixmap ui_res(e);
            QPixmap scaled_pixmap = ui_res.scaled(551, 171, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->image->setPixmap(scaled_pixmap);
        }
        else if(audio_path != "Empty")
        {
            QString ee = QString::number(what_post_i_am);
            QString e = QDir::currentPath() + "/content/" + global_ID + "/res/audio/" + ee;

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

        QString POST_ID = QString::number(what_post_i_am);

        QSqlDatabase test_the_like = QSqlDatabase::addDatabase("QSQLITE","the_like_area_like_view_prof_1");
        test_the_like.setDatabaseName(QDir::currentPath() + "/content/" + global_ID + "/like.db");
        test_the_like.open();

        QSqlQuery q_like(test_the_like);

        if(!q_like.exec("SELECT Who_like_id FROM '"+POST_ID+"' WHERE Who_like_id='"+ma_id+"'"))
        {
            qDebug() << "can't select the like database : " << q_like.lastError().text();
        }
        if(q_like.first())
        {
            ui->like->setIcon(QIcon("icons/heart-icon.png"));
        }
        else
        {
            ui->like->setIcon(QIcon("icons/heart-thin-icon.png"));
        }
    }
    else
    {
        qDebug() << "No record found for PostID: " << temp_for_selecting_the_post;
    }
}


void view_profile::on_audio_clicked()
{
    if(play_or_pause)
    {
        mediaPlayer->play();
        ui->audio->setText("pause");
    }
    else
    {
        mediaPlayer->pause();
        ui->audio->setText("play");
    }
    play_or_pause = !play_or_pause;
}


void view_profile::on_like_clicked()
{
    QString POST_ID = QString::number(what_post_i_am);
    QString MY_ID_HOME_PAGE = ma_id;

    QSqlDatabase test_the_like = QSqlDatabase::addDatabase("QSQLITE","the_like_area_bool_2");
    test_the_like.setDatabaseName(QDir::currentPath() + "/content/" + global_ID + "/like.db");
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
        ui->like->setIcon(QIcon("icons/heart-thin-icon.png"));
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
        ui->like->setIcon(QIcon("icons/heart-icon.png"));
    }
}


void view_profile::on_share_clicked()
{

}

