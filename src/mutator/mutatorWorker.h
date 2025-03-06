#include <vector>
#include <queue>
#include "../dataTypes/dataType.h"


class BitFlipMutatorWorker {
    private:
      std::deque<DataTypes::TestCase> mutatedTestCases;
      std::queue<DataTypes::TestCase> toMutateTestCases;
      
    public:
      BitFlipMutatorWorker();
      void receiveTestCases(std::vector<DataTypes::TestCase> testCases);
      void mutateTestCases();
      std::deque<DataTypes::TestCase> getMutatedTestCases(int numOfTestCases);
      DataTypes::TestCase insertRandomByte(DataTypes::TestCase &testCase);
      DataTypes::TestCase flipSignificantBit(DataTypes::TestCase &testCase);
      DataTypes::TestCase removeRandomByte(DataTypes::TestCase &testCase);

};

// Future: collaborate with other strategies