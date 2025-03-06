#include <string>
#include <deque>
#include <vector>
#include <unordered_map>
#include "../dataTypes/dataType.h"
using namespace std;


class CorpusManagerWorker {
    public:
        CorpusManagerWorker();
        // change to testcase type
        deque<DataTypes::TestCase> sendToMutator;
        // change to testcaseID and testcaseData type
        vector<pair<int, DataTypes::TestCaseData>> interestingTestCases;

        void receiveInterestingTestCases(vector<DataTypes::TestCase> testCasesFromFeedback);
        void modifyInterestingTestCasesScore(vector<int> feedbacksOfTestCases);
        //change to return vector<testcase> type
        vector<DataTypes::TestCase> sendInterestingTestCases(int numOfTestCases);
};