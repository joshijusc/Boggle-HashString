#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        // read string from right to left for hash table
        // string should not be > 28 characters long
        // make a w array to store string values from right to left (think of it like reading binary where most significant bit is the leftmost bit)
        // w array is unsigned long longs

        unsigned long long w[5];
        for (size_t i=0; i<5; i++){ // Initialization
            w[i] = 0;
        }
        size_t wIndex = 4;
        size_t numCharsPerWUsed = 0;
        size_t wMultiplier = 1;
        for (int i=k.size()-1; i>=0; i--){
            // keep a variable that is index of w outside loop starting at 4
            // before moving on to this character, first check if we have already worked with 6 characters, if so, then move to next w value
            if (numCharsPerWUsed == 6){ // If we have reached the max of 6, go to the next w index down and repeat the process again
                wIndex--;
                wMultiplier = 1;
                numCharsPerWUsed = 0;
            }
            w[wIndex] += wMultiplier * letterDigitToNumber((k[i]));
            wMultiplier *= 36; // Acts like pow() functions since it increases by 1 exponent each time as we work right to left
            numCharsPerWUsed++;
        }
        unsigned long long h = 0;
        for (size_t i=0; i<5; i++){ // Calculate the final result of the hash
            h += (rValues[i] * w[i]);
        }
        return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        // uppercase are same as lowercase
        // convert ascii for letters of uppercase and lowercase and digits
        if (letter >='A' && letter <= 'Z'){
            letter = tolower(letter);
        }
        if (letter >= 'a' && letter <= 'z'){
            return letter - 'a';
        } else if (letter >= '0' && letter <= '9') {
            return letter - '0' + 26;
        } else return (HASH_INDEX_T) - 1;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
