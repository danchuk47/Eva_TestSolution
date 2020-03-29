#pragma once

#include "TypesDefinition.h"
#include <string>
#include <memory>

namespace Receipt
{
    class IReceiptRawDataReader
    {
    public:
        virtual ~IReceiptRawDataReader() = default;

        virtual std::string ReadLine() = 0;
    };

    typedef std::unique_ptr<IReceiptRawDataReader> ReceiptRawDataReaderPtr;
}

