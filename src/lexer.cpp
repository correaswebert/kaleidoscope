#include <string>

#include "kaleidoscope/lexer.h"

namespace Lexer {

/**
 * @brief Capture `[a-zA-Z][a-zA-Z0-9]*`
 */
Token Lexer::get_identifier() {
  if (!isalpha(last_char)) {
    return Token::Unknown;
  }

  identifier = last_char;

  while (isalnum((last_char = getchar())))
    identifier += last_char;

  if (identifier == "def")
    return Token::Def;
  else if (identifier == "extern")
    return Token::Extern;
  return Token::Identifier;
}

/**
 * @brief Capture `[0-9.]+`
 */
Token Lexer::get_number() {
  if (!isdigit(last_char) && last_char != '.') {
    return Token::Unknown;
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
  return Token::Number;
}

/**
 * @brief Ignore comments starting with `#` until the end of the line.
 * 
 * Also retrigger getting the next token after the comment. This is to avoid
 * returning `Unknown` when a comment is encountered.
 */
Token Lexer::ignore_comment_get_next_token() {
  if (last_char != '#') {
    return Token::Unknown;
  }

  do
    last_char = getchar();
  while (last_char != EOF && last_char != '\n' && last_char != '\r');

  if (last_char != EOF)
    return Lexer::gettok();

  // should not reach here
  return Token::Unknown;
}

Token Lexer::gettok() {
  Token token = Token::Unknown;

  // skip whitespaces
  while (isspace(last_char))
    last_char = getchar();

  token = get_identifier();
  if (token != Token::Unknown)
    return token;

  token = get_number();
  if (token != Token::Unknown)
    return token;

  token = ignore_comment_get_next_token();
  if (token != Token::Unknown)
    return token;
  
  if (last_char == EOF)
    return Token::Eof;

  // return the character as its ascii value
  // this block handles single-character tokens like operators (+, -, *, etc.)
  // that aren't part of identifiers, numbers, or comments.
  opchar = last_char;
  last_char = getchar();
  return Token::Operator;
};

} // namespace Lexer
