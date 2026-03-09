#include "../../include/models/Comment.h"
#include <chrono>
#include <ctime>

Comment::Comment() : author(""), text(""), timeStamp("") {}
Comment::Comment(const std::string &author, const std::string &text,
                 const std::string &timestamp)
    : author(author), text(text), timeStamp(timestamp) {}

/*
 * Helper method to get comment author
 */
const std::string &Comment::getAuthor() const { return author; }

/*
 * Helper method to get comment text
 */
const std::string &Comment::getText() const { return text; }

/*
 * Helper method to get comment timestamp
 */
const std::string &Comment::getTimeStamp() const { return timeStamp; }

/*
 * Sets comment author
 */
void Comment::setAuthor(const std::string &author) { this->author = author; }

/*
 * Sets comment text
 */
void Comment::setText(const std::string &text) { this->text = text; }

/*
 * Sets comment psting timestamp
 */
void Comment::setTimeStamp(const std::string &timestamp) {
  this->timeStamp = timestamp;
}

/*
 * Helper method to generate timestamp for comment
 */
void Comment::generateTimeStamp() {
  auto now = std::chrono::system_clock::now();
  auto time_t = std::chrono::system_clock::to_time_t(now);
  std::string timeStr = std::ctime(&time_t);

  // remove newline from timestring
  if (!timeStr.empty() && timeStr.back() == '\n') {
    timeStr.pop_back();
  }

  this->timeStamp = timeStr;
}
