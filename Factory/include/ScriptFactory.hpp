/*
** EPITECH PROJECT, 2022
** ScriptFactory.hpp
** File description:
** header for ScriptFactory.cpp
*/

#pragma once

#include "Polymorph/Factory.hpp"
#include "Polymorph/Components.hpp"
#include "Polymorph/Core.hpp"

//@Initalizers
//${INITIALIZERS_INCLUDES}
#include "GameManagerInitializer.hpp"
#include "ScoreUpdaterInitializer.hpp"
#include "ClientNetworkManagerInitializer.hpp"
#include "MobNMInitializer.hpp"
#include "PlayerAnimatorInitializer.hpp"
#include "PlayerManagerInitializer.hpp"
#include "PlayerMoverIMInitializer.hpp"
#include "PlayerMoverNMInitializer.hpp"
#include "PlayerShooterIMInitializer.hpp"
#include "ProjectileNMInitializer.hpp"

//@Scripts
//${SCRIPTS_INCLUDES}
#include "GameManagerScript.hpp"
#include "ScoreUpdaterScript.hpp"
#include "GameManager/ClientNetworkManagerScript.hpp"
#include "Mobs/MobNMScript.hpp"
#include "Player/PlayerAnimatorScript.hpp"
#include "Player/PlayerManagerScript.hpp"
#include "Player/PlayerMoverIMScript.hpp"
#include "Player/PlayerMoverNMScript.hpp"
#include "Player/PlayerShooterIMScript.hpp"
#include "Projectiles/ProjectileNMScript.hpp"

namespace Polymorph
{
    class ScriptFactory : public IScriptFactory
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            ~ScriptFactory() override = default;


//////////////////////--------------------------/////////////////////////

//Builder template : {"${SCRIPT_NAME}", [](Config::XmlComponent &data, GameObject entity) -> Initializer{ return Initializer(new ${SCRIPT_NAME}Initializer(data, entity));}},

///////////////////////////// PROPERTIES ////////////////////////////////
        private:
            using FactoryLambda = std::function<Initializer (Config::XmlComponent &data, GameObject entity)>;
            using F = auto (Config::XmlComponent &data, GameObject entity) -> Initializer;
            static const inline std::map<std::string, FactoryLambda>
                _buildables =
                {
                    //${BUILDERS}

                };
//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            Initializer create(std::string &type, Config::XmlComponent &data,
                               GameObject entity) override;
//////////////////////--------------------------/////////////////////////

    };
}



