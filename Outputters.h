#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

/**
 * @brief Интерфейс для вывода данных.
 * Интерфейс IOutputter определяет метод output, который должен быть реализован
 * всеми классами, отвечающими за вывод данных.
 */
class IOutputter
{
public:
	virtual ~IOutputter() = default;

	/**
	 * @brief Выводит данные.
	 * @param commands Вектор команд для вывода.
	 * @param timestamp Временная метка, используемая для идентификации блока команд.
	 */
	virtual void output(const std::vector<std::string>& commands, time_t timestamp) = 0;
};

/**
 * @brief Класс для вывода данных в консоль.
 * Класс ConsoleOutputter реализует интерфейс IOutputter и выводит данные в консоль.
 */
class ConsoleOutputter : public IOutputter
{
public:
	/**
	 * @brief Выводит данные в консоль.
	 *
	 * @param commands Вектор команд для вывода.
	 * @param timestamp Временная метка, используемая для идентификации блока команд.
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
 * @brief Класс для вывода данных в файл.
 * Класс FileOutputter реализует интерфейс IOutputter и выводит данные в файл.
 * Файл создается в директории "LOG" с именем, содержащим временную метку.
 */
class FileOutputter : public IOutputter
{
public:
	/**
	 * @brief Выводит данные в файл.
	 * @param commands Вектор команд для вывода.
	 * @param timestamp Временная метка, используемая для идентификации блока команд.
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