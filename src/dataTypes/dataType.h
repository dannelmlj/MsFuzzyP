#include <vector>
#include <cstdint>
#pragma once

namespace DataTypes{
  class TestCase{
    private:
        int id;
        int feedBackId;
        std::vector<uint8_t> buffer;
    public:
        TestCase();
        TestCase(int id, std::vector<uint8_t> buffer);
        void setId(int id);
        int getId();
        void setFeedBackId(int feedBackId);
        int getFeedBackId();
        void setBuffer(std::vector<uint8_t> buffer);
        std::vector<uint8_t> getBuffer();
        TestCase copyBuffer();
        void generateUniqueId();


  };

  class TestCaseData {
    private:
        DataTypes::TestCase testCase;
        int score;
        int use_count;
    public:
        TestCaseData(DataTypes::TestCase testCase, int score);
        DataTypes::TestCase getTestCase();
        void setScore(int score);
        void addScore(int score);
        int getScore();

        void setUseCount(int use_count);
        int getUseCount();
        
  };

  class FeedbackData {

  };
};