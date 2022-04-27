#include "pch.h"
#include "CppUnitTest.h"
#include "../spring_alg2/spring_alg2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace springtest2
{
	TEST_CLASS(springtest2)
	{
	public:
		
		TEST_METHOD(TestCounter)
		{
			Counter* map = new Counter();
			map->insert('a', new int{ 1 });
			map->insert('b', new int{ 6 });
			map->insert('c', new int{ 4 });
			map->insert('d', new int{ 3 });
			map->insert('e', new int{ 5 });
			map->insert('f', new int{ 2 });
			Counter::Sorted* sorted = map->get_sorted();
			int** values = sorted->values;
			for (int i = 0; i < 6; i++) {
				Assert::AreEqual(i + 1, values[i][0]);
			}
		}

		TEST_METHOD(TestDecode)
		{
			RDictionary* dict = new RDictionary();
			dict->insert("111", 'i');
			dict->insert("01", 't');
			dict->insert("110", ' ');
			dict->insert("10", 's');
			dict->insert("0011", 'e');
			dict->insert("0010", 'r');
			dict->insert("0001", 'n');
			dict->insert("0000", 'g');
			std::string encoded = "111 01 110 111 10 110 01 0011 10 01 110 10 01 0010 111 0001 0000";
			std::string decoded = Coder::decode(encoded, dict);
			std::string expected = "it is test string";
			Assert::AreEqual(expected, decoded);
		}

		TEST_METHOD(TestEncodeAndDecode)
		{
			std::string str = "it is test string";
			Coder::EncodedString* encoded = Coder::encode(str);
			std::string decoded = Coder::decode(encoded->str, encoded->dictionary);
			Assert::AreEqual(str, decoded);
		}
	};
}
