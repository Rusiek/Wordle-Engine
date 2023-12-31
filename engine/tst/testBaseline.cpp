#include <gtest/gtest.h>
#include <vector>
#include "../algorithm.hpp"
#include "../baseline.hpp"

class TestBaseline : public ::testing::Test
{
public:
    static const engine::Baseline instance_s;
};

TEST_F(TestBaseline, TestGetAllOkWords1)
{
    const std::vector<std::string> ans_list{"xxxxx"};
    const std::array<uint8_t, engine::word_size> ans_info_1{
        {engine::correct_pos,
        engine::not_in_word,
        engine::not_in_word,
        engine::not_in_word,
        engine::not_in_word}};
    const std::vector<std::array<uint8_t, engine::word_size>> ans_info{ans_info_1};
    const std::vector<std::string> dataset{"abcde", "xyztq", "makao"};
    std::unique_ptr<std::vector<std::string>> possible_ans{std::make_unique<std::vector<std::string>>(dataset)};

    const auto result = TestBaseline::instance_s.get_all_ok_words(ans_list, ans_info, &possible_ans);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.at(0), "xyztq");
}

TEST_F(TestBaseline, TestGetAllOkWords2)
{
    const std::vector<std::string> ans_list{"xxxxx"};
    const std::array<uint8_t, engine::word_size> ans_info_1{
        {engine::correct_pos,
        engine::not_in_word,
        engine::not_in_word,
        engine::correct_pos,
        engine::not_in_word}};
    const std::vector<std::array<uint8_t, engine::word_size>> ans_info{ans_info_1};
    const std::vector<std::string> dataset{"abcde", "xxxxx", "xyztq", "makao", "xqqxq", "qqqxq"};
    std::unique_ptr<std::vector<std::string>> possible_ans{std::make_unique<std::vector<std::string>>(dataset)};

    const auto result = TestBaseline::instance_s.get_all_ok_words(ans_list, ans_info, &possible_ans);
    const std::vector<std::string> expected{"xxxxx", "xqqxq"};
    EXPECT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST_F(TestBaseline, TestGetAllOkWords3)
{
    const std::vector<std::string> ans_list{"xxxxx", "aaaaa"};
    const std::array<uint8_t, engine::word_size> ans_info_1{
        {engine::wrong_pos,
        engine::not_in_word,
        engine::not_in_word,
        engine::correct_pos,
        engine::not_in_word}};
    const std::array<uint8_t, engine::word_size> ans_info_2{
        {engine::correct_pos,
        engine::not_in_word,
        engine::not_in_word,
        engine::correct_pos,
        engine::not_in_word}};
    const std::vector<std::array<uint8_t, engine::word_size>> ans_info{ans_info_1, ans_info_2};
    const std::vector<std::string> dataset{"abbab", "bbbab", "abbbb", "xxxxx", "qbbab", "azzaa", "aaaaa"};
    std::unique_ptr<std::vector<std::string>> possible_ans{std::make_unique<std::vector<std::string>>(dataset)};

    const auto result = TestBaseline::instance_s.get_all_ok_words(ans_list, ans_info, &possible_ans);
    const std::vector<std::string> expected{"abbab", "azzaa", "aaaaa"};
    EXPECT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST_F(TestBaseline, TestSolFunction1a)
{
    const std::string test_path = "test";
    engine::Baseline instance(test_path, test_path, "makao");

    const std::vector<std::string> ans_list{};
    const std::vector<std::array<uint8_t, engine::word_size>> ans_info{};
    const std::vector<std::string> dataset{"abcde", "xyztq", "makao"};
    std::unique_ptr<std::vector<std::string>> possible_ans{std::make_unique<std::vector<std::string>>(dataset)};

    const auto result = instance.sol_function(ans_list, ans_info, &possible_ans);
    EXPECT_EQ(result, "makao");
    EXPECT_EQ(possible_ans->size(), dataset.size() - 1);
}

TEST_F(TestBaseline, TestSolFunction1b)
{
    const std::string test_path = "test";
    engine::Baseline instance(test_path, test_path, "abcde");

    const std::vector<std::string> ans_list{};
    const std::vector<std::array<uint8_t, engine::word_size>> ans_info{};
    const std::vector<std::string> dataset{"abcde", "xyztq", "makao"};
    std::unique_ptr<std::vector<std::string>> possible_ans{std::make_unique<std::vector<std::string>>(dataset)};

    const auto result = instance.sol_function(ans_list, ans_info, &possible_ans);
    EXPECT_EQ(result, "abcde");
    EXPECT_EQ(possible_ans->size(), dataset.size() - 1);
}

TEST_F(TestBaseline, TestSolFunction2)
{
    const std::string test_path = "test";
    engine::Baseline instance(test_path, test_path, "xxxxx");

    const std::vector<std::string> ans_list{"xxxxx"};
    const std::array<uint8_t, engine::word_size> ans_info_1{
        {engine::correct_pos,
        engine::not_in_word,
        engine::not_in_word,
        engine::not_in_word,
        engine::not_in_word}};
    const std::vector<std::array<uint8_t, engine::word_size>> ans_info{ans_info_1};
    const std::vector<std::string> dataset{"abcde", "xyztq", "makao"};
    std::unique_ptr<std::vector<std::string>> possible_ans{std::make_unique<std::vector<std::string>>(dataset)};

    const auto result = instance.sol_function(ans_list, ans_info, &possible_ans);
    EXPECT_EQ(result, "xyztq");
    EXPECT_EQ(possible_ans->size(), 0);
}

TEST_F(TestBaseline, TestSolFunction3)
{
    const std::string test_path = "test";
    engine::Baseline instance(test_path, test_path, "xxxxx");

    const std::vector<std::string> ans_list{"xxxxx"};
    const std::array<uint8_t, engine::word_size> ans_info_1{
        {engine::correct_pos,
        engine::not_in_word,
        engine::not_in_word,
        engine::correct_pos,
        engine::not_in_word}};
    const std::vector<std::array<uint8_t, engine::word_size>> ans_info{ans_info_1};
    const std::vector<std::string> dataset{"abcde", "xxxxx", "xyztq", "makao", "xqqxq", "qqqxq"};
    std::unique_ptr<std::vector<std::string>> possible_ans{std::make_unique<std::vector<std::string>>(dataset)};

    const auto result = instance.sol_function(ans_list, ans_info, &possible_ans);
    EXPECT_EQ(result, "xqqxq");
    EXPECT_EQ(possible_ans->size(), 1);
}

TEST_F(TestBaseline, TestSolFunction4)
{
    const std::string test_path = "test";
    engine::Baseline instance(test_path, test_path, "xxxxx");

    std::vector<std::string> ans_list{};
    std::vector<std::array<uint8_t, engine::word_size>> ans_info{};
    const std::vector<std::string> dataset{"abbab", "bbbab", "abbbb", "qbbab", "azzaz", "aaaaa", "xxxxx"};
    std::unique_ptr<std::vector<std::string>> possible_ans{std::make_unique<std::vector<std::string>>(dataset)};

    const std::string solution = "azzaz";
    auto result = instance.sol_function(ans_list, ans_info, &possible_ans);
    EXPECT_EQ(ans_list.size(), 0);
    EXPECT_EQ(ans_info.size(), 0);
    EXPECT_EQ(result, "xxxxx");
    EXPECT_EQ(possible_ans->size(), dataset.size() - 1);

    ans_list.push_back(result);
    ans_info.push_back(instance.validate_ans(result, solution));

    result = instance.sol_function(ans_list, ans_info, &possible_ans);
    EXPECT_EQ(ans_list.size(), 1);
    EXPECT_EQ(ans_list.at(0), "xxxxx");
    EXPECT_EQ(ans_info.size(), 1);
    for (auto & chr : ans_info.at(0))
    {
        EXPECT_EQ(chr, engine::not_in_word);
    }
    EXPECT_EQ(result, "aaaaa");
    EXPECT_EQ(possible_ans->size(), dataset.size() - 2);

    ans_list.push_back(result);
    ans_info.push_back(instance.validate_ans(result, solution));

    result = instance.sol_function(ans_list, ans_info, &possible_ans);
    EXPECT_EQ(ans_list.size(), 2);
    EXPECT_EQ(ans_list.at(1), "aaaaa");
    EXPECT_EQ(ans_info.size(), 2);
    EXPECT_EQ(ans_info.at(1).at(0), engine::correct_pos);
    EXPECT_EQ(ans_info.at(1).at(1), engine::not_in_word);
    EXPECT_EQ(ans_info.at(1).at(2), engine::not_in_word);
    EXPECT_EQ(ans_info.at(1).at(3), engine::correct_pos);
    EXPECT_EQ(ans_info.at(1).at(4), engine::not_in_word);
    EXPECT_EQ(result, "azzaz");
    EXPECT_EQ(possible_ans->size(), 1);
}
