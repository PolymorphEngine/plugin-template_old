/*
** EPITECH PROJECT, 2022
** ScriptFactory.hpp
** File description:
** header for ScriptFactory.cpp
*/

#pragma once

#include "ScriptingAPI/ScriptingApi.hpp"
#include "polymorph/Core.hpp"

//@Initalizers
//${INITIALIZERS_INCLUDES}

//@Scripts
//${SCRIPTS_INCLUDES}

namespace polymorph::engine
{
    using Initializer = std::shared_ptr<IComponentInitializer>;
    class ScriptFactory : public IScriptFactory
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            ~ScriptFactory() override = default;


//////////////////////--------------------------/////////////////////////

//Builder template : SCRIPT(${SCRIPT_NAME})
///////////////////////////// PROPERTIES ////////////////////////////////
        private:
            using GameObject = polymorph::engine::safe_ptr<polymorph::engine::Entity>;
            using FactoryLambda = std::function<Initializer (Config::XmlComponent &data, GameObject entity)>;
            template<typename T>
            static inline FactoryLambda _make()
            {
                return [](Config::XmlComponent &data, GameObject entity) -> Initializer{ return Initializer(new T(data, entity));};
            }

            const std::map<const std::string, FactoryLambda> _buildables = {
                    //${BUILDERS}
            };
//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            Initializer create(std::string &type, Config::XmlComponent &data,
                               GameObject entity) override;
            
            bool hasType(std::string &type) final;
//////////////////////--------------------------/////////////////////////

    };
}



