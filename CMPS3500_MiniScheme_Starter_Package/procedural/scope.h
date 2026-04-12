/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: scope.h                                  /
  / DATE: 04/11/2026                                    /
*/
#ifndef SCOPE_H
#define SCOPE_H

#include <string>
#include <vector>

// Represents a single entry in a scope
//mapping a name to a value
struct ScopeEntry
{
    std::string name;
    std::string value;
};

//a scope contains a list of entries 
//and a pointer to its parent scope
struct Scope
{
    std::vector<ScopeEntry> scope_entries;
    Scope *parent;
};

// Scope management
Scope *enterScope(Scope *current);
Scope *exitScope(Scope *current);

// Scope entry management
void addScopeEntry(Scope *scope, const std::string &name, const std::string &value);
std::string lookupScopeEntry(Scope *scope, const std::string &name);
bool existsInCurrentScope(Scope *scope, const std::string &name);

#endif
