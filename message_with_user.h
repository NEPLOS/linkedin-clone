#ifndef MESSAGE_WITH_USER_H
#define MESSAGE_WITH_USER_H

#include <QWidget>

void get_the_ideas_chat_screen(QString me , QString user);

namespace Ui {
class message_with_user;
}

class message_with_user : public QWidget
{
    Q_OBJECT

public:
    explicit message_with_user(QWidget *parent = nullptr);
    ~message_with_user();
    void add_scroll_area();

private slots:
    void on_send_clicked();

private:
    Ui::message_with_user *ui;
};

#endif // MESSAGE_WITH_USER_H
