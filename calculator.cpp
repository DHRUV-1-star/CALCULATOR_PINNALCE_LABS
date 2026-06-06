/*
 * ============================================================
 *   Pinnacle Labs — Console Calculator
 *   Features:
 *     + Basic arithmetic  (+ - * /)
 *     + Power             (^)
 *     + Square root       (sqrt)
 *     + Modulo            (%)
 *     + Calculation history
 *     + Error handling    (division by zero, invalid input)
 * ============================================================
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

// ── ANSI colour helpers ────────────────────────────────────────
#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#else
void enableANSI() {}
#endif

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"

// Foreground colours
#define FG_CYAN    "\033[96m"
#define FG_GREEN   "\033[92m"
#define FG_YELLOW  "\033[93m"
#define FG_RED     "\033[91m"
#define FG_WHITE   "\033[97m"
#define FG_MAGENTA "\033[95m"
#define FG_BLUE    "\033[94m"

// Background accents
#define BG_DARK    "\033[40m"

// ── Utility ────────────────────────────────────────────────────
void printLine(char ch = '-', int width = 52) {
    std::cout << FG_BLUE << std::string(width, ch) << RESET << "\n";
}

void printHeader() {
    std::cout << "\n";
    printLine('=');
    std::cout << FG_CYAN << BOLD
              << "   ██████╗ ██████╗ ██╗      ██████╗\n"
              << "  ██╔════╝██╔══██╗██║     ██╔════╝\n"
              << "  ██║     ███████║██║     ██║     \n"
              << "  ██║     ██╔══██║██║     ██║     \n"
              << "  ╚██████╗██║  ██║███████╗╚██████╗\n"
              << "   ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝\n"
              << RESET;
    std::cout << FG_MAGENTA << BOLD
              << "        Pinnacle Labs  |  C++ Calculator\n"
              << RESET;
    printLine('=');
    std::cout << "\n";
}

void printMenu() {
    std::cout << FG_YELLOW << BOLD << "  Operations Available:\n" << RESET;
    std::cout << FG_WHITE
              << "  " << FG_GREEN << "[+]" << FG_WHITE << "  Addition          "
              << FG_GREEN << "[-]" << FG_WHITE << "  Subtraction\n"
              << "  " << FG_GREEN << "[*]" << FG_WHITE << "  Multiplication    "
              << FG_GREEN << "[/]" << FG_WHITE << "  Division\n"
              << "  " << FG_GREEN << "[^]" << FG_WHITE << "  Power             "
              << FG_GREEN << "[%]" << FG_WHITE << "  Modulo\n"
              << "  " << FG_GREEN << "[s]" << FG_WHITE << "  Square Root       "
              << FG_GREEN << "[h]" << FG_WHITE << "  History\n"
              << "  " << FG_GREEN << "[c]" << FG_WHITE << "  Clear History     "
              << FG_GREEN << "[q]" << FG_WHITE << "  Quit\n"
              << RESET;
    printLine();
}

// ── History ────────────────────────────────────────────────────
struct Record {
    std::string expression;
    double      result;
};

std::vector<Record> history;

void addHistory(const std::string& expr, double result) {
    history.push_back({expr, result});
}

void showHistory() {
    printLine('=');
    std::cout << FG_CYAN << BOLD << "  Calculation History\n" << RESET;
    printLine('-');
    if (history.empty()) {
        std::cout << FG_YELLOW << "  No calculations yet.\n" << RESET;
    } else {
        for (size_t i = 0; i < history.size(); ++i) {
            std::cout << FG_WHITE << "  " << std::setw(2) << (i + 1) << ".  "
                      << FG_CYAN   << std::setw(28) << std::left << history[i].expression
                      << FG_WHITE  << " = "
                      << FG_GREEN  << BOLD << history[i].result
                      << RESET << "\n";
        }
    }
    printLine('=');
}

// ── Input helpers ──────────────────────────────────────────────
double getNumber(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << FG_YELLOW << "  " << prompt << RESET << " ";
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << FG_RED << "  ✗  Invalid number. Please try again.\n" << RESET;
    }
}

// ── Core calculation ───────────────────────────────────────────
void doOperation(char op) {
    double a, b, result;
    std::ostringstream expr;

    if (op == 's') {
        // Square root — single operand
        a = getNumber("Enter number:");
        if (a < 0) {
            std::cout << FG_RED << "  ✗  Cannot take square root of a negative number.\n" << RESET;
            return;
        }
        result = std::sqrt(a);
        expr << "sqrt(" << a << ")";
    } else {
        a = getNumber("Enter first number :");
        b = getNumber("Enter second number:");

        switch (op) {
            case '+':
                result = a + b;
                expr << a << " + " << b;
                break;
            case '-':
                result = a - b;
                expr << a << " - " << b;
                break;
            case '*':
                result = a * b;
                expr << a << " * " << b;
                break;
            case '/':
                if (b == 0) {
                    std::cout << FG_RED << "  ✗  Error: Division by zero is undefined.\n" << RESET;
                    return;
                }
                result = a / b;
                expr << a << " / " << b;
                break;
            case '^':
                result = std::pow(a, b);
                expr << a << " ^ " << b;
                break;
            case '%': {
                if (b == 0) {
                    std::cout << FG_RED << "  ✗  Error: Modulo by zero is undefined.\n" << RESET;
                    return;
                }
                // Support floating-point modulo
                result = std::fmod(a, b);
                expr << a << " % " << b;
                break;
            }
            default:
                std::cout << FG_RED << "  ✗  Unknown operation.\n" << RESET;
                return;
        }
    }

    // Display result
    printLine();
    std::cout << FG_WHITE << "  Expression : " << FG_CYAN  << expr.str()         << "\n"
              << FG_WHITE << "  Result     : " << FG_GREEN << BOLD
              << std::fixed << std::setprecision(6) << result << RESET << "\n";
    printLine();

    addHistory(expr.str(), result);
}

// ── Main ───────────────────────────────────────────────────────
int main() {
    enableANSI();
    printHeader();
    printMenu();

    std::string input;
    while (true) {
        std::cout << FG_MAGENTA << BOLD << "\n  > Choose operation: " << RESET;
        if (!std::getline(std::cin, input)) break;

        // Trim whitespace
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);

        if (input.empty()) { printMenu(); continue; }

        char choice = static_cast<char>(std::tolower(static_cast<unsigned char>(input[0])));

        if (choice == 'q') {
            printLine('=');
            std::cout << FG_CYAN << BOLD
                      << "  Thank you for using Pinnacle Labs Calculator!\n"
                      << RESET;
            printLine('=');
            break;
        }

        if (choice == 'h') { showHistory(); continue; }

        if (choice == 'c') {
            history.clear();
            std::cout << FG_GREEN << "  ✓  History cleared.\n" << RESET;
            continue;
        }

        // Map to supported ops
        static const std::string validOps = "+-*/^%s";
        if (validOps.find(choice) == std::string::npos) {
            std::cout << FG_RED << "  ✗  Invalid choice. Press Enter to see the menu.\n" << RESET;
            continue;
        }

        doOperation(choice);
    }

    return 0;
}
