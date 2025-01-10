
# **POCD Compiler**

## **Overview**  
The Compiler is a group project aimed at building a simple compiler capable of evaluating mathematical expressions. This project is implemented using **Flex** and **Bison**, with additional features such as custom functions, variable handling, and enhanced error reporting.

---

## **Features**
- **Basic Arithmetic**: Addition, subtraction, multiplication, and division.  
- **Operator Precedence**: Correct handling of precedence rules (e.g., `*` over `+`).  
- **Parentheses**: Support for grouping operations (e.g., `(2 + 3) * 4`).  
- **Variables**: Assign and use variables in expressions.  
- **Floating-Point Arithmetic**: Handles decimal values (e.g., `3.14`).  
- **Exponentiation**: Supports operations like `2^3`.  
- **Unary Operators**: Handles unary `+` and `-` (e.g., `-5`).  
- **Custom Functions**: Built-in functions like `sin`, `cos`, and `sqrt`.  
- **User-Defined Functions**: Define and call simple functions.  
- **Enhanced Error Reporting**: Clear messages for syntax and runtime errors.  

---

## **Directory Structure**

```
PCD-Compiler/
├── README.md           # Project description and setup instructions.
├── .gitignore          # Ignore unnecessary files.
├── .vscode/            # VS Code configuration files.
├── docs/               # Documentation and flowcharts.
│   ├── flowcharts/     # Flowcharts for compiler stages.
│   ├── requirements.md # Detailed scope and requirements.
│   └── milestones.md   # Task assignments and progress tracking.
├── src/                # Source code for the compiler.
│   ├── lexer/          # Lexical analysis (Flex files).
│   ├── parser/         # Parsing logic (Bison files).
│   ├── evaluator/      # Semantic analysis and evaluation logic.
│   ├── error/          # Error handling utilities.
│   └── main.c          # Main entry point of the compiler.
├── tests/              # Test cases and input files.
│   ├── inputs/         # Sample input files for testing.
│   └── outputs/        # Expected output files.
├── build/              # Build outputs (binary, Flex/Bison-generated files).
└── Makefile            # Build instructions for the project.
```

---

## **Getting Started**

### **Prerequisites**
- GCC Compiler  
- Flex and Bison  
- Git  

### **Setup**
1. Clone the repository:  
   ```bash
   git clone https://github.com/<your-username>/PCD-Compiler.git
   cd PCD-Compiler
   ```

2. Build the compiler:  
   ```bash
   make
   ```

3. Test the compiler:  
   ```bash
   ./build/compiler < tests/inputs/test1.txt
   ```

---

## **Usage**
### Input Format
- Write expressions, assignments, or function calls in a text file. Example:  
  ```text
  a = 3 + 2 * (5 - 1)
  b = sqrt(a) + sin(30)
  result = a + b
  ```

- Run the compiler with the input file:  
  ```bash
  ./build/compiler < input.txt
  ```

---

## **Development Guide**
### Build Commands
- **Build the project**:  
  ```bash
  make
  ```
- **Clean build artifacts**:  
  ```bash
  make clean
  ```

- **Run tests**:  
  ```bash
  make test
  ```

### Debugging
- Use `gdb` or the VS Code debug configuration to troubleshoot the compiler.

---

## **Contributing**
1. Create a new branch for your feature:  
   ```bash
   git checkout -b feature-name
   ```
2. Commit your changes:  
   ```bash
   git commit -m "Add feature description"
   ```
3. Push the branch to GitHub:  
   ```bash
   git push origin feature-name
   ```
4. Open a pull request for review.

---

## **Authors**
- Yeabsira Mekonnen  
- Yeabsira G/Michael  
- Yeabsira Zelalem  
- Yetnayet Lakew  
- Yeabsira Fikadu  
- Yared Zenebe  
- Firaol Tesfaye  
- Teklu Moges  
- Yordanos Legesse  
- Zekarias Kumsa  

---

## **License**
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Let me know if you'd like further refinements!