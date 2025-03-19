/*
 * @file aks_sys.cpp
 * @brief source file for definition of ask system class and it's member functions.
 *
 * @Author: Abdallah_Salem
 */

#include "../include/ask_manager.h"

using namespace ask;

AskSystemManager *AskSystemManager::conf_sys = { nullptr }; //make it null as default.

AskSystemManager::AskSystemManager() noexcept {
}

void AskSystemManager::addNewUser(std::string username, std::string password,
		std::string email) noexcept {
	users.push_back(use::user(username, password, email));
}

void AskSystemManager::checkEmptyField(const std::string input) {
	if (input.empty())
		throw err::EmptyFieldException(
				"\nEmpty Field, try again or Enter e/E to Exit.\n\n"); //error message.
}

void AskSystemManager::checkEmailValidation(const std::string email) {
	AskSystemManager::checkEmptyField(email);
	unsigned int pos = email.find('@');    //get position in the string.
	std::string sub = "";
	if (pos == std::string::npos || (pos < 6) || (pos > 30))
		throw err::InvalidEmailException(
				"\nInvalid Email, try again or Enter e/E to Exit\n\n");
	while (pos != (unsigned int) email.length()) {
		sub += email[pos];
		++pos;
	}
	if (sub != "@gmail.com" && sub != "@hotmail.com" && sub != "@outlook.com"
			&& sub != "@yahoo.com") //check that the substring after @ is valid.
		throw err::InvalidEmailException(
				"\nInvalid Email, try again or Enter e/E to Exit\n\n");
}

void AskSystemManager::checkPasswordValidation(const std::string password) {
	AskSystemManager::checkEmptyField(password);
	if (password.length() < 8 || password.length() > 30)
		throw err::InvalidPasswordException(
				"\nInvalid Password, It must be between 8 to 30 length, try again or Enter e/E to Exit\n\n"); //make sure that the string length between 8 and 30.
}

void AskSystemManager::checkPasswordExistence(const std::string password,
		const std::vector<use::user>::iterator user) {
	AskSystemManager::checkEmptyField(password);
	if (user->getPassword() != password)
		throw err::InvalidPasswordException(
				"\nIncorrect Password, try again or press e/E to Exit\n\n");
}

void AskSystemManager::checkUsernameValidation(const std::string username) {
	try {
		AskSystemManager::checkUsernameExistence(username); //avoid doubles.
	} catch (const err::InvalidUsernamException &e) {
		if (username.length() < 5 || username.length() > 25
				|| !std::all_of(username.begin(), username.end(), [](char c) {
					return (std::isalnum(c) || c == '_');
				})) {
			throw err::InvalidUsernamException(
					"\nInvalid user'name, Try again "
							"and make sure that it is from 5 to 25 "
							"length (only allowed letters, numbers and underscore('_')), try again or Enter e/E to Exit\n\n");
		}
		return;
	}
	//this means that the new user's name is already exist
	throw err::InvalidUsernamException(
			"\nThis user'name is already exist, Try again or try again or Enter e/E to Exit\n\n");
}

std::vector<use::user>::iterator AskSystemManager::checkUsernameExistence(
		const std::string username) {
	AskSystemManager::checkEmptyField(username);
	//find_if function to search for a hit or miss for user's name.
	auto user_it = std::find_if(users.begin(), users.end(),
			[username](const use::user &u) {
				return u.getUsername() == username;
			});
	if (user_it != users.end())
		return user_it;   //match
	throw err::InvalidUsernamException(
			"\nInvalid user's name, try again or Enter e/E to Exit\n\n"); //miss
}

std::vector<que::question>::iterator AskSystemManager::checkQuestionIdExistence(
		const std::string question_id) {
	AskSystemManager::checkEmptyField(question_id);
	int id { };
	try {
		id = std::stoi(question_id);
	} catch (...) {
		throw err::InvalidQuestionId(
				"Invalid question's id, try again or  Enter e/E to Exit/n"); //miss
	}
	auto question_it = std::find_if(parents.begin(), parents.end(),
			[id](const que::question &parent) {
				return id == parent.getQuestionId();
			});
	if (question_it != parents.end())
		return question_it;     //got a hit

	question_it = std::find_if(threads.begin(), threads.end(),
			[id](const que::question &thread) {
				return id == thread.getQuestionId();
			});
	if (question_it != threads.end())
		return question_it;         //got a hit

	throw err::InvalidQuestionId(
			"Invalid question's id, try again or  Enter e/E to Exit/n");  //miss
}

std::vector<use::user>::iterator AskSystemManager::logIn() {
	std::string user_input;
	auto user_it = users.end();
	bool error { };
	//check user' name
	do {
		error = { false };
		std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		std::cout << "Enter user's name: ";
		std::cin >> user_input;
		if (user_input == "e" || user_input == "E")        //call it off
			return users.end();
		try {                                        //check for errors
			user_it = AskSystemManager::checkUsernameExistence(user_input);
		} catch (const err::InvalidUsernamException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		} catch (const err::EmptyFieldException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		}
	} while (error);
	//check password
	do {
		error = { false };
		std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		std::cout << "Enter your password: ";     //ask for password
		std::cin >> user_input;
		if (user_input == "e" || user_input == "E")    //call it off
			return users.end();
		try {                                  //check for errors
			AskSystemManager::checkPasswordExistence(user_input, user_it);
		} catch (const err::EmptyFieldException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		} catch (const err::InvalidPasswordException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		}
	} while (error);
	return user_it;     //valid logging in
}

void AskSystemManager::signUp() {
	std::string username, password, email;
	bool error { };    //check new user's name
	do {
		error = { false };
		std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		std::cout << "Enter user's name: ";
		std::cin >> username;
		if (username == "e" || username == "E")        //Call it off
			return;
		try {
			AskSystemManager::checkUsernameValidation(username);
		} catch (const err::EmptyFieldException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		} catch (const err::InvalidUsernamException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		}
	} while (error);
	do {
		error = { false };
		std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		std::cout << "Enter your password: ";
		std::cin >> password;
		if (password == "e" || password == "E")
			return;              //call it off
		try {
			AskSystemManager::checkPasswordValidation(password);
		} catch (const err::EmptyFieldException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		} catch (const err::InvalidPasswordException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		}
	} while (error);
	do {
		error = { false };
		std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		std::cout << "Enter your E-mail: ";
		std::cin >> email;
		if (email == "e" || email == "E")
			return;              //call it off
		try {
			AskSystemManager::checkEmailValidation(email);
		} catch (const err::EmptyFieldException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		} catch (const err::InvalidEmailException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		}
	} while (error);

	AskSystemManager::addNewUser(username, password, email);  //create new user.
	std::vector < std::string
			> data { (username + "<>" + password + "<>" + email) };
	AskSystemManager::updateFile(user_file, data, true); //signed up successfully
}

void AskSystemManager::showFirstMenu() noexcept {
	std::cout << "1- Log In.\n";
	std::cout << "2- Sign Up.\n";
	std::cout << "3- Exit.\n";
}

void AskSystemManager::showSecondMenu() noexcept {
	std::cout << "1- Print Questions to me.\n";
	std::cout << "2- Print Questions from me.\n";
	std::cout << "3- Answer Question.\n";
	std::cout << "4- Delete Question.\n";
	std::cout << "5- Ask Question.\n";
	std::cout << "6- list System Users.\n";
	std::cout << "7- Feed.\n";
	std::cout << "8- Log Out.\n";
}

void AskSystemManager::printQuestionsToUser(
		const std::vector<use::user>::iterator user) const noexcept {
	std::cout
			<< "\n----------------------------------------------------------"
					"--------------------------------------------------------------"
					"----------------------------------------------------------------------\n\n";
	//print parent questions.
	for (const auto &parent : parents) {
		if (parent.getReceiverUser() == user) {
			auto author_user = parent.getSenderUser();
			std::cout
					<< "\t=> Question(" + std::to_string(parent.getQuestionId())
							+ ") to (" + author_user->getUsername() + ")\t\t"
					<< "Question: " + parent.getQuestionText()
							+ "\n\t\t\t- Answer: " + parent.getQuestionAnswer()
					<< std::endl;
		}
	}
	for (const auto &thread : threads) {
		if (thread.getReceiverUser() == user) {
			auto author_user = thread.getSenderUser();
			std::cout
					<< "\t=> Question(" + std::to_string(thread.getQuestionId())
							+ ") to (" + author_user->getUsername() + ")\t\t"
					<< "Question: " + thread.getQuestionText()
							+ "\n\t\t\t- Answer: " + thread.getQuestionAnswer()
					<< std::endl;
		}
	}

	std::cout
			<< "\n----------------------------------------------------------"
					"--------------------------------------------------------------"
					"----------------------------------------------------------------------\n\n";

}
void AskSystemManager::printQuestionsFromUser(
		const std::vector<use::user>::iterator user) const noexcept {
	std::cout
			<< "\n----------------------------------------------------------"
					"--------------------------------------------------------------"
					"----------------------------------------------------------------------\n\n";
	for (const auto &parent : parents) {
		if (parent.getSenderUser() == user) {
			auto asked_user = parent.getReceiverUser();
			std::cout
					<< "\t=> Question(" + std::to_string(parent.getQuestionId())
							+ ") to (" + asked_user->getUsername() + ")\t\t"
					<< "Question: " + parent.getQuestionText()
							+ "\n\t\t\t- Answer: " + parent.getQuestionAnswer()
					<< std::endl;
		}
	}
	for (const auto &thread : threads) {
		if (thread.getSenderUser() == user) {
			auto asked_user = thread.getReceiverUser();
			std::cout
					<< "\t=> Question(" + std::to_string(thread.getQuestionId())
							+ ") to (" + asked_user->getUsername() + ")\t\t"
					<< "Question: " + thread.getQuestionText()
							+ "\n\t\t\t- Answer: " + thread.getQuestionAnswer()
					<< std::endl;
		}
	}
	std::cout
			<< "\n----------------------------------------------------------"
					"--------------------------------------------------------------"
					"----------------------------------------------------------------------\n\n";

}

void AskSystemManager::userAskQuestion(
		std::vector<use::user>::iterator logged_user) {
	std::string question_text, user_input, question_type;
	auto asked_user = users.end();
	bool error { };
	std::cout << "New question or Thread question to old one?\n";
	std::cout << "New question    --> 1\nThread question --> 2\n";
	std::cin >> question_type;
	if (question_type != "1" && question_type != "2") {
		std::cerr << "\nFalse Input !!\n";
		return;     //call it off
	}
	//for new parent question.
	if (question_type == "1") {
		do {
			error = { false }; //out of loop if there is no error occurs while user enter data.
			std::cin.ignore(std::numeric_limits < std::streamsize > ::max(),
					'\n');
			std::cout << "Enter user'name you want to ask: ";
			std::cin >> user_input;
			if (user_input == "e" || user_input == "E")      //call it off
				return;
			try {
				asked_user = AskSystemManager::checkUsernameExistence(
						user_input);
				if (asked_user == logged_user)
					throw err::InvalidUsernamException(
							"Invalid User's name. press e/E to Exit\n"); //make sure that the user doen't ask himself.
			} catch (const err::EmptyFieldException &e) {
				std::cerr << e.what() << std::endl;
				error = { true };
			} catch (const err::InvalidUsernamException &e) {
				std::cerr << e.what() << std::endl;
				error = { true };
			}
		} while (error);
		do {
			error = { false };
			std::cin.ignore(std::numeric_limits < std::streamsize > ::max(),
					'\n');
			std::cout << "Enter your question: ";
			getline(std::cin, question_text);
			if (question_text == "e" || question_text == "E")
				return;
			try {
				AskSystemManager::checkEmptyField(question_text);
			} catch (const err::EmptyFieldException &e) { //make sure that the user didn't enter empty field.
				std::cerr << e.what() << std::endl;
				error = { true };
			}
		} while (error);
		parents.push_back(
				que::question(question_text, logged_user, asked_user));
		int parent_id = std::prev(parents.end())->getQuestionId();
		parent_thread[parent_id];
		std::vector < std::string
				> data { "Parent<>" + logged_user->getUsername() + "<>"
						+ asked_user->getUsername() + "<>" + question_text
						+ "<>Not answered" };
		//add new line in question file.
		AskSystemManager::updateFile(question_file, data, true);
		//For thread question.
	} else if (question_type == "2") {
		auto parent_it = parents.end();
		do {
			error = { false };
			std::cin.ignore(std::numeric_limits < std::streamsize > ::max(),
					'\n');
			std::cout << "Enter parent question's ID: ";
			std::cin >> user_input;
			if (user_input == "e" || user_input == "E")
				return;
			try {
				AskSystemManager::checkEmptyField(user_input);
				parent_it = std::find_if(parents.begin(),
						parents.end(),     //search between parents.
						[user_input](const que::question &parent) {
							return parent.getQuestionId()
									== std::stoi(user_input);
						});
				if (parent_it == parents.end()
						|| parent_it->getReceiverUser() == logged_user) //If not found or author user is the asked user.
					throw err::InvalidQuestionId(
							"Invalid question's id, try again or  Enter e/E to Exit\n");

			} catch (const err::EmptyFieldException &e) {
				std::cerr << e.what() << std::endl;
				error = { true };
			} catch (const err::InvalidQuestionId &e) {
				std::cerr << e.what() << std::endl;
				error = { true };
			} catch (...) {
				std::cerr << "Unknown Error, try again or Enter e/E to Exit\n";
				error = { true };
			}
		} while (error);
		do {
			error = { false };
			std::cin.ignore(std::numeric_limits < std::streamsize > ::max(),
					'\n');
			std::cout << "Enter your question: ";
			getline(std::cin, question_text);
			if (question_text == "e" || question_text == "E")
				return;
			try {
				AskSystemManager::checkEmptyField(question_text);
			} catch (const err::EmptyFieldException &e) { //make sure that the user didn't enter empty field.
				std::cerr << e.what() << std::endl;
				error = { true };
			}
		} while (error);
		auto asked_user = parent_it->getReceiverUser(); //get asked user iterator.
		threads.push_back(
				que::question(question_text, logged_user, asked_user)); //create new thread and add to list.
		int thread_id = std::prev(threads.end())->getQuestionId(); //get thread question id.
		int parent_id = parent_it->getQuestionId(); //get parent question id.
		parent_thread[parent_id].push_back(thread_id); //add thread to list of threads with parent
		//rewrite question file for new update.
		AskSystemManager::rewriteQuestionFile (question_file);
	}
}

void AskSystemManager::userDeleteQuestion(
		std::vector<use::user>::iterator logged_user) {
	std::string user_input;
	auto question = parents.end();
	bool error { };
	do {
		error = { false };
		AskSystemManager::printQuestionsFromUser(logged_user);
		//ask for question id
		std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		std::cout << "Enter question's id you want to delete: ";
		std::cin >> user_input;
		if (user_input == "e" || user_input == "E")
			return;
		try {
			question = AskSystemManager::checkQuestionIdExistence(user_input);
			if (question->getSenderUser() != logged_user)
				throw err::InvalidQuestionId(
						"Invalid ID, try again or press e/E to Exit.\n");
		} catch (const err::EmptyFieldException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		} catch (const err::InvalidQuestionId &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		}
	} while (error);
	int question_id = question->getQuestionId(); //get question id for some comparisons.
	auto map_it = parent_thread.find(question_id);
	if (map_it != parent_thread.end()) {
		for (auto thread_id : map_it->second) {
			auto id = std::remove_if(threads.begin(), threads.end(),
					[thread_id](const que::question &thread) {
						return thread.getQuestionId() == thread_id;
					});
			threads.erase(id);
		}
		parent_thread.erase(question_id); //remove parent and threads from map list.
		parents.erase(question);			//remove parent from parent list.
	} else {
		auto id = std::remove_if(threads.begin(), threads.end(),
				[question_id](const que::question &thread) {
					return thread.getQuestionId() == question_id;
				});
		threads.erase(id);
		for (auto it = parent_thread.begin(); it != parent_thread.end(); ++it) {
			auto id = std::remove_if(it->second.begin(), it->second.end(),
					[question_id](int id) {
						return id == question_id;
					});
			it->second.erase(id);
		}
	}
	AskSystemManager::rewriteQuestionFile (question_file); //update question file.
	std::cout << "\n\nQuestion is deleted successfully.\n\n"; //Confirmation message.
}

void AskSystemManager::userAnswerQuestion(
		std::vector<use::user>::iterator logged_user) {
	std::string user_input;
	auto question = parents.end();
	bool error { true };
	AskSystemManager::printQuestionsToUser(logged_user); //show questions forwarded to user.
	do {
		error = { false };
		std::cout << "Enter question's id you want to answer: ";
		std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		std::cin >> user_input;
		if (user_input == "e" || user_input == "E")
			return;
		try {
			question = AskSystemManager::checkQuestionIdExistence(user_input); //check validity of question's id
			if (question->getReceiverUser() != logged_user)
				throw err::InvalidQuestionId(
						"Invalid ID, try again or press e/E to Exit.\n");
		} catch (const err::EmptyFieldException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		} catch (const err::InvalidQuestionId &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		}
	} while (error);
	do {
		error = { false };
		std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		std::cout << "Fine, Enter your answer: ";
		getline(std::cin, user_input);
		try {
			AskSystemManager::checkEmptyField(user_input);
		} catch (const err::EmptyFieldException &e) {
			std::cerr << e.what() << std::endl;
			error = { true };
		}
	} while (error);
	question->setAnswer(user_input);
	AskSystemManager::rewriteQuestionFile (question_file); //update question file.

	std::cout << "\n\nAnswer is added.\n\n";
}

void AskSystemManager::listSystemUsers() const noexcept {
	std::cout << "\nUsers Signed Up In This System: \n"
			<< "-----------------------------------\n\n";
	for (const auto &user : users) {
		std::cout
				<< "User's Name: " + user.getUsername() + "\tUser's ID: "
						+ std::to_string(user.getUserId()) + "\nEmail: "
						+ user.getEmail()
						+ "\n-----------------------------------------\n"
				<< std::endl;
	}
}

void AskSystemManager::feeds() const {
	std::cout
			<< "\n\n----------------------------------------------------------"
					"--------------------------------------------------------------"
					"----------------------------------------------------------------------\nFeeds:\n\n";

	for (const auto& [parent_id, threads_id] : parent_thread) {

		auto parent = std::find_if(parents.begin(), parents.end(),
				[parent_id](const que::question &parent) {
					return parent.getQuestionId() == parent_id;
				});
		if (parent == parents.end())
			throw err::InvalidQuestionId("Data is corrupted\n");
		auto author_user = parent->getSenderUser(); //get author user info.
		auto asked_user = parent->getReceiverUser(); //get asked user info.
		std::cout
				<< "\t=> Question(" + std::to_string(parent->getQuestionId())
						+ ") from (" + author_user->getUsername() + ") to ("
						+ asked_user->getUsername() + ")\t\t" + "Question: "
						+ parent->getQuestionText() + "\n\t\t\t- Answer: "
						+ parent->getQuestionAnswer() << std::endl;
		for (const auto &thread_id : threads_id) { //print threads if exist
			auto thread = std::find_if(threads.begin(), threads.end(),
					[thread_id](const que::question &thread) {
						return thread.getQuestionId() == thread_id;
					});
			if (thread == threads.end())
				break;
			author_user = thread->getSenderUser();
			std::cout
					<< "\t\t=> Thread Question("
							+ std::to_string(thread->getQuestionId())
							+ ") from (" + author_user->getUsername() + ") to ("
							+ asked_user->getUsername() + ")\t\t" + "Question: "
							+ thread->getQuestionText() + "\n\t\t\t- Answer: "
							+ thread->getQuestionAnswer() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout
			<< "\n----------------------------------------------------------"
					"--------------------------------------------------------------"
					"----------------------------------------------------------------------\n\n";
}

std::vector<std::string> AskSystemManager::extractData(const std::string &line,
		const std::string delimiter) noexcept {
	std::string data_line = line;
	std::string info;
	std::vector < std::string > data;
	int pos { };
	while ((pos = (int) data_line.find(delimiter)) != (int) std::string::npos) {
		info = data_line.substr(0, pos);
		data.push_back(info);
		data_line.erase(0, pos + delimiter.length());
	}
	info = data_line;
	data.push_back(info);
	return data;
}

void AskSystemManager::readUserFile(const std::string &filename) {
	std::ifstream user_file(filename);
	if (!user_file.is_open())
		throw err::DataFileCorruptionException(   //terminate the program.
				"\n\nCan't Open Data File, Fix the error and run the program again line 659.\n");

	std::string line, email, password, username;
	std::vector < std::string > data;
	if (user_file.peek() == std::ifstream::traits_type::eof()) //check if file is empty.
		return;

	bool error { };

	while (getline(user_file, line)) {
		error = { false };
		if (line.empty())   //skip line if empty.
			continue;
		data = AskSystemManager::extractData(line); //extract data from the line.
		if (data.size() != 3)  //make sure that the line is valid.
			continue;
		email = data.back();   //get user's name
		data.pop_back();
		password = data.back();   //get password
		data.pop_back();
		username = data.back();     //get email
		data.pop_back();
		//check for any corruption.
		try {
			//make sure that data is valid (user's name, password, email).
			AskSystemManager::checkUsernameValidation(username);
			AskSystemManager::checkPasswordValidation(password);
			AskSystemManager::checkEmailValidation(email);
		} catch (const err::EmptyFieldException &e) {
			error = { true };
		} catch (const err::InvalidUsernamException &e) {
			error = { true };
		} catch (const err::InvalidPasswordException &e) {
			error = { true };
		} catch (const err::InvalidEmailException &e) {
			error = { true };
		} catch (...) {
			error = { true };
		}
		if (error)
			continue;
		AskSystemManager::addNewUser(username, password, email); //create new user.
	}
	user_file.close();   //close the file.
}

void AskSystemManager::readQuestionFile(const std::string &filename) {
	std::ifstream file(filename);
	if (!file.is_open())
		throw err::DataFileCorruptionException(
				"\n\nCan't Open Data File, Fix the error and run the program again line 700.\n");

	std::string line, question_type, question_text, question_answer,
			author_user, asked_user;
	std::vector < std::string > data;
	auto author_it = users.end();
	auto asked_it = users.end();
	auto last_parent = parents.end();
	if (file.peek() == std::ifstream::traits_type::eof()) //check if file is empty.
		return;
	bool error { };

	while (std::getline(file, line)) {
		error = { false };
		if (line.empty())  //skip line if empty.
			continue;
		while (!data.empty())
			data.pop_back();
		data = AskSystemManager::extractData(line);   //get data from line.
		if (data.size() != 5)
			continue;
		//extract data according to its order.
		question_answer = data.back();
		data.pop_back();
		question_text = data.back();
		data.pop_back();
		asked_user = data.back();
		data.pop_back();
		author_user = data.back();
		data.pop_back();
		question_type = data.back();
		data.pop_back();

		//check if data is corrupted and throw error if true.
		try {
			if ((question_type != "Parent" && question_type != "Thread")
					|| (author_user == asked_user))
				throw err::DataFileCorruptionException("Invalid data.\n");
			author_it = AskSystemManager::checkUsernameExistence(author_user);
			asked_it = AskSystemManager::checkUsernameExistence(asked_user);
		} catch (const err::EmptyFieldException &e) {
			error = { true };
		} catch (const err::InvalidUsernamException &e) {
			error = { true };
		} catch (const err::DataFileCorruptionException &e) {
			error = { true };
		} catch (...) {
			error = { true };
		}
		if (error)
			continue;
		//check if question is parent or thread.
		if (question_type == "Parent") {
			//create new question and adding it to lists.
			parents.push_back(
					que::question(question_text, author_it, asked_it));
			std::prev(parents.end())->setAnswer(question_answer);
			int parent_id = std::prev(parents.end())->getQuestionId();
			last_parent = std::prev(parents.end());
			parent_thread[parent_id];
		} else if (question_type == "Thread") {
			if (last_parent == parents.end())
				continue;
			threads.push_back(
					que::question(question_text, author_it, asked_it));
			std::prev(threads.end())->setAnswer(question_answer);
			int thread_id = std::prev(threads.end())->getQuestionId();
			int parent_id = last_parent->getQuestionId();
			parent_thread[parent_id].push_back(thread_id);
		}
	}
	file.close();  //close the file.
}

void AskSystemManager::updateFile(const std::string &filename,
		const std::vector<std::string> &lines, bool append) {
	auto status = std::ios::in | std::ios::out | std::ios::app; //adding new lines as default mode.
	if (!append)
		status = std::ios::in | std::ios::out | std::ios::trunc; //overwriting the whole file.

	std::fstream file(filename, status);
	if (file.fail())
		throw err::DataFileCorruptionException(
				"File is corrupted, Fix the error and run the program again line 776\n");

	for (const auto &line : lines)  //add lines
		file << line << "\n";

	file.close();  //close the file.
}

void AskSystemManager::rewriteQuestionFile(const std::string &filename) {
	std::vector < std::string > lines;
	//loop over questions.

	for (const auto& [parent_id, threads_id] : parent_thread) {

		auto parent = std::find_if(parents.begin(), parents.end(),
				[parent_id](const que::question &parent) {
					return parent.getQuestionId() == parent_id;
				});
		if (parent == parents.end())
			throw err::InvalidQuestionId("Data is corrupted\n");
		auto author_user = parent->getSenderUser(); //get author user info.
		auto asked_user = parent->getReceiverUser(); //get asked user info.
		lines.push_back(
				"Parent<>" + author_user->getUsername() + "<>"
						+ asked_user->getUsername() + "<>"
						+ parent->getQuestionText() + "<>"
						+ parent->getQuestionAnswer());
		for (const auto &thread_id : threads_id) { //print threads if exist
			auto thread = std::find_if(threads.begin(), threads.end(),
					[thread_id](const que::question &thread) {
						return thread.getQuestionId() == thread_id;
					});
			if (thread == threads.end())
				throw err::InvalidQuestionId("Data is corrupted\n");
			author_user = thread->getSenderUser();
			lines.push_back(
					"Thread<>" + author_user->getUsername() + "<>"
							+ asked_user->getUsername() + "<>"
							+ thread->getQuestionText() + "<>"
							+ thread->getQuestionAnswer());
		}
	}
	AskSystemManager::updateFile(filename, lines, false); //overwrite question file.
}

void AskSystemManager::rewriteUserFile(const std::string &filename) {
	std::vector < std::string > lines;  //list of lines.

	for (const auto &user : users) {
		lines.push_back(
				(user.getUsername() + "<>" + user.getPassword() + "<>"
						+ user.getEmail()));
	}
	AskSystemManager::updateFile(filename, lines, false); //overwrite user file.
}

void AskSystemManager::getDataReady() {
	//reading and rewriting user file.
	AskSystemManager::readUserFile (user_file);
	AskSystemManager::rewriteUserFile(user_file);
	//reading rewriting question file.
	AskSystemManager::readQuestionFile (question_file);
	AskSystemManager::rewriteQuestionFile(question_file);
}

void AskSystemManager::userInterface() {
	std::string input;
	//read and reset data base.
	AskSystemManager::getDataReady();
	std::cout << "Welcome to Ask FM System, hope you enjoy.\n\n"; //welcome message
	auto logged_user = users.end();
	while (true) {
		while (logged_user == users.end()) {
			AskSystemManager::showFirstMenu();
			std::cin >> input;
			if (input == "1")
				logged_user = AskSystemManager::logIn();
			else if (input == "2")
				AskSystemManager::signUp();
			else if (input == "3")
				return;
		}
		while (logged_user != users.end()) {
			AskSystemManager::showSecondMenu();
			std::cin >> input;
			if (input == "1")
				AskSystemManager::printQuestionsToUser(logged_user);
			else if (input == "2")
				AskSystemManager::printQuestionsFromUser(logged_user);
			else if (input == "3")
				AskSystemManager::userAnswerQuestion(logged_user);
			else if (input == "4")
				AskSystemManager::userDeleteQuestion(logged_user);
			else if (input == "5")
				AskSystemManager::userAskQuestion(logged_user);
			else if (input == "6")
				AskSystemManager::listSystemUsers();
			else if (input == "7")
				AskSystemManager::feeds();
			else if (input == "8")
				logged_user = users.end();  //log out
		}
	}
}

AskSystemManager* AskSystemManager::createInstanceSys() {
	if (conf_sys == nullptr) {
		conf_sys = new AskSystemManager(); //create new object if there is no one.
	}
	return conf_sys;    //return address of the created object.
}

void AskSystemManager::freeInstance() {
//	if instance is created, delete it then make it's pointer null.
	if (AskSystemManager::conf_sys != nullptr) {
		delete AskSystemManager::conf_sys;
		AskSystemManager::conf_sys = { nullptr };
	}
	std::cout << "\nGood bye, see you soon.\n";
}

void AskSystemManager::runTheProgram() {
	ask::AskSystemManager *ask_manager =
			ask::AskSystemManager::createInstanceSys(); //create only one instance
	ask_manager->userInterface();      //run the program.

	ask::AskSystemManager::freeInstance();  //Shutdown the program.
}

