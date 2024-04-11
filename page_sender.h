#ifndef PAGE_SENDER_H
#define PAGE_SENDER_H

#include <QMainWindow>

namespace Ui {
class page_sender;
}

class page_sender : public QMainWindow
{
    Q_OBJECT

public:
    explicit page_sender(QWidget *parent = nullptr);
    ~page_sender();

private:
    Ui::page_sender *ui;
};

#endif // PAGE_SENDER_H
