#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <iostream>
#include <string>
#include <vector>


namespace seneca {
class Guild {
  std::vector<Character *> m_members;
  std::string m_name;

public:
  // Default constructor
  Guild() = default;

  // Constructor with guild name
  Guild(const char *name) : m_name(name) {}

  // Copy constructor
  Guild(const Guild &other) {
    m_name = other.m_name;
    for (const auto &member : other.m_members) {
      m_members.push_back(member->clone());
    }
  }

  // Copy assignment operator
  Guild &operator=(const Guild &other) {
    if (this != &other) {
      m_name = other.m_name;
      for (const auto &member : m_members) {
        delete member;
      }
      m_members.clear();
      for (const auto &member : other.m_members) {
        m_members.push_back(member->clone());
      }
    }
    return *this;
  }

  // Move constructor
  Guild(Guild &&other) noexcept
      : m_name(std::move(other.m_name)), m_members(std::move(other.m_members)) {
  }

  // Move assignment operator
  Guild &operator=(Guild &&other) noexcept {
    if (this != &other) {
      m_name = std::move(other.m_name);
      m_members = std::move(other.m_members);
    }
    return *this;
  }

  // Destructor
  ~Guild() {
    for (const auto &member : m_members) {
      delete member;
    }
  }

  // Add a member to the guild
  void addMember(Character *c) {
    for (const auto &member : m_members) {
      if (member->getName() == c->getName()) {
        return; // Do not add duplicate members
      }
    }
    c->setHealthMax(c->getHealthMax() + 300);
    m_members.push_back(c);
  }

  // Remove a member from the guild by name
  void removeMember(const std::string &name) {
    for (auto it = m_members.begin(); it != m_members.end(); ++it) {
      if ((*it)->getName() == name) {
        (*it)->setHealthMax((*it)->getHealthMax() - 300);
        m_members.erase(it);
        return;
      }
    }
  }

  // Access a member by index
  Character *operator[](std::size_t idx) const {
    if (idx < m_members.size()) {
      return m_members[idx];
    }
    return nullptr;
  }

  // Display guild members
  void showMembers() const {
    if (m_members.empty()) {
      std::cout << "No guild." << std::endl;
      return;
    }
    std::cout << "[Guild] " << m_name << std::endl;
    for (size_t i = 0; i < m_members.size(); ++i) {
      std::cout << i + 1 << ": " << *m_members[i] << std::endl;
    }
  }
};
} // namespace seneca

#endif