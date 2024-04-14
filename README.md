# C++ CUDA compatible, header-only dynamic bitset

I didn't get any other dynamic bitset libraries to work with CUDA so I decided to make one quickly. I added some basic functions such as `set`, `unset`, `toggle`, `get_string`, `pop` and `push_back`.

### USAGE:

```c++
#include <iostream>
#include "dynamic_bitset.h"

int main() {
  dynamic_bitset bitset;
  bitset.push_back(0); // bit at index 0 = false
  bitset.push_back(1); // bit at index 1 = true
  bitset.push_back(1); // bit at index 2 = true

  bitset.unset(0); // bit at index 0 = false
  bitset.unset(1); // bit at index 1 = false

  bitset.set(1); // bit at index 1 = true
  bitset.set(2); // bit at index 2 = true

  bitset.toggle(0); // bit at index 0 = true
  bitset.toggle(0); // bit at index 0 = false

  std::cout << bitset.size() << "\n"; // prints the size of bitset, output: 3
  bitset.pop(1) // remove element at index 1
  std::cout << bitset.size() << "\n"; // prints the size of bitset, output: 2

  std::cout << bitset.get_string() << "\n"; // outputs the string representation of the bitset, output: 01

  bitset.destroy(); // deallocate memory, not calling this will cause memory leaks!

  return 0;
}

```

### STRUCTURE:

```c++
class dynamic_bitset {
private:
  int m_size = 0; // amount of bits in bitset (private variable)
  int* bytes = nullptr; // the actual data container (private variable)
public:
  bool operator[](int index); // the array index operator overload
  int size(); // returns m_size
  std::string get_string(); // returns the string representation of the bitset
  void set(int index); // set bit at index
  void unset(int index); // unset a bit at index
  void toggle(int index); // toggle the value of the bit at index
  void pop(int index); // remove bit at index from bitset
  void push_back(bool bit); // pushes a new bit to the end of the bitset
  void destroy(); // deallocates memory, not calling this will cause memory leaks!
}
```
