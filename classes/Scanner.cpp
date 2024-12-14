#include "Scanner.h"
#include "TokenType.h"
#include "lox.h"

bool Scanner::isAtEnd() { return current >= source.length(); }
std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }
  tokens.push_back(Token(TokenType::END_OF_FILE, "", nullptr, line));

  return tokens;
}

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
    addToken(RIGHT_BRACE);
    break;
  case '}':
    addToken(LEFT_BRACE);
    break;
  case ',':
    addToken(COMMA);
    break;
  case '.':
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
  default:
    Lox::error(line, "Unexpected character.");
    break;
  }
}
