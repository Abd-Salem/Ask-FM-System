/*
 * @file user.h
 * @brief header file for declaring user class.
 * this class is used to set user'name , password , email, id and store them for login process and others.
 *
 * @Author: Abdallah_Salem
 */

#ifndef HEADERS_USER_H_
#define HEADERS_USER_H_
#include<iostream>
#include<list>
#include<algorithm>

namespace que {  //forward declaration.
class question;
}

namespace use {   //name space for user class.

/**
 *@brief Represents a user with name , password, email and id.
 */
class user {
private:
	std::string user_name;		//member data for user's name.
	std::string user_password;	//member data for user's password.
	std::string email;			//member data for user's email.
	int user_id;        		//member data for user's id.
	static int next_id;			//static member data for user's new id
public:

	/**
	 * @brief Constructor for user object.
	 *
	 * @param username for user's name.
	 * @param password for user's password.
	 * @param email for user's email.
	 */
	user(std::string username, std::string password, std::string email) noexcept;

	/**
	 * @brief get user's name.
	 *
	 * @return user's name.
	 */
	const std::string& getUsername() const noexcept;

	/**
	 * @brief get user's id.
	 *
	 * @return user's id.
	 */
	int getUserId() const noexcept;

	/**
	 * @brief get user's password.
	 *
	 * @return user's password.
	 */
	const std::string& getPassword() const noexcept;

	/**
	 * @brief get user's email.
	 *
	 * @return user's email.
	 */
	const std::string& getEmail() const noexcept;
};

}

#endif /* HEADERS_USER_H_ */
