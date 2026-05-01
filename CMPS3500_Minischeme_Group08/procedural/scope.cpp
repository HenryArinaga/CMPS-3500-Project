/*
  / NAME: Henry Arinaga, Alberto Molina, Peter Uzuriaga  /
  / ASGT: CHECKPOINT 2                                  /
  / ORGN: CSUB - CMPS 3500                              /
  / FILE: scope.cpp                                  /
  / DATE: 04/11/2026                                    /
*/
#include "scope.h"
#include <string>

// Scope management implementation
Scope *enterScope(Scope *current)
{
    Scope *new_scope = new Scope;
    new_scope->parent = current;
    return new_scope;
}
// Exits the current scope and returns the parent scope
Scope *exitScope(Scope *current)
{
    if (current == nullptr)
    {
        return nullptr;
    }

    Scope *parent_scope = current->parent;
    delete current;
    return parent_scope;
}
// Adds a new entry to the current scope
void addScopeEntry(Scope *scope, const std::string &name, const std::string &value)
{
    if (scope == nullptr)
    {
        return;
    }

    ScopeEntry b;
    b.name = name;
    b.value = value;
    scope->scope_entries.push_back(b);
}
// Looks up a name in the scope chain and returns its value, 
//or "NOT FOUND" if it doesn't exist
std::string lookupScopeEntry(Scope *scope, const std::string &name)
{
    Scope *temp = scope;

    while (temp != nullptr)
    {
        for (int i = 0; i < (int)temp->scope_entries.size(); i++)
        {
            if (temp->scope_entries[i].name == name)
            {
                return temp->scope_entries[i].value;
            }
        }

        temp = temp->parent;
    }

    return "NOT FOUND";
}

// Checks if a name exists in the current scope
bool existsInCurrentScope(Scope *scope, const std::string &name)
{
    if (scope == nullptr)
    {
        return false;
    }

    for (int i = 0; i < (int)scope->scope_entries.size(); i++)
    {
        if (scope->scope_entries[i].name == name)
        {
            return true;
        }
    }

    return false;
}
