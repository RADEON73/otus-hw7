#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

/**
 * @brief ��������� ��� ������ ������.
 * ��������� IOutputter ���������� ����� output, ������� ������ ���� ����������
 * ����� ��������, ����������� �� ����� ������.
 */
class IOutputter
{
public:
    virtual ~IOutputter() = default;

    /**
     * @brief ������� ������.
     * @param commands ������ ������ ��� ������.
     * @param timestamp ��������� �����, ������������ ��� ������������� ����� ������.
     */
    virtual void output(const std::vector<std::string>& commands, time_t timestamp) = 0;
};

/**
 * @brief ����� ��� ������ ������ � �������.
 * ����� ConsoleOutputter ��������� ��������� IOutputter � ������� ������ � �������.
 */
class ConsoleOutputter : public IOutputter
{
public:
    /**
     * @brief ������� ������ � �������.
     *
     * @param commands ������ ������ ��� ������.
     * @param timestamp ��������� �����, ������������ ��� ������������� ����� ������.
     */
    void output(const std::vector<std::string>& commands, time_t timestamp) override {
        std::cout << "bulk: ";
        for (size_t i = 0; i < commands.size(); ++i) {
            std::cout << commands[i];
            if (i < commands.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
};

/**
 * @brief ����� ��� ������ ������ � ����.
 * ����� FileOutputter ��������� ��������� IOutputter � ������� ������ � ����.
 * ���� ��������� � ���������� "LOG" � ������, ���������� ��������� �����.
 */
class FileOutputter : public IOutputter
{
public:
    /**
     * @brief ������� ������ � ����.
     * @param commands ������ ������ ��� ������.
     * @param timestamp ��������� �����, ������������ ��� ������������� ����� ������.
     */
    void output(const std::vector<std::string>& commands, time_t timestamp) override {
        std::filesystem::path logDir = "LOG";
        if (!std::filesystem::exists(logDir)) {
            std::filesystem::create_directory(logDir);
        }
        std::stringstream filename;
        filename << "bulk" << timestamp << ".log";
        std::filesystem::path filePath = logDir / filename.str();
        std::ofstream file(filePath, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            return;
        }
        file << "bulk: ";
        for (size_t i = 0; i < commands.size(); ++i) {
            file << commands[i];
            if (i < commands.size() - 1)
                file << ", ";
        }
        file << std::endl;
    }
};