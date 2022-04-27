#include <iostream>
#include "Coder.h"

using namespace std;

int main()
{
	string input;
	char c;
	while ((c = cin.get()) != '\n') {
		input += c;
	}
	int init_size = input.size() * 8; // initial size
	printf("Memory: %d bits\n\n", init_size);
	Counter::Sorted* counter;
	Coder::EncodedString* encoded = Coder::encode(input, &counter);
	cout << "Frequency table:\n";
	for (int i = counter->size - 1; i >= 0; i--) {
		printf("  %c", counter->keys[i]);
	}
	cout << '\n';
	for (int i = counter->size - 1; i >= 0; i--) {
		printf(" %2d", *counter->values[i]);
	}
	cout << "\n\nEncoding/decoding table:\n";
	RDictionary* dict = encoded->dictionary;
	int dict_size = dict->get_size();
	for (int i = 0; i < dict_size; i++) {
		printf("    %c", dict->get_values()[i]);
	}
	cout << '\n';
	for (int i = 0; i < dict_size; i++) {
		printf(" %4s", dict->get_keys()[i].c_str());
	}
	cout << "\n\nEncoded string:\n" << encoded->str << '\n';
	int res_size = encoded->nospaces.size(); // size after compression
	double k = double(init_size) / res_size;
	printf("Memory: %d bits\nCompression efficiency: %f\n", res_size, k);
	string decoded = Coder::decode(encoded->str, encoded->dictionary);
	cout << "After decoding: " << decoded << '\n';
}