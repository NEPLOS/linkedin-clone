#include "content.h"


content::content(QString sender_ID , QString content_text , QString content_Picture ,QString content_Video, QString content_Audio )
{

    this->sender_ID = sender_ID;
    this->content_text = content_text;
    this->content_Picture = content_Picture;
    this->content_Video = content_Video;
    this->content_Audio = content_Audio;
}

QString content::get_content_Audio()
{
    return content_Audio;
}

QString content::get_sender_ID()
{
    return sender_ID;
}

QString content::get_content_text()
{
    return content_text;
}

QString content::get_content_Picture()
{
    return content_Picture;
}

QString content::get_content_Video()
{
    return content_Video;
}

timew content::get_time_send()
{
    return time_send;
}
