#pragma once
#include <string>
#include <vector>
#include "Outputters.h"

/**
 * @class BulkProcessor
 * @brief Обрабатывает команды и управляет блоками команд.
 *
 * Класс BulkProcessor предназначен для обработки команд, группировки их в блоки
 * и выполнения операций над этими блоками, таких как вывод на экран и логирование.
 */
class BulkProcessor
{
public:
	/**
	* @brief Конструктор класса BulkProcessor.
	* @param block_size Размер блока команд.
	*/
	explicit BulkProcessor(size_t block_size, std::vector<std::shared_ptr<IOutputter>> outputters)
		: block_size_(block_size), outputters_(std::move(outputters)) {
	}

	/**
	* @brief Обрабатывает команду.
	* @param command Команда для обработки.
	*/
	void process(const std::string& command);
	/**
	* @brief Завершает обработку команд и выполняет финализацию.
	*/
	void finalize();

	/**
	* @brief Начинает новый динамический блок команд.
	*/
	void startBlock();

	/**
	* @brief Завершает текущий динамический блок команд.
	*/
	void endBlock();

	/**
	* @brief Добавляет команду в текущий блок.
	* @param command Команда для добавления.
	*/
	void addCommand(const std::string& command);

private:
	/**
	* @brief Сбрасывает текущий блок, выводя и логируя его содержимое.
	*/
	void flush();

	/**
	* @struct Block
	* @brief Структура, представляющая блок команд.
	*/
	struct Block
	{
		/**
		* @brief Сбрасывает блок, очищая его данные и сбрасывая флаги.
		*/
		void reset();

		std::vector<std::string> data; ///< Вектор команд в блоке.
		bool is_dynamic{ false }; ///< Флаг, указывающий, является ли блок динамическим.
		size_t depth{ 0 }; ///< Глубина вложенности блоков.
		time_t createTimeStamp{ 0 }; ///< Время создания блока
	};

	size_t block_size_; ///< Размер блока команд.
	Block current_block_; ///< Текущий блок команд.
	std::vector<std::shared_ptr<IOutputter>> outputters_; ///< Обработчики вывода информации
};