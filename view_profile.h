#ifndef VIEW_PROFILE_H
#define VIEW_PROFILE_H

#include <QWidget>
#include <QString>

void get_the_ID(QString ID);

namespace Ui {
class view_profile;
}

class view_profile : public QWidget
{
    Q_OBJECT

public:
    explicit view_profile(QWidget *parent = nullptr);
    ~view_profile();

private slots:
    void on_home_button_clicked();

    void on_me_button_clicked();

    void on_pushButton_3_clicked();

    void on_serach_button_clicked();

    void on_message_button_clicked();

    void on_mynetwork_button_clicked();

    void on_job_button_clicked();

    void on_connect_button_clicked();

private:
    Ui::view_profile *ui;
};

#endif // VIEW_PROFILE_H
