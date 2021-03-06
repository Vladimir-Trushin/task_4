/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */

#include <iostream>
#include <stdlib.h>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
using namespace bullpgia;

#define RAND_SORT_LEN 10 //
#define RAND_LEN 100	 // to increase or decrease the length of the random number (smarty test case)

int main()
{
	try
	{

		ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};
		cout << play(c1234, g1234, 4, 100) << "  : "; // prints 1 - guesser wins in one turn.
		cout << "prints 1   - guesser wins in one turn." << endl;
		cout << play(c1234, g9999, 4, 100) << ": "; // prints 101 - guesser loses by running out of turns.
		cout << "prints 101 - guesser loses by running out of turns." << endl;
		cout << play(c1234, g12345, 4, 100) << ": "; // prints 101 - guesser loses technically by making an illegal guess (too long).
		cout << "prints 101 - guesser loses technically by making an illegal guess (too long)." << endl;
		cout << play(c12345, g1234, 4, 100) << "  : "; // prints 0 - chooser loses technically by choosing an illegal number (too long).
		cout << "prints 0   - chooser loses technically by choosing an illegal number (too long)." << endl;

		RandomChooser randy;
		RandomGuesser guessy;
		cout << endl;
		cout << endl;
		cout << "Random guesser";
		uint bad = 0;
		for (uint i = 0; i < 100; ++i) // guesser should often win but sometimes lose.
		{
			int num = play(randy, guessy, 2, 100);

			if (i % 10 == 0)
				cout << endl;

			if (-1 < num && num < 10)
				cout << num << "    ";
			else if (10 <= num && num < 100)
				cout << num << "   ";
			else
			{
				bad++;
				cout << "BAD"
					 << "  ";
			}
		}
		cout << endl;
		cout << endl;
		cout << "BAD : " << bad << endl;
		cout << "GOOD: " << (100 - bad) << endl;

		cout << endl;
		cout << endl;

		SmartGuesser smarty;

		cout << "Smart guesser test: length = 4" << endl;
		cout << "Maximum possible steps for number with length = n = 2^x: n*log(n) + 10" << endl;
		cout << "For this example length = n = 4 and max steps 100";
		for (uint i = 0; i < 100; ++i)
		{
			int num = play(randy, smarty, 4, 100); // smarty should always win in at most 10 turns!

			if (i % 10 == 0)
				cout << endl;

			if (-1 < num && num < 10)
				cout << num << "  ";
			else
				cout << num << " ";
		}

		cout << endl;
		cout << endl;
		cout << endl;

		cout << "Smart guesser test: short length" << endl;
		cout << "Possible steps for random number with short length = n: ~ n*log(n) + 15" << endl;
		cout << "For this example length = random[0, 10] and max steps: n*log(n) + 15" << endl;

		bad = 0;
		for (uint i = 0; i < 100; ++i)
		{
			int len = (rand() % RAND_SORT_LEN);
			int max = len * SmartGuesser::log2(len) + 15; // n*log(n) + 15
			int num = play(randy, smarty, len, max);

			if (num > max)
			{
				bad++;
				cout << "steps: " << num;
				cout << "        \t max steps: " << max;
				cout << "        \t length: " << len;
				cout << "\t BAD";
			}
			else
			{
				cout << "steps: " << num;
				cout << "        \t max steps: " << max;
				cout << "        \t length: " << len;
				cout << "        \t max - steps: " << (max - num);
			}

			cout << endl;
		};
		cout << endl;
		cout << "BAD : " << bad << endl;
		cout << "GOOD: " << (100 - bad) << endl;

		cout << endl;
		cout << endl;

		cout << "Smart guesser test: big length" << endl;
		cout << "Possible steps for random number with big length = n: ~ n*log(n)" << endl;
		cout << "For this example length = random[20, 100] and max steps: n*log(n)" << endl;

		bad = 0;
		for (uint i = 0; i < 100; ++i)
		{
			int len = (20 + (rand() % (RAND_LEN - 20)));
			int max = len * SmartGuesser::log2(len); // n*log(n)
			int num = play(randy, smarty, len, max);

			if (num > max)
			{
				bad++;
				cout << "steps: " << num;
				cout << "        \t max steps: " << max;
				cout << "        \t length: " << len;
				cout << "\t BAD";
			}
			else
			{
				cout << "steps: " << num;
				cout << "        \t max steps: " << max;
				cout << "        \t length: " << len;
				cout << "        \t max - steps: " << (max - num);
			}

			cout << endl;
		};
		cout << endl;
		cout << "BAD : " << bad << endl;
		cout << "GOOD: " << (100 - bad) << endl;
	}
	catch (std::exception ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}
