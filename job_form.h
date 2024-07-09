#ifndef JOB_FORM_H
#define JOB_FORM_H

#include <QWidget>

namespace Ui {
class job_form;
}

class job_form : public QWidget
{
    Q_OBJECT

public:
    explicit job_form(QWidget *parent = nullptr);
    ~job_form();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_apply_clicked();

    void on_ignore_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_home_button_clicked();

    void on_me_button_clicked();

    void on_pushButton_clicked();

    void on_mynetwork_button_clicked();

    void on_message_button_clicked();

    void on_serach_button_clicked();

private:
    Ui::job_form *ui;
};

#endif // JOB_FORM_H
