#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        
        for (int i = k.size(), subString = 4; i > 0 && subString >= 0; i -= 6, --subString) {
          unsigned long long value = 0;
          value += letterDigitToNumber(k[i - 1]) * 1ULL;
          if (i - 2 >= 0)
            value += letterDigitToNumber(k[i - 2]) * 36ULL;
          if (i - 3 >= 0)
            value += letterDigitToNumber(k[i - 3]) * 1296ULL;
          if (i - 4 >= 0)
            value += letterDigitToNumber(k[i - 4]) * 46656ULL;
          if (i - 5 >= 0)
            value += letterDigitToNumber(k[i - 5]) * 1679616ULL;
          if (i - 6 >= 0)
            value += letterDigitToNumber(k[i - 6]) * 604661776ULL;

          w[subString] = value;
        }

        unsigned long long output = 0;
        for (int i = 0; i < 5; ++i) {
          output += rValues[i] * w[i];
        }
        return output;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'a' && letter <= 'z') {
          return static_cast<HASH_INDEX_T>(letter - 'a');
        }
        else if (letter >= 'A' && letter <= 'Z') {
          return static_cast<HASH_INDEX_T>(letter - 'A');
        }
        else {
          return static_cast<HASH_INDEX_T>(letter - 'a');
        }
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
