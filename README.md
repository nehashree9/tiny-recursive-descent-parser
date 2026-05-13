# Recursive Descent Parser for TINY Language

A complete Compiler Design project in C implementing a Recursive Descent Parser for the TINY programming language.

## Project Description
This project implements the syntax analysis phase of a compiler. It reads source code written in the TINY programming language, performs lexical analysis to extract tokens, and then uses a recursive descent parsing technique to ensure the syntax is correct according to the TINY grammar. 

## Compiler Phases
1. **Lexical Analysis (Scanner)**: Reads raw characters and groups them into meaningful tokens while ignoring whitespace and comments. It identifies keywords, symbols, variables, and numbers, discarding spaces and comments formatted within `{ }`.
2. **Syntax Analysis (Parser)**: Takes tokens from the scanner and checks them against the context-free grammar using recursive descent functions. The parser builds a call tree implicitly through function calls matching the grammar rules.

## Grammar Explained
The implemented subset of the TINY grammar rules uses EBNF (Extended Backus-Naur Form):
```
program       → stmt-seq
stmt-seq      → stmt { ; stmt }
stmt          → if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt
if-stmt       → if exp then stmt-seq [else stmt-seq] end
repeat-stmt   → repeat stmt-seq until exp
assign-stmt   → identifier := exp
read-stmt     → read identifier
write-stmt    → write exp
exp           → simple-exp [ comparison-op simple-exp ]
comparison-op → < | =
simple-exp    → term { addop term }
addop         → + | -
term          → factor { mulop factor }
mulop         → * | /
factor        → ( exp ) | number | identifier
```

## How to Compile
You need GCC (GNU Compiler Collection) installed on your system.
1. Open a terminal or VS Code command prompt.
2. Navigate to the project directory.
3. Run the following command:
   ```bash
   make
   ```

## How to Run
To run the parser on the default `input.tiny` file:
```bash
make run
```
Or you can manually pass any `.tiny` file as a parameter:
```bash
./tinyparser sample_programs/valid1.tiny
```
*(On Windows CMD or PowerShell, run: `tinyparser.exe sample_programs/valid1.tiny`)*

## Sample Output

**Valid Program Execution**
```
--------------------------------
TINY Recursive Descent Parser
--------------------------------
Reading input.tiny...
Parsing started...

Parsing Successful
```

**Invalid Program Execution**
```
--------------------------------
TINY Recursive Descent Parser
--------------------------------
Reading sample_programs/invalid1.tiny...
Parsing started...

Syntax Error at line 2 near 'if'
```

## Recursive Descent Flow
Recursive Descent Parsing relies on a set of mutually recursive functions. For every non-terminal symbol in the grammar, there is a corresponding C function. 
- Example: the `stmt_seq` rule can consist of multiple statements separated by `;`. Therefore, the `stmt_seq()` function calls `stmt()`, checks for a `;` token, and repeats if necessary.
- The `match(TokenType expected)` function compares the current token with the expected terminal token. If they match, it advances to the next token; otherwise, it triggers a syntax error, halting the parsing process to inform the user about the issue's location (line number).

## Future Enhancements
- Build an Abstract Syntax Tree (AST) visually.
- Add semantic analysis (type and bounds checking).
- Implement an interpreter or target code generator (Assembly/C).
- Add error recovery mechanisms (like panic mode) to continue parsing after encountering a syntax error.
