#pragma once
#include "User.h"
class Admin: public User
{
public:
	Admin(std::string firstName, std::string lastName, std::string userName, std::string password, bool isAdmin=true);
    void editUser(User& user, int userID=0) override;
	
private:
	
};

