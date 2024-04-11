#ifndef VERIFY_CODE_H
#define VERIFY_CODE_H

#include <QMainWindow>

void set_bool_dark_mode_verify_code(bool n);

namespace Ui {
class verify_code;
}

void haveacc(bool t);

class verify_code : public QMainWindow
{
    Q_OBJECT

public:


    explicit verify_code(QWidget *parent = nullptr);
    ~verify_code();

private slots:

    void set_color_verify_code();

    void on_get_the_code_clicked();

    void on_done_clicked();

private:
    Ui::verify_code *ui;
};

#endif // VERIFY_CODE_H
