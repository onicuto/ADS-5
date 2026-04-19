// Copyright 2025 NNTU-CS
#include "alg.h"

#include <cctype>
#include <sstream>
#include <string>

#include "tstack.h"

namespace {
bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int priority(char op) {
  if (op == '*' || op == '/') {
    return 2;
  }
  if (op == '+' || op == '-') {
    return 1;
  }
  return 0;
}

void addToken(std::string *result, const std::string &token) {
  if (!result->empty()) {
    *result += ' ';
  }
  *result += token;
}
} // namespace

std::string infx2pstfx(const std::string &inf) {
  TStack<char, 100> operations;
  std::string result;

  for (size_t i = 0; i < inf.size(); ++i) {
    const char ch = inf[i];

    if (std::isspace(static_cast<unsigned char>(ch))) {
      continue;
    }

    if (std::isdigit(static_cast<unsigned char>(ch))) {
      std::string number;
      while (i < inf.size() &&
             std::isdigit(static_cast<unsigned char>(inf[i]))) {
        number += inf[i];
        ++i;
      }
      --i;
      addToken(&result, number);
      continue;
    }

    if (ch == '(') {
      operations.push(ch);
      continue;
    }

    if (ch == ')') {
      while (!operations.isEmpty() && operations.top() != '(') {
        addToken(&result, std::string(1, operations.pop()));
      }
      if (!operations.isEmpty()) {
        operations.pop();
      }
      continue;
    }

    if (isOperator(ch)) {
      while (!operations.isEmpty() && operations.top() != '(' &&
             priority(operations.top()) >= priority(ch)) {
        addToken(&result, std::string(1, operations.pop()));
      }
      operations.push(ch);
    }
  }

  while (!operations.isEmpty()) {
    addToken(&result, std::string(1, operations.pop()));
  }

  return result;
}

int eval(const std::string &post) {
  TStack<int, 100> values;
  std::istringstream input(post);
  std::string token;

  while (input >> token) {
    if (token.size() == 1 && isOperator(token[0])) {
      const int right = values.pop();
      const int left = values.pop();

      switch (token[0]) {
      case '+':
        values.push(left + right);
        break;
      case '-':
        values.push(left - right);
        break;
      case '*':
        values.push(left * right);
        break;
      case '/':
        values.push(left / right);
        break;
      }
    } else {
      values.push(std::stoi(token));
    }
  }

  return values.pop();
}
