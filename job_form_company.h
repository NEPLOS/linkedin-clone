#ifndef JOB_FORM_COMPANY_H
#define JOB_FORM_COMPANY_H

#include <QWidget>

namespace Ui {
class job_form_company;
}

class job_form_company : public QWidget
{
    Q_OBJECT

public:
    explicit job_form_company(QWidget *parent = nullptr);
    ~job_form_company();

private slots:
    void on_mod_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_Accept_clicked();

    void on_Deny_clicked();

    void on_home_button_clicked();

    void on_me_button_clicked();

    void on_pushButton_2_clicked();

    void on_message_button_clicked();

    void on_mynetwork_button_clicked();

    void on_serach_button_clicked();

private:
    Ui::job_form_company *ui;
};

#endif // JOB_FORM_COMPANY_H
