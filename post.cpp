#include "post.h"

Post::Post(QString sender_ID , QString content_text , QString content_Picture ,QString content_Video ,QString content_Audio , QString Post_ID)
    : content(sender_ID , content_text ,content_Picture ,content_Video,content_Audio)
{
    this->Post_ID = Post_ID;
}

QString Post::get_Post_ID()
{
    return Post_ID;
}
int Post::get_Responset_counter()
{
    return Responset_counter;
}
