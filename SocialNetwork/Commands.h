#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "User.h"
#include "Admin.h"
//library needed to visualize the password as stars
#include <conio.h>
#include "Theme.h"
/*
* The class whici is representing the engine of the programm
* Comands here are:
* opening a file
* saving into same/new file
* 
* There will be 2 text files:
* one with users
* one with themes, questions and comments 
* When open is added, only one of the things can be read
* Òhe function open() can find out if the file contains Users, or Themes by the first row of the file
* which contains an indication number like:
* 1 - for users
* 2 - for themes
*
* This method is way easier for reading data from file and the data in the files is way more organized. 
* 
*/
const int MAX_CONTENT = 1000;
class Commands
{
public:
	Commands(std::string com);
	Commands();
	void load();
	void close();
	void save();
	void exit();
	void saveAs(const std::string& newFilename);
	void CreatenewFile();

	//signing up the user in the system
	void signup(std::string firstName, std::string lastName, std::string userName, std::string password);

	void login(std::string userName, std::string password);
	void create(std::string title, std::string description);
	void search(std::string titleWord);
	void open(int num);
	void open(std::string title);
	void list();
	void post(std::string title, std::string content);
	void post_open(int num);
	void post_quit();
	void quit();
	void logout();


	void edit();

	void run();

private:
	//list of all excisting users in the system
	std::vector <User> users;
	//list of all excisting themes
	std::vector<Theme> themes;
	//opened theme opened
	Theme& opened;
	//opened post
	Question& nowOPenedQu;

	//user which is currently logged in the system
	//unfortunatelly for now there could be only one logged in user at a time
	User& current;

	//default values to make the refferences
	//having default values to be used as references is considered better practise in OOP than using pointers
	//(in this case)
	User defaultU;
	Theme defaultT;
	Question defaultQ;

	//a simple function that checks if a username is unique
	bool isUsernameUnique(std::string username);
	//returns the index of a user with this username
	int getUserByUsername(std::string username);
	//checks if a password is correct
	bool isPasswordCorrect(std::string username, std::string password);
	//function to enter a crypted password
	std::string enterPassword(std::string password);
	//a helping function to find is a string is a number
	bool is_number(const std::string& s);
	//a simple function that checks if a title of a theme is found
	bool isTitleFound(std::string title);
	//returns the index of a theme by its title
	int getThemeByTitle(std::string title);

	

	std::string command;
	std::string file;
	std::fstream newFile;
};

