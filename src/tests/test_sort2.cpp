#include "SortData.h"
#include "Sorter.h"
#include <chrono>
#include <gtest/gtest.h>

TEST(test_select, MeasureSortTime)
{
    Sorter* sorter = new Sorter();
    SortData<float, std::vector> data;
    int dsize = 128 + rand() % 100;
    for (unsigned i = 0; i < dsize; i++) data.add(float(rand() % 1024) / 4096);
    auto start_unsorted = std::chrono::high_resolution_clock::now();
    auto error_unsorted = sorter->sort<float, std::vector, STT_SELECT>(data);
    auto end_unsorted = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_unsorted =
        end_unsorted - start_unsorted;
    std::cout << "Sorting time (unsorted): " << duration_unsorted.count()
              << " ms" << std::endl;
    ASSERT_TRUE(std::is_sorted(data.data().begin(), data.data().end()));
    ASSERT_EQ(error_unsorted, SE_SUCCESS);
    auto start_sorted = std::chrono::high_resolution_clock::now();
    auto error_sorted = sorter->sort<float, std::vector, STT_SELECT>(data);
    auto end_sorted = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_sorted =
        end_sorted - start_sorted;
    std::cout << "Sorting time (already sorted): " << duration_sorted.count()
              << " ms" << std::endl;
    ASSERT_TRUE(std::is_sorted(data.data().begin(), data.data().end()));
    ASSERT_EQ(error_sorted, SE_SUCCESS);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}