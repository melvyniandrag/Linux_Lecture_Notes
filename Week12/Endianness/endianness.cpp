#include <cstdint>
#include <cstdio>

int main(){
        uint32_t num = 64;
        char * numAddr = (char*)&num ;
        for ( size_t i = 0; i < sizeof(num); ++i )
                printf("0x%02X\n", numAddr[i]);
}
