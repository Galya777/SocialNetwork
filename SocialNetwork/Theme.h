#pragma once
#include <string>
#include <vector>
#include "Question.h"

class Theme
{
public:
	Theme(const std::string& title, int userID, const std::string& description);
	Theme();

	//getters
	std::string getTitle() const;
	std::string getDescription() const;
	int getThemeID() const;
	Question getQuestion(int id) const;

	//setters
	void setTitle(const std::string& title);
	void setDescription(const std::string& description);

	void addQuestion(Question question);
	void removeQuestion(Question question);

	void readFromFile(std::fstream& file);
	void writeToFile(std::fstream& file);

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

	static int THIS_IDT;
};

