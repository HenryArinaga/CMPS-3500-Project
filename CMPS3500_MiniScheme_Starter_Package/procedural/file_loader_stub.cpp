/*
  / NAME: Walter Morales (provided file loader stub)    /
  / NAME: Henry Ariaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 1                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: file_loader_stub.cpp                          /
  / DATE: 03/15/2026 provided by Walter Morales         /
  / DATE: 03/29/2026 added exception catch              /
*/

// Tiny file-loading helper stub for the procedural implementation.
// Replace or adapt as needed.
#include <fstream>
#include <sstream>
#include <string>

std::string read_file(const std::string& path) {
    std::ifstream in(path);
    //error handling: throw an exception if the file cannot be opened
    if (!in) {
        throw std::runtime_error("Could not open file: " + path);
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}
