#pragma once

#include <string>
#include <functional>

typedef unsigned int uint;
typedef unsigned char uchar;

struct ReceiptItemData
{
    std::string name;
    uint price;
    uint commodityCount;
    uint discount;
};

template <typename Signature>
using Fn = std::function<Signature>;


