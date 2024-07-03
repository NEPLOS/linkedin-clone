#ifndef MESSAGE_CONTACT_H
#define MESSAGE_CONTACT_H

#include <QWidget>
#include <QVBoxLayout>

void get_the_user_ID(QString ID_ID_ID);

namespace Ui {
class message_contact;
}

class message_contact : public QWidget
{
    Q_OBJECT

public:
    explicit message_contact(QWidget *parent = nullptr);
    ~message_contact();

private slots:
    void on_pushButton_clicked();

    void on_me_button_clicked();

    void on_home_button_clicked();

    void on_job_button_clicked();

    void on_mynetwork_button_clicked();

    void on_serach_button_clicked();

    void on_pushButton_2_clicked();

    void on_next_clicked();

    void on_previous_clicked();

private:
    void loadDataFromDatabase();
    Ui::message_contact *ui;
};

#endif // MESSAGE_CONTACT_H
