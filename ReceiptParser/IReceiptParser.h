#pragma once

#include "TypesDefinition.h"
#include <memory>

namespace Receipt
{
    typedef std::unique_ptr<ReceiptItemData> ReceiptItemDataPtr;

    class IReceiptParser
    {
    public:
        virtual ~IReceiptParser() = default;

        virtual ReceiptItemDataPtr SerializeItem()const = 0;
    };

    typedef std::unique_ptr<IReceiptParser> ReceiptParserPtr;
}
