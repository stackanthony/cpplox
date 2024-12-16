#include "lox.h"
#include "Scanner.h"
#include "Token.h"
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Lox::main(int argc, char* argv[]) {
  if (argc > 2) {
    std::cout << "Usage: cpplox [script]" << std::endl;
    exit(64);
  } else if (argc == 2) {
    Lox::runFile(argv[0]);
  } else {
    Lox::runPrompt();
  }
}

void Lox::runFile(std::string path) {
  try {
    std::ifstream file(path, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string stringFileContents = buffer.str();

    Lox::run(stringFileContents);

    if (Lox::hadError) {
      exit(65);
    }

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void Lox::runPrompt() {
  std::string line;

  while (true) {
    std::cout << "> ";
    if (!std::getline(std::cin, line)) { // Check for EOF (Ctrl+D)
      break;
    }
    run(line);
    Lox::hadError = false;
  }
}

// INFO: This should print our tokens once we have that step done
void Lox::run(std::string content) {
  // std::vector<Token> tokens =
  Scanner scanner{content};
  std::vector<Token> tokens = scanner.scanTokens();

  for (Token& token : tokens) {
    std::cout << token.toString() << std::endl;
  }
}

void Lox::report(int line, std::string where, std::string message) {
  std::cout << "[line " << line << "] Error" << where << ": " << message
            << std::endl;
  Lox::hadError = true;
}

void Lox::error(int line, std::string message) {
  Lox::report(line, "", message);
}
