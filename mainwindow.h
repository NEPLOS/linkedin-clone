#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

void set_bool_dark_mode_mainwindows(bool n);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    bool have_dark_mode_mainwindows = false;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void set_color();

    void on_DC_clicked();

    void on_AC_clicked();

    void on_pushButton_clicked();

    void on_hide_pass_clicked();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
