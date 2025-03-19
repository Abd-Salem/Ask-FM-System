/**
 * @file question.cpp
 * @brief source file for definition of question class implementing it's member functions ( setters , getters and etc).
 *
 * @Author: Abdallah_Salem
 */

#include "../include/question.h"
#include "../include/user.h"
using namespace que;

int question::next_id = { };  //initialize first id.

question::question(std::string text, std::vector<use::user>::iterator author,
		std::vector<use::user>::iterator asked) noexcept :
		question_text(text), author_it(author), asked_it(asked), question_id(
				++next_id) {
	question_answer = "Not answered"; //setting a default value for question's answer.
}

int question::getQuestionId() const noexcept {
	return question_id;
}

const std::string& question::getQuestionText() const noexcept {
	return question_text;
}

const std::string& question::getQuestionAnswer() const noexcept {
	return question_answer;
}

std::vector<use::user>::iterator question::getSenderUser() const noexcept {
	return author_it;
}

std::vector<use::user>::iterator question::getReceiverUser() const noexcept {
	return asked_it;
}

void question::setAnswer(const std::string &answer) noexcept {
	question_answer = answer;
}

