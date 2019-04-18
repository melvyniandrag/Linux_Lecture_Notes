/**
* To run this:
* sudo apt-get install build-essential
* g++ endianness.cpp
* ./a.out
* You'll see 0x40 as the first  byte in the array. that's because
* Intel CPUs are little endian, they put the lowest byte first.
*/
#include <cstdint>
#include <cstdio>

int main(){
        uint32_t num = 64;
        char * numAddr = (char*)&num ;
        for ( size_t i = 0; i < sizeof(num); ++i )
                printf("0x%02X\n", numAddr[i]);
}
