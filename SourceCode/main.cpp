#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
// REMOVE THIS LATER
#include "DatalogProgram.h"

int main(int argc, char* argv[]) {
    std::string fileInput;
    std::ifstream inFS;
    inFS.open(argv[1]);     // Open file and check that the open was successful
    if (!inFS.is_open()) {
        std::cout << "Unable to open file \"" << argv[1] << "\"" << std::endl;
        return 1;
    }

    while (inFS.peek() != EOF) {    // Read file contents into a single string "fileInput"
        fileInput += inFS.get();
    }

    inFS.close();

    // Create Datalog Lexer and pass it the string of the file contents
    Lexer DatalogLexer;
    DatalogLexer.Run(fileInput);

    // Create Datalog Parser, pass it the vector of tokens generated above, and parse the tokens
    Parser DatalogParser;
    std::vector<Token*> fileTokens = DatalogLexer.getTokens();

    // TEST INTERPRETER
    Interpreter testInterpreter(DatalogParser.Parse(fileTokens));

    // Deallocate memory for the Lexer and Interpreter
    return 0;
}
