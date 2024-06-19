#pragma once
#include <string>
#include <iostream>
#include <fstream>
static int THIS_ID = 0;
//Instead of dynamic casting, I use virtual polimorphism because otherwise I do not have a chance to have refferences and default values
//I found two solutions to this problem: 
// 1. polymorphism and virtual functions
// 2. Visitor Pattern
//This application's operations are relatively simple and closely related to the objects themselves, so I go with polymorphism and virtual functions
class User
{
public:
	User(const std::string firstName, const std::string lastName, const std::string userName, const std::string password, bool isAdmin = false);
	User();

	virtual ~User() {}
	//the parameter is optional because only admins can edit other users
	virtual void editUser(User& user, int userID = 0);
	

	//setters
	void setFirstName(const std::string firstName);
	void setLastName( const std::string lastName);
	void setUserName( const std::string userName);
	void setPassword( const std::string password);
	void setPoints(int point);

	//getters
	std::string getfirstName() const;
	std::string getlastName() const;
	std::string getuserName() const;
	std::string getpassword() const;
	double getPoints() const;
	int getUserID() const;

	void readFromFile(std::fstream& file);
	void writeToFile(std::fstream& file) const;

	bool isUserAdmin() const;

	//this function askes for the changer of the status 
	//the reason for this is only admins can change roles
	//we do not want random users touch user rights
	//being protected, the Admin class has not the access to access it
	//Maybe there is a better solution for this problem but this is what I could come with
	//Another thing that can be done is making User and Admin friend but this breaks the Encapsulation principle
	void setIsModerator(User changer, bool isModerator);

protected:
	
	std::string firstName;
	std::string lastName;
	std::string userName;
	std::string password;
	int unique;
	double points;

	bool loged;
	bool isAdmin;

	
};

