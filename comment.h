#ifndef COMMENT_H
#define COMMENT_H

#include "content.h"

class Comment : public content
{

    QString Post_ID;
    QString comment_ID;

public:
    Comment(QString sender_ID , QString content_text , QString content_Picture ,QString content_Video, QString content_audio , QString Post_ID , QString comment_ID);
    QString get_Post_ID();
    QString get_comment_ID();
};

#endif // COMMENT_H
