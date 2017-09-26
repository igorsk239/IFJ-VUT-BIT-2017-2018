#ifndef _TOKEN_H
#define _TOKEN_H

#include "lexer_fsm.h"

/**
 * @brief List of token types
 */
typedef enum {
    TOKEN_UNKNOWN = 0,

    // !!!! Token types must have the same value as final state !!!!
    TOKEN_MULTIPLY = LEX_FSM__MULTIPLY,
    TOKEN_ADD = LEX_FSM__ADD,
    TOKEN_DIVIDE = LEX_FSM__DIVIDE,
    TOKEN_SUBTRACT = LEX_FSM__SUBTRACT,
    TOKEN_LEFT_BRACKET = LEX_FSM__LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET = LEX_FSM__RIGHT_BRACKET,
    TOKEN_IDENTIFIER = LEX_FSM__IDENTIFIER_FINISHED,
    TOKEN_BIGGER = LEX_FSM__BIGGER,
    TOKEN_SMALLER = LEX_FSM__SMALLER,
    TOKEN_BIGGER_EQUAL = LEX_FSM__BIGGER_EQUAL,
    TOKEN_SMALLER_EQUAL = LEX_FSM__SMALLER_EQUAL,
    TOKEN_INTEGER_LITERAL = LEX_FSM__INTEGER_LITERAL_FINISHED,
    TOKEN_EQUAL = LEX_FSM__EQUAL,
    TOKEN_SEMICOLON = LEX_FSM__SEMICOLON,

    TOKEN_AS = LEX_FSM__AS,
    TOKEN_ASC = LEX_FSM__ASC,
    TOKEN_DECLARE = LEX_FSM__DECLARE,
    TOKEN_DIM = LEX_FSM__DIM,
    TOKEN_DO = LEX_FSM__DO,
    TOKEN_DOUBLE = LEX_FSM__DOUBLE,
    TOKEN_ELSE = LEX_FSM__ELSE,
    TOKEN_END = LEX_FSM__END,
    TOKEN_CHR = LEX_FSM__CHR,
    TOKEN_FUNCTION = LEX_FSM__FUNCTION,
    TOKEN_IF = LEX_FSM__IF,
    TOKEN_INPUT = LEX_FSM__INPUT,
    TOKEN_INTEGER = LEX_FSM__INTEGER,
    TOKEN_LENGTH = LEX_FSM__LENGTH,
    TOKEN_LOOP = LEX_FSM__LOOP,
    TOKEN_PRINT = LEX_FSM__PRINT,
    TOKEN_RETURN = LEX_FSM__RETURN,
    TOKEN_SCOPE = LEX_FSM__SCOPE,
    TOKEN_STRING = LEX_FSM__STRING,
    TOKEN_SUBSTR = LEX_FSM__SUBSTR,
    TOKEN_THEN= LEX_FSM__THEN,
    TOKEN_WHILE = LEX_FSM__WHILE,
    TOKEN_AND = LEX_FSM__AND,
    TOKEN_BOOLEAN = LEX_FSM__BOOLEAN,
    TOKEN_CONTINUE = LEX_FSM__CONTINUE,
    TOKEN_ELSEIF = LEX_FSM__ELSEIF,
    TOKEN_EXIT = LEX_FSM__EXIT,
    TOKEN_FALSE = LEX_FSM__FALSE,
    TOKEN_FOR = LEX_FSM__FOR,
    TOKEN_NEXT = LEX_FSM__NEXT,
    TOKEN_NOT = LEX_FSM__NOT,
    TOKEN_OR = LEX_FSM__OR,
    TOKEN_SHARED = LEX_FSM__SHARED,
    TOKEN_STATIC = LEX_FSM__STATIC,
    TOKEN_TRUE = LEX_FSM__TRUE,
    TOKEN_DOUBLE_LITERAL = LEX_FSM__DOUBLE_FINISHED,
    TOKEN_STRING_VALUE = LEX_FSM__STRING_VALUE,
    TOKEN_COMMA = LEX_FSM__COMMA,
    TOKEN_SMALLER_BIGGER = LEX_FSM__SMALLER_BIGGER,

    TOKEN_EOL = LEX_FSM__EOL,
    TOKEN_ERROR = LEX_FSM__ERROR,
    TOKEN_EOF = LEX_FSM__EOF,

} TokenType;

/**
 * @brief Represents a token
 */
typedef struct token_t {
    TokenType type; // Type of token
} Token;


#endif //_TOKEN_H