#pragma once
#include <string>
#include <vector>
#include "Outputters.h"

/**
 * @class BulkProcessor
 * @brief ������������ ������� � ��������� ������� ������.
 *
 * ����� BulkProcessor ������������ ��� ��������� ������, ����������� �� � �����
 * � ���������� �������� ��� ����� �������, ����� ��� ����� �� ����� � �����������.
 */
class BulkProcessor
{
public:
	/**
	* @brief ����������� ������ BulkProcessor.
	* @param block_size ������ ����� ������.
	*/
	explicit BulkProcessor(size_t block_size, std::vector<std::shared_ptr<IOutputter>> outputters)
		: block_size_(block_size), outputters_(std::move(outputters)) {
	}

	/**
	* @brief ������������ �������.
	* @param command ������� ��� ���������.
	*/
	void process(const std::string& command);
	/**
	* @brief ��������� ��������� ������ � ��������� �����������.
	*/
	void finalize();

	/**
	* @brief �������� ����� ������������ ���� ������.
	*/
	void startBlock();

	/**
	* @brief ��������� ������� ������������ ���� ������.
	*/
	void endBlock();

	/**
	* @brief ��������� ������� � ������� ����.
	* @param command ������� ��� ����������.
	*/
	void addCommand(const std::string& command);

private:
	/**
	* @brief ���������� ������� ����, ������ � ������� ��� ����������.
	*/
	void flush();

	/**
	* @struct Block
	* @brief ���������, �������������� ���� ������.
	*/
	struct Block
	{
		/**
		* @brief ���������� ����, ������ ��� ������ � ��������� �����.
		*/
		void reset();

		std::vector<std::string> data; ///< ������ ������ � �����.
		bool is_dynamic{ false }; ///< ����, �����������, �������� �� ���� ������������.
		size_t depth{ 0 }; ///< ������� ����������� ������.
		time_t createTimeStamp{ 0 }; ///< ����� �������� �����
	};

	size_t block_size_; ///< ������ ����� ������.
	Block current_block_; ///< ������� ���� ������.
	std::vector<std::shared_ptr<IOutputter>> outputters_; ///< ����������� ������ ����������
};