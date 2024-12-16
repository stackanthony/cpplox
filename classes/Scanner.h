#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"
#include "TokenType.h"
#include <string>
#include <vector>
class Scanner {
public:
  Scanner(std::string source) : source(source) {};
  std::vector<Token> scanTokens();

private:
  int start = 0;
  int current = 0;
  int line = 1;
  const std::string source;
  std::vector<Token> tokens;
  bool isAtEnd();
  void scanToken();
  char advance();

  void addToken(TokenType type);
  void
  addToken(TokenType type,
           const std::variant<std::nullptr_t, std::string, double> literal);
  bool match(char expected);
  char peek();
  void string();
  void number();
  void reserved();
};
#endif
