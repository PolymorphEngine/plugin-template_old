/*
** EPITECH PROJECT, 2022
** ScriptFactory.hpp
** File description:
** header for ScriptFactory.cpp
*/

#pragma once

#include "ScriptingAPI/ScriptingApi.hpp"
#include "Polymorph/Core.hpp"

//@Initalizers
//${INITIALIZERS_INCLUDES}

//@Scripts
//${SCRIPTS_INCLUDES}

namespace Polymorph
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
            using GameObject = Polymorph::safe_ptr<Polymorph::Entity>;
            using FactoryLambda = std::function<Initializer (Config::XmlComponent &data, GameObject entity)>;
            template<typename T>
            static inline FactoryLambda _make()
            {
                return [](Config::XmlComponent &data, GameObject entity) -> Initializer{ return Initializer(new T(data, entity));};
            }

            static inline std::map<std::string, FactoryLambda> _buildables = {
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



