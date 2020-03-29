#pragma once

#include "IDiscountSeparator.h"

namespace Receipt
{
    class ReceiptBuildManager
    {
    public:
        explicit ReceiptBuildManager() = default;
        ~ReceiptBuildManager() = default;

        void Normalize(const ReceiptItemData& receiptItem, Fn<void(const ReceiptItemData&)>&& outCallback)const;

    private:
        virtual DiscountSeparatorPtr CreateDiscountSeparator(uint commodityCount, uint discount)const;
    };
}
