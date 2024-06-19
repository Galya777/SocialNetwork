#pragma once
#include "Comment.h"
#include <vector>
#include <string>
static int QID = 0;
class Question
{
public:
	Question(std::string title, std::string content, int asker);
	Question();

	void addComment(Comment comment);
	void deleteComment(int commentId, User& author);
	

	//react
	void upvoteComment(int commentId);
	void downvoteComment(int commentId);


	std::string getTitle() const;
	int getUniqueQ() const;
	Comment getComment(int id) const;

	void show() const;
	void showComments() const;

	void readFromFile(std::fstream& file);
	void writeToFile(std::fstream& file) const;

	int findCommentIndex(int commentId) const;

private:
	std::vector<Comment> comments;

	std::string title;
	std::string content;
	int asker;
	int uniqueQ;

	
};

