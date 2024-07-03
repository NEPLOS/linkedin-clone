#ifndef MAKE_JOB_H
#define MAKE_JOB_H

#include <QWidget>

namespace Ui {
class make_job;
}

class make_job : public QWidget
{
    Q_OBJECT

public:
    explicit make_job(QWidget *parent = nullptr);
    ~make_job();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::make_job *ui;
};

#endif // MAKE_JOB_H
