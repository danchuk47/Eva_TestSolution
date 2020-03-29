#include "gtest/gtest.h"
#include "ReceiptParser.h"
#include "ReceiptRawDataReaderMoc.h"
#include "ReceiptException.h"

using namespace Receipt;

TEST(ReceiptParser, CheckValidParsing)
{
    std::vector<std::string> mocData{
        "Товар_А, 127 коп. , 3 шт, скидка 23."
    };
    ReceiptRawDataReaderPtr fileReader(new Moc::ReceiptRawDataReaderMoc(std::move(mocData)));
    ReceiptParserPtr receiptParser = std::make_unique<ReceiptParser>(std::move(fileReader));

    ReceiptItemDataPtr receiptData = receiptParser->SerializeItem();
    ASSERT_TRUE(receiptData->name == "Товар_А");
    ASSERT_TRUE(receiptData->price == 127);
    ASSERT_TRUE(receiptData->commodityCount == 3);
    ASSERT_TRUE(receiptData->discount == 23);
}

TEST(ReceiptParser, CheckValidParsing_WhenSeveralLine)
{
    std::vector<std::string> mocData{
        "Товар_А, 127 коп. , 3 шт, скидка 23.",
        "Товар_Б, 353 коп. , 5 шт, скидка 45."
    };
    ReceiptRawDataReaderPtr fileReader(new Moc::ReceiptRawDataReaderMoc(std::move(mocData)));
    ReceiptParserPtr receiptParser = std::make_unique<ReceiptParser>(std::move(fileReader));

    ReceiptItemDataPtr receiptData = receiptParser->SerializeItem();
    ASSERT_TRUE(receiptData->name == "Товар_А");
    ASSERT_TRUE(receiptData->price == 127);
    ASSERT_TRUE(receiptData->commodityCount == 3);
    ASSERT_TRUE(receiptData->discount == 23);
    receiptData = receiptParser->SerializeItem();
    ASSERT_TRUE(receiptData->name == "Товар_Б");
    ASSERT_TRUE(receiptData->price == 353);
    ASSERT_TRUE(receiptData->commodityCount == 5);
    ASSERT_TRUE(receiptData->discount == 45);
}

TEST(ReceiptParser, CheckValidParsing_WhenDataIsAbsent)
{
    std::vector<std::string> mocData;
    ReceiptRawDataReaderPtr fileReader(new Moc::ReceiptRawDataReaderMoc(std::move(mocData)));
    ReceiptParserPtr receiptParser = std::make_unique<ReceiptParser>(std::move(fileReader));

    ReceiptItemDataPtr receiptData = receiptParser->SerializeItem();
    receiptData = receiptParser->SerializeItem();
    ASSERT_TRUE(receiptData.get() == nullptr);
    receiptData = receiptParser->SerializeItem();
    ASSERT_TRUE(receiptData.get() == nullptr);
}

TEST(ReceiptParser, CheckInvalidParsing_WhenCanNotParseNumber)
{
    std::vector<std::string> mocData{
        "Товар_А, 127 коп. , три шт , скидка 23."
    };
    ReceiptRawDataReaderPtr fileReader(new Moc::ReceiptRawDataReaderMoc(std::move(mocData)));
    ReceiptParserPtr receiptParser = std::make_unique<ReceiptParser>(std::move(fileReader));

    ASSERT_THROW(receiptParser->SerializeItem(), ReceiptException);
}

TEST(ReceiptParser, CheckInvalidParsing_WhenNotAllParametersPresent)
{
    std::vector<std::string> mocData{
        "Товар_А, 127 коп. , 3 шт."
    };
    ReceiptRawDataReaderPtr fileReader(new Moc::ReceiptRawDataReaderMoc(std::move(mocData)));
    ReceiptParserPtr receiptParser = std::make_unique<ReceiptParser>(std::move(fileReader));

    ASSERT_THROW(receiptParser->SerializeItem(), ReceiptException);
}

TEST(ReceiptParser, CheckInvalidParsing_WhenIsTooBigNumberPresent)
{
    std::vector<std::string> mocData{
        "Товар_А, 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999 коп. , 3 шт, скидка 23."
    };
    ReceiptRawDataReaderPtr fileReader(new Moc::ReceiptRawDataReaderMoc(std::move(mocData)));
    ReceiptParserPtr receiptParser = std::make_unique<ReceiptParser>(std::move(fileReader));

    ASSERT_THROW(receiptParser->SerializeItem(), ReceiptException);
}