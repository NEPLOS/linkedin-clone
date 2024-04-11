#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QMainWindow>

void set_dark_mode_main_page(bool g);

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

    void set_color();

    void on_pushButton_clicked();

private:
    Ui::main_page *ui;
};

#endif // MAIN_PAGE_H
