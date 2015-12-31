// yeah.cpp
//
// Copyright (c) 2016 Jim Park
//
// Licensed under the Common Public License version 1.0 (the "License");
// you may not use this file except in compliance with the License.
//
// Licence details can be found in the file COPYING.
// 
// This software is provided 'as-is', without any express or implied
// warranty.

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

using namespace std;

// Note: We have to use int with milliseconds because of MSVC bug. Once this bug is
// fixed, we can just pass in chrono::duration<double> that we construct
// directly from the command line.
void out(const string& answer, int ms) {
   if (ms != 0) {
      this_thread::sleep_for(chrono::milliseconds(ms));
   }
   cout << answer << endl;
}

void print_help(string prog) {
   cout << "Usage: " << prog << " [-r <rate>] [-s <duration>] [STRING]" << endl;
   cout << "  -r {seconds}  the firing rate in seconds. E.g. -r 0.5" << endl;
   cout << "  -s {seconds}  the number of seconds to fire. Default is infinity." << endl;
   cout << "  -h            display this help and exit." << endl;
   cout << endl;
   cout << "This is an improved version of the Unix 'yes' command. Some programs" << endl;
   cout << "never quit if the standard input continues to feed data. This program" << endl;
   cout << "adds the number of seconds to fire to limit how long this program will" << endl;
   cout << "continue in a loop. Also it has a firing rate option if that is desired." << endl;
} 

unordered_map<string, string> parse_args(int argc, char* argv[]) {
   unordered_map<string, string> result;
   string k;
   string v;
   enum State {
      Key,
      Value
   };
   State state = Key;

   for (auto i = 1; i < argc; ++i) {
      if (argv[i][0] == '-') {
         if (state == Value) {
            result[k] = "";
         }
         k = &argv[i][1];
         state = Value;
      } else {
         v = argv[i];
         if (state == Value) {
            result[k] = v;
            k.clear();
            v.clear();
            state = Key;
         } else {
            result[""] = v;
            state = Key;
         }
      }
   }

   if (!k.empty() && state == Value) {
      result[k] = "";
   }

   return result;
}

int main(int argc, char* argv[]) {
   if (argc == 0) {
      while (true) {
         out("y", 0);
      }
      return 0;
   } 

   auto result = parse_args(argc, argv);

   if (result.find("h") != result.end() ||
       result.find("?") != result.end()) {
      print_help(argv[0]);
      return 0;
   }

   string answer = "y";

   if (result.find("") != result.end()) {
      answer = result[""];
   }

   int rate = 0;

   if (result.find("r") != result.end()) {
      rate = static_cast<int>((stod(result["r"]) * 1000));
   }

   if (result.find("s") != result.end()) {
      auto start = chrono::system_clock::now();

      chrono::duration<double> limit(stod(result["s"]));
      while (chrono::system_clock::now() - start < limit) {
         out(answer, rate);
      }
   } else {
      while (true) {
         out(answer, rate);
      }
   }

   return 0;
} 
