#include "ReceiptRawDataReaderMoc.h"

using namespace Moc;

ReceiptRawDataReaderMoc::ReceiptRawDataReaderMoc(std::vector<std::string>&& mocData) : 
    m_data(std::move(mocData)),
    m_curentLine{0}
{
}

std::string ReceiptRawDataReaderMoc::ReadLine()
{
    if (m_curentLine >= m_data.size())
    {
        return std::string();
    }

    return m_data.at(m_curentLine++);
}

