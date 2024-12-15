#ifndef LOX_H
#define LOX_H

#include <string>
class Lox {
public:
  inline static bool hadError = false;
  static void main(int argc, char* argv[]);
  static void error(int line, std::string message);
  static void report(int line, std::string where, std::string mesage);

private:
  static void runFile(std::string path);
  static void runPrompt();
  static void run(std::string content);
};

#endif
