#ifndef FILL_THE_FORM_H
#define FILL_THE_FORM_H

#include <QMainWindow>

namespace Ui {
class fill_the_form;
}

void mailmail(QString hmm);
void set_dark_mode_fill_the_form(bool n);

class fill_the_form : public QMainWindow
{
    Q_OBJECT

public:

    explicit fill_the_form(QWidget *parent = nullptr);
    ~fill_the_form();

private slots:

    void set_color();

    void on_Done_clicked();

    void on_company_box_activated(int index);

    void on_job_box_activated(int index);

    void on_uni_box_activated(int index);


private:

    Ui::fill_the_form *ui;
};

#endif // FILL_THE_FORM_H
