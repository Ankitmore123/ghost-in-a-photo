#include <iostream>
#include <bitset>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// This saves the modified 'img' array as a new file
int width, height, channels;

// This line opens the file and creates the large array in memory
void extractBits(char c) {
    std::cout << "Character: " << c << " Binary: " << std::bitset<8>(c) << std::endl;

    for (int i = 7; i >= 0; --i) {
        // Shift the bit we want to the 0th position, then mask it
        int bit = (c >> i) & 1; 
        std::cout << "Bit at position " << i << " is: " << bit << std::endl;
    }
}
unsigned char pixel = 157;       // Binary: 10011101
unsigned char mask = 0xFE;      // Binary: 11111110 
unsigned char cleared = pixel & mask; // Result: 10011100
//message is preserved and the last one is guarenteed to be 0
int secretBit = 1;              // This is the bit you want to hide
unsigned char finalPixel = cleared | secretBit;

void encode(unsigned char* img, std::string message, size_t max_bytes) {
    int pixelIndex = 0;

    // Safety Check: Do we have enough pixels for the message + null terminator?
    if ((message.length() + 1) * 8 > max_bytes) {
        std::cerr << "Error: Image is too small for this message!" << std::endl;
        return;
    }

    // Loop through the message PLUS the hidden '\0' at the end
    // Using <= ensures we process the null terminator
    for (int k = 0; k <= message.length(); k++) {
        char c = message[k];

        // Peel 8 bits from the character
        for (int i = 7; i >= 0; --i) {
            int bit = (c >> i) & 1;

            // The surgery: Clear LSB, then OR with our secret bit
            img[pixelIndex] = (img[pixelIndex] & 0xFE) | bit;
            
            pixelIndex++;
        }
    }
    std::cout << "Message encoded successfully into " << pixelIndex << " bytes." << std::endl;
}
void decode(unsigned char* img,size_t max_bytes) {
    std::string decodedMessage = "";
    int pixelIndex = 0;

    while (pixelIndex + 8 <= max_bytes) {
        char c = 0;
        // Inner loop: Rebuild one character from 8 pixels
        for (int j = 7; j >= 0; --j) {
            int bit = img[pixelIndex] & 1; // Extract the LSB
            c = (c << 1) | bit;            // Shift and push into the bucket
            pixelIndex++;
        }

        // If we hit the Null Terminator, we stop
        if (c == '\0') {
            break;
        }

        decodedMessage += c;
    }

    std::cout << "Decoded Message: " << decodedMessage << std::endl;
}
int main() {
    int width, height, channels;

    // 1. LOAD the image first
    unsigned char* img = stbi_load("input.png", &width, &height, &channels, 0);

    // 2. CHECK if it actually loaded before doing anything else
    if (img == NULL) {
        std::cout << "Could not find the image! Make sure 'my_photo.png' is in the folder." << std::endl;
        return 1;
    }

    // 3. PREPARE the data
    std::string secret = "Engineering is fascinating!"; 
    size_t total_bytes = width * height * channels;

    // 4. ENCODE the secret into the loaded image buffer
    encode(img, secret, total_bytes);

    // 5. SAVE the modified buffer to a new file
    stbi_write_png("secret_cat.png", width, height, channels, img, width * channels);
    std::cout << "Success! Saved secret to 'secret_cat.png'" << std::endl;
    decode(img,total_bytes);
    // 6. CLEANUP memory
    stbi_image_free(img);

    return 0;
}
//  std::string decodedMessage = "";
//     pixelIndex = 0; // Reset to the start of the image!

//     while (true) {
//         char c = 0;
//         for (int j = 7; j >= 0; --j) {
//             int bit = img[pixelIndex] & 1;
//             c = (c << 1) | bit;
//             pixelIndex++;
//         }
        
//         if (c == '\0') break; 
//         decodedMessage += c;
//     }
// std::cout << "Decoded: " << decodedMessage << std::endl;
//unsigned char* img =