#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QMainWindow>
#include <QMediaPlayer>

void set_dark_mode_main_page(bool g);
void set_ID_from_LOGIN(QString g);

namespace Ui {
class main_page;
}

class main_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_page(QWidget *parent = nullptr);
    ~main_page();

private slots:

    void set_color(char c);

    void on_pushButton_clicked();

    void on_next_pushbutton_clicked();

    void on_previous_pushbutton_clicked();

    void on_serach_button_clicked();

    void on_pushButton_2_clicked();

    void on_me_button_clicked();

    void on_profile_clicked();

    void on_mynetwork_button_clicked();

    void on_job_button_clicked();

    void on_message_button_clicked();

    void on_comment_clicked();

    void on_like_button_clicked();

    void on_audio_clicked();

private:
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    Ui::main_page *ui;
};

#endif // MAIN_PAGE_H
