#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "fragments.h"
#include "overlap.h"
#include "debug.h"
#include "shotgun_sequencer.h"

// This function contains our program's main functionality:

void run (std::vector<std::string>& args)
{
  debug::verbose = std::erase (args, "-v");

  if (args.size() < 3)  //.empty function is more descriptive and is a more robust check than .size() ==0 or < 1
    throw std::runtime_error ("missing arguments - expected 2 arguments: input_fragments output_sequence");

  ShotgunSequencer solver (args[1], 10);

  std::cerr << "initial sequence has size " << solver.sequence().size() << "\n";

  while (solver.iterate());

  solver.check_remaining_fragments();

  std::cerr << "final sequence has length " << solver.sequence().size() << "\n";

  solver.save (args[2]);
}

// a skeleton main() function, whose purpose is  to pass the arguments to
// run() in the expected format, and catch and handle any exceptions that may
// be thrown.

int main (int argc, char* argv[])
{
  try {
    std::vector<std::string> args (argv, argv+argc);
    run (args);
  }
  catch (std::exception& excp) {
    std::cerr << "ERROR: " << excp.what() << " - aborting\n";  //can use cout or cerr
    return 1;
  }
  catch (...) {
    std::cerr << "ERROR: unknown exception thrown - aborting\n"; //'\n' is the new line operator
    return 1;
  }

  return 0;
}

//  compiling
// g++ -std=c++20 -c overlap.cpp
// g++ -std=c++20 -c fragments.cpp
// g++ -std=c++20 -c shotgun.cpp
//  link them together - g++ -std=c++20 overlap.o shotgun.o fragments.o -o shotgun_run
// now run this
// ./shotgun_run fragments-1.txt fragments.2.txt fragments-3.txt output.txt

// oop_build is thenew compiler to compile numerous linked files
// oop_build clean cleans the files
// -verbsose next to compiler tells you the rationale behidn the scripts actions
// to see the output of the preprocessor : g++ -E shotgun.cpp | less -->pipes output through the less interactive text viewer

// adding -Wall to the end of the complier compiles the line with error warnings
// |grep  searches for things and then passes it to something else in the pipeline

// compile and command line: 
// g++ -std=c++20 shotgun.cpp -o shotgun && ./shotgun OneDrive - King's College London/Year 2/OOP/first_project/DATA/fragments-1.txt

// g++ -std=c++20 shotgun.cpp -o shotgun && ./shotgun /Users/arjunbhasin/Library/CloudStorage/OneDrive-King'sCollegeLondon/Year 2/OOP/first_project/DATA/fragments-1.txt
