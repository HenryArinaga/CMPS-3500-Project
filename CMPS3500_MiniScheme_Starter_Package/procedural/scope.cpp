#include "scope.h"
#include <string>

Scope *enterScope(Scope *current)
{
    Scope *new_scope = new Scope;
    new_scope->parent = current;
    return new_scope;
}

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
