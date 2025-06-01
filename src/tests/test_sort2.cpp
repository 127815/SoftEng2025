#include <gtest/gtest.h>
#include "Sorter.h"
#include "SortData.h"
#include <chrono>

TEST(test_select, MeasureSortTime)
{
	// Ustawiamy generator liczb losowych
	srand(static_cast<unsigned>(time(NULL)));

	Sorter* sorter = new Sorter();
	SortData<float, std::vector> data;

	// Losujemy rozmiar od 128 do 227
	int dsize = 128 + (rand() % 100);
	for (unsigned i = 0; i < static_cast<unsigned>(dsize); ++i) {
		float value = float(rand() % 1024) / 4096.0f;
		data.add(value);
	}

	// Pierwsze sortowanie na nieposortowanych danych
	auto start_unsorted = std::chrono::high_resolution_clock::now();
	SortError error_unsorted = sorter->sort<float, std::vector, STT_SELECT>(data);
	auto end_unsorted = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration_unsorted = end_unsorted - start_unsorted;

	std::cout << "Sorting time (unsorted): " << duration_unsorted.count() << " ms\n";

	// Sprawdzamy, czy dane s¹ posortowane rosn¹co i czy zwrócono SE_SUCCESS
	ASSERT_EQ(error_unsorted, SE_SUCCESS);
	{
		const auto& container = data.data();
		for (size_t i = 1; i < container.size(); ++i) {
			ASSERT_LE(container[i - 1], container[i])
				<< "Wektor float po pierwszym sortowaniu nie jest posortowany na pozycji " << i;
		}
	}

	// Drugie sortowanie na ju¿ posortowanych danych
	auto start_sorted = std::chrono::high_resolution_clock::now();
	SortError error_sorted = sorter->sort<float, std::vector, STT_SELECT>(data);
	auto end_sorted = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration_sorted = end_sorted - start_sorted;

	std::cout << "Sorting time (already sorted): " << duration_sorted.count() << " ms\n";

	ASSERT_EQ(error_sorted, SE_SUCCESS);
	{
		const auto& container = data.data();
		for (size_t i = 1; i < container.size(); ++i) {
			ASSERT_LE(container[i - 1], container[i])
				<< "Wektor float po drugim sortowaniu (ju¿ posortowany) nie jest posortowany na pozycji " << i;
		}
	}

	delete sorter;
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
