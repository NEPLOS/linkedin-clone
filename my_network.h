#ifndef MY_NETWORK_H
#define MY_NETWORK_H

#include <QWidget>

void get_user_id_my_network(QString id);

namespace Ui {
class my_network;
}

class my_network : public QWidget
{
    Q_OBJECT

public:
    explicit my_network(QWidget *parent = nullptr);
    ~my_network();

private slots:
    void on_request_button_clicked();

    void on_me_button_clicked();

    void on_pushButton_clicked();

    void on_home_button_clicked();

    void on_job_button_clicked();

    void on_serach_button_clicked();

    void on_message_button_clicked();

    void on_accept_button_1_clicked();

    void on_decline_button_1_clicked();

private:
    Ui::my_network *ui;
};

#endif // MY_NETWORK_H
