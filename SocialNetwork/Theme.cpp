#include "Theme.h"
#include <iostream>

Theme::Theme(std::string title, int userID, std::string description)
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

void Theme::setTitle(std::string title)
{
	this->title = title;
}

void Theme::setDescription(std::string description)
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
	file >> userID >> title >> userID >> description;
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

void Theme::writeToFile(std::fstream& file) const
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


