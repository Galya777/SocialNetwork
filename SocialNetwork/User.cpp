#include "User.h"

std::string User::getfirstName() const
{
    return firstName;
}

std::string User::getlastName() const
{
    return lastName;
}

std::string User::getuserName() const
{
    return userName;
}

std::string User::getpassword() const
{
    return password;
}

double User::getPoints() const
{
    return points;
}

int User::getUserID() const
{
    return unique;
}

void User::readFromFile(std::fstream& file)
{
    file >> firstName >> lastName >> userName >> password>>points >> isAdmin;
    //file.read((char*)userName.c_str(), sizeof(userName));
    //file.read((char*)password.c_str(), sizeof(password));
    this->unique = THIS_ID;
    THIS_ID++;
}

void User::writeToFile(std::fstream& file) const
{
    file << firstName << "  " << lastName<<" " << userName<<" " << password<< " " << isAdmin;
}

bool User::isUserAdmin() const
{
    return isAdmin;
}

void User::setIsModerator(User changer, bool isModerator)
{
    if (changer.isUserAdmin()) {
        this->isAdmin = isModerator; 
    }
    else {
        std::cout << "You do not have permission to do that!\n";
    }
}

User::User(std::string firstName, std::string lastName, std::string userName, std::string password, bool isAdmin)
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

User::User()
{
}

void User::editUser(User& user, int userID)
{
    int option;
    std::cout << "What do you want to edit?\n";
    std::cout << "1. First Name\n";
    std::cout << "2. Last Name\n";
    std::cout << "3. Password\n";
    std::cout << "Please enter the number: ";
    std::cin >> option;
    std::string attribute;
    std::string confirm;
    switch (option) {
    case 1:
        std::cout << "Enter your new first name: ";
        std::cin >> attribute;
        setFirstName(attribute);
        std::cout << "Name changed successfully!\n";
        break;
    case 2:
        std::cout << "Enter your new last name: ";
        std::cin >> attribute;
        setLastName(attribute);
        std::cout << "Name changed successfully!\n";
        break;
    case 3:
        std::cout << "Enter your new password: ";
        std::cin >> attribute;
        std::cout << "Please confirm your new password: ";
        std::cin >> confirm;
        while (attribute != confirm) {
            std::cout << "Passwords are not nthe same!\nTry again!\n";
            std::cin >> confirm;
        }
        setPassword(attribute);
        std::cout << "Password changed successfully!\n";
        break;
    default:
        std::cout << "Invalid option!\n";
        break;
    }
    
}

void User::setFirstName(std::string firstName)
{
    this->firstName = firstName;
}

void User::setLastName(std::string lastName)
{
    this->lastName = lastName;
}

void User::setUserName(std::string userName)
{
    this->userName = userName;
}

void User::setPassword(std::string password)
{
    this->password = password;
}

void User::setPoints(int point)
{
    this->points = points;
}
