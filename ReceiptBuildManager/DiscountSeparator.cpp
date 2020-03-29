#include "DiscountSeparator.h"

using namespace Receipt;

DiscountSeparator::DiscountSeparator(uint commodityCount, uint discount): 
    m_discount{commodityCount, discount},
    m_dicountMod(commodityCount > 0 ? discount % commodityCount : 0)
{
}

bool DiscountSeparator::IsNeedSeparate()const
{
    return m_dicountMod != 0;
}

void DiscountSeparator::Separate(Fn<void(uint, uint)>&& outCallback) const
{
    if (IsNeedSeparate())
    {
        const uint firstItemCommodityCount = m_dicountMod;
        const uint firstItemDiscount = firstItemCommodityCount * ((m_discount.fullDiscount / m_discount.commodityCount) + 1);
        outCallback(firstItemCommodityCount, firstItemDiscount);

        const uint secondItemCommodityCount = m_discount.commodityCount - m_dicountMod;
        const uint secondItemDiscount = secondItemCommodityCount * (m_discount.fullDiscount / m_discount.commodityCount);
        outCallback(secondItemCommodityCount, secondItemDiscount);
    }
    else
    {
        outCallback(m_discount.commodityCount, m_discount.fullDiscount);
    }
    
}