#include "comment.h"

Comment::Comment(QString sender_ID , QString content_text , QString content_Picture ,QString content_Video, QString content_audio , QString Post_ID , QString comment_ID)
    : content(sender_ID , content_text ,content_Picture ,content_Video,content_audio)
{
    this->Post_ID = Post_ID;
    this->comment_ID = comment_ID;
}

QString Comment::get_Post_ID()
{
    return Post_ID;
}

QString Comment::get_comment_ID()
{
    return comment_ID;
}
