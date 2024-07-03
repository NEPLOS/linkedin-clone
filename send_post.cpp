#include "send_post.h"
#include "ui_send_post.h"
#include <QFileDialog>
#include <QString>
#include "post.h"
#include "qdebug.h"
#include <qlabel.h>
#include "QSqlDatabase"
#include "QSqlDriver"
#include "QMessageBox"
#include "QSqlQuery"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include "QSqlError"
#include <QFile>
#include "qdebug.h"
#include <string>
#include <QWidget>
#include "main_page.h"
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include "welcome.h"
#include "profile.h"
#include "job_form.h"
#include "my_network.h"
#include "view_profile.h"
#include "message_contact.h"


QString Global_file_path;

QString search(QString input);

send_post::send_post(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::send_post)
{
    ui->setupUi(this);
    ui->address->setEnabled(false);

    ui->home_button->setIcon(QIcon("icons/Home.jpg"));
    ui->notif_button->setIcon(QIcon("icons/bell-line-icon.png"));
    ui->pushButton_3->setIcon(QIcon("icons/logout-line-icon.png"));
    ui->serach_button->setIcon(QIcon("icons/search-line-icon.png"));
    ui->job_button->setIcon(QIcon("icons/hand-shake-icon.png"));
    ui->mynetwork_button->setIcon(QIcon("icons/world-globe-line-icon.png"));
    ui->message_button->setIcon(QIcon("icons/speech-bubble-line-icon.png"));
    ui->me_button->setIcon(QIcon("icons/person-profile-image-icon.png"));

    QString database_path = QDir::currentPath();

    database_path = database_path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);
    db.open();
}

send_post::~send_post()
{
    delete ui;
}

void send_post::on_Upload_button_clicked()
{
    QString path = QDir::currentPath();

    QString path_path = path + "/linkedin_C.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_path);
    db.open();

    QString vidlink = "Empty";
    QString piclink = "Empty";
    QString audiolink = "Empty";

    QString text = ui->capshion->text();
    if(text.size() == 0 || text[0] == ' ')
    {
        QMessageBox::warning(this,"Error" , "enter the capshion");
        return;
    }

    QString f = ui->address->text();

    QString temp_for_format = search(f);
    QFileInfo fi(temp_for_format);
    QString ext = fi.suffix();

    if(true)
    {
        if(temp_for_format != "Empty")
        {

            if     (ext == "mp4" )   {vidlink = f;}
            else if(ext == "mov" )   {vidlink = f;}
            else if(ext == "png" )   {piclink = f;}
            else if(ext == "jpeg")   {piclink = f;}
            else if(ext == "jpg" )   {piclink = f;}
            else if(ext == "mp3" )   {audiolink = f;}
            else if(ext == "wav" )   {audiolink = f;}
        }

        QSqlQuery data(db);
        QString user_id;

        data.exec("SELECT ID FROM userdb");
        if(data.first())
        {
            user_id = data.value(0).toString();
        }

        QString database_path = QDir::currentPath();
        database_path = database_path + "/content/" + user_id;

        QString post_data_base_path = database_path +  + "/post.db";
        QString like_data_base_path = database_path +  + "/like.db";
        QString comment_data_base_path = database_path +  + "/comment.db";

        QSqlDatabase post_database = QSqlDatabase::addDatabase("QSQLITE");
        post_database.setDatabaseName(post_data_base_path);
        post_database.open();

        QSqlQuery databaseQuery(post_database);

        databaseQuery.prepare("CREATE TABLE IF NOT EXISTS postdata (senderID TEXT, ContentText TEXT, ContentPicture TEXT, ContentVideo TEXT, ContentAudio TEXT, day TEXT , month TEXT , year TEXT , hour TEXT , minute TEXT , second TEXT , PostID TEXT , Repostedcounter int);");

        if (!databaseQuery.exec())
        {
            qDebug() << "cant";
            return;
        }

        QSqlQuery post_user(post_database);

        post_user.prepare("SELECT COUNT(*) FROM postdata");

        if (!post_user.exec())
        {

            return;
        }
        int numRows = 0;
        if (post_user.next())
        {
            numRows = post_user.value(0).toInt();
        }

        QString amount_0f_post = QString::number(numRows + 1);

        Post post(user_id,text,piclink,vidlink,audiolink,amount_0f_post);

        //databaseQuery.exec("INSERT INTO postdata(senderID,Contenttext,ContentPicture,ContentVideo,day,month,year,hour,minute,second,PostID,Repostedcounter)VALUES('"+post.get_sender_ID()+"' , '"+post.get_content_text()+"' , '"+post.get_content_Picture()+"' , '"+post.get_content_Video()+"' , '"+post.get_time_send().get_day()+"' , '"+post.get_time_send().get_month()+"' , '"+post.get_time_send().get_year()+"' , '"+post.get_time_send().get_hour()+"' , '"+post.get_time_send().get_minute()+"' , '"+post.get_time_send().get_second()+"' , '"+post.get_Post_ID()+"' , '"+post.get_Responset_counter()+"')"))
        // ContentAudio
        databaseQuery.exec("INSERT INTO postdata(PostID)VALUES('"+post.get_Post_ID()+"')");
        databaseQuery.exec("UPDATE postdata SET senderID='"+post.get_Post_ID()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET ContentText='"+post.get_content_text()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET ContentPicture='"+post.get_content_Picture()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET ContentVideo='"+post.get_content_Video()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET ContentAudio='"+post.get_content_Audio()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET day='"+post.get_time_send().get_day()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET month='"+post.get_time_send().get_month()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET year='"+post.get_time_send().get_year()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET hour='"+post.get_time_send().get_hour()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET minute='"+post.get_time_send().get_minute()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        databaseQuery.exec("UPDATE postdata SET second='"+post.get_time_send().get_second()+"' WHERE PostID='"+post.get_Post_ID()+"'");
        std::string temp = std::to_string(post.get_Responset_counter());
        QString reocounter = QString::fromStdString(temp);
        databaseQuery.exec("UPDATE postdata SET Repostedcounter='"+reocounter+"' WHERE PostID='"+post.get_Post_ID()+"'");

        QSqlDatabase like_database = QSqlDatabase::addDatabase("QSQLITE");
        like_database.setDatabaseName(like_data_base_path);
        like_database.open();

        QSqlQuery like_q(post_database);

        like_q.prepare("CREATE TABLE IF NOT EXISTS '"+post.get_Post_ID()+"'(Who_like_id TEXT, like_id TEXT, day TEXT , month TEXT , year TEXT , hour TEXT , minute TEXT , second TEXT);");

        if (!like_q.exec())
        {
            qDebug() << "cant";
            return;
        }

        QSqlDatabase commet_database = QSqlDatabase::addDatabase("QSQLITE");
        commet_database.setDatabaseName(comment_data_base_path);
        commet_database.open();

        QSqlQuery comment_q(post_database);

        comment_q.prepare("CREATE TABLE IF NOT EXISTS '"+post.get_Post_ID()+"'(senderID TEXT, Contenttext TEXT, ContentPicture TEXT, ContentVideo TEXT , ContentAudio TEXT, day TEXT , month TEXT , year TEXT , hour TEXT , minute TEXT , second TEXT , PostID TEXT , commentID TEXT);");

        if (!comment_q.exec())
        {
            qDebug() << "cant";
            return;
        }

        database_path = database_path + "/res";

        if(vidlink != "Empty")
        {
            QString if_vid = database_path + "/vid/";
            if_vid = if_vid + post.get_Post_ID() + "." + ext;
            QFile::copy(f,if_vid);
        }
        if(piclink != "Empty")
        {
            QString if_pic = database_path + "/pic/";
            if_pic = if_pic + post.get_Post_ID() + "." + ext;
            QFile::copy(f,if_pic);
        }
        if(audiolink != "Empty")
        {
            QString if_audio = database_path + "/audio/";
            if_audio = if_audio + post.get_Post_ID() + "." + ext;
            QFile::copy(f,if_audio);
        }

        QSqlDatabase dat = QSqlDatabase::addDatabase("QSQLITE" , "make_the_comments_table");

        QSqlDatabase likes = QSqlDatabase::addDatabase("QSQLITE" , "make_the_likes_table");

        likes.setDatabaseName(QDir::currentPath() + "/content/" + user_id + "/like.db");
        likes.open();

        QSqlQuery likes_table(likes);

        likes_table.exec("CREATE TABLE IF NOT EXISTS '"+amount_0f_post+"'(who_liked_id TEXT , like_id TEXT , hour TEXT , minute TEXT , second TEXT , year TEXT , month TEXT , day TEXT )");


        return;
    }

}


void send_post::on_cancel_button_clicked()
{
    main_page* p = new main_page;
    p->show();
    this->close();
}

void send_post::on_post_clicked()
{
    QString file_path = QFileDialog::getOpenFileName();

    Global_file_path = file_path;

    if(search(file_path) == "Empty")
    {
        ui->address->setText("--- Invalid Post , try again or the post will be sended without any pics/vids ---");
        return;
    }

    QFileInfo file_path_info(file_path);

    QString format = file_path_info.suffix();

    if((format == "jpeg" || format == "jpg" || format == "png"))
    {
        ui->address->setText(file_path);
        QPixmap ui_res(file_path);
        QPixmap scaled_pixmap = ui_res.scaled(381, 171, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->res_lable->setPixmap(scaled_pixmap);
    }
    else if(format == "mp4" || format == "mov")
    {
        mediaPlayer = new QMediaPlayer(this);
        videoWidget = new QVideoWidget(this);

        mediaPlayer->setVideoOutput(videoWidget);
        videoWidget->setGeometry(170, 180, 381, 171);
        videoWidget->show();

        mediaPlayer->setMedia(QUrl::fromLocalFile(file_path));
        mediaPlayer->play();
        ui->address->setText(file_path);
    }
    else if(format == "mp3" || format == "wav")
    {
        ui->address->setText(file_path);
        QMediaPlayer *player = new QMediaPlayer(this);
        player->setMedia(QUrl::fromLocalFile(file_path));
        player->setVolume(50);
        player->play();
    }
}

QString search(QString input)
{
    QString list[] = {"mp4","png","jpg","mov","jpeg","mp3","wav"};

    QFileInfo fi(input);
    QString ext = fi.suffix();

    for(int i = 0 ; i < 7 ; i++)
    {
        if(ext == list[i])
        {return input;}
    }
    return "Empty";
}

void send_post::on_pushButton_3_clicked()
{
    QSqlQuery q;
    q.exec("DELETE FROM userdb");

    welcome *t = new welcome;
    t->show();
    this->close();
}


void send_post::on_me_button_clicked()
{
    profile* t = new profile;
    t->show();
    this->close();
}


void send_post::on_home_button_clicked()
{
    main_page* t = new main_page;
    t->show();
    this->close();
}


void send_post::on_job_button_clicked()
{
    job_form* job_page_open = new job_form;

    job_page_open->show();

    this->close();
}


void send_post::on_mynetwork_button_clicked()
{
    my_network* n = new my_network;
    n->show();
    this->close();
}


void send_post::on_serach_button_clicked()
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


void send_post::on_message_button_clicked()
{
    message_contact* n = new message_contact;
    n->show();
    this->close();
}

