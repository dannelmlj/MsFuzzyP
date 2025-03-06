#include "helper.h"
#include <iostream>
#include "../src/fuzzer/fuzzer.h"

using namespace std;

int main (int argc, char *argv[]) {
  auto arguments = parseArguments(argc, argv);
  Fuzzer fuzzer = Fuzzer(arguments.maximumExecutionTime, arguments.maximumIterations, arguments.numOfCores, arguments.inputCorpusPath, arguments.outputResultPath);

  fuzzer.runSingleFuzzer();

  return 0;


}