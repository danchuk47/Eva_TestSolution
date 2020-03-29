#include "ReceiptParser.h"
#include "ReceiptException.h"

using namespace Receipt;

ReceiptParser::ReceiptParser(ReceiptRawDataReaderPtr&& rawDataReader) : m_rawDataReader(std::move(rawDataReader))
{
}

ReceiptItemDataPtr ReceiptParser::SerializeItem()const
{
    std::string lineFromReceipt = m_rawDataReader->ReadLine();

    if (lineFromReceipt.empty())
    {
        return ReceiptItemDataPtr();
    }

    std::vector<std::string> splitedData;
    const char separator = ',';
    Split(lineFromReceipt, separator, splitedData);

    return Parse(splitedData);
}

void ReceiptParser::Split(const std::string& text, char separator, std::vector<std::string>& outData)const
{
    size_t pos = 0;
    std::string token;
    std::string inputText(text);
    while ((pos = inputText.find(separator)) != std::string::npos) {
        token = inputText.substr(0, pos);
        outData.push_back(token);
        inputText.erase(0, pos + sizeof(char));
    }

    if (!inputText.empty())
    {
        outData.push_back(inputText);
    }
}

std::string ReceiptParser::ParseDiscountNumStr(const std::string& rawDiscountStr)const
{
    size_t discountPosBeg = 0;
    size_t discountPosEnd = 0;
    const char separator = ' ';

    discountPosBeg = rawDiscountStr.rfind(separator);
    discountPosEnd = rawDiscountStr.size() - 1;
    return rawDiscountStr.substr(discountPosBeg, discountPosEnd - discountPosBeg);
}

ReceiptItemDataPtr ReceiptParser::Parse(const std::vector<std::string>& rawData)const
{
    const uint rawDataSize = DISCOUNT_INDEX + 1;
    if (rawData.size() != rawDataSize)
    {
        throw ReceiptException(ReceiptException::ErrorType::FAILED_READ_DATA, "Not all parameters present for parsing");
    }

    std::string discountStr = ParseDiscountNumStr(rawData[DISCOUNT_INDEX]);
    uint price = 0, commodityCount = 0, discount = 0;

    try
    {
        price = static_cast<uint>(std::stoi(rawData[PRICE_INDEX]));
        commodityCount = static_cast<uint>(std::stoi(rawData[COMMODITY_COUNT_INDEX]));
        discount = static_cast<uint>(std::stoi(discountStr));
    }
    catch (const std::invalid_argument&)
    {
        throw ReceiptException(ReceiptException::ErrorType::FAILED_PARSING_DATA, "Incorrect a number parametr present");
    }
    catch (const std::out_of_range&)
    {
        throw ReceiptException(ReceiptException::ErrorType::FAILED_PARSING_DATA, "A number parametr is too big");
    }

    return ReceiptItemDataPtr(new ReceiptItemData
    {
        rawData[NAME_INDEX],
        price,
        commodityCount,
        discount
    });
}