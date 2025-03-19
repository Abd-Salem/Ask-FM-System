/*
 * @file ask_sys.h
 * @brief header file for declaring ask system class which works as operating system.
 *
 * @Author: Abdallah_Salem
 */

#ifndef HEADERS_ASK_SYS_H_
#define HEADERS_ASK_SYS_H_
#include<map>
#include<memory>
#include<ctype.h>
#include<limits>
#include<fstream>
#include "custom_exceptions.h"
#include "user.h"
#include "question.h"

namespace ask {
/**
 * @brief Ask system manager with lists( users, questions), maps between parents and threads, data base files names and pointer for singleton pattern design.
 *
 */
class AskSystemManager {
private:
	std::vector<use::user> users; //member data for list of all signed up users in the system.
	std::vector<que::question> parents;
	std::vector<que::question> threads;
	std::map<int, std::vector<int>> parent_thread;
	const std::string user_file = "Data Base/Users.txt"; //data file name for users.
	const std::string question_file = "Data Base/Questions.txt"; // data file name for questions.
	static AskSystemManager *conf_sys;          //shared instance.

	/**
	 * @brief Empty Constructor
	 */
	AskSystemManager() noexcept;

	/**
	 * @brief add new user to the system.
	 *
	 * @param username for user's name.
	 * @param password for user's password.
	 * @param email for user's email.
	 */
	void addNewUser(std::string username, std::string password,
			std::string email) noexcept;

	/**
	 * @brief check for empty fields.
	 *
	 * @param input for input entered by user.
	 */
	void checkEmptyField(const std::string input);

	/**
	 * @brief check if email is written in valid way.
	 *
	 * @param email for email text provided by user.
	 */
	void checkEmailValidation(const std::string email);

	/**
	 * @brief check password is created in valid way.
	 *
	 * @param password for password provided by user.
	 */
	void checkPasswordValidation(const std::string password);

	/**
	 * @brief check if password is for the username for login.
	 *
	 * @param password for password provided by user.
	 * @param user for user for login.
	 */
	void checkPasswordExistence(const std::string password,
			const std::vector<use::user>::iterator user);

	/**
	 * @brief check if user's name provided by the user is in valid way.
	 *
	 * @param username for new user's name provided by user.
	 */
	void checkUsernameValidation(const std::string username);

	/**
	 * @brief check if user'name is already exist.
	 *
	 * @param username for username provided by user.
	 *
	 * @return iterator to user if found else throw an error.
	 */
	std::vector<use::user>::iterator checkUsernameExistence(
			const std::string username);

	/**
	 * @brief check if question's id is already exist.
	 *
	 * @param question_id for id provided by user.
	 *
	 * @return iterator to question if found else throw an error.
	 */
	std::vector<que::question>::iterator checkQuestionIdExistence(
			const std::string question_id);

	/**
	 * @brief login ask user the credential and check the validity.
	 *
	 * @return iterator to user if valid else iterator to end of user's vector.
	 */
	std::vector<use::user>::iterator logIn();

	/**
	 * @brief sign up new user in the system ask the user for new user's name, password and email.
	 */
	void signUp();

	/**
	 * @brief show first menu that shows choices for user.
	 */
	void showFirstMenu() noexcept;

	/**
	 * @brief show second menu if user is logged in and showing some choices.
	 */
	void showSecondMenu() noexcept;

	/**
	 * @brief show the questions forwarded to the user.
	 *
	 * @param user for logged user in the system.
	 */
	void printQuestionsToUser(
			const std::vector<use::user>::iterator user) const noexcept;

	/**
	 * @brief show the questions forwarded from user to others.
	 *
	 * @param user for logged user in the system.
	 */
	void printQuestionsFromUser(
			const std::vector<use::user>::iterator user) const noexcept;

	/**
	 * @brief user ask a new question providing it's content and type( parent or thread ).
	 *
	 * @param logged_user for logged user in the system.
	 */
	void userAskQuestion(std::vector<use::user>::iterator logged_user);

	/**
	 * @brief user delete a question he asked before.
	 *
	 * @param logged_user for logged user in the system.
	 */
	void userDeleteQuestion(std::vector<use::user>::iterator logged_user);

	/**
	 * @brief user answer a question which is forwarded to him.
	 *
	 * @param logged_user for logged user in the system.
	 */
	void userAnswerQuestion(std::vector<use::user>::iterator logged_user);

	/**
	 * @brief show a list of users signed up in the system.
	 */
	void listSystemUsers() const noexcept;

	/**
	 * @brief show the feeds of the system with details for questions asked from and to users and questions id.
	 */
	void feeds() const;

	/**
	 * @brief extract data from lines read from data files.
	 *
	 * @param line for line got from data file.
	 * @param delimiter as indicator for separating data types.
	 *
	 * @return data which is separated in vector of strings.
	 */
	std::vector<std::string> extractData(const std::string &line,
			const std::string delimiter = "<>") noexcept;

	/**
	 * @brief read user data file and extract data from it's lines.
	 *
	 * @param filename for data file name.
	 */
	void readUserFile(const std::string &filename);

	/**
	 * @brief read question data file and extract data from it's lines.
	 *
	 * @param filename for data file name.
	 */
	void readQuestionFile(const std::string &filename);

	/**
	 * @brief update file with new data in the system.
	 *
	 * @param filename data file name which will be updated.
	 * @param lines for new lines to the file.
	 * @param append for appending or overwriting.
	 */
	void updateFile(const std::string &filename,
			const std::vector<std::string> &lines, bool append);

	/**
	 * @brief rewriting question file for new data added or changed.
	 *
	 * @param filename for data file name.
	 */
	void rewriteQuestionFile(const std::string &filename);

	/**
	 * @brief rewriting user file for new data added or changed.
	 *
	 * @param filename for data file name.
	 */
	void rewriteUserFile(const std::string &filename);

	/**
	 * @brief reading files and rewriting them for system to be ready.
	 */
	void getDataReady();

	/**
	 * @brief to creating instance object for ask system manager.
	 */
	static AskSystemManager* createInstanceSys();

	/**
	 * @brief choices for user that he/she will interface with such as login , sign up and etc.
	 */
	void userInterface();

	/**
	 * @brief free the pointer to the ask system manager before shutdown the system.
	 */
	static void freeInstance();

public:

	/**
	 * @brief run the program.
	 */
	void static runTheProgram();

};
}

#endif /* HEADERS_ASK_SYS_H_ */
