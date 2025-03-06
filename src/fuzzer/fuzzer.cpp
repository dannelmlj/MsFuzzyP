#include <string>
#include "fuzzer.h"
#include <boost/asio.hpp>
#include <vector>
#include <deque>
#include "../corpusManager/corpusManagerWorker.h"
#include "../mutator/mutatorWorker.h"
#include "../helper.h"
#include <sys/wait.h>

using namespace std;

Fuzzer::Fuzzer(int maximumExecutionTime, int maximumIterations, int numOfCores, string inputCorpusPath, string outputResultPath) {
    this->maximumExecutionTime = maximumExecutionTime;
    this->maximumIterations = maximumIterations;
    this->numOfCores = numOfCores;
    this->inputCorpusPath = inputCorpusPath;
    this->outputResultPath = outputResultPath;
}


void Fuzzer::monitoringService(){

}

void Fuzzer::corpusManagerService(){

}

void Fuzzer::mutationService(){

}

void Fuzzer::executionService(){

}

void Fuzzer::feedbackService(){

}

void Fuzzer::runAsyncFuzzer(){

}

void Fuzzer::runSingleFuzzer(){
    CorpusManagerWorker corpusManagerWorker = CorpusManagerWorker();
    BitFlipMutatorWorker bitFlipMutatorWorker = BitFlipMutatorWorker();



    vector<DataTypes::TestCase> testCases = readInputCorpus(this->inputCorpusPath);
    corpusManagerWorker.receiveInterestingTestCases(testCases);

    // deque<DataTypes::TestCase> corpusAndMutator = corpusManagerWorker.sendToMutator;
    deque<DataTypes::TestCase> mutatorAndExecutor;

    while (true){
        vector<DataTypes::TestCase> interesting = corpusManagerWorker.sendInterestingTestCases(10);

        bitFlipMutatorWorker.receiveTestCases(interesting);
        bitFlipMutatorWorker.mutateTestCases();

        mutatorAndExecutor = bitFlipMutatorWorker.getMutatedTestCases(10);

        for (int i = 0 ; i < mutatorAndExecutor.size(); i++){
            const char* tempFile = "temp_input.pdf";
            std::ofstream outfile(tempFile, std::ios::binary);
            if (!outfile.good()) {
                std::cerr << "Failed to create temporary file: " << tempFile << std::endl;
                return;
            }
            vector<uint8_t> corpus = mutatorAndExecutor.front().getBuffer();
            mutatorAndExecutor.pop_front();
            outfile.write(reinterpret_cast<const char*>(corpus.data()), corpus.size());
            outfile.close();
    
            // Setup a pipe for capturing output.
            int pipefd[2];
            if (pipe(pipefd) == -1) {
                std::perror("pipe");
                return;
            }   
    
            pid_t pid = fork();
            if (pid < 0) {
                std::perror("fork");
                return;
            }
    
            if (pid == 0) {
                // Child process.
                close(pipefd[0]); // Close read end.
                // Redirect STDOUT to the pipe.
                if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
                    std::perror("dup2");
                    exit(1);
                }
                close(pipefd[1]);
                // Execute the target program.
                execl("pdfinfo", "pdfinfo", tempFile, (char*)NULL);
                // If execl fails.
                std::perror("execl");
                exit(1);
            } else {
                // Parent process.
                close(pipefd[1]); // Close write end.
                
                int status;
                if (waitpid(pid, &status, 0) == -1) {
                    std::perror("waitpid");
                    return ;
                }
    
                // Check for crash conditions: if the child terminated due to a signal.
                bool crashed = false;
                if (WIFSIGNALED(status)) {
                    int sig = WTERMSIG(status);
                    std::cout << "Iteration " << ": Process terminated by signal " << sig;
                    // You can check specific signals like SIGSEGV, SIGABRT, etc.
                    if (sig == SIGSEGV || sig == SIGABRT || sig == SIGFPE || sig == SIGILL) {
                        crashed = true;
                    }
                    std::cout << " (likely a crash)." << std::endl;
                } else if (WIFEXITED(status)) {
                    // In this simple example, we treat non-zero exit as no crash.
                    // Adjust this check as needed for your target.
                    int exitCode = WEXITSTATUS(status);
                    if (exitCode != 0) {
                        // Sometimes, non-zero exit code can indicate a crash.
                        // For clarity, we only output for a crash triggered by a signal.
                        std::cout << "Iteration: " << i << ": Process exited with code " << exitCode << "." << std::endl;
                    }
                }
    
                if (crashed) {
                    // Capture the output from the crashed execution.
                    std::string output;
                    char buffer[128];
                    ssize_t count;
                    while ((count = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
                        buffer[count] = '\0';
                        output += buffer;
                    }
                    std::cout << "Crashed! Output from pdfinfo:\n" << output << std::endl;
                    close(pipefd[0]);
                    std::remove(tempFile);
                    // We stop running after the crash.
                    break;
                }
                close(pipefd[0]);
            }
            std::remove(tempFile);
        }
    

            // cout << "Testcase id: " << mutatorAndExecutor[i].getId() << endl;
        }
        // corpusAndMutator = corpusManagerWorker.sendInterestingTestCases(10);
        // mutatorAndExecutor = mutatorWorker.getMutatedTestCases(10);
        // executorWorker.executeTestCases(mutatorAndExecutor);
        // feedbackWorker.receiveFeedback();
        // corpusManagerWorker.receiveInterestingTestCases(feedbackWorker.getFeedback());




        

    for (int i = 0; i< testCases.size(); i++){
        cout << "Testcase id: " << corpusManagerWorker.interestingTestCases[i].first << endl;
    }
    // corpusManagerWorker.sendInterestingTestCases(10);

}



