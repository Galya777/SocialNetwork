#include "Theme.h"
#include <iostream>
int Theme::THIS_IDT = 0;
Theme::Theme(const std::string& title, int userID, const std::string& description)
{
	setTitle(title);
	this->uniqueID = THIS_IDT;
	THIS_IDT++;
	setDescription(description);
	isOpen = true;
	this->userID = userID;
}

Theme::Theme()
{
}

std::string Theme::getTitle() const
{
	return title;
}

std::string Theme::getDescription() const
{
	return description;
}

int Theme::getThemeID() const
{
	return uniqueID;
}

Question Theme::getQuestion(int id) const
{
	return id < questions.size() ? questions[id] : throw("Question not excisting!\n");
}

void Theme::setTitle(const std::string& title)
{
	this->title = title;
}

void Theme::setDescription(const std::string& description)
{
	this->description = description;
}

void Theme::addQuestion(Question question)
{
	questions.push_back(question);
}

void Theme::removeQuestion(Question question)
{
	if (!findQuestion(question.getTitle())) {
		std::cout << "Question is not excisting!\n";
	}
	else {
		questions.erase(questions.begin() + getQuestionId(question.getTitle()));
		std::cout << "Question successfully removed!\n";
	}
}

void Theme::readFromFile(std::fstream& file)
{
	file >> userID;
	char cht, chd;             // Variable to store each character read from the file
	// Read character by character
	while (file.get(cht)) {
		if (cht == ',') {  // Check if the character is a comma
			break;        // Exit the loop if a comma is found
		}
		title += cht;     // Append character to the result string
	}
	file >> userID;
	// Read character by character
	while (file.get(chd)) {
		if (chd == ',') {  // Check if the character is a comma
			break;        // Exit the loop if a comma is found
		}
		description += chd;     // Append character to the result string
	}
	//find a way to read the questions
	Question question;
	std::string line;
	size_t pos;
	while (getline(file, line)) {
		pos = line.find("Theme");
		if (pos != std::string::npos) {
			break;
		}
		else {
			question.readFromFile(file);
			questions.push_back(question);
		}
	}
}

void Theme::writeToFile(std::fstream& file) 
{
	file << "Theme "<<uniqueID << ": " << title << " " << userID << " " << description;
	for (size_t i = 0; i < questions.size(); i++)
	{
		questions[i].writeToFile(file);
		file << "\n";
	}
}

void Theme::printQuestions()
{
	for (size_t i = 0; i < questions.size(); i++)
	{
		std::cout << questions[i].getTitle() << " {id: "<<questions[i].getUniqueQ()<< " }\n";
	}
}

bool Theme::findQuestion(std::string title)
{
	for (size_t i = 0; i < questions.size(); i++)
	{
		if (questions[i].getTitle() == title) {
			return true;
		}
	}
	return false;
}

int Theme::getQuestionId(std::string title)
{
	for (size_t i = 0; i < questions.size(); i++)
	{
		if (questions[i].getTitle() == title) {
			return i;
		}
	}
	return -1;
}


