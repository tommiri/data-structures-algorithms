#include <stack>
#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream file("./example.txt");
    std::string line{};
    std::stack<char> characters{};

    if (!file)
    {
        std::cout << "Error opening file.\n";
        return EXIT_FAILURE;
    }

    getline(file, line);

    for (const char &c: line)
    {
        characters.push(c);
    }

    std::string reverseStr{};
    while (!characters.empty())
    {
        reverseStr.push_back(characters.top());
        characters.pop();
    }

    std::ofstream reversed_file("./reversed_example.txt");
    reversed_file << reverseStr << "\n";

    file.close();
    reversed_file.close();
    return EXIT_SUCCESS;
}