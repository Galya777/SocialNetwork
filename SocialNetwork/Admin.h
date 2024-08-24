#pragma once
#include "User.h"
class Admin: public User
{
public:
	Admin(const std::string& firstName, const std::string& lastName, const std::string& userName, const std::string& password, bool isAdmin =true);
    void editUser(User& user, int userID=0) override;
	
private:
	
};

