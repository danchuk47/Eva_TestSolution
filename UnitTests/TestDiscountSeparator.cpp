#include "gtest/gtest.h"
#include "DiscountSeparator.h"

using namespace Receipt;

TEST(DiscountSeparator, CheckValidSepareting_1)
{
    std::vector<std::pair<uint, uint>> separatedDiscount;
    DiscountSeparatorPtr discountSeparator = std::make_unique<DiscountSeparator>(7, 50);
    discountSeparator->Separate([&](uint count, uint discount) {
        separatedDiscount.push_back(std::pair<uint, uint>{ count, discount });
    });
    ASSERT_TRUE(separatedDiscount.size() == 2);
    ASSERT_TRUE(separatedDiscount.at(0).first == 1);
    ASSERT_TRUE(separatedDiscount.at(0).second == 8);
    ASSERT_TRUE(separatedDiscount.at(1).first == 6);
    ASSERT_TRUE(separatedDiscount.at(1).second == 42);
}

TEST(DiscountSeparator, CheckValidSepareting_2)
{
    std::list<std::pair<uint, uint>> separatedDiscount;
    DiscountSeparatorPtr discountSeparator = std::make_unique<DiscountSeparator>(7, 48);
    discountSeparator->Separate([&](uint count, uint discount) {
        separatedDiscount.push_back(std::pair<uint, uint>{ count, discount });
    });
    ASSERT_TRUE(separatedDiscount.size() == 2);
    std::list<std::pair<uint, uint>>::const_iterator it = separatedDiscount.cbegin();
    ASSERT_TRUE(it->first == 6);
    ASSERT_TRUE(it->second == 42);
    ++it;
    ASSERT_TRUE(it->first == 1);
    ASSERT_TRUE(it->second == 6);
}

TEST(DiscountSeparator, CheckInvalidSepareting_WhenCommodityCountIsZerro)
{
    std::list<std::pair<uint, uint>> separatedDiscount;
    DiscountSeparatorPtr discountSeparator = std::make_unique<DiscountSeparator>(0, 48);
    discountSeparator->Separate([&](uint count, uint discount) {
        separatedDiscount.push_back(std::pair<uint, uint>{ count, discount });
    });
    ASSERT_TRUE(separatedDiscount.size() == 1);
    std::list<std::pair<uint, uint>>::const_iterator it = separatedDiscount.cbegin();
    ASSERT_TRUE(it->first == 0);
    ASSERT_TRUE(it->second == 48);
}

TEST(DiscountSeparator, CheckSepareting_WhenItIsNotNecessary)
{
    std::list<std::pair<uint, uint>> separatedDiscount;
    DiscountSeparatorPtr discountSeparator = std::make_unique<DiscountSeparator>(7, 35);
    discountSeparator->Separate([&](uint count, uint discount) {
        separatedDiscount.push_back(std::pair<uint, uint>{ count, discount });
    });
    ASSERT_TRUE(separatedDiscount.size() == 1);
    std::list<std::pair<uint, uint>>::const_iterator it = separatedDiscount.cbegin();
    ASSERT_TRUE(it->first == 7);
    ASSERT_TRUE(it->second == 35);
}

TEST(DiscountSeparator, CheckIsNeedSeparate_True)
{
    DiscountSeparatorPtr discountSeparator = std::make_unique<DiscountSeparator>(7, 36);
    
    ASSERT_TRUE(discountSeparator->IsNeedSeparate());
}

TEST(DiscountSeparator, CheckIsNeedSeparate_False)
{
    DiscountSeparatorPtr discountSeparator = std::make_unique<DiscountSeparator>(7, 35);

    ASSERT_TRUE(!discountSeparator->IsNeedSeparate());
}



