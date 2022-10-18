#include <iostream>
#include <memory>
#include <vector>
#include <Polymorph/Core.hpp>
#include <Polymorph/Config.hpp>

namespace Polymorph
{
    class PluginCore : public IPlugin
    {

        public:
            using XmlNode = myxmlpp::Node;
            PluginCore(XmlNode &data, Engine &game);
            ~PluginCore() = default;


        private:
            std::string _packageName;
            XmlNode _data;
            std::vector<std::shared_ptr<Config::XmlEntity>> _prefabs;
            std::vector<std::shared_ptr<Config::XmlComponent>> _templates;
            std::unique_ptr<IScriptFactory> _factory;
            Engine &_game;

        public:
            virtual std::string getPackageName() final;

            virtual std::shared_ptr<IComponentInitializer> createComponent(std::string &type,
            Config::XmlComponent &data, GameObject entity) final;
            
            virtual bool hasComponent(std::string &type) final;

            virtual bool hasPrefab(std::string &id) final;

            virtual std::shared_ptr<Config::XmlEntity> &getPrefabConf(std::string &id) final;

            virtual std::vector<std::shared_ptr<Config::XmlComponent>> &getComponentTemplates() final;

            virtual void preUpdateInternalSystems(std::shared_ptr<Scene> &scene) final;

            virtual void updateInternalSystems(std::shared_ptr<Scene> &scene) final;

            virtual void postUpdateInternalSystems(std::shared_ptr<Scene> &scene) final;
            
        private:
            void _loadPrefabs();
            void _loadTemplates();

    };
}