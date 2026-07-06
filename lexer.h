#ifndef LEXER_H
#define LEXER_H

typedef enum {
    // Start
    ST_START,
    // Comment
    ST_COMMENT,
    // Multline comment start
    ST_ML_COMMENT_BEGIN,
    // String begin
    ST_STR_BEGIN,
    // Format string begin
    ST_F_STR_BEGIN,
    // Multiline string begin
    ST_ML_STR_BEGIN,
    // Multiline format string begin
    ST_ML_F_STR_BEGIN,
    // Object string begin
    ST_O_STR_BEGIN,
    // Object format string begin
    ST_O_F_STR_BEGIN,
    // Object multiline format string begin
    ST_O_ML_F_STR_BEGIN,
    // Multiline continue
    ST_ML,
    // Multiline format continue
    ST_ML_F,
    // Multline string end
    ST_ML_STR_END,
    // Mutliline comment end
    ST_ML_COMMENT_END,
    // Escape sequence
    ST_ESCAPE,
    // Identifier, keyword, or string start
    ST_ID_KW_STR,
    // Identifier or keyword
    ST_ID_KW,
    // Whitespace
    ST_WHITESPACE,
    // Digits
    ST_DIGIT,
    // Symbol
    ST_SYMBOL,
} State;

#endif