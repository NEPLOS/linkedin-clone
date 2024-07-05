#ifndef WELCOME_PAGE_H
#define WELCOME_PAGE_H

#include <QMainWindow>

namespace Ui {
class welcome_page;
}

class welcome_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit welcome_page(QWidget *parent = nullptr);
    ~welcome_page();

private slots:
    void on_pushButton_clicked();

private:
    Ui::welcome_page *ui;
};

#endif // WELCOME_PAGE_H
