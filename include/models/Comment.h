#ifndef COMMENT_H
#define COMMENT_H

#include <string>

class Comment {
private:
  std::string author;
  std::string text;
  std::string timeStamp;

public:
  Comment();
  Comment(const std::string &author, const std::string &text,
          const std::string &timeStamp);

  ~Comment() = default;

  const std::string &getAuthor() const;
  const std::string &getText() const;
  const std::string &getTimeStamp() const;

  void setAuthor(const std::string &author);
  void setText(const std::string &text);
  void setTimeStamp(const std::string &timeStamp);
  void generateTimeStamp();
};

#endif // Comment.h
