// team.h
#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <vector>
#include <string>
#include <iostream>

namespace seneca {
    class Team {
        std::vector<Character*> m_members;
        std::string m_name;

    public:
        // Default constructor
        Team() = default;

        // Constructor with team name
        Team(const char* name) : m_name(name) {}

        // Copy constructor
        Team(const Team& other) : m_name(other.m_name) {
            for (const auto& member : other.m_members) {
                m_members.push_back(member->clone());
            }
        }

        // Copy assignment operator
        Team& operator=(const Team& other) {
            if (this != &other) {
                clearMembers();
                m_name = other.m_name;
                for (const auto& member : other.m_members) {
                    m_members.push_back(member->clone());
                }
            }
            return *this;
        }

        // Move constructor
        Team(Team&& other) noexcept : m_name(std::move(other.m_name)), m_members(std::move(other.m_members)) {
            other.m_members.clear(); // Prevent original object from deleting moved pointers
        }

        // Move assignment operator
        Team& operator=(Team&& other) noexcept {
            if (this != &other) {
                clearMembers();
                m_name = std::move(other.m_name);
                m_members = std::move(other.m_members);
                other.m_members.clear(); // Prevent double deletion
            }
            return *this;
        }

        // Destructor
        ~Team() {
            clearMembers();
        }

        // Add a member to the team
        void addMember(const Character* c) {
            for (const auto& member : m_members) {
                if (member->getName() == c->getName()) {
                    return; // Do not add duplicate members
                }
            }
            m_members.push_back(c->clone());
        }

        // Remove a member from the team by name
        void removeMember(const std::string& name) {
            for (auto it = m_members.begin(); it != m_members.end(); ++it) {
                if ((*it)->getName() == name) {
                    delete *it;
                    m_members.erase(it);
                    return;
                }
            }
        }

        // Access a member by index
        Character* operator[](std::size_t idx) const {
            if (idx < m_members.size()) {
                return m_members[idx];
            }
            return nullptr;
        }

        // Display team members
        void showMembers() const {
            if (m_members.empty()) {
                std::cout << "No team." << std::endl;
                return;
            }
            std::cout << "[Team] " << m_name << std::endl;
            for (size_t i = 0; i < m_members.size(); ++i) {
                std::cout << i + 1 << ": " << *m_members[i] << std::endl;
            }
        }

    private:
        void clearMembers() {
            for (auto& member : m_members) {
                delete member;
            }
            m_members.clear();
        }
    };
}

#endif