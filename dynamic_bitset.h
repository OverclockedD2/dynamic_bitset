/*
*                       dynamic_bitset.h
* 
*   This is a header-only, CUDA compatible dynamic bitset library.
*   Orignial version made by github.com/OverclockedD2. Make sure to
*   read the documentation: github.com/OverclockedD2/dynamic_bitset.
* 
*                   Copyroght (c) 2024 OverclockedD2
* 
*           Permission is hereby granted, free of charge, 
*           to any person obtaining a copy of this software 
*           and associated documentation files (the "Software"), 
*           to deal in the Software without restriction, 
*           including without limitation the rights to use, 
*           copy, modify, merge, publish, distribute, sublicense, 
*           and/or sell copies of the Software, and to permit 
*           persons to whom the Software is furnished to do so, 
*           subject to the following conditions: 
*
*           The above copyright notice and this permission notice 
*           shall be included in all copies or substantial portions 
*           of the Software.
* 
*           THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF 
*           ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
*           TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
*           PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
*           THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
*           DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
*           CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
*           CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
*           IN THE SOFTWARE.
*/

#pragma once

#include <stdexcept>
#include <string>

class dynamic_bitset {
private:
    int m_size = 0;
    char* bytes = nullptr;
public:
    bool operator[](int index) {
        if (index < m_size) {
            return bytes[index / 8] >> (index % 8) & 1;
        }
        else {
            throw std::out_of_range("Specified bitset index is out of range!");
        }
    }
    int size() {
        return m_size;
    }
    std::string get_string() {
        std::string binary = "";
        for (int i = 0; i < m_size; i++) {
            binary += std::to_string(((bytes[i / 8] >> (i % 8)) & 1));
        }
        return binary;
    }
    void set(int index) {
        if (index < m_size) {
            bytes[index / 8] |= 1 << (index % 8);
        }
        else {
            throw std::out_of_range("Specified bitset index is out of range!");
        }
    }
    void unset(int index) {
        if (index < m_size) {
            bytes[index / 8] &= ~(1 << (index % 8));
        }
        else {
            throw std::out_of_range("Specified bitset index is out of range!");
        }
    }
    void toggle(int index) {
        if (index < m_size) {
            bytes[index / 8] ^= 1 << (index % 8);
        }
        else {
            throw std::out_of_range("Specified bitset index is out of range!");
        }
    }
    void pop(int index) {
        if (index < m_size) {
            char* new_bytes = new char[((m_size - 1) % 8 == 0) ? ((m_size - 1) / 8) : ((m_size - 1) / 8 + 1)](); // Calculate amount of bytes needed to store new size
            for (int i = 0; i < index; i++) {
                if (((bytes[i / 8] >> (i % 8)) & 1) == 1) new_bytes[i / 8] |= (1 << (i % 8)); // If bits[i] is 1, set new bits[i] to 1
                else new_bytes[i / 8] &= ~(1 << (i % 8)); // If bits[i] is 0, set new bits[i] to 0
            }
            for (int i = index; i < m_size; i++) {
                if (((bytes[i / 8] >> (i % 8)) & 1) == 1) new_bytes[(i - 1) / 8] |= (1 << ((i - 1) % 8)); // If bits[i] is 1, set new bits[i-1] to 1
                else new_bytes[(i - 1) / 8] &= ~(1 << ((i - 1) % 8)); // If bits[i] is 0, set new bits[i-1] to 0
            }

            m_size--; // Update size

            bytes = NULL;
            delete[] bytes;
            bytes = new_bytes;
            new_bytes = NULL;
            delete[] new_bytes;
        }
        else {
            throw std::out_of_range("Specified bitset index is out of range!");
        }
    }
    void push_back(bool bit) {
        char* new_bytes = new char[((m_size + 1) % 8 == 0) ? ((m_size + 1) / 8) : ((m_size + 1) / 8 + 1)](); // Calculate amount of bytes needed to store new size
        for (int i = 0; i < m_size; i++) {
            if (((bytes[i / 8] >> (i % 8)) & 1) == 1) new_bytes[i / 8] |= (1 << (i % 8)); // If bits[i] is 1, set new bits[i] to 1
            else new_bytes[i / 8] &= ~(1 << (i % 8)); // If bits[i] is 0, set new bits[i] to 0
        }
        if (bit == 1) new_bytes[(m_size + 1) / 8] |= 1 << (m_size % 8); // If new bit is 1 set new bits[last] to 1
        else new_bytes[(m_size + 1) / 8] &= ~(1 << (m_size % 8)); // If new bit is 0 set new bits[last] to 0

        m_size++; // Update size

        bytes = NULL;
        delete[] bytes;
        bytes = new_bytes;
        new_bytes = NULL;
        delete[] new_bytes;
    }
    void destroy() {
        delete[] bytes;
    }
};
