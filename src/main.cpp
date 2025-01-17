#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stack>

enum TokenType {
    KEYWORD,       // Keywords like int, float, return
    IDENTIFIER,    // Variable or function names
    OPERATOR,      // Operators like +, -, *, /, ^, etc.
    LITERAL,       // Integer or floating-point numbers
    DELIMITER,     // Symbols like (, ), {, }, ;, etc.
    BUILTIN_FUNC,  // Built-in functions like sin, cos, sqrt
    COMMENT,       // Comments (e.g., single-line or multi-line comments)
    UNARY_OPERATOR,// Unary operators (+, - used as unary)
    FUNCTION,      // Add FUNCTION type for built-in functions like sin, cos, etc.
    UNKNOWN        // Any unrecognized tokens
};

struct Token {
    TokenType type;        // The type of the token (e.g., KEYWORD, IDENTIFIER, etc.)
    std::string value;     // The actual value of the token (e.g., "int", "x", "+")
    int lineNumber;        // The line number where the token was found
    int columnNumber;      // The column number where the token starts
};


bool isKeyword(const std::string& str) {
    // List of supported keywords
    return (str == "int" || str == "float" || str == "return" || str == "sin" || str == "cos" || str == "sqrt");
}

TokenType getTokenType(const std::string& str) {
    // Check for keywords, including built-in functions
    if (isKeyword(str)) return KEYWORD;

    // Check for identifiers (variables or user-defined functions)
    if (std::isalpha(str[0]) || str[0] == '_') return IDENTIFIER;

    // Check for operators, including the new exponentiation operator (^)
    if (str == "=" || str == "+" || str == "-" || str == "*" || str == "/" || str == "^" || str == ";") return OPERATOR;

    // Check for unary operators (+, - used as unary)
    if (str == "+" || str == "-") return UNARY_OPERATOR;

    // Check for floating-point or integer literals
    if (std::isdigit(str[0])) {
        bool hasDecimalPoint = false;
        for (char c : str) {
            if (c == '.') {
                if (hasDecimalPoint) return UNKNOWN;  // Invalid if multiple decimal points
                hasDecimalPoint = true;
            } else if (!std::isdigit(c)) {
                return UNKNOWN;  // Invalid character for a literal
            }
        }
        return LITERAL;
    }

    // Check for delimiters (e.g., parentheses, braces)
    if (str == "(" || str == ")" || str == "{" || str == "}" || str == ",") return DELIMITER;

    return UNKNOWN;  // If no match, return UNKNOWN
}


std::vector<Token> lexicalAnalyze(std::stack<char>& inputStack) {
    std::vector<Token> tokens;
    std::string buffer;
    int lineNumber = 1;
    int columnNumber = 1;

    while (!inputStack.empty()) {
        char c = inputStack.top();
        inputStack.pop();

        // Handle new line for tracking line numbers
        if (c == '\n') {
            lineNumber++;
            columnNumber = 1;
            continue;
        }

        // Skip spaces
        if (std::isspace(c)) {
            columnNumber++;
            continue;
        }

        // Handle numbers (LITERALs)
        if (std::isdigit(c)) {
            buffer.clear();
            buffer += c;
            while (!inputStack.empty() && (std::isdigit(inputStack.top()) || inputStack.top() == '.')) {
                buffer += inputStack.top();
                if (inputStack.top() == '.') {
                    // Ensure only one decimal point is allowed
                    if (buffer.find('.') != std::string::npos) {
                        break;  // Invalid number, break out
                    }
                }
                inputStack.pop();
            }
            tokens.push_back({LITERAL, buffer, lineNumber, columnNumber});
            columnNumber += buffer.length();
            continue;
        }

        // Handle identifiers and keywords
        if (std::isalpha(c) || c == '_') {
            buffer.clear();
            buffer += c;
            while (!inputStack.empty() && (std::isalnum(inputStack.top()) || inputStack.top() == '_')) {
                buffer += inputStack.top();
                inputStack.pop();
            }
            tokens.push_back({getTokenType(buffer), buffer, lineNumber, columnNumber});
            columnNumber += buffer.length();
            continue;
        }

        // Handle operators and delimiters
        if (c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == ';') {
            tokens.push_back({OPERATOR, std::string(1, c), lineNumber, columnNumber});
            columnNumber++;
            continue;
        }

        // Handle delimiters (parentheses, braces, commas)
        if (c == '(' || c == ')' || c == '{' || c == '}' || c == ',') {
            tokens.push_back({DELIMITER, std::string(1, c), lineNumber, columnNumber});
            columnNumber++;
            continue;
        }

        // Handle unary operators (+, - used as unary)
        if (c == '+' || c == '-') {
            tokens.push_back({UNARY_OPERATOR, std::string(1, c), lineNumber, columnNumber});
            columnNumber++;
            continue;
        }

        // Handle comments (single-line // or multi-line /* */)
        if (c == '/' && !inputStack.empty() && inputStack.top() == '/') {
            while (!inputStack.empty() && inputStack.top() != '\n') {
                inputStack.pop();  // Skip the rest of the comment line
            }
            continue;
        }

        if (c == '/' && !inputStack.empty() && inputStack.top() == '*') {
            inputStack.pop();  // Skip the opening '*'
            while (!inputStack.empty()) {
                if (inputStack.top() == '*' && !inputStack.empty() && inputStack.top() == '/') {
                    inputStack.pop();  // Skip the closing '/'
                    break;
                }
                inputStack.pop();  // Skip inside the comment
            }
            continue;
        }

        // Handle unknown characters
        tokens.push_back({UNKNOWN, std::string(1, c), lineNumber, columnNumber});
        columnNumber++;
    }

    return tokens;
}


void displayTokens(const std::vector<Token>& tokens) {
    for (const Token& token : tokens) {
        std::string type;
        switch (token.type) {
            case KEYWORD:      type = "KEYWORD"; break;
            case IDENTIFIER:   type = "IDENTIFIER"; break;
            case OPERATOR:     type = "OPERATOR"; break;
            case LITERAL:      type = "LITERAL"; break;
            case DELIMITER:    type = "DELIMITER"; break;
            case UNARY_OPERATOR: type = "UNARY_OPERATOR"; break;
            case FUNCTION:     type = "FUNCTION"; break;
            case UNKNOWN:      type = "UNKNOWN"; break;
            default:           type = "UNKNOWN"; break;
        }
        std::cout << "Token Type: " << type 
                  << ", Value: " << token.value 
                  << ", Line: " << token.lineNumber 
                  << ", Column: " << token.columnNumber
                  << "\n";
    }
}

int main() {
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    std::stack<char> inputStack;
    std::string line;
    int lineNumber = 1;  // Track line numbers

    // Read the file line by line
    while (std::getline(inputFile, line)) {
        // Push the line into the stack in reverse order
        for (auto it = line.rbegin(); it != line.rend(); ++it) {
            inputStack.push(*it);
        }
        // Push newline character to indicate end of line
        inputStack.push('\n');
        lineNumber++;
    }

    inputFile.close();

    // Tokenize the input
    std::vector<Token> tokens = lexicalAnalyze(inputStack);

    // Display the tokens with line and column info
    std::cout << "Tokens for code in the file:\n";
    displayTokens(tokens);

    return 0;
}

