/**
 * @file question.h
 * @brief file for declaring a question class for ask system.
 * this class is used for set questions asked from and to users in the system and store its content as members inside this class.
 *
 * @Author: Abdallah_Salem
 */

#ifndef HEADERS_QUESTION_H_
#define HEADERS_QUESTION_H_
#include<iostream>
#include<vector>

namespace use {  //forward declaration.
class user;
}

namespace que {    //name space for question class.

/**
 *@brief Represents a question with text , answer, author user ,receiver user, and id.
 *
 */
class question {
private:
	std::string question_text;    		      //member data for question's text.
	std::string question_answer;	        //member data for question's answer.
	std::vector<use::user>::iterator author_it; //member data (user's name) for user who asks the question.
	std::vector<use::user>::iterator asked_it; //member data (user's name)s for user who is asked.
	int question_id;                        //member data for question's id.
	static int next_id;	//static member data that used to set ids for objects' creation.

public:
	/**
	 * @brief Constructor for question object.
	 *
	 * @param text for question content.
	 * @param author for author user.
	 * @param asked for asked user.
	 */
	question(std::string text, std::vector<use::user>::iterator author,
			std::vector<use::user>::iterator asked) noexcept;

	/**
	 * @brief get question content.
	 *
	 * @return question content.
	 */
	const std::string& getQuestionText() const noexcept;

	/**
	 * @brief get question's id.
	 *
	 * @return id.
	 */
	int getQuestionId() const noexcept;

	/**
	 * @brief get question's answer.
	 *
	 * @return question's answer.
	 *
	 */
	const std::string& getQuestionAnswer() const noexcept;

	/**
	 * @brief get author user's name.
	 *
	 * @return author user's name.
	 */
	std::vector<use::user>::iterator getSenderUser() const noexcept;

	/**
	 * @brief get asked user's name.
	 *
	 * @return asked user's name.
	 */
	std::vector<use::user>::iterator getReceiverUser() const noexcept;

	/**
	 * @brief set answer to the question.
	 *
	 * @param answer content.
	 */
	void setAnswer(const std::string &answer) noexcept;
};

}

#endif /* HEADERS_QUESTION_H_ */
