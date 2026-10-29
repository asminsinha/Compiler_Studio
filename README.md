# Compiler Studio

### Compiler Design and Control-Flow Workbench

**Course:** Compiler Design Lab (BCSE307P)\
**Project:** Design and Development of a Compiler for Structured Control
Flow Using Three-Address Code and Backpatching\
**Implementation:** Flex, Bison, C, Python, React, TypeScript

Compiler Studio is a learning and experimentation environment for a
small imperative language. It connects a native Flex/Bison compiler with
a browser-based interface for inspecting intermediate code and exploring
control flow. The compiler demonstrates lexical analysis, syntax
analysis, syntax-directed translation, backpatching, intermediate
representations, and execution of generated code.

> **Scope note:** Compiler Studio implements a defined subset of an
> imperative language; it is not a drop-in compiler for C, Java, or
> Python. Feature availability in the browser depends on the Python
> backend and frontend being integrated with the same compiler
> functionality as the native executable.

## Contents

-   [Features](#features)
-   [Architecture and source files](#architecture-and-source-files)
-   [Supported language](#supported-language)
-   [Grammar overview](#grammar-overview)
-   [How compilation works](#how-compilation-works)
-   [Requirements](#requirements)
-   [Get the project onto your PC](#get-the-project-onto-your-pc)
-   [Build and run on Windows with
    WSL2](#build-and-run-on-windows-with-wsl2)
-   [Run the web application](#run-the-web-application)
-   [Run a source program with the native
    compiler](#run-a-source-program-with-the-native-compiler)
-   [Example: switch-case](#example-switch-case)
-   [Intermediate representations and
    analysis](#intermediate-representations-and-analysis)
-   [Testing and troubleshooting](#testing-and-troubleshooting)
-   [Limitations and future work](#limitations-and-future-work)

## Features

### Lexing and parsing

-   Flex-based lexical analysis in `lexer.l`.
-   Bison grammar and syntax-directed actions in `parser.y`.
-   Token, source-location, and diagnostic information where emitted by
    the compiler.
-   Syntax for assignments, arithmetic expressions, output statements,
    blocks, conditionals, loops, and switch selection.

### Structured control flow and backpatching

-   `if` and `if-else` branching.
-   `while` loops.
-   Assignment-based `for` loops.
-   `switch`, integer `case` labels, optional `default`, and `break` to
    exit a switch.
-   Nested blocks and combinations of supported constructs, subject to
    grammar and regression testing.
-   Three-address-code generation with labels and temporary values.
-   Backpatching lists and operations based on `makelist()`, `merge()`,
    and `backpatch()` to resolve jump targets.

The implemented switch form uses integer case constants and does not use
C-style fall-through: execution leaves a selected case body rather than
automatically continuing into the next case. The native compiler has
been built and exercised with a test where `x = 2` selects `case 2`,
prints `20`, and then continues after the switch to print `99`.

### Intermediate code and execution

-   Three-Address Code (TAC), with symbolic labels.
-   Quadruples (`op`, `arg1`, `arg2`, `result`).
-   Triples and indirect triples, where enabled by the checked-out
    UI/backend version.
-   Backpatching information and jump targets.
-   Native TAC execution with runtime output and final variable state.

### Workbench and analysis

The workbench design includes source editing, sample programs, token
streams and diagnostics; intermediate-representation inspection;
control-flow graph (CFG) exploration; optimization experiments;
execution inspection; liveness and register-allocation analysis; and a
reference/viva guide. These panels depend on their corresponding modules
being present and connected to the current backend. A native compiler
build alone does not verify every web-workbench feature.

The optimization exercises include constant folding, constant
propagation, common-subexpression elimination (CSE), and dead-code
elimination (DCE), where those modules are implemented and enabled.

## Architecture and source files

The project has a native compiler toolchain and a web application.
Principal paths are shown below; optional files can vary by repository
version.

``` text
compiler-design-project/
├── lexer.l                  # Flex lexical rules and token recognition
├── parser.y                 # Bison grammar, semantic actions, TAC/backpatching
├── Makefile                 # Native compiler build targets
├── launch_studio.bat        # Optional Windows launcher, if included
├── compiler                 # Generated executable (created by make; do not commit)
├── lex.yy.c                 # Generated Flex source
├── parser.tab.c             # Generated Bison parser source
├── parser.tab.h             # Generated Bison token/header file
├── backend/
│   ├── server.py            # Python web/API server
│   └── compiler_core.py     # Python-side compiler integration, if included
├── frontend/
│   ├── package.json         # Frontend dependencies and npm scripts
│   ├── src/                 # React/TypeScript application source
│   └── ...                  # Build configuration and public assets
├── tests/                   # Automated tests, if included
├── test_nested.c            # Example/regression input, if included
├── test_if_else.c           # Example/regression input, if included
├── test_for_loops.c         # Example/regression input, if included
├── test_infinite.c          # Step-limit test, if included
└── test_optimizable.c       # Optimization example, if included
```

  -----------------------------------------------------------------------
  Component                           Responsibility
  ----------------------------------- -----------------------------------
  `lexer.l`                           Recognizes keywords, identifiers,
                                      numbers, strings, operators, and
                                      punctuation; returns tokens to
                                      Bison.

  `parser.y`                          Defines grammar and semantic
                                      actions; emits TAC/quadruples and
                                      uses backpatching to resolve
                                      control-flow destinations.

  `Makefile`                          Runs Bison and Flex and compiles
                                      generated C files with GCC.

  `backend/server.py`                 Starts the Python HTTP/API server
                                      used by the web application.

  `backend/compiler_core.py`          Python-side compilation and
                                      analysis integration, where
                                      present.

  `frontend/`                         React and TypeScript source for the
                                      browser-based workbench.

  `launch_studio.bat`                 Optional convenience launcher, if
                                      included and configured.
  -----------------------------------------------------------------------

Generated files such as `lex.yy.c`, `parser.tab.c`, `parser.tab.h`, and
the `compiler` executable are build outputs and are regenerated by the
build process.

## Supported language

The source language is intentionally small and C-like.

  ------------------------------------------------------------------------------------------------
  Construct               Example                                          Notes
  ----------------------- ------------------------------------------------ -----------------------
  Assignment              `x = 5;`                                         Assignment to a
                                                                           variable.

  Arithmetic              `z = x + y * 2;`                                 Operators and
                                                                           precedence are defined
                                                                           by the grammar.

  Numeric output          `print(x);`                                      Prints an expression's
                                                                           value.

  String output           `print("hello");`                                Supported by the native
                                                                           grammar where string
                                                                           output is enabled.

  Conditional             `if (x < 5) { print(x); }`                       Conditional execution.

  Two-way conditional     `if (x == 1) { print(1); } else { print(0); }`   `if-else` branching.

  `while` loop            `while (x < 5) { x = x + 1; }`                   Condition-controlled
                                                                           iteration.

  `for` loop              `for (i = 0; i < 5; i = i + 1) { print(i); }`    Assignment-based
                                                                           initialization and
                                                                           step.

  `switch-case`           `switch (x) { case 1: print(10); break; }`       Integer selector and
                                                                           integer case constants.

  `default`               `default: print(0);`                             Optional fallback case.

  `break`                 `break;`                                         Implemented for exiting
                                                                           a switch; do not assume
                                                                           general loop-break
                                                                           support without
                                                                           testing.

  Block                   `{ x = 1; print(x); }`                           Groups statements.
  ------------------------------------------------------------------------------------------------

The exact accepted operators, precedence, and syntax are determined by
`parser.y` and `lexer.l`. Do not assume support for declarations,
arrays, functions, pointers, floating-point types, increment operators
such as `i++`, or all standard C syntax.

Not currently part of the documented language subset: - `do-while` -
`continue` - Function definitions and `return` - Source-level labels and
`goto` - C-style switch fall-through - General-purpose C compatibility

## Grammar overview

The authoritative grammar is in `parser.y`; lexer rules are in
`lexer.l`. The following is a high-level grammar sketch to explain the
supported constructs, not a replacement for the exact Bison grammar:

``` bnf
program         ::= statement_list
statement_list  ::= statement_list statement | statement
statement       ::= assignment
                  | print_statement
                  | if_statement
                  | while_statement
                  | for_statement
                  | switch_statement
                  | block
assignment      ::= IDENTIFIER "=" expression ";"
print_statement ::= "print" "(" expression ")" ";"
                  | "print" "(" STRING_LITERAL ")" ";"
if_statement    ::= "if" "(" condition ")" statement
                  | "if" "(" condition ")" statement "else" statement
while_statement ::= "while" "(" condition ")" statement
for_statement  ::= "for" "(" assignment_part ";" condition ";"
                   assignment_part ")" statement
switch_statement ::= "switch" "(" expression ")" "{"
                     case_list default_part "}"
case_list       ::= case_list case_clause | empty
case_clause     ::= "case" INTEGER_LITERAL ":" statement_list
default_part    ::= "default" ":" statement_list | empty
block           ::= "{" statement_list "}"
```

In the current switch implementation, case labels are integer literals
and `break;` exits the switch. Consult `parser.y` for the exact
productions and semantic-action details. The `for` syntax uses explicit
assignments such as `i = i + 1`, rather than `i++`.

## How compilation works

1.  **Lexical analysis:** Flex returns tokens such as `IF`, `WHILE`,
    `SWITCH`, `CASE`, `DEFAULT`, `BREAK`, identifiers, literals,
    operators, and punctuation.
2.  **Syntax analysis:** Bison checks the token stream against the
    grammar in `parser.y`.
3.  **Syntax-directed translation:** Semantic actions emit intermediate
    instructions as the parser recognizes statements and expressions.
4.  **Backpatching:** Unresolved conditional and unconditional jump
    destinations are recorded in lists and filled when the target
    becomes known. The core operations are `makelist()`, `merge()`, and
    `backpatch()`.
5.  **Intermediate representation:** The compiler emits TAC and a
    quadruple table; other representations and analysis views are
    available where implemented.
6.  **Execution:** The native compiler's TAC interpreter follows
    generated jump targets, prints program output, and reports the final
    variable store. The web workbench may provide additional inspection
    or step-through features when connected to the corresponding backend
    modules.

A conditional statement can be translated before its destination
instruction is known. The compiler records the unresolved jump in a
list; once the destination is known, `backpatch()` fills in the
instruction number. This is useful for `if-else`, loops, and switch
dispatch.

## Requirements

For native compilation on Windows, use **WSL2 with Ubuntu**. Installing
tools only in Windows CMD is not sufficient unless their Windows
executables are also installed and on `PATH`.

-   Windows 10/11.
-   WSL2 with Ubuntu.
-   GCC, Make, Flex, and Bison inside Ubuntu.
-   Python 3.10 or later.
-   Node.js 18 or later and npm.
-   Git, if cloning the repository.

## Get the project onto your PC

### Option A --- Clone from GitHub

1.  Install Git for Windows if needed.
2.  Open CMD or PowerShell.
3.  Replace the placeholders below with the actual GitHub owner and
    repository name:

``` powershell
cd $HOME\Documents
git clone https://github.com/<YOUR-USERNAME>/<YOUR-REPOSITORY>.git
cd <YOUR-REPOSITORY>
```

Do not type the angle brackets as part of the URL or folder name.

### Option B --- Download a ZIP

1.  Open the repository page on GitHub.
2.  Select **Code → Download ZIP**.
3.  Extract it to a simple path, for example
    `C:\Users\<YOUR-WINDOWS-USERNAME>\Documents\compiler-design-project`.
4.  Open a terminal in the extracted project root.

Replace the example username and path with your actual folder location.

## Build and run on Windows with WSL2

### 1. Install WSL2 and Ubuntu

If WSL2 is not already installed, open PowerShell as Administrator and
run:

``` powershell
wsl --install
```

Restart if requested, open Ubuntu, and complete its first-run setup. If
WSL is already installed, open the existing Ubuntu distribution.

### 2. Install native build tools

In the **Ubuntu/WSL terminal**, run:

``` bash
sudo apt update
sudo apt install -y build-essential flex bison make
```

Confirm the tools are available:

``` bash
gcc --version
make --version
flex --version
bison --version
```

### 3. Navigate to the project

For a project on the Windows `C:` drive, WSL mounts the drive at
`/mnt/c`.

For example, if the project is at
`C:\Users\YOUR-WINDOWS-USERNAME\Documents\compiler-design-project`, run
this in Ubuntu:

``` bash
cd /mnt/c/Users/YOUR-WINDOWS-USERNAME/Documents/compiler-design-project
```

Replace the example username and path with the location where you cloned
or extracted the project. You should be in the directory containing
`Makefile`, `lexer.l`, and `parser.y`.

### 4. Build the compiler

``` bash
make clean
make
```

The Makefile should run Bison, Flex, and GCC to generate the
parser/lexer sources and native executable. A successful build ends
without a Bison, Flex, or GCC error and creates the `compiler`
executable in the project root.

To run the same build from Windows CMD, substitute your actual path in
WSL format:

``` bat
wsl bash -c "cd /mnt/c/Users/YOUR-WINDOWS-USERNAME/Documents/compiler-design-project && make clean && make"
```

If `bison`, `flex`, or `gcc` is not recognized in Windows CMD but is
installed in WSL, that is expected. Run the tools inside Ubuntu or
prefix the command with `wsl bash -c`.

## Run the web application

The following assumes the repository contains `backend/server.py` and
`frontend/package.json`.

### 1. Install Python dependencies

From the project root, create and activate a virtual environment:

``` bat
python -m venv .venv
.venv\Scripts\activate
python -m pip install --upgrade pip
```

If the repository contains `requirements.txt`, install its dependencies:

``` bat
python -m pip install -r requirements.txt
```

Otherwise, for the known Flask-based backend dependencies:

``` bat
python -m pip install flask flask-cors
```

Use the dependency file if one is included and describes the backend
requirements.

### 2. Install and build the frontend

Open a second terminal in the project root:

``` bat
cd frontend
npm install
npm run build
```

If `package.json` defines a development command such as `npm run dev`,
use the scripts listed in that file.

### 3. Start the backend

From the project root, with the Python virtual environment activated:

``` bat
python backend/server.py
```

Keep the terminal open while using the application.

### 4. Open the application

If the server reports that it is listening on port `5000`, open:

``` text
http://127.0.0.1:5000
```

Use the port shown by the server and its configuration. If
`launch_studio.bat` is included and configured for your environment, it
may provide a convenience launch path.

## Run a source program with the native compiler

Create a file named `switch_test.txt` in the project root:

``` c
x = 2;

switch (x) {
    case 1:
        print(10);
        break;
    case 2:
        print(20);
        break;
    default:
        print(0);
}

print(99);
```

Build first, then run the executable from WSL:

``` bash
./compiler < switch_test.txt
```

Or run from Windows CMD using your actual project path converted to
`/mnt/c/...`:

``` bat
wsl bash -c "cd /mnt/c/Users/YOUR-WINDOWS-USERNAME/Documents/compiler-design-project && ./compiler < switch_test.txt"
```

Expected runtime output for this example:

``` text
OUTPUT: 20
OUTPUT: 99
```

The compiler also prints intermediate-code/backpatching information and
the final variable memory state. Exact formatting depends on the current
executable and its command-line options.

## Example: switch-case

The native compiler's tested example demonstrates this flow:

``` c
x = 2;
switch (x) {
    case 1:
        print(10);
        break;
    case 2:
        print(20);
        break;
    default:
        print(0);
}
print(99);
```

Conceptually, dispatch is translated into comparisons and jumps similar
to:

``` text
if x == 1 goto CASE_1
if x == 2 goto CASE_2
goto DEFAULT

CASE_1:
    print 10
    goto SWITCH_END

CASE_2:
    print 20
    goto SWITCH_END

DEFAULT:
    print 0
    goto SWITCH_END

SWITCH_END:
    print 99
```

The actual TAC uses numbered labels and quadruple indices. With `x = 2`,
the selected body prints `20`, then execution continues after the switch
and prints `99`.

## Intermediate representations and analysis

### Three-Address Code (TAC)

TAC breaks expressions and control flow into small instructions. Labels
and jumps make branching and loops explicit.

### Quadruples

A quadruple records an operation and its operands/result:

  -----------------------------------------------------------------------
  Field                               Meaning
  ----------------------------------- -----------------------------------
  `op`                                Operation, such as assignment,
                                      arithmetic, comparison, print, or
                                      jump.

  `arg1`                              First operand, if required.

  `arg2`                              Second operand, if required.

  `result`                            Destination variable or branch
                                      target, depending on the operation.
  -----------------------------------------------------------------------

### Triples and indirect triples

Where enabled, triples refer to instruction operands by instruction
position, while indirect triples use a separate pointer/order table.
Check the current frontend/backend implementation to determine which
representations are available in a given build.

### Control-flow graph

A CFG represents basic blocks as nodes and possible control transfers as
directed edges. If the CFG module is enabled, it can help inspect
branching, loop back-edges, and basic-block structure.

### Optimization

The workbench's optimization exercises include constant folding,
constant propagation, common-subexpression elimination, and dead-code
elimination, where those modules are implemented and enabled. Compare
original and transformed instructions when the corresponding module is
available.

### Virtual execution, liveness, and register allocation

The workbench design includes execution inspection and analysis of
variable usage. Where implemented, stepping through execution helps
explain state changes; liveness analysis estimates when values are still
needed; and graph-coloring register allocation models assignment of live
values to a limited number of registers.

## Testing and troubleshooting

### Native build

From WSL, in the project root:

``` bash
make clean
make
```

If Bison says a symbol such as `COLON` is not defined, check that it is
declared in `parser.y` and that `lexer.l` returns the token for the
corresponding character.

### `bison`, `flex`, or `gcc` is not recognized in Windows CMD

If the tools were installed inside Ubuntu/WSL, invoke them there:

``` bat
wsl bash -c "cd /mnt/c/PATH/TO/PROJECT && make clean && make"
```

Replace `/mnt/c/PATH/TO/PROJECT` with the actual WSL path.

### `make: command not found`

Install build tools in Ubuntu:

``` bash
sudo apt update
sudo apt install -y build-essential flex bison make
```

### Python module errors

Activate the virtual environment and install the backend dependencies or
repository dependency file. Use the same Python environment when
starting the server.

### Frontend command errors

Check Node.js and npm:

``` bat
node --version
npm --version
```

Run `npm install` from the directory containing `package.json`, usually
`frontend/`.

### Switch program output is wrong

Rebuild after editing the grammar or lexer:

``` bash
make clean
make
```

Then rerun the source test. Inspect both TAC jump targets and runtime
output. A successful native build does not prove that the web frontend
is using the same updated switch implementation.

### Suggested regression programs

If these files are included in the repository, use them to check
existing constructs:

-   `test_nested.c` --- nested-loop behavior.
-   `test_if_else.c` --- conditional branching.
-   `test_for_loops.c` --- assignment-based `for` loops.
-   `test_infinite.c` --- execution step-limit protection.
-   `test_optimizable.c` --- optimization examples.

A useful manual switch test matrix is: 1. A matching first case. 2. A
matching later case. 3. A selector matching no case when `default`
exists. 4. A selector matching no case when there is no `default`. 5.
Duplicate case constants. 6. `break` outside a switch. 7. Nested
switches and switches inside loops.

Record observed results instead of assuming every edge case passes.

## Limitations and future work

Compiler Studio is an educational compiler for a limited source
language. It is not a standards-compliant C compiler and does not claim
every language control-flow feature. Useful future work includes
expanding automated tests for switch dispatch and nesting, aligning
native and Python/web compilation behavior, extending `break` to loops
if desired, adding `continue` and `do-while`, and verifying that all IR,
CFG, optimization, and execution views remain consistent after language
features are added.

## Author and academic context

Developed as a Compiler Design Lab project for BCSE307P, focused on
structured control flow, three-address code generation, and
backpatching.

**Author:** Asmin Sinha
