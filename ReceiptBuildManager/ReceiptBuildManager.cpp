#include "ReceiptBuildManager.h"
#include "DiscountSeparator.h"

using namespace Receipt;

void ReceiptBuildManager::Normalize(const ReceiptItemData& receiptItem, Fn<void(const ReceiptItemData&)>&& outCallback)const
{
    DiscountSeparatorPtr discountSeparator = CreateDiscountSeparator(receiptItem.commodityCount, receiptItem.discount);
    discountSeparator->Separate([&](uint count, uint discount) {
        ReceiptItemData normalizedItem{
            receiptItem.name,
            receiptItem.price,
            count,
            discount
        };
        outCallback(normalizedItem);
    });
}

DiscountSeparatorPtr ReceiptBuildManager::CreateDiscountSeparator(uint commodityCount, uint discount)const
{
    return std::make_unique<DiscountSeparator>(commodityCount, discount);
}