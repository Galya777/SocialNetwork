#pragma once
#include <string>
#include <vector>
#include "Question.h"
static int THIS_IDT = 0;
class Theme
{
public:
	Theme(std::string title, int userID, std::string description);
	Theme();

	//getters
	std::string getTitle() const;
	std::string getDescription() const;
	int getThemeID() const;
	Question getQuestion(int id) const;

	//setters
	void setTitle(std::string title);
	void setDescription(std::string description);

	void addQuestion(Question question);
	void removeQuestion(Question question);

	void readFromFile(std::fstream& file);
	void writeToFile(std::fstream& file) const;

	void printQuestions();

private:
	std::string title;
	int userID;
	std::string description;
	int uniqueID;

	std::vector<Question> questions;
	bool isOpen;

	bool findQuestion(std::string title);
	int getQuestionId(std::string title);
};

