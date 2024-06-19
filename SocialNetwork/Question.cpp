#include "Question.h"

void Question::upvoteComment(int commentId)
{
    int index = findCommentIndex(commentId);
    if (index != -1) {
        comments[index].setGrade(comments[index].getGrade()+1);
        comments[index].getAuthor().setPoints(comments[index].getAuthor().getPoints() + 1);
    }
    else {
        std::cout << "Comment is not excisting!\n";
    }
}

void Question::downvoteComment(int commentId)
{
    int index = findCommentIndex(commentId);
    if (index != -1) {
        comments[index].setGrade(comments[index].getGrade() - 1);
        comments[index].getAuthor().setPoints(comments[index].getAuthor().getPoints()-1);
    }
    else {
        std::cout << "Comment is not excisting!\n";
    }
}

std::string Question::getTitle() const
{
    return title;
}

int Question::getUniqueQ() const
{
    return uniqueQ;
}

Comment Question::getComment(int id) const
{
    return id<comments.size()?comments[id]:throw("Comment not excisting!\n");
}

void Question::show() const
{
    std::cout << "Title: " << title << "\n";
    std::cout << "Content: " << content << "\n";
    std::cout << "Number of comments: " << comments.size() << "\n";
}

void Question::showComments() const
{
    for (size_t i = 0; i < comments.size(); ++i) {
        comments[i].print();
        std::cout << "\n";
    }
}

void Question::readFromFile(std::fstream& file)
{
    file >>  uniqueQ >> title >> content >> asker;
    Comment comment;
    std::string line;
    size_t pos;
    while (getline(file, line)) {
        pos = line.find("Question");
        if (pos != std::string::npos) {
            break;
        }
        else {
            comment.readFromFile(file);
            comments.push_back(comment);
        }
    }
}

void Question::writeToFile(std::fstream& file) const
{
    file << "Question " << uniqueQ << ": " << title << " " << content << " " << asker;
    for (size_t i = 0; i < comments.size(); i++)
    {
        comments[i].writeToFile(file);
        file << "\n";
    }
}

int Question::findCommentIndex(int commentId) const
{
    for (size_t i = 0; i < comments.size(); ++i) {
        if (comments[i].getId() == commentId) {
            return i;
        }
    }
    return -1; // not found
}

Question::Question(std::string title, std::string content, int asker)
{
    this->title = title;
    this->content = content;
    this->asker = asker;
    this->uniqueQ = QID;
    QID++;
}

Question::Question()
{

}

void Question::addComment(Comment comment)
{
    comments.push_back(comment);
}

void Question::deleteComment(int commentId, User& author)
{
    int index = findCommentIndex(commentId);
    if (index != -1 && (comments[index].getAuthor().getuserName() == author.getuserName() || author.isUserAdmin())) {
        comments.erase(comments.begin() + index);
    }
    std::cout << "You have no permission to delete this comment!\n";
}
