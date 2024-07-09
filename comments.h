#ifndef COMMENTS_H
#define COMMENTS_H

#include <QWidget>

void get_the_id(QString post_id , QString sender_id , QString my_id);

namespace Ui {
class comments;
}

class comments : public QWidget
{
    Q_OBJECT

public:
    explicit comments(QWidget *parent = nullptr);
    ~comments();
    void add_scroll_area();
private slots:
    void on_send_clicked();

private:
    Ui::comments *ui;
};

#endif // COMMENTS_H
