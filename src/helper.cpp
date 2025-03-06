#include <string>
#include <cstring>
#include <iostream>
#include <typeinfo>
#include <filesystem>
#include <fstream>
#include "./dataTypes/dataType.h"
#include "helper.h"
#include <vector>
#pragma once
using namespace std;

void helpMenu() {
  cout << "Usage: ./MsFuzzyP [OPTIONS]\n"
      << "Options:\n"
      << "  --maxExec <int>    Maximum execution time\n"
      << "  --maxIter <int>    Maximum number of iterations\n"
      << "  --cores <int>      Number of cores to use\n"
      << "  -i <path>          Path to input corpus\n"
      << "  -o <path>          Path to output result\n";
}
auto parseArguments (int argc, char *argv[]) -> arguments {
  // struct {
  //   int maximumExecutionTime;
  //   int maximumIterations;
  //   int numOfCores;
  //   string inputCorpusPath;
  //   string outputResultPath;
  // } arguments;

  int maximumExecutionTime;
  int maximumIterations;
  int numOfCores;
  string inputCorpusPath;
  string outputResultPath;

  bool inputCorpusPathFlag = false;
  bool outputResultPathFlag = false;

  if (argc <= 1) {
    helpMenu();
    exit(1);
  }
  for (int i = 1; i < argc; i++) {
    // cout << argv[i] << " type: " << typeid(argv[i]).name() <<  endl;
      if (strcmp(argv[i], "--maxExec") == 0 && i + 1 < argc) {
          maximumExecutionTime = atoi(argv[++i]); // Convert to int
      } else if (strcmp(argv[i], "--maxIter") == 0 && i + 1 < argc) {
          maximumIterations = atoi(argv[++i]); // Convert to int
      } else if (strcmp(argv[i], "--cores") == 0 && i + 1 < argc) {
          numOfCores = atoi(argv[++i]); // Convert to int
      } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
          inputCorpusPath = argv[++i];
          inputCorpusPathFlag = true;
      } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
          outputResultPath = argv[++i];
          outputResultPathFlag = true;
      } 
  }

  if (!inputCorpusPathFlag) {
    cout << "[Error!] Input Corpus Path is required" << endl;
    cout << inputCorpusPathFlag << endl;
    exit(1);
  }
  if (!outputResultPathFlag) {
    cout << "[Error!] Output Result Path is required" << endl;
    exit(1);
  }

  if (!filesystem::exists(inputCorpusPath)) {
    cout << "[Error!] Input Corpus Path does not exist" << endl;
    exit(1);
  }

  if (!filesystem::exists(outputResultPath)) {
    cout << "[Error!] Output Result Path does not exist" << endl;
    exit(1);
  }

  return {maximumExecutionTime, maximumIterations, numOfCores, inputCorpusPath, outputResultPath};
}

vector<DataTypes::TestCase> readInputCorpus(string inputCorpusPath) {
  vector<DataTypes::TestCase> testCases;
  for (const auto & entry : filesystem::directory_iterator(inputCorpusPath)) {
    string filePath = entry.path();
    vector<uint8_t> buffer;

    std::ifstream file(filePath, ios::binary);

    if (file.good()){
      buffer = vector<uint8_t>(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
      file.close();
    }

    DataTypes::TestCase testCase = DataTypes::TestCase(0, buffer);
    testCases.push_back(testCase);

    // cout << filePath << endl;
    // Read file
    // Create test case
    // Add to testCases
  }

  return testCases;
}