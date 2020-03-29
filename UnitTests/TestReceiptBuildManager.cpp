#include "gtest/gtest.h"
#include "ReceiptBuildManager.h"

using namespace Receipt;

TEST(ReceiptBuildManager, CheckValidNormalizing_1)
{
    ReceiptBuildManager receiptBuildManager;
    ReceiptItemData inputData{
        "Товар_А",
        127,
        3,
        23
    };

    std::vector<ReceiptItemData> normalizedDataContainer;

    receiptBuildManager.Normalize(inputData, [&](const ReceiptItemData& normalizedItem) {
        normalizedDataContainer.push_back(normalizedItem);
    });

    ASSERT_TRUE(normalizedDataContainer.size() == 2);
    ASSERT_TRUE(normalizedDataContainer[0].name == "Товар_А");
    ASSERT_TRUE(normalizedDataContainer[0].price == 127);
    ASSERT_TRUE(normalizedDataContainer[0].commodityCount == 2);
    ASSERT_TRUE(normalizedDataContainer[0].discount == 16);

    ASSERT_TRUE(normalizedDataContainer[1].name == "Товар_А");
    ASSERT_TRUE(normalizedDataContainer[1].price == 127);
    ASSERT_TRUE(normalizedDataContainer[1].commodityCount == 1);
    ASSERT_TRUE(normalizedDataContainer[1].discount == 7);
}


TEST(ReceiptBuildManager, CheckValidNormalizing_2)
{
    ReceiptBuildManager receiptBuildManager;
    ReceiptItemData inputData{
        "Товар_B",
        127,
        7,
        50
    };

    std::vector<ReceiptItemData> normalizedDataContainer;

    receiptBuildManager.Normalize(inputData, [&](const ReceiptItemData& normalizedItem) {
        normalizedDataContainer.push_back(normalizedItem);
    });

    ASSERT_TRUE(normalizedDataContainer.size() == 2);
    ASSERT_TRUE(normalizedDataContainer[0].name == "Товар_B");
    ASSERT_TRUE(normalizedDataContainer[0].price == 127);
    ASSERT_TRUE(normalizedDataContainer[0].commodityCount == 1);
    ASSERT_TRUE(normalizedDataContainer[0].discount == 8);

    ASSERT_TRUE(normalizedDataContainer[1].name == "Товар_B");
    ASSERT_TRUE(normalizedDataContainer[1].price == 127);
    ASSERT_TRUE(normalizedDataContainer[1].commodityCount == 6);
    ASSERT_TRUE(normalizedDataContainer[1].discount == 42);
}

TEST(ReceiptBuildManager, CheckValidNormalizing_WhenSeparatingIsNotNeed)
{
    ReceiptBuildManager receiptBuildManager;
    ReceiptItemData inputData{
        "Товар_B",
        127,
        7,
        35
    };

    std::vector<ReceiptItemData> normalizedDataContainer;

    receiptBuildManager.Normalize(inputData, [&](const ReceiptItemData& normalizedItem) {
        normalizedDataContainer.push_back(normalizedItem);
    });

    ASSERT_TRUE(normalizedDataContainer.size() == 1);
    ASSERT_TRUE(normalizedDataContainer[0].name == "Товар_B");
    ASSERT_TRUE(normalizedDataContainer[0].price == 127);
    ASSERT_TRUE(normalizedDataContainer[0].commodityCount == 7);
    ASSERT_TRUE(normalizedDataContainer[0].discount == 35);
}