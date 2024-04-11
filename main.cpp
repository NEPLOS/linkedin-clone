#include "page_sender.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    page_sender w;
    return a.exec();
}
