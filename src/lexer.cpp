#include <string>

#include "kaleidoscope/lexer.h"

namespace kaleidoscope {

/**
 * @brief Capture `[a-zA-Z][a-zA-Z0-9]*`
 */
int Lexer::get_identifier() {
  if (!isalpha(last_char)) {
    return static_cast<int>(Token::Unknown);
  }

  identifier = last_char;

  while (isalnum((last_char = getchar())))
    identifier += last_char;

  if (identifier == "def")
    return static_cast<int>(Token::Def);
  else if (identifier == "extern")
    return static_cast<int>(Token::Extern);
  return static_cast<int>(Token::Identifier);
}

/**
 * @brief Capture `[0-9.]+`
 */
int Lexer::get_number() {
  if (!isdigit(last_char) && last_char != '.') {
    return static_cast<int>(Token::Unknown);
  }

  identifier = last_char;

  while (isdigit((last_char = getchar())))
    identifier += last_char;

  if (last_char == '.') {
    identifier += last_char;
    while (isdigit((last_char = getchar())))
      identifier += last_char;
  }

  number = strtod(identifier.c_str(), nullptr);
  return static_cast<int>(Token::Number);
}

/**
 * @brief Ignore comments starting with `#` until the end of the line.
 * 
 * Also retrigger getting the next token after the comment. This is to avoid
 * returning `Unknown` when a comment is encountered.
 */
int Lexer::ignore_comment_get_next_token() {
  if (last_char != '#') {
    return static_cast<int>(Token::Unknown);
  }

  do
    last_char = getchar();
  while (last_char != EOF && last_char != '\n' && last_char != '\r');

  if (last_char != EOF)
    return Lexer::gettok();

  // should not reach here
  return static_cast<int>(Token::Unknown);
}

int Lexer::gettok() {
  int token = static_cast<int>(Token::Unknown);

  // skip whitespaces
  while (isspace(last_char))
    last_char = getchar();

  token = get_identifier();
  if (token != static_cast<int>(Token::Unknown))
    return token;

  token = get_number();
  if (token != static_cast<int>(Token::Unknown))
    return token;

  token = ignore_comment_get_next_token();
  if (token != static_cast<int>(Token::Unknown))
    return token;
  
  if (last_char == EOF)
    return static_cast<int>(Token::Eof);

  // return the character as its ascii value
  // this block handles single-character tokens like operators (+, -, *, etc.)
  // that aren't part of identifiers, numbers, or comments.
  opchar = last_char;
  last_char = getchar();
  return static_cast<int>(Token::Operator);
};

} // namespace kaleidoscope
