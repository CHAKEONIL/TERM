#include <random>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

const double PI = 3.14159265358979;
const double DEG2RAD = PI / 180.0;
const double e = 1.602e-19;
const int Z = 2;
const int Z_prime = 79;


double DCX(int E, int degree)
{
	double denom = Z * Z_prime * e * e;
	double numer = 4 * E;
	double theta = degree * DEG2RAD;

	return pow(denom / numer, 2) / (pow(sin(theta / 2), 4));
}

int main()
{
	std::random_device rd;
	std::mt19937 mt(rd());

    std::uniform_int_distribution<int> gen(1, 90);

	std::vector<int> Es = { 1,5,10 };
	std::vector<int> times = { 1000, 10000, 100000, 1000000 };
	std::vector<double> avgs;
	avgs.reserve(Es.size() * times.size());

	for (const int E : Es)
	{
		for (const int t : times)
		{
			std::stringstream fileName;
			fileName << "E=" << E << ", " << t << "times.txt";

			std::ofstream fs(fileName.str());

			if (!fs.is_open())
			{
				std::cout << "File open failed!" << std::endl;
				return -1;
			}
			fs << "time \t generated degree \t dcx value\n";

			double avg = 0;
			for (int i = 0; i < t; i++)
			{
				std::stringstream oss;

				int rad = gen(mt);
				double dcx = DCX(E, rad);
				avg += dcx;

				oss << i << "\t" << rad << "\t" << dcx << "\n";
				fs << oss.str();
			}
			avg /= static_cast<double>(t);

			avgs.push_back(avg);
			fs << "average dcx = " << avg << "\n";

			std::cout << "E = " << E << ", " << t << " times average dcx = " << avg << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}
