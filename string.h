#include <algorithm>
#include <cstring>
#include <iostream>

class String {
 private:
  size_t size_;
  size_t capacity_;
  char* string_;

  void expand();
  void set_end();

 public:
  String();
  String(const char*);
  String(size_t, char);
  String(const String&);
  ~String();

  String& operator=(const String&);
  void swap(String&);

  const char& operator[](size_t) const;
  char& operator[](size_t);

  size_t length() const;

  void push_back(char);
  void pop_back();
  const char& front() const;
  char& front();
  const char& back() const;
  char& back();

  String& operator+=(const String&);
  String& operator+=(char);

  size_t find(const String&) const;
  size_t rfind(const String&) const;

  String substr(size_t, size_t) const;

  bool empty() const;
  void clear();

  void shrink_to_fit();

  const char* data() const;
  char* data();
  size_t size() const;
  size_t capacity() const;
};

String::String()
    : size_(0), capacity_(0), string_(new char[capacity_ + 1]{'\0'}) {}

String::String(size_t size, char filler)
    : size_(size), capacity_(size), string_(new char[capacity_ + 1]) {
  std::fill(string_, string_ + size, filler);
  set_end();
}

String::String(const char* other)
    : size_(strlen(other)), capacity_(size_), string_(new char[capacity_ + 1]) {
  std::copy(other, other + size_ + 1, string_);
}

String::String(const String& other)
    : size_(other.size_),
      capacity_(other.size_),
      string_(new char[capacity_ + 1]) {
  std::copy(other.string_, other.string_ + other.size_ + 1, string_);
}

String::~String() { delete[] string_; }

void String::expand() {
  capacity_ = capacity_ * 2 + static_cast<size_t>(capacity_ == 0);
  char* temporary = new char[capacity_ + 1];
  std::copy(string_, string_ + size_ + 1, temporary);
  std::swap(string_, temporary);
  delete temporary;
}

void String::set_end() { string_[size_] = '\0'; }

void String::swap(String& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(string_, other.string_);
}

String& String::operator=(const String& other) {
  if (capacity_ >= other.size_) {
    std::copy(other.string_, other.string_ + size_ + 1, string_);
    size_ = other.size_;
    return *this;
  }
  String copy = other;
  swap(copy);
  return *this;
}

bool operator==(const String& first, const String& second) {
  return (first.size() != second.size())
             ? false
             : std::strcmp(first.data(), second.data()) == 0;
}

bool operator!=(const String& first, const String& second) {
  return !(first == second);
}

bool operator<(const String& first, const String& second) {
  return std::strcmp(first.data(), second.data()) < 0;
}

bool operator>(const String& first, const String& second) {
  return second < first;
}

bool operator<=(const String& first, const String& second) {
  return !(first > second);
}

bool operator>=(const String& first, const String& second) {
  return !(first < second);
}

const char& String::operator[](size_t index) const { return string_[index]; }

char& String::operator[](size_t index) { return string_[index]; }

size_t String::length() const { return size_; }

void String::push_back(char character) {
  if (size_ >= capacity_) {
    expand();
  }
  string_[size_] = character;
  size_++;
  set_end();
}

void String::pop_back() {
  size_--;
  set_end();
}

const char& String::front() const { return string_[0]; }

char& String::front() { return string_[0]; }

const char& String::back() const { return string_[size_ - 1]; }

char& String::back() { return string_[size_ - 1]; }

String& String::operator+=(const String& other) {
  if (capacity_ <= size_ + other.size_) {
    char* temporary = new char[size_ + other.size_ + 1];
    capacity_ += size_ + other.size_;
    std::copy(string_, string_ + size_, temporary);
    std::swap(string_, temporary);
    delete temporary;
  }
  std::copy(other.string_, other.string_ + other.size_, string_ + size_);
  size_ += other.size_;
  return *this;
}

String& String::operator+=(char character) {
  push_back(character);
  return *this;
}

String operator+(const String& lhs, const String& rhs) {
  String temporary = lhs;
  temporary += rhs;
  return temporary;
}

String operator+(char lhs, const String& rhs) {
  String temporary;
  temporary += lhs;
  temporary += rhs;
  return temporary;
}

String operator+(const String& lhs, char rhs) {
  String temporary = lhs;
  temporary += rhs;
  return temporary;
}

size_t String::find(const String& substr) const {
  char* it = std::strstr(string_, substr.string_);
  if (it == nullptr) return size_;
  return it - string_;
}

size_t String::rfind(const String& substr) const {
  return std::find_end(string_, string_ + size_, substr.string_,
                       substr.string_ + substr.size_) -
         string_;
}

String String::substr(size_t start, size_t length) const {
  String other(length, '\0');
  std::copy(string_ + start, string_ + start + length, other.string_);
  return other;
}

bool String::empty() const { return size_ == 0; }

void String::clear() {
  size_ = 0;
  set_end();
}

void String::shrink_to_fit() {
  if (size_ == capacity_) return;
  String other = *this;
  swap(other);
}

std::istream& operator>>(std::istream& is, String& string) {
  char character;
  string.clear();
  while (is >> std::noskipws >> character && std::iswspace(character))
    ;
  string += character;
  while (is >> std::noskipws >> character) {
    if (std::iswspace(character)) break;
    string += character;
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
  os << string.data();
  return os;
}

const char* String::data() const { return string_; }

char* String::data() { return string_; }

size_t String::size() const { return size_; }

size_t String::capacity() const { return capacity_; }