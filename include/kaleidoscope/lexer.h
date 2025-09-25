#pragma once

#include <string>

namespace Lexer {

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

  Token get_identifier();
  Token get_number();
  Token ignore_comment_get_next_token();

public:
  Token gettok();
};

} // namespace Lexer
