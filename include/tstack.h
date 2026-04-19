// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template <typename T, int size> class TStack {
private:
  T data[size];
  int pos;

public:
  TStack() : pos(0) {}

  bool isEmpty() const { return pos == 0; }

  bool isFull() const { return pos == size; }

  bool empty() const { return isEmpty(); }

  bool full() const { return isFull(); }

  int getSize() const { return pos; }

  int Size() const { return getSize(); }

  void push(const T &value) {
    if (isFull()) {
      throw std::overflow_error("stack overflow");
    }
    data[pos++] = value;
  }

  void Push(const T &value) { push(value); }

  T pop() {
    if (isEmpty()) {
      throw std::out_of_range("stack is empty");
    }
    return data[--pos];
  }

  T Pop() { return pop(); }

  T &top() {
    if (isEmpty()) {
      throw std::out_of_range("stack is empty");
    }
    return data[pos - 1];
  }

  const T &top() const {
    if (isEmpty()) {
      throw std::out_of_range("stack is empty");
    }
    return data[pos - 1];
  }

  T &Top() { return top(); }

  const T &Top() const { return top(); }
};

#endif // INCLUDE_TSTACK_H_
