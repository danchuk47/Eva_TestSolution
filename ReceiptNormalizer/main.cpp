#include <iostream>
#include "FileReader.h"
#include "ReceiptParser.h"
#include "ReceiptBuildManager.h"
#include "ReceiptException.h"

using namespace Receipt;

void ShowHelp()
{
    std::cout << "Run the app with one of following options" << std::endl;
    std::cout << "    without any parameters - There must be present the inputData.txt file near this app in this case." << std::endl;
    std::cout << "    [-path <path to input data>] - This command launches reading input data from a file" << std::endl;
    std::cout << "                                   <path to input data> It is a path to a file where is present the input data inside." << std::endl;

    std::cout << "    [-h] - This command showes this help" << std::endl;
}


int main(int argc, char* argv[])
{
    if (argc != 1 && argc != 2 && argc != 3)
    {
        std::cout << "Incorrect input parameters" << std::endl;
        ShowHelp();
        return 0;
    }

    std::string inputDataFilePath("inputData.txt");

    if (argc > 1)
    {
        std::string inputParameter = argv[1];

        if (inputParameter == "-h" && argc == 2)
        {
            ShowHelp();
            return 0;
        }
        else if (inputParameter == "-path" && argc == 3)
        {
            inputDataFilePath = std::string(argv[2]);
        }
        else
        {
            std::cout << "Unknown input parameter" << std::endl;
            ShowHelp();
            return 0;
        }
    }
    
    try
    {
        ReceiptRawDataReaderPtr fileReader = std::make_unique<FileReader>(std::move(inputDataFilePath));
        ReceiptParserPtr receiptParser = std::make_unique<ReceiptParser>(std::move(fileReader));

        ReceiptItemDataPtr receiptItem = receiptParser->SerializeItem();

        if (receiptItem.get() == nullptr)
        {
            std::cout << "Can not read any data from input file." << std::endl;
            std::cout << "Please check both you typed valid path or the inputData.txt is near this app.";
            ShowHelp();
            return 0;
        }
        else
        {
            setlocale(LC_ALL, "Russian");

            while (receiptItem.get() != nullptr)
            {
                ReceiptBuildManager receiptBuildManager;
                receiptBuildManager.Normalize(*receiptItem.get(), [&](const ReceiptItemData& normalizedItem) {
                    std::cout << normalizedItem.name << ", " << normalizedItem.price << " коп., " << normalizedItem.commodityCount << " шт, скидка " << normalizedItem.discount << "." << std::endl;
                });
                receiptItem = receiptParser->SerializeItem();
            }
        }
    }
    catch (const ReceiptException& ex)
    {
        std::cout << "Error: could not handle input data." << std::endl;
        std::cout << "Reason of issue is in following:" << std::endl;
        std::cout << ex.what() << std::endl;
    }    

    system("pause");
    return 0;
}