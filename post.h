#ifndef POST_H
#define POST_H

#include "content.h"
#include "like.h"
#include "comment.h"
#include <vector>

class Post : public content
{

    QString Post_ID;
    int Responset_counter = 0;
    std::vector<LIKE> likes;
    std::vector<Comment> comments;

public:
    Post(QString sender_ID , QString content_text , QString content_Picture ,QString content_Video ,QString content_Audio , QString Post_ID);
    QString get_Post_ID();
    int get_Responset_counter();
};

#endif // POST_H
