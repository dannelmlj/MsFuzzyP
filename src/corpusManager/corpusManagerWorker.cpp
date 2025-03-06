#include <string>
#include "corpusManagerWorker.h"
#include <boost/asio.hpp>
#include "../dataTypes/dataType.h"

using namespace std;

//Default Constructor

CorpusManagerWorker::CorpusManagerWorker() {}

void CorpusManagerWorker::receiveInterestingTestCases(vector<DataTypes::TestCase> testCasesFromFeedback){
  for (int i = 0; i < testCasesFromFeedback.size(); i++){
      // Generate testcaseId
      testCasesFromFeedback[i].generateUniqueId();
      int newTestCaseId = testCasesFromFeedback[i].getId();
      // create new testcase data
      DataTypes::TestCaseData newTestCaseData = DataTypes::TestCaseData(testCasesFromFeedback[i], 100);

      // Add to interestingTestCases
      interestingTestCases.push_back(make_pair(newTestCaseId, newTestCaseData));
  }

}

void CorpusManagerWorker::modifyInterestingTestCasesScore(vector<int> feedbacksOfTestCases){
  for (int i = 0; i < feedbacksOfTestCases.size(); i++){
      // Get id 
      int testCaseId = 1;
      // e.g. int testcaseId = feedbacksOfTestCases[i].getId();

      // Get feedback
      // e.g. enum feedback = feedbacksOfTestCases[i].getFeedback();
      // logics to modify score

      // Update score
      // if (interestingTestCases.at(testCaseId) != interestingTestCases.end()){
          // interestingTestCases[testCaseId] = 1;
      // }
      // e.g. interestingTestCases[testcaseId] = feedback;
  }
}

bool compScore(pair<int, DataTypes::TestCaseData> a, pair<int, DataTypes::TestCaseData> b){
  return a.second.getScore() > b.second.getScore();
}

// change to vector<testcase> type || This pushes the interesting test case into the queue for the mutator to pick up
vector<DataTypes::TestCase> CorpusManagerWorker::sendInterestingTestCases(int numOfTestCases){
  if (interestingTestCases.empty()){
      return vector<DataTypes::TestCase>();
  }
  vector<DataTypes::TestCase> topTestCases;
  sort(interestingTestCases.begin(), interestingTestCases.end(), compScore);

  while (sendToMutator.size() < numOfTestCases){
    // get highest score testcase from interestingTestCases
    DataTypes::TestCase topTestCase = interestingTestCases.begin()->second.getTestCase();

    // Send to Mutator queue
    sendToMutator.push_back(topTestCase);
    topTestCases.push_back(topTestCase);

    // Remove from interestingTestCases
    interestingTestCases.erase(interestingTestCases.begin());
  }
  return topTestCases;
}



