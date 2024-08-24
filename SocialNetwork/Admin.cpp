#include "Admin.h"

Admin::Admin(const std::string& firstName, const std::string& lastName, const std::string& userName, const std::string& password, bool isAdmin)
{
    setFirstName(firstName);
    setLastName(lastName);
    setUserName(userName);
    setPassword(password);
    this->isAdmin = isAdmin;
    this->points = 0;
    this->loged = true;
    this->unique = THIS_ID;
    THIS_ID++;
}

void Admin::editUser(User& user, int userID)
{
    std::cout << "Will you change admin rights to this user?: ";
    std::string answer;
    if (answer == "yes") {
        if (user.isUserAdmin()) {
            user.setIsModerator(*this, false);
        }
        else {
            user.setIsModerator(*this, true);
        }
    }
    else if (answer == "no") {
        user.editUser(user);
    }
    else {
        std::cout << "Invalid answer!\n";
    }
}
