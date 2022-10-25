/*
** EPITECH PROJECT, 2022
** ScriptFactory.cpp
** File description:
** ScriptFactory.cpp
*/
#include "../include/ScriptFactory.hpp"

Polymorph::Initializer Polymorph::ScriptFactory::create(std::string &type, Config::XmlComponent &data,
                                 GameObject entity)
{
    return _buildables.at(type)(data, entity);
}

bool Polymorph::ScriptFactory::hasType(std::string &type)
{
    return _buildables.contains(type);
}

