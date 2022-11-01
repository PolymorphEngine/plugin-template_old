/*
** EPITECH PROJECT, 2020
** ObjectFactory.cpp
** File description:
** ObjectFactory.cpp
*/

#include "../include/ObjectFactory.hpp"

std::shared_ptr<polymorph::engine::ASerializableObject>
polymorph::engine::ObjectFactory::createS(std::string type,
                                          std::shared_ptr<myxmlpp::Node> &data,
                                          polymorph::engine::Config::XmlComponent &manager)
{
    return _factoriesS[type](data, manager);
}

bool polymorph::engine::ObjectFactory::hasType(std::string &type)
{
    return _factoriesS.find(type) != _factoriesS.end();
}
