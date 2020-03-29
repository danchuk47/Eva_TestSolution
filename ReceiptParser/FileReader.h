#pragma once

#include "IReceiptRawDataReader.h"
#include <fstream>

namespace Receipt
{
    class FileReader: public IReceiptRawDataReader
    {
    public:
        explicit FileReader(std::string&& filePath);
        virtual ~FileReader();

        virtual std::string ReadLine();

    private:
        std::fstream m_file;
    };
}
