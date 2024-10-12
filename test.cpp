#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;
namespace fs = std::filesystem;

string construct_cmd(string fname, string out_path, string test_path){
  string cmd_str = "g++ -ggdb -Wall -Wextra -Wpedantic -o" + out_path+fname + ".o " + test_path + fname + ".cpp" + " nn.cpp la.cpp operators.cpp";
  return cmd_str;
}

vector<string> build_tests(vector<string> tests, string out_path, string test_path) {
  vector<string> execs;
  for (uint i = 0; i < tests.size(); i++){
    // Build test executable if it doesn't already exists
    if (not fs::exists(out_path + tests[i] + ".o")){
      string cmd = construct_cmd(tests[i], out_path, test_path);
      cout << "[CMD] " << cmd << endl;
      system(cmd.c_str());
    }
    execs.push_back(out_path + tests[i] + ".o");
  }

  return execs;
}

vector<string> load_avail_tests(string test_path){
  vector<std::string> tests;
  fs::directory_iterator it = fs::directory_iterator(test_path);

  for (const auto & entry : it){
    string p = entry.path();
    if (fs::is_directory(entry.path())){
      continue;
    }
    p = p.erase(0,p.rfind('/')+1); // Preserve only file name
    p = p.erase(p.rfind('.'),p.size()); // Remove extension
    tests.push_back(p.c_str());
  }
  return tests;
}

int run_test_cases(vector<string> executables){
  int passed = 0;
  for (int i = 0; i < (int) executables.size(); i++){
    cout << "[TEST " << i+1 << "/" << executables.size() << "] " << executables[i] << "... ";
    if (system(executables[i].c_str())) {
      cout << "FAILED." << endl;
      continue;
    }
    cout << "PASSED." << endl;
    passed++;
  }
  return passed;
}

int main(int argc, char *argv[]){
  int FORCE_REBUILD = true;
  if (argc > 1){
    if ((string) argv[1] == "--no-force-rebuild"){
      FORCE_REBUILD = false;
    }
  }

  const string test_path = "./tests/";
  const string build_script_path = "./test_build.sh";
  const string out_path = "./tests/builds/";

  if (fs::exists(out_path) && FORCE_REBUILD)
    fs::remove_all(out_path);

  fs::create_directory(out_path);

  cout << "[!] Loading tests...";
  vector<string> available_tests = load_avail_tests(test_path);
  cout << " Loaded " << available_tests.size() << " test cases." << endl;

  cout << "[!] Building tests..." << endl;
  vector<string> executables = build_tests(available_tests, out_path, test_path);
  cout << "[!] All test cases have been built successfully." << endl;

  cout << "[!] Running tests..." << endl;
  int passed = run_test_cases(executables);

  cout << "[!] Final Results: " << passed << "/" << (int) available_tests.size() << " tests passed.";

  if (passed != (int) available_tests.size()){
    return 1;
  }
  return 0;
}
