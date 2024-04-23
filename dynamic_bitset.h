/*
*                       dynamic_bitset.h
*
*   This is a header-only, CUDA compatible dynamic bitset library.
*   Orignial version made by github.com/OverclockedD2. Make sure to
*   read the documentation: github.com/OverclockedD2/dynamic_bitset.
*
*                   Copyright (c) 2024 OverclockedD2
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

#include <string>
#include <exception>

namespace dynamic_bitset {
	class dynamic_bitset {
	public:
		bool initialized = false;
		unsigned int size = 0;
		char* bytes = nullptr;

		void push_i(unsigned int index, bool bit) {
			if (initialized) {
				if (index <= size) {
					char* new_bytes = new char[(++size + 7) / 8]();
					for (unsigned int i = 0; i < index; i++) {
						if ((((bytes[i / 8]) >> (i % 8)) & 1) == 1) {
							new_bytes[i / 8] |= 1 << (i % 8);
						}
						else {
							new_bytes[i / 8] &= ~(1 << (i % 8));
						}
					}
					if (bit == 1) {
						new_bytes[index / 8] |= 1 << (index % 8);
					}
					else {
						new_bytes[index / 8] &= ~(1 << (index % 8));
					}
					for (unsigned int i = index + 1; i < size; i++) {
						if ((((bytes[(i - 1) / 8]) >> ((i - 1) % 8)) & 1) == 1) {
							new_bytes[i / 8] |= 1 << (i % 8);
						}
						else {
							new_bytes[i / 8] &= ~(1 << (i % 8));
						}
					}
					delete[] bytes;
					bytes = new_bytes;

				}
				else {
					throw std::exception("[dynamic_bitset] ERROR: SPECIFIED INDEX OUT OF RANGE!");
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void pop_i(unsigned int index) {
			if (initialized) {
				if (index < size) {
					char* new_bytes = new char[(--size + 7) / 8]();
					for (unsigned int i = 0; i < index; i++) {
						if ((((bytes[i / 8]) >> (i % 8)) & 1) == 1) {
							new_bytes[i / 8] |= 1 << (i % 8);
						}
						else {
							new_bytes[i / 8] &= ~(1 << (i % 8));
						}
					}
					for (unsigned int i = index + 1; i < size + 1; i++) {
						if ((((bytes[i / 8]) >> (i % 8)) & 1) == 1) {
							new_bytes[(i - 1) / 8] |= 1 << ((i - 1) % 8);
						}
						else {
							new_bytes[(i - 1) / 8] &= ~(1 << ((i - 1) % 8));
						}
					}
					delete[] bytes;
					bytes = new_bytes;
				}
				else {
					throw std::exception("[dynamic_bitset] ERROR: SPECIFIED INDEX OUT OF RANGE!");
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void set_i(unsigned int index) {
			if (initialized) {
				if (index < size) {
					bytes[index / 8] |= 1 << (index % 8);
				}
				else {
					throw std::exception("[dynamic_bitset] ERROR: SPECIFIED INDEX OUT OF RANGE!");
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void set() {
			if (initialized) {
				for (unsigned int i = 0; i < size; i++) {
					bytes[i / 8] |= 1 << (i % 8);
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void unset_i(unsigned int index) {
			if (initialized) {
				if (index < size) {
					bytes[index / 8] &= ~(1 << (index % 8));
				}
				else {
					throw std::exception("[dynamic_bitset] ERROR: SPECIFIED INDEX OUT OF RANGE!");
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void unset() {
			if (initialized) {
				for (unsigned int i = 0; i < size; i++) {
					bytes[i / 8] &= ~(1 << (i % 8));
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void toggle_i(unsigned int index) {
			if (initialized) {
				if (index < size) {
					bytes[index / 8] ^= 1 << (index % 8);
				}
				else {
					throw std::exception("[dynamic_bitset] ERROR: SPECIFIED INDEX OUT OF RANGE!");
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void toggle() {
			if (initialized) {
				for (unsigned int i = 0; i < size; i++) {
					bytes[i / 8] ^= 1 << (i % 8);
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void swap(unsigned int index_1, unsigned int index_2) {
			if (initialized) {
				if (index_1 < size) {
					if (index_2 < size) {
						if (((bytes[index_1 / 8] >> (index_1 % 8)) & 1) == 1) {
							if (((bytes[index_2 / 8] >> (index_2 % 8)) & 1) == 1) {

							}
							else {
								bytes[index_1 / 8] &= ~(1 << (index_1 % 8));
								bytes[index_2 / 8] |= 1 << (index_2 % 8);
							}
						}
						else {
							if (((bytes[index_2 / 8] >> (index_2 % 8)) & 1) == 1) {
								bytes[index_1 / 8] |= 1 << (index_1 % 8);
								bytes[index_2 / 8] &= ~(1 << (index_2 % 8));
							}
							else {

							}
						}
					}
					else {
						throw std::exception("[dynamic_bitset] ERROR: SPECIFIED INDEX OUT OF RANGE!");
					}
				}
				else {
					throw std::exception("[dynamic_bitset] ERROR: SPECIFIED INDEX OUT OF RANGE!");
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void reverse() {
			if (initialized) {
				char* new_bytes = new char[(size + 7) / 8]();
				for (unsigned int i = 0; i < size; i++) {
					if (((bytes[i / 8] >> (i % 8)) & 1) == 1) {
						new_bytes[(size - i - 1) / 8] |= 1 << ((size - i - 1) % 8);
					}
					else {
						new_bytes[(size - i - 1) / 8] &= ~(1 << ((size - i - 1) % 8));
					}
				}
				delete[] bytes;
				bytes = new_bytes;
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		void extend(unsigned int amount, bool default_bit) {
			if (initialized) {
				char* new_bytes = new char[(size + amount + 7) / 8]();
				for (unsigned int i = 0; i < size; i++) {
					if (((bytes[i / 8] >> (i % 8)) & 1) == 1) {
						new_bytes[i / 8] |= 1 << (i % 8);
					}
					else {
						new_bytes[i / 8] &= ~(1 << (i % 8));
					}
				}
				if (default_bit == 1) {
					for (unsigned int i = size; i < size + amount; i++) {
						new_bytes[i / 8] |= 1 << (i % 8);
					}
				}
				else {
					for (unsigned int i = size; i < size + amount; i++) {
						new_bytes[i / 8] &= ~(1 << (i % 8));
					}
				}

				size += amount;

				delete[] bytes;
				bytes = new_bytes;
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}

		void set_string(std::string input) {
			if (initialized) {
				char* new_bytes = new char[(input.length() + 7) / 8]();
				for (unsigned int i = 0; i < input.length(); i++) {
					if (input[i] == '1') {
						new_bytes[i / 8] |= 1 << (i % 8);
					}
					else if (input[i] == '0') {
						new_bytes[i / 8] &= ~(1 << (i % 8));
					}
					else {
						throw std::exception("[dynamic_bitset] ERROR: INVALID CHARACTER IN INPUT STRING!");
					}
				}
				size = input.length();

				delete[] bytes;
				bytes = new_bytes;
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
		}
		std::string get_string() {
			if (initialized) {
				std::string output = "";
				for (unsigned int i = 0; i < size; i++) {
					if (((bytes[i / 8] >> (i % 8)) & 1) == 1) {
						output += '1';
					}
					else {
						output += '0';
					}
				}
				return output;
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED BITSET HAS NOT BEEN INITIALIZED!");
			}
			return "";
		}
		bool get_bit(unsigned int index) {
			if (initialized) {
				if (index < size) {
					return (bytes[index / 8] >> (index % 8)) & 1;
				}
			}
			else {
				throw std::exception("[dynamic_bitset] ERROR: SPECIFIED INDEX OUT OF RANGE!");
			}
			return 0;
		}


		dynamic_bitset() {
			if (not initialized) {
				initialized = true;
				size = 0;
				bytes = new char[0];
			}
		}
		~dynamic_bitset() {
			if (initialized) {
				initialized = false;
				delete[] bytes;
			}
		}
		void destroy() {
			if (initialized) {
				initialized = false;
				delete[] bytes;
			}
		}
	};
}
