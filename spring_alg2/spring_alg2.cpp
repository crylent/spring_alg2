#include <iostream>
#include <conio.h>
#include "Coder.h"

using namespace std;

int main()
{
	cout << "Press Ctrl+D, then Enter when finished typing\n\n";
	string input;
	char c;
	while ((c = cin.get()) != 4) {
		input += c;
	}
	int init_size = input.size() * 8; // initial size
	printf("Memory: %d bits\n\n", init_size);
	Counter::Sorted* counter;
	Coder::EncodedString* encoded = Coder::encode(input, &counter);
	cout << "Frequency table:\n";
	for (int i = counter->size - 1; i >= 0; i--) {
		char k = counter->keys[i];
		if (k != '\n') printf("   %c", counter->keys[i]);
		else printf("  \\n");
	}
	cout << '\n';
	for (int i = counter->size - 1; i >= 0; i--) {
		printf(" %3d", *counter->values[i]);
	}
	cout << "\n\nEncoding/decoding table:\n";
	RDictionary* dict = encoded->dictionary;
	int dict_size = dict->get_size();
	const int line_size = 15;
	int i = 0, j = 0;
	while (i < dict_size) {
		bool skip_check = true;
		for (; i < dict_size; i++) {
			char k = dict->get_values()[i];
			if (k != '\n') printf("          %c", dict->get_values()[i]);
			else printf("         \\n");
			if (i % line_size == 0 && !skip_check) {
				break;
			}
			skip_check = false;
		}
		cout << '\n';
		skip_check = true;
		for (; j < dict_size; j++) {
			printf(" %10s", dict->get_keys()[j].c_str());
			if (j % line_size == 0 && !skip_check) {
				break;
			}
			skip_check = false;
		}
		cout << '\n';
	}
	cout << "\nEncoded string:\n" << encoded->str << '\n';
	int res_size = encoded->nospaces.size(); // size after compression
	double k = double(init_size) / res_size;
	printf("Memory: %d bits\nCompression efficiency: %f\n", res_size, k);
	string decoded = Coder::decode(encoded->str, encoded->dictionary);
	cout << "After decoding:\n" << decoded << '\n';
}