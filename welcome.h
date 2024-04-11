#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

namespace Ui {
class welcome;
}

class welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = nullptr);
    ~welcome();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::welcome *ui;
};

#endif // WELCOME_H
