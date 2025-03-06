#include <vector>
#include <random>
#include <ctime>
#include "mutatorWorker.h"


BitFlipMutatorWorker::BitFlipMutatorWorker() {}

void BitFlipMutatorWorker::receiveTestCases(std::vector<DataTypes::TestCase> testCases){
  for (int i = 0; i < testCases.size(); i++){
      // Add to toMutateTestCases
      toMutateTestCases.push(testCases[i]);
  }

}

void BitFlipMutatorWorker::mutateTestCases(){
  for (int i = 0; i < toMutateTestCases.size(); i++){
    DataTypes::TestCase testCase = toMutateTestCases.front();
    toMutateTestCases.pop();

    DataTypes::TestCase mutateByInsert = insertRandomByte(testCase);
    DataTypes::TestCase mutateByFlip = flipSignificantBit(testCase);
    DataTypes::TestCase mutateByRemove = removeRandomByte(testCase);

    mutatedTestCases.push_back(mutateByInsert);
    mutatedTestCases.push_back(mutateByFlip);
    mutatedTestCases.push_back(mutateByRemove);
    // Mutate testcase
    // e.g. DataTypes::TestCase mutatedTestCase = mutate(testCase);
    // mutatedTestCases.push_back(mutatedTestCase);
  }
}

std::deque<DataTypes::TestCase> BitFlipMutatorWorker::getMutatedTestCases(int numOfTestCases){
  std::deque<DataTypes::TestCase> mutatedTestCasesToSend;
  for (int i = 0; i < numOfTestCases; i++){
    if (mutatedTestCases.empty()){
      break;
    }
    mutatedTestCasesToSend.push_back(mutatedTestCases.front());
    mutatedTestCases.pop_front();
  }
  return mutatedTestCasesToSend;
}

// Bitflip mutators

DataTypes::TestCase BitFlipMutatorWorker::insertRandomByte(DataTypes::TestCase &testCase){
  // Insert random byte
  std::vector<uint8_t> buffer = testCase.getBuffer();
  std::vector<uint8_t> newBuffer = buffer;

  std::default_random_engine generate(std::time(nullptr));
  std::uniform_int_distribution<int> bufferDistribution(0, buffer.size()+1);
  std::uniform_int_distribution<int> byteDistribution(0, 255);

  int randomIndex = bufferDistribution(generate);
  uint8_t randomByte = byteDistribution(generate);
  
  newBuffer.insert(newBuffer.begin() + randomIndex, randomByte);

  DataTypes::TestCase newTestCase = DataTypes::TestCase(testCase.getId(), newBuffer);

  return newTestCase;
}

DataTypes::TestCase BitFlipMutatorWorker::flipSignificantBit(DataTypes::TestCase &testCase){
  std::vector<uint8_t> buffer = testCase.getBuffer();
  std::vector<uint8_t> newBuffer = buffer;

  std::default_random_engine generate(std::time(nullptr));
  std::uniform_int_distribution<int> bufferDistribution(0, buffer.size()+1);

  int randomIndex = bufferDistribution(generate);
  uint8_t significantBit = 7;
  
  newBuffer[randomIndex] ^= (1 << significantBit);

  DataTypes::TestCase newTestCase = DataTypes::TestCase(testCase.getId(), newBuffer);

  return newTestCase;
}

DataTypes::TestCase BitFlipMutatorWorker::removeRandomByte(DataTypes::TestCase &testCase){
  // Insert random byte
  std::vector<uint8_t> buffer = testCase.getBuffer();
  std::vector<uint8_t> newBuffer = buffer;

  std::default_random_engine generate(std::time(nullptr));
  std::uniform_int_distribution<int> bufferDistribution(0, buffer.size()+1);

  int randomIndex = bufferDistribution(generate);
  
  newBuffer.erase(newBuffer.begin() + randomIndex);

  DataTypes::TestCase newTestCase = DataTypes::TestCase(testCase.getId(), newBuffer);

  return newTestCase;
}