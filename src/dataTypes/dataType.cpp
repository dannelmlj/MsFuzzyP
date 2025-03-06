#include <vector>
#include "dataType.h"
// enum DeterministicPasses{

// }

// class TestCaseDeterministic{
//   private:
//     std::vector<enum> done;
//     std::vector<enum> to_do;
// }

DataTypes::TestCase::TestCase(){
    this->id = 0;
    this->feedBackId = 0;
}

DataTypes::TestCase::TestCase(int id, std::vector<uint8_t> buffer){
    this->id = id;
    this->feedBackId = 0;
    this->buffer = buffer;
}

void DataTypes::TestCase::setId(int id){
    this->id = id;
}

int DataTypes::TestCase::getId(){
    return this->id;
}

void DataTypes::TestCase::setFeedBackId(int feedBackId){
    this->feedBackId = feedBackId;
}

int DataTypes::TestCase::getFeedBackId(){
    return this->feedBackId;
}

void DataTypes::TestCase::setBuffer(std::vector<uint8_t> buffer){
    this->buffer = buffer;
}

std::vector<uint8_t> DataTypes::TestCase::getBuffer(){
    return this->buffer;
}

DataTypes::TestCase DataTypes::TestCase::copyBuffer(){
    return DataTypes::TestCase(this->id, this->buffer);
}

int count = 0;
int generateUnqId(){
  count++;
  return count;
}
void DataTypes::TestCase::generateUniqueId(){
    this->id = generateUnqId();
}



DataTypes::TestCaseData::TestCaseData(DataTypes::TestCase testCase, int score){
    this->testCase = testCase;
    this->score = score;
    this->use_count = 0;
}

DataTypes::TestCase DataTypes::TestCaseData::getTestCase(){
    return this->testCase;
}

void DataTypes::TestCaseData::setScore(int score){
    this->score = score;
}

void DataTypes::TestCaseData::addScore(int score){
    this->score += score;
}

int DataTypes::TestCaseData::getScore(){
    return this->score;
}

void DataTypes::TestCaseData::setUseCount(int use_count){
    this->use_count = use_count;
}

int DataTypes::TestCaseData::getUseCount(){
    return this->use_count;
}