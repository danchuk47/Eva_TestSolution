#pragma once

#include "TypesDefinition.h"
#include <memory>

namespace Receipt
{
    class IDiscountSeparator
    {
    public:
        virtual ~IDiscountSeparator() = default;

        virtual bool IsNeedSeparate()const = 0;
        virtual void Separate(Fn<void(uint, uint)>&& outCallback)const = 0;
    };
}

typedef std::unique_ptr<Receipt::IDiscountSeparator> DiscountSeparatorPtr;
