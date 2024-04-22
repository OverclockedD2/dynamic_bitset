# C++ dynamic bitset

This is a header-only dynamic bitset developed in C++20, but probably works for other versions as well. This is also doesn't cause CUDA to freak out when included. This library has includes the most basic features a bitset needs: `push_i`, `pop_i`, `set_i`, `set`, `unset_i`, `unset`, `toggle_i`, `toggle`, `swap`, `reverse`, `set_string`, `get_string`, `get_bit`, `destroy`. More about all of those functions later. This library can defintetely be improved in terms of performance and memory useage, but the current version does a pretty good job, the amount of bytes that the data container takes up is calculated like this: `floor(n_bits / 8)`, plus `sizeof(bool)` and `sizeof(int)`. The deconstructor of the bitset class deallocates all dynamically allocated memory, but if you wish, you can deallocate the memory before exit using `destroy()`. This library also does basic error checking, but some stuff might bypass, so be careful and try to avoid giving it invalid data.

> [!caution]
> MD5 CHECKSUM: 95f7fc2e21d53363db9df3a4cbff2733 (i used https://md5file.com/calculator)

### USAGE:
```c++
#include "dynamic_bitset.h" // include
#include <iostream>

int main() {
  dynamic_bitset::dynamic_bitset bitset; // define and construct bitset

  bitset.push_i(0, 1); // push bit 1 to index 0
  bitset.push_i(1, 0); // push bit 0 to index 1
  bitset.push_i(2, 1); // push bit 1 to index 2
  bitset.push_i(3, 0); // push bit 0 to index 3

  bitset.pop_i(0); // pop bit at index 0
  bitset.pop_i(1); // pop bit at index 1

  bitset.set_i(0); // give bit at index 0 value 1

  bitset.set(); // give all bits value 1

  bitset.unset_i(1); // give bit at index 1 value 0

  bitset.unset(); // give all bits value 0

  bitset.toggle_i(0); // toggle the value of bit at index 0

  bitset.toggle(); // toggle the value of all bits

  bitset.swap(0, 1); // swap the values of bits at index 0 and 1

  bitset.reverse(); // reverse the bits in bitset

  bitset.extend(5, 0); // extend the bitset with 5 bits which all have a default value 0

  bitset.set_string("1101001"); // set the contents of bitset to 1101001

  std::cout << bitset.get_string(); // get contents of bitset

  std::cout << bitset.get_bit(0); // get value of bit and index 0

  std::cout << "\n";

  bitset.destroy(); // destroy bitset (frees up some memory, not necessary as the deconstrucor also does this)
  return 0;
} // OUTPUT: 11010011
```

### STRUCTURE:

```c++
#pragma once
#include <string>
#include <exception>

namespace dynamic_bitset {
  class dynamic_bitset {
  public:
    bool initialized = false; // if bitset is initialized
    unsigned int size = 0; // amount of bits in bitset
    char* bytes = nullptr; // contains the bits

    void push_i(unsigned int index, bool bit); // push (insert) bit to index
    void pop_i(unsigned int index); // pop (remove) bit at index
    void set_i(unsigned int index); // set bit at index
    void set(); // set all bits
    void unset_i(unsigned int index); // unset bit at index
    void unset(); // unset all bits
    void toggle_i(unsigned int index); // toggle bit at index
    void toggle(); // toggle all bits
    void swap(unsigned int index_1, unsigned int index_2); // swap bits at index_1 and index_2
    void reverse(); // reverse the order of bits in bitset
    void extend(unsigned int amount, bool default_bit); // add bits with default value

    void set_string(std::string input); // set the contents bitset using string, example "1101001"
    std::string get_string(); // get the contents of the bitset in string format
    bool get_bit(unsigned int index); // get the value of bit at index

    dynamic_bitset(); // constructor
    ~dynamic_bitset(); // deconstructor
    void destroy(); // deallocate the bit container and set bitset to uninitialized
  }
}
```
