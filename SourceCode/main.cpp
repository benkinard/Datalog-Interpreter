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

    // Create Datalog Parser and pass it the vector of tokens generated above
    Parser DatalogParser;
    std::vector<Token*> fileTokens = DatalogLexer.getTokens();

    // Parse the tokens and pass the resulting DatalogProgram to the Interpreter
    Interpreter DatalogInterpreter(DatalogParser.Parse(fileTokens));

    // Evaluate the Rules from the DatalogProgram
    DatalogInterpreter.evaluateRules();

    // Evaluate the Queries from the DatalogProgram
    DatalogInterpreter.evaluateQueries();

    return 0;
}
