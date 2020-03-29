#pragma once

#include "IDiscountSeparator.h"
#include <list>

namespace Receipt
{
    class DiscountSeparator: public IDiscountSeparator
    {
    public:
        DiscountSeparator(uint commodityCount, uint discount);
        virtual ~DiscountSeparator() = default;

        virtual bool IsNeedSeparate()const;
        virtual void Separate(Fn<void(uint, uint)>&& outCallback)const;

    private:
        struct Discount
        {
            uint commodityCount;
            uint fullDiscount;
        };

    private:
        Discount m_discount;
        uint m_dicountMod;
    };
}
