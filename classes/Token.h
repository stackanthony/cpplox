#ifndef TOKEN_H
#define TOKEN_H
#include "TokenType.h"
#include <cstddef>
#include <string>
#include <unordered_map>
#include <variant>

class Token {
private:
  const TokenType type;
  const std::string lexeme;
  const std::variant<std::nullptr_t, std::string, double> literal;
  const int line;

public:
  Token(TokenType type, std::string lexeme,
        std::variant<std::nullptr_t, std::string, double> literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line) {}

  inline static const std::unordered_map<std::string, TokenType> reserved_map =
      {{"and", AND},     {"class", CLASS}, {"else", ELSE},
       {"false", FALSE}, {"fun", FUN},     {"for", FOR},
       {"if", IF},       {"nil", NIL},     {"or", OR}};
  std::string toString() {
    std::string literalStr;
    if (std::holds_alternative<std::string>(literal)) {
      literalStr = std::get<std::string>(literal);
    } else if (std::holds_alternative<double>(literal)) {
      literalStr = std::to_string(std::get<double>(literal));
    }
    return "type: " + std::to_string(static_cast<int>(type)) +
           " lexeme: " + lexeme + " literal: " + literalStr;
  }

  std::variant<std::nullptr_t, std::string, double> getLiteral() {
    return literal;
  }
};
#endif
