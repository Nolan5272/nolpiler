#include <stdio.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics;
} CoffHeader;
#pragma pack(pop)

int main() {

    FILE *file = fopen("min.obj", "wb");
    if(!file){
        perror("error w/file");
        return 1;
    }

    CoffHeader header;
    header.Machine = 0x014C;
    header.NumberOfSections = 0;
    header.TimeDateStamp = 0;
    header.PointerToSymbolTable = 0;
    header.NumberOfSymbols = 0;
    header.SizeOfOptionalHeader = 0;
    header.Characteristics = 0;

    fwrite(&header, sizeof(CoffHeader), 1, file);
    fclose(file);
    printf("write coff header to min.obj\n");
    return 0;
}

