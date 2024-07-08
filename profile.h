#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>

namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_Edit_profile_button_clicked();

    void on_home_button_clicked();

    void on_submit_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_switch_mode_currentIndexChanged(int index);

    void on_make_company_clicked();

    void on_mynetwork_button_clicked();

    void on_job_button_clicked();

    void on_serach_button_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_message_button_clicked();

private:
    Ui::profile *ui;
};

#endif // PROFILE_H
