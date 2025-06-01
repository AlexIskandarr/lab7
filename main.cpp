#include <iostream>
#include <string>
#include <stdexcept> 


bool isDigitWord(const std::string& word);
void checkEmptyInput(const std::string& input);
std::string processInput(const std::string& input);

int main() {
    try {
        std::string input;
        std::cout << "enter text: ";
        std::getline(std::cin, input);
        
        checkEmptyInput(input);
        std::string result = processInput(input);
        std::cout << "result: " << result << '\n';
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

bool isDigitWord(const std::string& word) {
    for (char c : word) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

void checkEmptyInput(const std::string& input) {
    if (input.empty() || input.find_first_not_of(' ') == std::string::npos) {
        throw std::runtime_error("Input is empty or contains only spaces");
    }
}

std::string processInput(const std::string& input) {
    std::string result;   
    std::string remaining;      
    size_t start {};
    size_t end {input.find(' ')};
    bool expect_digit {true};
    bool digit_found {false};

    while (true) {
        std::string word;
        if (end == std::string::npos) {
            word = input.substr(start);
        } else {
            word = input.substr(start, end - start);
        }

        if (!word.empty()) {
            bool is_digit = isDigitWord(word);

            if (is_digit) {
                digit_found = true;
            }

            if (expect_digit) {
                if (is_digit) {
                    if (!result.empty()) {
                        result += ' ';
                    }
                    result += word;
                    expect_digit = false;
                } else {
                    if (!remaining.empty()) {
                        remaining += ' ';
                    }
                    remaining += word;
                }
            } else {
                if (!is_digit) {
                    if (!result.empty()) {
                        result += ' ';
                    }
                    result += word;
                    expect_digit = true;
                } else {
                    if (!remaining.empty()) {
                        remaining += ' ';
                    }
                    remaining += word;
                }
            }
        }

        if (end == std::string::npos) {
            break;
        }
        start = end + 1;
        end = input.find(' ', start);
    }

    if (!digit_found) {
        throw std::runtime_error("No digit words found in input");
    }

    if (!remaining.empty()) {
        if (!result.empty()) {
            result += ' ';
        }
        result += remaining;
    }

    return result;
}