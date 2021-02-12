#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"

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
    Lexer* DatalogLexer = new Lexer();
    DatalogLexer->Run(fileInput);

    // Create Datalog Parser, pass it the vector of tokens generated above, and parse the tokens
    Parser* DatalogParser = new Parser();
    std::vector<Token*> fileTokens = DatalogLexer->getTokens();
    DatalogParser->Parse(fileTokens);

    // Deallocate memory for the Lexer and Parser
    delete DatalogLexer;
    delete DatalogParser;
    return 0;
}
