#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ACNode.hpp"
#include "ACAutomaton.hpp"
#include "ACAutomaton.cpp"  // should link .cpp since constructor in it
#include "Timer.hpp"
#include "Timer.cpp"

using namespace std;


/* to get /r/n and /r to /n, from stack overflow */
std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

void load_dict(ACAutomaton& dict, istream& queries) {
  string data = "";
  while (safeGetline(queries, data)) {
    if (queries.eof())
      break;
    dict.insert(data);
  }
}

void match_db(ACAutomaton& dict, istream& database) {
  string data = "";
  while (safeGetline(database, data)) {
    if (database.eof())
      break;
    dict.match(data);
  }
}

int main(int argc, char*argv[]) {

  if (argc != 4) {
    cout << "Incorrect number of arguments." << endl;
    cout << "\t First argument: dictionary file." << endl;
    cout << "\t Second argument: database file." << endl;
    cout << "\t Third argument: 1 - print result, 0 - no printing" << endl;
    cout << endl;
    exit(-1);
  }

  ifstream qin(argv[1], ios_base::in);
  ifstream din(argv[2], ios_base::in);

  ACAutomaton* ACT = new ACAutomaton();
  Timer T;

  /* Load the dictionart */
  load_dict(*ACT, qin);
  // cout << ACT->GetSize() << " patterns loaded." << endl;

  /* Build the trei recurrsion */
  ACT->build();

  /* Match the database and print */
  T.begin_timer();
  match_db(*ACT, din);
  cout << "Tunning time \t" << T.end_timer() << " nanoseconds" << endl;

  if (stoi(argv[3])) {
    ACT->print();
  }

  qin.close();
  din.close();
  delete ACT;
  return 0;
}
