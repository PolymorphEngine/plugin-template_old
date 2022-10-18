#include <iostream>
#include <memory>
#include <vector>
#include <Polymorph/Core.hpp>
#include <Polymorph/Config.hpp>
#include <Polymorph/Plugins.hpp>

namespace Polymorph
{
    class PluginCore : public IPlugin
    {

        public:
            using XmlNode = myxmlpp::Node;
            PluginCore(XmlNode &data, Engine &game, std::string PluginsPath);
            ~PluginCore() = default;


        private:
            std::string _packageName;
            std::string _pluginsPath;
            XmlNode _data;
            std::vector<std::shared_ptr<Config::XmlEntity>> _prefabs;
            std::vector<std::shared_ptr<Config::XmlComponent>> _templates;
            std::unique_ptr<IScriptFactory> _factory;
            Engine &_game;

        public:
            std::string getPackageName() final;

            std::shared_ptr<IComponentInitializer> createComponent(std::string &type,
            Config::XmlComponent &data, GameObject entity) final;
            
            bool hasComponent(std::string &type) final;

            bool hasPrefab(std::string &id) final;

            std::shared_ptr<Config::XmlEntity> &getPrefabConf(std::string &id) final;

            std::vector<std::shared_ptr<Config::XmlComponent>> &getComponentTemplates() final;

            void preUpdateInternalSystems(std::shared_ptr<Scene> &scene) final;

            void updateInternalSystems(std::shared_ptr<Scene> &scene) final;

            void postUpdateInternalSystems(std::shared_ptr<Scene> &scene) final;
            
        private:
            void _loadPrefabs();
            void _loadTemplates();

    };
}