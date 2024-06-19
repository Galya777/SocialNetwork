#pragma once
#include <string>
#include <vector>
#include "User.h"
static int QU = 0;

class Comment
{
public:
	Comment(User& author, std::string text);
	Comment() :author(authorD) {};
	Comment(const Comment& other);
	Comment& operator=(const Comment& other);

	void answerComment(Comment answer);
	void printAnswers();

	//getters
     User& getAuthor() const;
	std::string getText() const;
	unsigned int getGrade() const;
	int getId() const;

	//setters
	void setGrade(int grade);

	void print() const;

	void readFromFile(std::fstream& file);
	void writeToFile(std::fstream& file) const;

private:
	void copy(const Comment& other);
	
	
	std::vector<Comment> replies;
    User& author;
	std::string text;
	unsigned int grade;
	int uniqueComment;

	User authorD;
};

