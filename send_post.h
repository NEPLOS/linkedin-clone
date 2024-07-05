#ifndef SEND_POST_H
#define SEND_POST_H

#include <QDialog>
#include <QString>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>

namespace Ui {
class send_post;
}

class send_post : public QDialog
{
    Q_OBJECT

public:
    explicit send_post(QWidget *parent = nullptr);
    ~send_post();
private slots:
    void on_Upload_button_clicked();

    void on_cancel_button_clicked();

    void on_post_clicked();
    void on_pushButton_3_clicked();

    void on_me_button_clicked();

    void on_home_button_clicked();

    void on_job_button_clicked();

    void on_mynetwork_button_clicked();

    void on_serach_button_clicked();

    void on_message_button_clicked();

    void on_play_clicked();

    void on_pause_clicked();

    void on_user_mod_currentIndexChanged(int index);

private:
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QPushButton *playButton;
    Ui::send_post *ui;
};

#endif // SEND_POST_H
