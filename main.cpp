#include <iostream>
#include "BulkProcessor.h"
#include <string>

/**
 * @brief Точка входа в программу.
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <block_size>" << std::endl;
        return 1;
    }
    size_t block_size = std::stoul(argv[1]);
    auto consoleOutputter = std::make_shared<ConsoleOutputter>();
    auto fileOutputter = std::make_shared<FileOutputter>();
    std::vector<std::shared_ptr<IOutputter>> outputters = { consoleOutputter, fileOutputter };
    BulkProcessor processor(block_size, outputters);
    std::string command;
    while (std::getline(std::cin, command)) {
        if (command == "EOF") {
            processor.finalize();
            break;
        }
        processor.process(command);
    }
    processor.finalize();
    return 0;
}