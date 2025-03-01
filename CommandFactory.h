#pragma once
#include <memory>
#include "Commands.h"

/**
 * @class CommandFactory
 * @brief ‘абрика дл¤ создани¤ команд.
 *
 *  ласс CommandFactory создает объекты команд на основе входной строки.
 */
class CommandFactory
{
public:
    /**
 * @brief —оздает команду на основе входной строки.
 * @param command ¬ходна¤ строка команды.
 * @return ”казатель на созданную команду.
 */
    static std::unique_ptr<ICommand> create(const std::string& command) {
        if (command == "{") {
            return std::make_unique<StartBlockCommand>();
        }
        else if (command == "}") {
            return std::make_unique<EndBlockCommand>();
        }
        else {
            return std::make_unique<RegularCommand>(command);
        }
    }
};