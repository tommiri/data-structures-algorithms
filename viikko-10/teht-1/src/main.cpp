#include <iostream>
#include <string>
#include <limits>

#include "../include/Stack.h"

char getCommand();

bool executeCommand(char command, Stack &stack);

void introduction();

void instructions();

bool getStackTop(Stack &stack, double &value);

bool getStackValues(Stack &stack, double &num1, double &num2);

void attemptPush(Stack &stack, double value);

double getStackSum(Stack &stack);

using std::cout, std::cin, std::tolower, std::string;

int main()
{
    Stack numbers;
    introduction();
    instructions();
    while (executeCommand(getCommand(), numbers))
    {
    }

    return EXIT_SUCCESS;
}

char getCommand()
{
    char command;
    string validCommands = "?=+-*/xsaq";
    bool isValidCmd = false;

    while (!isValidCmd)
    {
        cout << "Select command and press <Enter>: ";
        cin >> command;
        command = tolower(command);
        isValidCmd = validCommands.find(command) != string::npos;

        if (!isValidCmd)
        {
            cout << "Please enter a valid command:\n";
            instructions();
        }
    }

    return command;
}

bool executeCommand(char command, Stack &stack)
{
    double num1, num2;

    switch (command)
    {
        case '?':
        {
            double userInput{};
            for (;;)
            {
                cout << "Enter a real number: ";
                if (cin >> userInput)
                {
                    break;
                }
                else
                {
                    cout << "ERROR: Invalid input\n";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            attemptPush(stack, userInput);
            break;
        }

        case '=':
        {
            if (getStackTop(stack, num1))
            {
                cout << num1 << '\n';
            }
            break;
        }

        case '+':
        {
            if (getStackValues(stack, num1, num2))
            {
                attemptPush(stack, num1 + num2);
            }
            break;
        }

        case '-':
        {
            if (getStackValues(stack, num1, num2))
            {
                attemptPush(stack, num2 - num1);
            }
            break;
        }

        case '*':
        {
            if (getStackValues(stack, num1, num2))
            {
                attemptPush(stack, num1 * num2);
            }
            break;
        }

        case '/':
        {
            if (getStackValues(stack, num1, num2))
            {
                attemptPush(stack, num2 / num1);
            }
            break;
        }

        case 'x':
        {
            if (getStackValues(stack, num1, num2))
            {
                attemptPush(stack, num1);
                attemptPush(stack, num2);
            }
            break;
        }

        case 's':
        {
            double sum = getStackSum(stack);
            stack.push(sum);
            break;
        }

        case 'a':
        {
            double count = stack.size();
            double sum = getStackSum(stack);
            stack.push(sum / count);
            break;
        }

        case 'q':
        {
            cout << "Calculation finished.\n";
            return false;
        }

        default:
        {
            cout << "UNEXPECTED ERROR: Exiting program...\n";
            return false;
        }
    }
    return true;
}

void introduction()
{
    cout << "Welcome to Tommi's Postfix Calculator!\n";
}

void instructions()
{
    cout << "\nUsage instructions\n"
            "------------------------------------\n"
            "[?] Push to stack   [=] Print top    [x] Exchange values\n"
            "[s] Calculate sum  [a] Calculate average\n"
            "[+] [-] [*] [/]    Arithmetic operations\n"
            "[h] Print these instructions\n"
            "[q] Exit\n"
            "------------------------------------\n\n";
}

bool getStackTop(Stack &stack, double &value)
{
    if (stack.top(value) == underflow)
    {
        cout << "Stack empty\n";
        return false;
    }

    return true;
}

bool getStackValues(Stack &stack, double &num1, double &num2)
{
    if (!getStackTop(stack, num1))
    {
        return false;
    }
    stack.pop();

    if (stack.top(num2) == underflow)
    {
        cout << "Stack has just one entry\n";
        stack.push(num1);
        return false;
    }
    stack.pop();

    return true;
}

void attemptPush(Stack &stack, double value)
{
    if (stack.push(value) == overflow)
    {
        cout << "Warning: Stack full, lost result\n";
    }
}

double getStackSum(Stack &stack)
{
    double sum{}, value{};

    while (!stack.empty())
    {
        stack.top(value);
        stack.pop();
        sum += value;
    }

    return sum;
}
