#include "FileReader.h"
#include <vector>

using namespace Receipt;

FileReader::FileReader(std::string&& filePath) :m_file(filePath, std::ios::in | std::ios::binary)
{
}

FileReader::~FileReader()
{
    if (m_file)
    {
        m_file.close();
    }
}

std::string FileReader::ReadLine()
{
    if (!m_file || m_file.eof())
    {
        return std::string();
    }

    std::vector<char> buffer(500, 0);
    const char lineSeparator = '\n';
    m_file.getline(&buffer.at(0), buffer.size() - 1, lineSeparator);
    return &buffer.at(0);
}