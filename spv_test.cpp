#include <gtest/gtest.h>
#include "sp_vector_ni.h"
using namespace std;

// sparse vector tests
TEST(SparseVector, defaultCtorCounts)
{
    sparse_vector<int> spv_int;
    EXPECT_EQ(spv_int.size(), 10);
    EXPECT_EQ(spv_int.nd_count(), 0);

    sparse_vector<float> spv_float;
    EXPECT_EQ(spv_float.size(), 10);
    EXPECT_EQ(spv_float.nd_count(), 0);
}

TEST(SparseVector, ctorCounts)
{
    sparse_vector<double> spv_double(666);
    EXPECT_EQ(spv_double.size(), 666);
    EXPECT_EQ(spv_double.nd_count(), 0);

    sparse_vector<std::string> spv_string(42);
    EXPECT_EQ(spv_string.size(), 42);
    EXPECT_EQ(spv_string.nd_count(), 0);
}

TEST(SparseVector, constIndexingDefaultElements)
{
    const sparse_vector<int> spv_int(5);
    for (size_t idx = 0; idx < spv_int.size(); ++idx)
        EXPECT_EQ(spv_int[idx], int());

    const sparse_vector<bool> spv_bool(7);
    for (size_t idx = 0; idx < spv_bool.size(); ++idx)
        EXPECT_EQ(spv_bool[idx], bool());
}

TEST(SparseVector, constIndexingExceptions)
{
    const sparse_vector<float> spv_float(5);
    EXPECT_THROW(spv_float[-1], std::invalid_argument);
    EXPECT_THROW(spv_float[spv_float.size()], std::invalid_argument);

    const sparse_vector<string> spv_string(123456789);
    EXPECT_THROW(spv_string[-76543210], std::invalid_argument);
    EXPECT_THROW(spv_string[spv_string.size() + 12345678], std::invalid_argument);
}

TEST(SparseVector, indexingWithAssignmentOne)
{
    sparse_vector<int> spv_int(5);
    EXPECT_EQ(spv_int[0], int());
    EXPECT_EQ(spv_int.size(), 5);
    EXPECT_EQ(spv_int.nd_count(), 1);

    spv_int[0] = 42;
    EXPECT_EQ(spv_int[0], 42);
    EXPECT_EQ(spv_int.nd_count(), 1);
}

TEST(SparseVector, indexingWithAssignmentTwo)
{
    sparse_vector<string> spv_string(11);
    EXPECT_EQ(spv_string[spv_string.size()-1], std::string());
    EXPECT_EQ(spv_string.size(), 11);
    EXPECT_EQ(spv_string.nd_count(), 1);

    spv_string[spv_string.size()-1] = "last";
    EXPECT_EQ(spv_string[spv_string.size()-1], "last");
    EXPECT_EQ(spv_string.nd_count(), 1);

    spv_string[0] = "first";
    EXPECT_EQ(spv_string.size(), 11);
    EXPECT_EQ(spv_string.nd_count(), 2);
    EXPECT_EQ(spv_string[0], "first");
}

TEST(SparseVector, indexingWithAssignmentAll)
{
    sparse_vector<float> spv_float(7);
    for (size_t idx = 0; idx < spv_float.size(); ++idx)
        spv_float[idx] = (float) idx;

    EXPECT_EQ(spv_float.size(), 7);
    EXPECT_EQ(spv_float.nd_count(), 7);
    for (size_t idx = 0; idx < spv_float.size(); ++idx)
        EXPECT_EQ(spv_float[idx], (float) idx);

    EXPECT_EQ(spv_float.size(), 7);
    EXPECT_EQ(spv_float.nd_count(), 7);
}

TEST(SparseVector, constIndexingNonDefaults)
{
    sparse_vector<int> spv_int(17);
    for (size_t idx = 0; idx < spv_int.size(); ++idx)
        spv_int[idx] = idx - 9;

    const sparse_vector<int> spv_cpy(spv_int);
    EXPECT_EQ(spv_cpy.size(), 17);
    EXPECT_EQ(spv_cpy.nd_count(), 17);
    for (size_t idx = 0; idx < spv_cpy.size(); ++idx)
        EXPECT_EQ(spv_cpy[idx], idx - 9);
}

TEST(SparseVector, clear)
{
    sparse_vector<float> spv_float(777);
    for (size_t idx = 0; idx < spv_float.size(); idx += 37)
        spv_float[idx] = (float) idx;

    EXPECT_EQ(spv_float.size(), 777);
    EXPECT_EQ(spv_float.nd_count(), 777 / 37);

    spv_float.clear();
    EXPECT_EQ(spv_float.size(), 777);
    EXPECT_EQ(spv_float.nd_count(), 0);
}

TEST(SparseVector, insertOperatorEmpty)
{
    std::stringstream ss;
    ss << sparse_vector<int>(0);
    EXPECT_EQ(ss.str(), "[]");
}

TEST(SparseVector, insertOperatorDefault)
{
    std::stringstream ss;
    ss << sparse_vector<int>();
    EXPECT_EQ(ss.str(), "[0 0 0 0 0 0 0 0 0 0 ]");
}

TEST(SparseVector, insertOperator)
{
    sparse_vector<int> spv_int(12);
    for (size_t idx = 0; idx < spv_int.size(); idx += 2)
        spv_int[idx] = idx;

    std::stringstream ss;
    ss << spv_int;
    EXPECT_EQ(ss.str(), "[0 0 2 0 4 0 6 0 8 0 10 0 ]");
}
