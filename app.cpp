#include <iostream>  // For printing things to the screen.
#include <cctype>    // To check if a character is a letter or a number.
#include <string>    // To work with strings.
using namespace std; // We don’t need to type std:: before every function.

#define LETTER 0    // Used to represent a letter (A-Z, a-z).
#define DIGIT 1     // Used to represent a digit (0-9).
#define UNKNOWN 99  // For characters we don’t know.
#define EOF_FLAG -1 // Marks the end of the input.

#define INT_LIT 10     // A number (e.g., 5, 100).
#define IDENT 11       // A word (e.g., variable name).
#define ASSIGN_OP 20   // Equals sign (=).
#define ADD_OP 21      // Plus sign (+).
#define SUB_OP 22      // Minus sign (-).
#define MULT_OP 23     // Asterisk (*) for multiplication.
#define DIV_OP 24      // Slash (/) for division.
#define LEFT_PAREN 25  // Left parenthesis '('.
#define RIGHT_PAREN 26 // Right parenthesis ')'.
#define SEMICOLON 27   // Semicolon (;).

// Variables to store the current character and information about tokens.
int charClass;                  // Tells us if the character is a letter, digit, or unknown.
char lexeme[100];               // Holds the current word or symbol we're working with.
char nextChar;                  // Stores the character we're currently analyzing.
int lexLen;                     // The length of the current word.
int nextToken;                  // The type of token we're analyzing (e.g., number, operator).
string input = "sum = 5 + 3 ;"; // This is our input string for testing.
int inputindex = 0;             // Tracks where we are in the input string.

void addChar()
{
    if (lexLen <= 98)
    {                                // Prevents adding more than 100 characters.
        lexeme[lexLen++] = nextChar; // Add the character to the word.
        lexeme[lexLen] = '\0';       // Mark the end of the word.
    }
    else
    {
        cout << "Error - lexeme too long\n"; // If the word is too long, show an error.
    }
}

void getChar()
{
    if (inputindex < input.length())
    {                                   // If there are more characters to read.
        nextChar = input[inputindex++]; // Get the next character.
        if (isalpha(nextChar))
            charClass = LETTER; // If it’s a letter, classify it as a letter.
        else if (isdigit(nextChar))
            charClass = DIGIT; // If it’s a number, classify it as a digit.
        else
            charClass = UNKNOWN; // If it’s something else, mark it as unknown.
    }
    else
    {
        charClass = EOF_FLAG; // If we’ve reached the end, set EOF_FLAG.
    }
}

void getNonBlank()
{
    while (isspace(nextChar))
        getChar(); // Skip any spaces or tabs.
}

int lookup(char ch)
{ // Check what special symbol we have.
    switch (ch)
    {
    case '(':
        addChar();
        return LEFT_PAREN; // Left parenthesis.
    case ')':
        addChar();
        return RIGHT_PAREN; // Right parenthesis.
    case '+':
        addChar();
        return ADD_OP; // Plus sign.
    case '-':
        addChar();
        return SUB_OP; // Minus sign.
    case '*':
        addChar();
        return MULT_OP; // Asterisk (multiplication).
    case '/':
        addChar();
        return DIV_OP; // Slash (division).
    case '=':
        addChar();
        return ASSIGN_OP; // Equals sign.
    case ';':
        addChar();
        return SEMICOLON; // Semicolon.
    default:
        addChar();
        return UNKNOWN; // If it’s something else, mark it as unknown.
    }
}

int lex()
{
    lexLen = 0;    // Start fresh with an empty word.
    getNonBlank(); // Skip over spaces or tabs.

    switch (charClass)
    {            // Check the type of character.
    case LETTER: // If it's a letter, it’s probably a word or variable name.
        addChar();
        getChar(); // Add the letter to the word and get the next character.
        while (charClass == LETTER || charClass == DIGIT)
        { // Add more letters or digits.
            addChar();
            getChar();
        }
        nextToken = IDENT; // It's an identifier (a word).
        break;
    case DIGIT: // If it’s a digit, it’s a number.
        addChar();
        getChar(); // Add the digit to the word and get the next character.
        while (charClass == DIGIT)
        { // Keep adding digits.
            addChar();
            getChar();
        }
        nextToken = INT_LIT; // It's a number.
        break;
    case UNKNOWN:                     // If it's an operator or symbol.
        nextToken = lookup(nextChar); // Find out what the symbol is.
        getChar();                    // Get the next character after processing the current one.
        break;
    case EOF_FLAG:              // If we’ve reached the end of the input.
        nextToken = EOF_FLAG;   // Mark it as end of input.
        sprintf(lexeme, "EOF"); // Set the word to "EOF".
        break;
    }

    // Print the token and the word.
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken; // Return the token we found.
}

int main()
{
    cout << "lexeme is " << input << endl;
    inputindex = 0; // Start at the beginning of the input string.
    getChar();      // Get the first character.
    do
    {
        lex(); // Analyze the next token.
    } while (nextToken != EOF_FLAG); // Keep going until we reach the end.

    return 0; // All done.
}
