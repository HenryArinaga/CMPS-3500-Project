#ifndef SCOPE_H
#define SCOPE_H

#include <string>
#include <vector>

struct ScopeEntry
{
    std::string name;
    std::string value;
};

struct Scope
{
    std::vector<ScopeEntry> scope_entries;
    Scope *parent;
};

Scope *enterScope(Scope *current);
Scope *exitScope(Scope *current);

void addScopeEntry(Scope *scope, const std::string &name, const std::string &value);
std::string lookupScopeEntry(Scope *scope, const std::string &name);
bool existsInCurrentScope(Scope *scope, const std::string &name);

#endif
