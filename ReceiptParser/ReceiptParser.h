#pragma once

#include "IReceiptParser.h"
#include "IReceiptRawDataReader.h"
#include <vector>

namespace Receipt
{
    class ReceiptParser: public IReceiptParser
    {
    public:
        explicit ReceiptParser(ReceiptRawDataReaderPtr&& rawDataReader);
        virtual ~ReceiptParser() = default;

        virtual ReceiptItemDataPtr SerializeItem()const;

    private:
        void Split(const std::string& text, char separator, std::vector<std::string>& outData)const;
        std::string ParseDiscountNumStr(const std::string& rawDiscountStr)const;
        ReceiptItemDataPtr Parse(const std::vector<std::string>& rawData)const;

    private:
        ReceiptRawDataReaderPtr m_rawDataReader;
        const uint NAME_INDEX = 0;
        const uint PRICE_INDEX = 1;
        const uint COMMODITY_COUNT_INDEX = 2;
        const uint DISCOUNT_INDEX = 3;
    };
}
