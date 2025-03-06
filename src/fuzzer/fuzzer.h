#include <string>
#pragma once
using namespace std;


class Fuzzer {
    public:
        int maximumExecutionTime;
        int maximumIterations;
        int numOfCores;
        string inputCorpusPath;
        string outputResultPath;
        Fuzzer(int maximumExecutionTime, int maximumIterations, int numOfCores, string inputCorpusPath, string outputResultPath);
        void corpusManagerService();
        void mutationService();
        void executionService();
        void feedbackService();
        void monitoringService();
        void runAsyncFuzzer();
        void runSingleFuzzer();
};