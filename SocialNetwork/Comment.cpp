#include "Comment.h"
int Comment::QU = 0;
Comment::Comment(User& author, const std::string& text): author(author)
{
	this->grade = 0;
	this->text = text;
	this->uniqueComment = QU;
	QU++;
}

Comment::Comment(const Comment& other):author(other.author)
{
	copy(other);
}

Comment& Comment::operator=(const Comment& other)
{
	if (this == &other) return *this; // Handle self-assignment
	copy(other);
	return *this;
	// TODO: insert return statement here
}

void Comment::answerComment(Comment answer)
{
	replies.push_back(answer);
}

void Comment::printAnswers()
{
	for (size_t i = 0; i < replies.size(); i++)
	{
		replies[i].print();
	}
}

 User& Comment::getAuthor() const
{
	return author;
	// TODO: insert return statement here
}

std::string Comment::getText() const
{
	return text;
}

unsigned int Comment::getGrade() const
{
	return grade;
}

int Comment::getId() const
{
	return uniqueComment;
}

void Comment::setGrade(int grade)
{
	this->grade = grade;
}

void Comment::print() const
{
	std::cout << "ID: " <<uniqueComment << ", Author: " << author.getuserName()
		<< ", Rating: " <<grade << "\n";
	std::cout << "Text: "<<text << "\n";
}

void Comment::readFromFile(std::fstream& file)
{
	file >> uniqueComment;
	author.readFromFile(file);
	char ch;           
	// Read character by character
	while (file.get(ch)) {
		if (ch == ',') {  // Check if the character is a comma
			break;        // Exit the loop if a comma is found
		}
		text += ch;     // Append character to the result string
	}
	file>> grade;
	Comment comment;
	std::string line;
	size_t pos;
	while (getline(file, line)) {
		pos = line.find("Comment");
		if (pos != std::string::npos) {
			break;
		}
		else {
			comment.readFromFile(file);
			replies.push_back(comment);
		}
	}
}

void Comment::writeToFile(std::fstream& file) const
{
	file << "Comment " << uniqueComment << ": ";
	author.writeToFile(file);
	file << text << " " << grade;
	for (size_t i = 0; i < replies.size(); i++)
	{
		replies[i].writeToFile(file);
		file << "\n";
	}
}

void Comment::copy(const Comment& other)
{
	this->author = other.author;
	this->grade = other.grade;
	this->uniqueComment = other.uniqueComment;
	this->text = other.text;
	this->replies = other.replies;
}




