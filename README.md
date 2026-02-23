# ghost-in-a-photo

 C++ LSB Steganography Tool:A lightweight systems-programming tool to hide secret messages inside PNG images using Least Significant Bit (LSB) substitution.
 Engineering Logic::
 Data Density: Hides 1 bit of data per color channel (RGB).
 Bitwise Surgery: Uses bit-shifting and masking to modify the $2^0$ bit of each pixel byte.
 Lossless Integrity: Utilizes the STB library for PNG processing to ensure no data loss during compression.
 How to RunPlace your input.png in the folder.Compile: g++ src/main.cpp -I ./include -o stegoRun: ./stego
i have used the stb headers, people are free to use it in their own code  

