#ifndef MAKE_COMPANY_H
#define MAKE_COMPANY_H

#include <QWidget>

namespace Ui {
class make_company;
}

class make_company : public QWidget
{
    Q_OBJECT

public:
    explicit make_company(QWidget *parent = nullptr);
    ~make_company();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::make_company *ui;
};

#endif // MAKE_COMPANY_H
