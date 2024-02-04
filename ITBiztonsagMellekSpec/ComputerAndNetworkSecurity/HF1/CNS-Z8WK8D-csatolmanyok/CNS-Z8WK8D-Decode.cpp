
#pragma warning(disable:4996)

#include <iostream>


void crypt (const char* in, const char* out)
{
    FILE* input = fopen(in, "rb");
    FILE* output = fopen(out, "wb");
    unsigned int local_c = 0xae541251;
    int local_24 = 0x11552211;
    int local_28 = 2;

    if ((input == (FILE*)0x0) || (output == (FILE*)0x0)) {
        std::cout << "No file exists!" << std::endl;
        return;
    }

    size_t local_30;
    unsigned int current;
    unsigned char bVar1;

    while (local_30 = fread(&current, 1, 4, input), local_30 != 0) {
        bVar1 = (unsigned char)local_28 & 0x1f;
        current = (current ^ local_c) << bVar1 | (current ^ local_c) >> 0x20 - bVar1;
        local_c = local_c * local_24;
        fwrite(&current, 1, local_30, output);
    }
    fclose(input);
    fclose(output);
    puts("Obfuscation completed.");
    
}

void decrypt(const char* in, const char* out)
{
    FILE* input = fopen(in, "rb");
    FILE* output = fopen(out, "wb");
    unsigned int local_c = 0xae541251;
    int local_24 = 0x11552211;
    int local_28 = 2;

    if ((input == (FILE*)0x0) || (output == (FILE*)0x0)) {
        std::cout << "No file exists!" << std::endl;
        return;
    }

    size_t local_30;
    unsigned int current;
    unsigned char bVar1;

    while (local_30 = fread(&current, 1, 4, input), local_30 != 0) {
        unsigned char bVar1 = (unsigned char)local_28 & 0x1f;
        unsigned int x = (current >> bVar1) | (current << (32 - bVar1));
        current = x ^ local_c;
        local_c = local_c * local_24;
        fwrite(&current, 1, local_30, output);
    }

    fclose(input);
    fclose(output);
}


int main()
{
    //crypt("C:\\BME\\Hálózatbiztonság\\HF1\\in.bin", "C:\\BME\\Hálózatbiztonság\\HF1\\out.bin");
    //decrypt("C:\\BME\\Hálózatbiztonság\\HF1\\out.bin", "C:\\BME\\Hálózatbiztonság\\HF1\\in.bin");
    decrypt("C:\\BME\\Hálózatbiztonság\\HF1\\decodedBase64.bin", "C:\\BME\\Hálózatbiztonság\\HF1\\out.bin");
}

