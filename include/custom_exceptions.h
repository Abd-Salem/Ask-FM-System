/*
 * @file custom_exceptions.h
 * @brief header file for creating some custom errors fit with the system with names and messages.
 *
 * @Author: Abdallah_Salem
 */

#ifndef HEADERS_CUSTOM_EXCEPTIONS_H_
#define HEADERS_CUSTOM_EXCEPTIONS_H_
#include<stdexcept>

namespace err {
/**
 * @brief login error for errors that may occur while logging in.
 *
 */
class LoginException: public std::runtime_error {
public:
	using std::runtime_error::runtime_error;
};

/**
 * @brief Empty field exception for empty fields may provided by user.
 *
 */
class EmptyFieldException: public LoginException {
public:
	EmptyFieldException(const std::string message) :
			LoginException(message) {
	}
};

/**
 * @brief invalid username exception for invalid user's names.
 */
class InvalidUsernamException: public LoginException {
public:
	InvalidUsernamException(const std::string message) :
			LoginException(message) {
	}
};

/**
 * @brief invalid password exception for invalid passwords.
 *
 */
class InvalidPasswordException: public LoginException {
public:
	InvalidPasswordException(const std::string message) :
			LoginException(message) {
	}
};

/**
 * @brief invalid email exception for invalid email.
 *
 */

class InvalidEmailException: public LoginException {
public:
	InvalidEmailException(const std::string message) :
			LoginException(message) {
	}
};

/**
 * @brief invalid question id for invalid question's id.
 *
 */
class InvalidQuestionId: public LoginException {
public:
	InvalidQuestionId(const std::string message) :
			LoginException(message) {
	}
};

/**
 * @brief invalid user id for invalid user's id.
 *
 */

class InvalidUserId: public LoginException {
public:
	InvalidUserId(const std::string message) :
			LoginException(message) {
	}
};

/**
 * @brief data file corruption exception for corrupted data.
 *
 */
class DataFileCorruptionException: public LoginException {
public:
	DataFileCorruptionException(const std::string message) :
			LoginException(message) {
	}
};

}

#endif /* HEADERS_CUSTOM_EXCEPTIONS_H_ */
