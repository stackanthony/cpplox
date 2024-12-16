#include "Scanner.h"
#include "TokenType.h"
#include "lox.h"
#include <cctype>
#include <iostream>
#include <ostream>
#include <string>

bool Scanner::isAtEnd() { return current >= source.length(); }
std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }
  tokens.push_back(Token(TokenType::END_OF_FILE, "EOF", nullptr, line));

  return tokens;
}

// INFO: Increments current and returns the character before the increment
char Scanner::advance() {
  current++;
  return source[current - 1];
}

void Scanner::addToken(TokenType type) { addToken(type, nullptr); }
void Scanner::addToken(
    TokenType type, std::variant<std::nullptr_t, std::string, double> literal) {
  std::string text = source.substr(start, current - start);
  tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::match(char expected) {
  if (isAtEnd()) {
    return false;
  }
  if (source[current] != expected) {
    return false;
  }

  current++;
  return true;
}

char Scanner::peek() { return source[current]; }

void Scanner::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') {
      line++;
    }
    advance();
  }

  if (isAtEnd()) {
    Lox::error(line, "Unterminated String Literal");
    return;
  }

  // Advance past the closing "
  advance();

  std::string stringLiteral =
      source.substr(start + 1, (current - 1) - (start + 1));
  addToken(STRING, stringLiteral);
}

void Scanner::number() {
  char peekChar = peek();
  int dotCount = 0;

  while (std::isdigit(peekChar) || (peekChar == '.')) {
    if (peekChar == '.') {
      dotCount++;
    }
    char prevChar = advance();
    peekChar = peek();

    if (!std::isdigit(peekChar) && prevChar == '.') {
      Lox::error(line, "No trailing decimals.");
      return;
    }
  }

  if (dotCount > 1) {
    Lox::error(line, "Invalid Double Representation. Too many dots bozo");
    return;
  }

  std::string doubleSubstr = source.substr(start, current);
  addToken(NUMBER, std::stod(doubleSubstr));
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
  case '(':
    addToken(LEFT_PAREN);
    break;
  case ')':
    addToken(RIGHT_PAREN);
    break;
  case '{':
    addToken(LEFT_BRACE);
    break;
  case '}':
    addToken(RIGHT_BRACE);
    break;
  case ',':
    addToken(COMMA);
    break;
  case '.':
    if (std::isdigit(peek())) {
      Lox::error(line, "We don't support leading decimals. womp womp :(");
      while (std::isdigit(peek())) {
        advance();
      }
      break;
    }
    addToken(DOT);
    break;
  case '-':
    addToken(MINUS);
    break;
  case '+':
    addToken(PLUS);
    break;
  case ';':
    addToken(SEMICOLON);
    break;
  case '*':
    addToken(STAR);
    break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG);
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL);
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS);
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER);
    break;
  case '/':
    if (match('/')) {
      while (peek() != '\n' && !isAtEnd()) {
        advance();
      }
      break;
    }
    addToken(SLASH);
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    line++;
    break;
  case '"':
    string();
    break;
  default:
    // If the current character is a digit, then go through the number lexical
    // analysis
    if (std::isdigit(c)) {
      number();
      break;
    }
    Lox::error(line, "Unexpected character.");
    break;
  }
}
