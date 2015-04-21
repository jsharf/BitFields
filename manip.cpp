#include "manip.h"

#include <iostream>
#include <cstdint>
#include <cstdio>

namespace IPSR
{
    Field<uint8_t, 0, 8> ISR_NUMBER;
}

int main()
{
    uint32_t IPSR = 0x00;
    
    printf("0x%x\n", IPSR);

    uint8_t isrnum = 5;

    std::cout << "Setting ISR_NUMBER = " << isrnum << std::endl;

    {
        using namespace IPSR;
        IPSR = modify(IPSR, ISR_NUMBER = isrnum);
    }
    
    printf("0x%x\n", IPSR);
   
    uint8_t extract_test;

    {
        using namespace IPSR;
        extract_test = extract(IPSR, ISR_NUMBER);
    }

    std::cout << "Extracted ISR number: ";
    
    printf("0x%x\n",  extract_test);
}
