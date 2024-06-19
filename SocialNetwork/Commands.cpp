#include "Commands.h"
#include <iostream>

Commands::Commands(std::string com): current(defaultU), opened(defaultT), nowOPenedQu(defaultQ)
{
	command == com;
}

Commands::Commands() : current(defaultU), opened(defaultT), nowOPenedQu(defaultQ)
{
	command == "";
}

void Commands::load()
{
    std::cout << "Enter the name of your file: ";
	std::cin >> file;
	newFile.open(file);
	if (newFile) {
		char arr[MAX_CONTENT];
        User user;
        Theme theme;
            newFile.getline(arr, MAX_CONTENT);

            //read content from file
            if (arr[0] == '1') { 
                // Read from file until end or error
                while (true) {
                    // Attempt to read data
                    user.readFromFile(newFile);

                    // Store the read user in the vector
                    users.push_back(user);

                    // Check for end of file or error
                    if (newFile.eof()) {
                        break; // End of file reached
                    }
                    else if (newFile.fail()) {
                        std::cerr << "Failed to read from file\n";
                        break; // Error occurred
                    }

                    
                }
            }
            else if (arr[0] == '2') {
                //read themes
               // Read from file until end or error
                while (true) {
                    // Attempt to read data
                    theme.readFromFile(newFile);

                    // Store the read user in the vector
                    themes.push_back(theme);

                    // Check for end of file or error
                    if (newFile.eof()) {
                        break; // End of file reached
                    }
                    else if (newFile.fail()) {
                        std::cerr << "Failed to read from file\n";
                        break; // Error occurred
                    }

                    
                }
                
            }
            else {
                std::cout << "File does not contain useful information!\n";
                
            }
        
	}
	else {
		CreatenewFile();
	}
	std::cout << "File successfully opened!" << std::endl;
	close();
}

void Commands::close()
{
	newFile.close();
	std::cout << "File successfully closed!" << std::endl;
}

void Commands::save() {
    if (file.empty()) {
        std::cout << "No file is currently open." << std::endl;
        return;
    }
    std::ofstream File(file);
    if (File.is_open()) {
        for (size_t i = 0; i < users.size(); i++)
        {
            users.at(i).writeToFile(newFile);
        }
        for (size_t i = 0; i < themes.size(); i++)
        {
            themes.at(i).writeToFile(newFile);
        }
        std::cout << "Successfully saved " << file << std::endl;
        File.close();
    }
    else {
        std::cout << "Failed to save file " << file << std::endl;
    }
}

void Commands::saveAs(const std::string& newFilename) {
    std::ofstream file(newFilename);
    if (file.is_open()) {
        for (size_t i = 0; i < users.size(); i++)
        {
            users.at(i).writeToFile(newFile);
        }
        for (size_t i = 0; i < themes.size(); i++)
        {
            themes.at(i).writeToFile(newFile);
        }
        std::cout << "Successfully saved as " << newFilename << std::endl;
        file.close();
    }
    else {
        std::cout << "Failed to save as " << newFilename << std::endl;
    }
}

void Commands::CreatenewFile()
{
    // Create an ofstream object, which represents the file
    std::ofstream emptyFile(file);

    // Check if the file was successfully created
    if (emptyFile) {
        std::cout << "File " << file << " created successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to create file " << file << "." << std::endl;
    }

    // Close the file
    emptyFile.close();
}

void Commands::signup(std::string firstName, std::string lastName, std::string userName, std::string password)
{
    if (users.empty()) {
        Admin newone= Admin(firstName, lastName, userName, password);
        users.push_back(newone);
        current = newone;
    }
    else {
        User newone = User(firstName, lastName, userName, password);
        users.push_back(newone);
        //when a user sign-up in a system, he is logged in authomatically
        current = newone;
    }
}

void Commands::login(std::string userName, std::string password)
{
    if (isPasswordCorrect(userName, password)) {
        current = users.at(getUserByUsername(userName));
        std::cout << "Logged in successfully!\n";
        std::cout << "Welcome, " << userName<<"\n";
    }
    else {
        std::cout << "Wrong password!\n";
    }
   
}

void Commands::create(std::string title, std::string description)
{
    Theme newone= Theme(title, current.getUserID(), description);
    themes.push_back(newone);
}

void Commands::search(std::string titleWord)
{
    for (size_t i = 0; i < themes.size(); i++)
    {
        if (themes[i].getTitle().find(titleWord) != std::string::npos) {
            std::cout << themes[i].getTitle() << " { id: " << themes[i].getThemeID() << " }\n";
        }
    }
}

void Commands::open(int num)
{
    if (num > themes.size()) {
        std::cout << "Sorry, we cannot find a theme with this id!\n";
    }
    else {
        opened = themes.at(num);
    }
}

void Commands::open(std::string title)
{
    if (isTitleFound(title)) {
        opened = themes.at(getThemeByTitle(title));
    }
    else {
        std::cout << "Sorry, no title found!\n";
    }
}

void Commands::list()
{
    opened.printQuestions();
}

void Commands::post(std::string title, std::string content)
{
    if (opened.getTitle() == "") {
        std::cout << "First you have to open a theme!\n";
    }
    else {
        Question newOne = Question(title, content, current.getUserID());
        opened.addQuestion(newOne);
        themes.at(getThemeByTitle(opened.getTitle())) = opened;
        std::cout << "Question added successfully!\n";
    }
}

void Commands::post_open(int num)
{
    //validation was made in the run() function, so here we assume everything is valid 
    std::string post_command;
    do {
        std::cout << "Enter a command related to the post: ";
        std::cin >> post_command;
        if (post_command == "add") {
            std::string text;
            std::cout << "Please, enter your comment: ";
            std::cin >> text;
            Comment newComment(current, text);
            nowOPenedQu.addComment(newComment);
        }
        else if (post_command == "answer") {
            std::cout << "Enter the id of the comment you want to vote for: ";
            int id;
            std::cin >> id;
            std::string answer;
            if (nowOPenedQu.findCommentIndex(id) != -1) {
                std::cout << "Enter your answer: ";
                std::cin >> answer;
                Comment newanswer(current, answer);
                nowOPenedQu.getComment(id).answerComment(newanswer);
            }
            else {
                std::cout << "Comment is not excisting!\n";
            }
        }
        else if (post_command == "upvote") {
            std::cout << "Enter the id of the comment you want to vote for: ";
            int id;
            std::cin >> id;
            nowOPenedQu.upvoteComment(id);
        }
        else if (post_command == "downvote") {
            std::cout << "Enter the id of the comment you want to vote for: ";
            int id;
            std::cin >> id;
            nowOPenedQu.downvoteComment(id);
        }
        else if (post_command == "remove") {
            std::cout << "Enter the id of the comment you want to vote for: ";
            int id;
            std::cin >> id;
            if (nowOPenedQu.findCommentIndex(id) != -1) {
                nowOPenedQu.deleteComment(id, current);
            }
            else {
                std::cout << "Comment is not excisting!\n";
            }
        }
        else if (post_command == "show") {
            nowOPenedQu.showComments();
        }
        else if (post_command != "post_quit") {
            std::cout << "Invalid command!\n";
        }
    } while (post_command != "post_quit");
    post_quit();
}

void Commands::post_quit()
{
    if (nowOPenedQu.getTitle() == "") {
        std::cout << "No opened post right now!\n";
    }
    else {
        nowOPenedQu = Question();
        std::cout << "Post successfully closed!\n";
    }
}

void Commands::quit()
{
    if (opened.getTitle() == "") {
        std::cout << "No opened theme right now!\n";
    }
    else {
        opened = Theme();
        std::cout << "Theme successfully closed!\n";
    }
}

void Commands::exit() {
        std::string choice;
        std::cout << "Do you want to save changes before exiting? (yes/no): ";
        std::cin >> choice;
        if (choice == "yes") {
            save();
        }
    std::cout << "Exiting text editor." << std::endl;
}














void Commands::logout()
{
    if (current.getuserName() == "") {
        std::cout << "You are not logged in!\n";
    }
    else {
        current = User();
        std::cout << "Successfully logged out!\n";
    }
}

void Commands::edit()
{
    if (current.isUserAdmin()) {
        int option, userID;
        std::cout << "Are you going to edit your profile or somebody else's?\n";
        std::cout << "Please enter '1' for your profile or 2 for somebody else \n";
        std::cin >> option;
        switch (option)
        {
        case 1:
            current.editUser(current);
            users.at(getUserByUsername(current.getuserName())) = current;
            break;
        case 2:
            std::cout << "Please enter userId for another account: ";
            std::cin >> userID;
            if (userID > users.size()) {
                std::cout << "Invalid user!\n";
            }
            else {
                current.editUser(users.at(userID), userID);
            }
        
            break;
        default:
            std::cout << "Invalid option!\n";
            break;
        }
      
    }
    else {
        current.editUser(current);
        users.at(getUserByUsername(current.getuserName())) = current;
    }
}

//THE MOST IMPORTANT FUNCTION
//the main function of the program. 
void Commands::run()
{
    do {
 std::cout << "Please enter a command: ";
    std::cin >> command;
    if (command == "load") {
        load();
   } else if (command == "close") {
        close();
    }
   else if (command == "save") {
        save();
    }
   else if (command == "save as") {
        std::cout << "Enter the name of the new file: ";
        std::string name;
        std::cin >> name;
        saveAs(name);
    }
    else if (command == "signup") {
        std::string name;
        std::string lastname;
        std::string username;
        std::string password;

        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter your last name: ";
        std::cin >> lastname;
        std::cout << "Enter your username: ";
        std::cin >> username;
        while (!isUsernameUnique(username)) {
            std::cout << "Sorry, this username is already taken! Try new one!\n";
            std::cin >> username;
        }
        std::cout << "Choose a password: ";
         enterPassword(password);
        signup(name, lastname, username, password);
    }
    else if (command == "login") {
        std::string username;
        std::cout << "Enter your username: ";
        std::cin >> username;
        if (isUsernameUnique(username)) {
            std::cout << "Sorry, we cannot find you!\n";
        }
        else {
            std::string password;
            std::cout << "Enter your password: ";
            password=enterPassword(password);
            login(username, password);
        }
    }
    else if (command == "edit") {
        if (current.getuserName() == "") {
            std::cout << "You have to log in first!\n";
        }
        else {
            edit();
        }
    }
    else if (command == "create") {
        if (current.getuserName() == "") {
            std::cout << "You have to log in first!\n";
        }
        else {
            std::string title;
            std::string description;
            std::cout << "Enter the title of your theme: ";
            std::cin >> title;
            std::cout << "Enter a description: ";
            std::cin >> description;
            create(title, description);
        }
    }
    else if (command == "search") {
        std::string titleWord;
        std::cout << "Enter a key word: ";
        std::cin >> titleWord;
        search(titleWord);
    }
    else if (command == "open") {
        std::string option;
        std::cout << "Enter a full title or id of a theme: ";
        std::cin >> option;
        if (is_number(option)) {
            int id = stoi(option);
            open(id);
        }
        else {
            open(option);
        }
    }
    else if (command == "list") {
        if (opened.getTitle() == "") {
            std::cout << "No opened theme!\n";
        }
        else {
            list();
        }
    }
    else if (command == "post") {
        if (current.getuserName() == "") {
            std::cout << "You have to log in first!\n";
        }
        else if (opened.getTitle() == "") {
            std::cout << "No theme is opened!\n";
        }
        else {
            std::string title;
            std::string content;
            std::cout << "Enter the title of your questiom: ";
            std::cin >> title;
            std::cout << "Enter a content: ";
            std::cin >> content;
            post(title, content);
        }
    }

    //add other commands here 
    else if (command == "post_open") {
        int qid;
        if (opened.getTitle() == " ") {
            std::cout << "No theme is opned!\n";
        }
        else {
            std::cout << "Enter post id: ";
            std::cin >> qid;
            nowOPenedQu = opened.getQuestion(qid);
            post_open(qid);
        }
       //should a theme be opened first or it should be searched in all themes
       //this solution needs a theme to be opened first in order to edit questions
    }
    else if (command == "post_quit") {
        post_quit();
    }
    else if (command == "quit") {
        quit();
    }
    else if (command == "logout") {
        logout();
    }
    else if (command != "exit") {
        std::cout << "Command unknown! Please try again!\n";
    }
    } while (command != "exit");
    exit();
}

bool Commands::isUsernameUnique(std::string username)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].getuserName() == username) {
            return false;
        }
    }
    return true;
}

int Commands::getUserByUsername(std::string username)
{
    int index = -1;
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].getuserName() == username) {
            index = i;
        }
    }
    return index;
}

bool Commands::isPasswordCorrect(std::string username, std::string password)
{
    return users.at(getUserByUsername(username)).getpassword() == password;
   
}

//this fragment visualised the password as stars while it is inputed 
std::string Commands::enterPassword(std::string password)
{
    char ch;
    // Read characters until Enter is pressed
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') { // Backspace character
            if (!password.empty()) {
                std::cout << "\b \b"; // Move the cursor back and erase the character
                password.pop_back(); // Remove the last character from the password
            }
        }
        else {
            std::cout << '*'; // Display asterisk instead of the actual character
            password.push_back(ch); // Add the character to the password string
        }
        
    }
    std::cout << "\n";
    return password;
}
bool Commands::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool Commands::isTitleFound(std::string title)
{
    for (size_t i = 0; i < themes.size(); i++)
    {
        if (themes[i].getTitle()==title) {
            return true;
        }
    }
    return false;
}

int Commands::getThemeByTitle(std::string title)
{
    int index = -1;
    for (size_t i = 0; i < themes.size(); i++)
    {
        if (themes[i].getTitle()==title) {
            index = i;
        }
    }
    return index;
}
