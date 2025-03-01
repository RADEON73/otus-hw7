#pragma once
#include <memory>
#include "Commands.h"

/**
 * @class CommandFactory
 * @brief ������� ��� �������� ������.
 *
 * ����� CommandFactory ������� ������� ������ �� ������ ������� ������.
 */
class CommandFactory
{
public:
    /**
 * @brief ������� ������� �� ������ ������� ������.
 * @param command ������� ������ �������.
 * @return ��������� �� ��������� �������.
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