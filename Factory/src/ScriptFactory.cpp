/*
** EPITECH PROJECT, 2022
** ScriptFactory.cpp
** File description:
** ScriptFactory.cpp
*/
#include "../include/ScriptFactory.hpp"

polymorph::engine::Initializer polymorph::engine::ScriptFactory::create(std::string &type, Config::XmlComponent &data,
                                 GameObject entity)
{
    return _buildables.at(type)(data, entity);
}

bool polymorph::engine::ScriptFactory::hasType(std::string &type)
{
    return _buildables.contains(type);
}

