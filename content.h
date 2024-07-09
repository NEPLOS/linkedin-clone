#ifndef CONTENT_H
#define CONTENT_H

#include <QString>
#include "timew.h"

class content
{

private:

    timew time_send;
    QString sender_ID;
    QString content_text;
    QString content_Picture;
    QString content_Video;
    QString content_Audio;

public:
    content(QString sender_ID , QString content_text , QString content_Picture ,QString content_Video , QString content_Audio);
    QString get_sender_ID();
    QString get_content_text();
    QString get_content_Picture();
    QString get_content_Video();
    QString get_content_Audio();
    timew get_time_send();

};

#endif // CONTENT_H
