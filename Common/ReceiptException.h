#pragma once

#include <exception>
#include  <string>

namespace Receipt
{
    class ReceiptException : public std::exception
    {
    public:
        enum ErrorType {
            NOT_IMPLEMENTED,
            FAILED_READ_DATA,
            FAILED_PARSING_DATA
        };

        explicit ReceiptException(ErrorType errorType, const std::string &s) : m_errorType(errorType), m_what(s) {}
        virtual ~ReceiptException() throw() {}
        const char *what() const throw() { return (m_what.c_str()); }
        const std::string &GetWhat() const { return m_what; }
        void SetWhat(const std::string &s) { m_what = s; }
        ErrorType GetErrorType() const { return m_errorType; }
        void SetErrorType(ErrorType errorType) { m_errorType = errorType; }

    private:
        ErrorType m_errorType;
        std::string m_what;
    };
}
