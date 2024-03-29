# Datalog-Interpreter
This repository contains code to run an interpreter for Datalog programs. According to [Techopedia.com](https://www.techopedia.com/definition/3915/datalog), "Datalog is a programming language used in deductive database work. It is part of another language called Prolog and incorporates basic logic principles for data integration, database queries, etc. Datalog is used by many open-source systems and other database systems." The interpreter consists of a lexer, parser, and execution engine.

# Lexer
The lexer scans an input file for tokens it has been programmed to recognize. The output of the lexer is then a list of the tokens generated from the input file that is then passed to the parser.

# Parser
The parser takes as input the list of tokens generated by the lexer and assigns meaning to the Datalog program based on the sequence of tokens. The parser uses the Datalog grammar to determine whether or not the sequence of tokens it is parsing follows valid syntax. If the parser reaches the end of the sequence of tokens without an error, then it determines it has been given a syntactically valid Datalog program and the interpreter moves onto the execution engine

# Execution Engine
The execution engine takes as input the interpreted meaning of the tokens generated by the parser. A Datalog program first defines schemes (tables), then defines facts (rows in tables), then defines rules (relationships between tables), and finally provides a list of queries to execute. Because the input Datalog program has reached the execution engine, it is given that the program does not contain any syntax errors. If there are any logic errors or "bugs" then the execution engine will catch them. Otherwise, the program will run successfully and the results of each of the queries listed at the end of the program will be returned.
