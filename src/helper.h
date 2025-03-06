#include <string>
#include <cstring>
#include <iostream>
#include <typeinfo>
#include <filesystem>
#include <fstream>
#include "./dataTypes/dataType.h"
#include <vector>
#pragma once
using namespace std;

void helpMenu();
struct arguments {
  int maximumExecutionTime;
  int maximumIterations;
  int numOfCores;
  string inputCorpusPath;
  string outputResultPath;
};
auto parseArguments (int argc, char *argv[]) -> arguments;

vector<DataTypes::TestCase> readInputCorpus(string inputCorpusPath);