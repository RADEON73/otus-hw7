#include "BulkProcessor.h"
#include "CommandFactory.h"
#include <chrono>
#include <iostream>

void BulkProcessor::startBlock() {
    if (current_block_.depth == 0)
        flush();
    ++current_block_.depth;
    current_block_.is_dynamic = true;
}

void BulkProcessor::endBlock() {
    if (current_block_.depth > 0) {
        --current_block_.depth;
        if (current_block_.depth == 0)
            flush();
    }
}

void BulkProcessor::addCommand(const std::string& command) {
	if (current_block_.data.empty())
        current_block_.createTimeStamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    current_block_.data.push_back(command);
    if (!current_block_.is_dynamic && current_block_.data.size() >= block_size_)
        flush();
}

void BulkProcessor::process(const std::string& command) {
    auto cmd = CommandFactory::create(command);
    cmd->execute(*this);
}

void BulkProcessor::finalize() {
    if (current_block_.depth == 0)
        flush();
    else
        current_block_.data.clear();
}

void BulkProcessor::flush() {
    if (!current_block_.data.empty()) {
        for (const auto& outputter : outputters_)
            outputter->output(current_block_.data, current_block_.createTimeStamp);
        current_block_.reset();
    }
}

void BulkProcessor::Block::reset()
{
    data.clear();
    is_dynamic = false;
    depth = 0;
    createTimeStamp = 0;
}