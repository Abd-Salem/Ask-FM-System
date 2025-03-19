/*
 * @file user.cpp
 * @brief source file for definition user class and implement it's member functions.
 *
 * @Author: Abdallah_Salem
 */

#include "../include/user.h"
#include "../include/question.h"

using namespace use;

int user::next_id = { };   //initialize first id.

user::user(std::string username, std::string password,
		std::string email) noexcept :
		user_name(username), user_password(password), email(email), user_id(
				++next_id) {
}

const std::string& user::getUsername() const noexcept {
	return user_name;
}

int user::getUserId() const noexcept {
	return user_id;
}

const std::string& user::getPassword() const noexcept {
	return user_password;
}

const std::string& user::getEmail() const noexcept {
	return email;
}

//End of file

