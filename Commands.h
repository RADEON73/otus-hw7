#pragma once
#include "bulkProcessor.h"

/**
 * @class ICommand
 * @brief ��������� ��� ���� ������.
 *
 * ��������� ICommand ���������� ����� execute, ������� ������ ���� ����������
 * ����� �������� ������.
 */
class ICommand
{
public:
    virtual ~ICommand() = default;
    /**
    * @brief ��������� �������.
    * @param processor ������ BulkProcessor, ������� ����� ������������ �������.
    */
    virtual void execute(BulkProcessor& processor) = 0;
};

/**
 * @class StartBlockCommand
 * @brief ������� ��� ������ ������ ������������� �����.
 *
 * ����� StartBlockCommand ��������� ������� ������ ������ ������������� �����.
 */
class StartBlockCommand : public ICommand
{
public:
    void execute(BulkProcessor& processor) override {
        processor.startBlock();
    }
};

/**
 * @class EndBlockCommand
 * @brief ������� ��� ���������� �������� ������������� �����.
 *
 * ����� EndBlockCommand ��������� ������� ���������� �������� ������������� �����.
 */
class EndBlockCommand : public ICommand
{
public:
    void execute(BulkProcessor& processor) override {
        processor.endBlock();
    }
};

/**
 * @class RegularCommand
 * @brief ������� ��� ���������� ������� ������� � ����.
 *
 * ����� RegularCommand ��������� ������� ���������� ������� ������� � ������� ����.
 */
class RegularCommand : public ICommand
{
public:
    /**
 * @brief ����������� ������ RegularCommand.
 * @param command ������� ��� ����������.
 */
    explicit RegularCommand(const std::string& command) : command_(command) {}

    void execute(BulkProcessor& processor) override {
        processor.addCommand(command_);
    }

private:
    std::string command_; ///< ������� ��� ����������.
};