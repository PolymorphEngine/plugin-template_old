/*
** EPITECH PROJECT, 2020
** ObjectFactory.hpp
** File description:
** header for ObjectFactory.c
*/

#ifndef PLUGIN_TEMPLATE_OBJECTFACTORY_HPP
#define PLUGIN_TEMPLATE_OBJECTFACTORY_HPP

#include "ScriptingAPI/ISerializableObjectFactory.hpp"
#include <unordered_map>

namespace polymorph::engine
{
    class ObjectFactory : public ISerializableObjectFactory
    {
        public:
            ~ObjectFactory() override = default;

            std::shared_ptr<ASerializableObject>
            createS(std::string type, std::shared_ptr<myxmlpp::Node> &data,
                    Config::XmlComponent &manager) override;

            bool hasType(std::string &type) override;
            
            std::unordered_map<std::string, FactoryLambdaS> _factoriesS = {
                
            };
    };
}


#endif //PLUGIN_TEMPLATE_OBJECTFACTORY_HPP
