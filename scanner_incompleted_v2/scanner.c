/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"

extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];
int state;
int ln, cn;
char str[MAX_IDENT_LEN];
char c;
int count; // count length of string

/***************************************************************/
// void skipBlank()
// {
//   while (currentChar != -1 && charCodes[currentChar] == CHAR_SPACE)
//     readChar();
// }
Token *readNumber(void)
{
  Token *token = makeToken(TK_NUMBER, lineNo, colNo);
  int index = 0;

  while (charCodes[currentChar] == CHAR_DIGIT)
  {
    // 10 digits maximum
    if (index > 9)
    {
      // TODO: colNo - 1?
      error(ERR_NUMBERTOOLONG, lineNo, colNo);
    }
    token->string[index] = currentChar;
    readChar();
    index++;
  }
  token->string[index] = '\0';

  token->value = atoi(token->string);
  return token;
}
/* *********************************************************** */
Token *getToken(void)
{
  // Token *token;
  Token *token = (Token *)malloc(sizeof(Token));
  // Token *token = makeToken(TK_IDENT, lineNo, colNo);

  // printf("\nState = %d \n", state);
  switch (state)
  {
  case 0:
    if (currentChar == EOF)
    {
      state = 1;
    }
    else
      switch (charCodes[currentChar])
      {
      case CHAR_SPACE:
        state = 2;
        break;
      case CHAR_LETTER:
        // ln = lineNo;
        // cn = colNo;
        state = 3;
        break;
      case CHAR_DIGIT:
        state = 7;
        break;
      case CHAR_PLUS:
        state = 9;
        break;
      case CHAR_MINUS:
        state = 10;
        break;
      case CHAR_TIMES:
        state = 11;
        break;
      case CHAR_SLASH:
        state = 12;
        break;
      case CHAR_LT:
        state = 13;
        break;
      case CHAR_GT:
        state = 16;
        break;
      case CHAR_EQ:
        state = 19;
        break;
      case CHAR_EXCLAIMATION:
        state = 20;
        break;
      case CHAR_COMMA:
        state = 23;
        break;
      case CHAR_PERIOD:
        state = 24;
        break;
      case CHAR_SEMICOLON:
        state = 27;
        break;
      case CHAR_COLON:
        state = 28;
        break;
      case CHAR_SINGLEQUOTE:
        state = 31;
        break;
      case CHAR_LPAR:
        state = 35;
        break;
      case CHAR_RPAR:
        state = 42;
        break;
      default:
        state = 43;
      }
    return getToken();
  case 1:
    state = 0;
    return makeToken(TK_EOF, lineNo, colNo);
  case 2:
    // TODO (Skip blanks)
    // skipBlank();
    while (currentChar != EOF && charCodes[currentChar] == CHAR_SPACE)
      readChar();
    state = 0;
    return getToken();
  case 3:
    // TODO Recognize Identifiers and keywords
    // return readIdentKeyword();
    memset(str, 0, sizeof(str));
    count = 0;
    ln = lineNo;
    cn = colNo;
    while (charCodes[currentChar] == CHAR_LETTER || charCodes[currentChar] == CHAR_DIGIT)
    {
      str[count] = currentChar;
      readChar();
      count++;
    }
    str[count] = '\0';
    if(count > MAX_IDENT_LEN)
      error(ERR_IDENTTOOLONG, ln, cn);
    state = 4;
    return getToken();
  case 4:
    // TODO
    if (checkKeyword(str) == TK_NONE)
      state = 5;
    else
    {
      state = 6;
    }
    // printf("%s ", str);
    return getToken();
  case 5:
    // TODO Identifiers
    token = makeToken(TK_IDENT, ln, cn);
    strcpy(token->string, str);
    // state = 0;
    return token;
  case 6:
    // TODO Keywords
    token = makeToken(checkKeyword(str), ln, cn);
    state = 0;
    return token;
  case 7:
    // TODO  Numbers
    // readChar();
    // if (charCodes[currentChar] == CHAR_DIGIT)
    //   state = 7;
    // else
    //   state = 8;
    // return getToken();
    state = 0;
    return readNumber();
  // case 8:
  //   state = 0;
  //   token = makeToken(TK_NUMBER, lineNo, colNo - 1);
  //   return token;
  case 9:
    readChar();
    // state = 0;
    return makeToken(SB_PLUS, lineNo, colNo - 1);
  case 10:
    // TODO
    readChar();
    // state = 0;
    return makeToken(SB_MINUS, lineNo, colNo - 1);
  case 11:
    // TODO
    readChar();
    // state = 0;
    return makeToken(SB_TIMES, lineNo, colNo - 1);
  case 12:
    // TODO
    readChar();
    // state = 0;
    return makeToken(SB_SLASH, lineNo, colNo - 1);
  case 13:
    readChar();
    if (charCodes[currentChar] == CHAR_EQ)
      state = 14;
    else
      state = 15;
    return getToken();
  case 14:
    readChar();
    // state = 0;
    return makeToken(SB_LE, lineNo, colNo - 1);
  case 15:
    // state = 0;
    return makeToken(SB_LT, lineNo, colNo - 1);
  case 16:
    // TODO
    readChar();
    if (charCodes[currentChar] == CHAR_EQ)
      state = 17;
    else
      state = 18;
    return getToken();
  case 17:
    // TODO
    readChar();
    // state = 0;
    return makeToken(SB_GE, lineNo, colNo - 1);
  case 18:
    // TODO
    // state = 0;
    return makeToken(SB_GT, lineNo, colNo - 1);
  case 19:
    // TODO
    readChar();
    // state = 0;
    return makeToken(SB_EQ, lineNo, colNo - 1);
  case 20:
    // TODO
    readChar();
    if (charCodes[currentChar] == CHAR_EQ)
      state = 21;
    else
      state = 22;
    return getToken();
  case 21:
    readChar();
    // state = 0;
    return makeToken(SB_NEQ, lineNo, colNo - 2);
  case 22:
    // state = 0;
    token = makeToken(TK_NONE, lineNo, colNo - 1);
    error(ERR_INVALIDSYMBOL, token->lineNo, token->colNo);
    return token;
  case 23:
    // TODO
    readChar();
    // state = 0;
    return makeToken(SB_COMMA, lineNo, colNo - 1);
  case 24:
    // TODO
    readChar();
    if (charCodes[currentChar] == CHAR_RPAR)
      state = 25;
    else
      state = 26;
    return getToken();
  case 25:
    // TODO
    readChar();
    // state = 0;
    return makeToken(SB_RSEL, lineNo, colNo - 1);
  case 26:
    // TODO
    // state = 0;
    return makeToken(SB_PERIOD, lineNo, colNo - 1);
  case 27:
    // TODO
    readChar();
    // state = 0;
    return makeToken(SB_SEMICOLON, lineNo, colNo - 1);
  case 28:
    // TODO
    readChar();
    if (charCodes[currentChar] == CHAR_EQ)
      state = 29;
    else
      state = 30;
    return getToken();
  case 29:
    // TODO
    readChar();
    state = 0;
    return makeToken(SB_ASSIGN, lineNo, colNo - 2);
  case 30:
    // TODO
    // state = 0;
    return makeToken(SB_COLON, lineNo, colNo - 1);
  case 31:
    readChar();
    if (currentChar == EOF || !isprint(currentChar))
      state = 34;
    else
      state = 32;
    return getToken();
  case 32:
    c = currentChar;
    readChar();
    if (charCodes[currentChar] == CHAR_SINGLEQUOTE)
      state = 33;
    else
      state = 34;
    return getToken();
  case 33:
    // state = 0;
    token = makeToken(TK_CHAR, lineNo, colNo - 2);
    token->string[0] = c;
    token->string[1] = '\0';
    readChar();
    return token;
  case 34:
    error(ERR_INVALIDCHARCONSTANT, lineNo, colNo - 2);
  case 35: // tokens begin with lpar, skip comments
    ln = lineNo;
    cn = colNo;
    readChar();
    if (currentChar == EOF)
      state = 41;
    else
      switch (charCodes[currentChar])
      {
      case CHAR_PERIOD:
        state = 36;
        break;
      case CHAR_TIMES:
        state = 38;
        break;
      default:
        state = 41;
      }
    return getToken();

  case 36:
    // TODO
    // state = 0;
    readChar();
    return makeToken(SB_LSEL, ln, cn);
  case 37:
    // TODO
    readChar();
    if (charCodes[currentChar] == CHAR_TIMES)
      state = 38;
    else if (currentChar == EOF)
      state = 40;
    else
      state = 37;
    return getToken();
  case 38:
    // TODO
    readChar();
    if (charCodes[currentChar] == CHAR_RPAR)
      state = 39;
    else if (charCodes[currentChar] == CHAR_TIMES)
      state = 38;
    else if (currentChar == EOF)
      state = 40;
    else
      state = 37;
    return getToken();
  case 39:
    // TODO
    readChar();
    state = 0;
    return getToken();
  case 40:
    error(ERR_ENDOFCOMMENT, lineNo, colNo);
  case 41:
    // state = 0;
    return makeToken(SB_LPAR, ln, cn);    
  case 42:
    readChar();
    // state = 0;
    return makeToken(SB_RPAR, lineNo, colNo - 1); // colNo
  case 43:
    // state = 0;
    token = makeToken(TK_NONE, lineNo, colNo);
    error(ERR_INVALIDSYMBOL, lineNo, colNo);
    readChar();
    return token;
    // default:
    //   state = 0;
    //   token = makeToken(TK_NONE, lineNo, colNo);
    //   error(ERR_INVALIDSYMBOL, lineNo, colNo);
    //   readChar();
    //   return token;
  }
  return token;
}

/******************************************************************/

void printToken(Token *token)
{

  printf("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType)
  {
  case TK_NONE:
    printf("TK_NONE\n");
    break;
  case TK_IDENT:
    printf("TK_IDENT(%s)\n", token->string);
    break;
  case TK_NUMBER:
    printf("TK_NUMBER(%s)\n", token->string);
    break;
  case TK_CHAR:
    printf("TK_CHAR(\'%s\')\n", token->string);
    break;
  case TK_EOF:
    printf("TK_EOF\n");
    break;

  case KW_PROGRAM:
    printf("KW_PROGRAM\n");
    break;
  case KW_CONST:
    printf("KW_CONST\n");
    break;
  case KW_TYPE:
    printf("KW_TYPE\n");
    break;
  case KW_VAR:
    printf("KW_VAR\n");
    break;
  case KW_INTEGER:
    printf("KW_INTEGER\n");
    break;
  case KW_CHAR:
    printf("KW_CHAR\n");
    break;
  case KW_ARRAY:
    printf("KW_ARRAY\n");
    break;
  case KW_OF:
    printf("KW_OF\n");
    break;
  case KW_FUNCTION:
    printf("KW_FUNCTION\n");
    break;
  case KW_PROCEDURE:
    printf("KW_PROCEDURE\n");
    break;
  case KW_BEGIN:
    printf("KW_BEGIN\n");
    break;
  case KW_END:
    printf("KW_END\n");
    break;
  case KW_CALL:
    printf("KW_CALL\n");
    break;
  case KW_IF:
    printf("KW_IF\n");
    break;
  case KW_THEN:
    printf("KW_THEN\n");
    break;
  case KW_ELSE:
    printf("KW_ELSE\n");
    break;
  case KW_WHILE:
    printf("KW_WHILE\n");
    break;
  case KW_DO:
    printf("KW_DO\n");
    break;
  case KW_FOR:
    printf("KW_FOR\n");
    break;
  case KW_TO:
    printf("KW_TO\n");
    break;
  case SB_SEMICOLON:
    printf("SB_SEMICOLON\n");
    break;
  case SB_COLON:
    printf("SB_COLON\n");
    break;
  case SB_PERIOD:
    printf("SB_PERIOD\n");
    break;
  case SB_COMMA:
    printf("SB_COMMA\n");
    break;
  case SB_ASSIGN:
    printf("SB_ASSIGN\n");
    break;
  case SB_EQ:
    printf("SB_EQ\n");
    break;
  case SB_NEQ:
    printf("SB_NEQ\n");
    break;
  case SB_LT:
    printf("SB_LT\n");
    break;
  case SB_LE:
    printf("SB_LE\n");
    break;
  case SB_GT:
    printf("SB_GT\n");
    break;
  case SB_GE:
    printf("SB_GE\n");
    break;
  case SB_PLUS:
    printf("SB_PLUS\n");
    break;
  case SB_MINUS:
    printf("SB_MINUS\n");
    break;
  case SB_TIMES:
    printf("SB_TIMES\n");
    break;
  case SB_SLASH:
    printf("SB_SLASH\n");
    break;
  case SB_LPAR:
    printf("SB_LPAR\n");
    break;
  case SB_RPAR:
    printf("SB_RPAR\n");
    break;
  case SB_LSEL:
    printf("SB_LSEL\n");
    break;
  case SB_RSEL:
    printf("SB_RSEL\n");
    break;
  }
}

int scan(char *fileName)
{
  Token *token;

  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  token = getToken();
  // printToken(token);
  while (token->tokenType != TK_EOF)
  {
    printToken(token);
    free(token);
    state = 0;
    token = getToken();
  }

  free(token);
  closeInputStream();
  return IO_SUCCESS;
}

/******************************************************************/

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("scanner: no input file.\n");
    return -1;
  }

  if (scan(argv[1]) == IO_ERROR) {
    printf("Can\'t read input file!\n");
    return -1;
  }

  return 0;
}

/* int main()
{
  if (scan("./test/example1.kpl") == IO_ERROR)
  {
    printf("Can\'t read input file!\n");
  }
  return 0;
} */
