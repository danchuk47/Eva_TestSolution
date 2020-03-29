#pragma once

#include "IReceiptRawDataReader.h"
#include <vector>

namespace Moc
{
    class ReceiptRawDataReaderMoc : public Receipt::IReceiptRawDataReader
    {
    public:
        explicit ReceiptRawDataReaderMoc(std::vector<std::string>&& mocData);
        virtual ~ReceiptRawDataReaderMoc() = default;

        virtual std::string ReadLine();



    private:
        std::vector<std::string> m_data;
        uint m_curentLine;
    };
}

