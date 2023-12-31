#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "utils/utils.hpp"

namespace engine 
{
enum output_status 
{ 
    correct_pos = 0, 
    wrong_pos = 1, 
    not_in_word = 2
};

class Base 
{
public:
    Base(
        const std::string & input_path,
        const std::string & output_path,
        const std::string & starting_word);
    Base(const Base &) = delete;
    Base(Base &&) = delete;
    auto operator=(const Base &) -> Base & = delete;
    auto operator=(Base &&) -> Base & = delete;

    virtual ~Base() = default;

    static std::string get_random_word(std::unique_ptr<std::vector<std::string>> * possible_ans)
    {
        std::string guess = (*possible_ans)->at((*possible_ans)->size() - 1);
        (*possible_ans)->pop_back();
        return guess;
    }

    static auto validate_ans(const std::string & ans, const std::string & sol) -> std::array<uint8_t, word_size> 
    {
        std::array<uint8_t, word_size> output{
            output_status::not_in_word,
            output_status::not_in_word,
            output_status::not_in_word,
            output_status::not_in_word,
            output_status::not_in_word
            };
        std::vector<uint8_t> temp_index;
        std::string temp_ans;
        std::string temp_word;

        for (uint8_t i = 0; i < word_size; ++i)
        {
            if (ans.at(i) == sol.at(i)) 
            {
                output.at(i) = output_status::correct_pos;
            }
            else 
            {
                temp_ans.push_back(ans.at(i));
                temp_word.push_back(sol.at(i));
                temp_index.push_back(i);
            }
        }

        std::string temp_substring{};
        for (uint8_t i = 0; i < temp_ans.size(); ++i)
        {
            uint8_t substring_occurences = std::count(temp_substring.begin(), temp_substring.end(), temp_ans.at(i));
            uint8_t word_occurences = std::count(temp_word.begin(), temp_word.end(), temp_ans.at(i));
               
            if ((temp_word.find(temp_ans.at(i)) != std::string::npos) && (substring_occurences < word_occurences))
            {
                output.at(temp_index.at(i)) = output_status::wrong_pos;
            }
            temp_substring.push_back(temp_ans.at(i));
        }
        return output;
    }

    void validate_algorithm();
    void validate_algorithm_multithreaded();

    virtual auto get_starting_word(std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string;
    virtual auto sol_function(
        const std::vector<std::string> & ans_list,
        const std::vector<std::array<uint8_t, word_size>> & ans_info,
        std::unique_ptr<std::vector<std::string>> * possible_ans) -> std::string = 0;

private:
    std::string starting_word{};
    std::string output_path{};
    std::vector<std::string> data;
};
} // namespace engine
