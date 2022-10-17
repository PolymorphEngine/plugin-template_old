/*
** EPITECH PROJECT, 2022
** ScriptFactory.cpp
** File description:
** ScriptFactory.cpp
*/
#include "ScriptFactory.hpp"

Polymorph::Initializer Polymorph::ScriptFactory::create(std::string &type, Config::XmlComponent &data,
                                 GameObject entity)
{
    return _buildables.at(type)(data, entity);
}

