#pragma once

#include <string>

namespace kaleidoscope {

enum class Token {
  Unknown,
  Eof,

  Def,
  Extern,

  Identifier,
  Number,
  Operator,
};

class Lexer {
  char opchar = ' ';
  char last_char = ' ';
  std::string identifier;
  double number;

  int get_identifier();
  int get_number();
  int ignore_comment_get_next_token();

public:
  Lexer() : last_char(' '), opchar(' '), identifier(""), number(0.) {}
  int gettok();
};

} // namespace kaleidoscope
