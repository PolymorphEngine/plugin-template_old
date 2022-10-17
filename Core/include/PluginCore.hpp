#include <iostream>
#include <memory>
#include <vector>
#include <Polymorph/Core.hpp>
#include <Polymorph/Config.hpp>

namespace Polymorph
{
    class PluginCore : IPlugin
    {

        public:
            PluginCore(XmlNode data);
            ~PluginCore() = default;


        private:
            std::string _packageName;
            XmlNode _data;
            std::vector<std::shared_ptr<Config::XmlEntity> _prefabs;
            std::vector<std::shared_ptr<Config::XmlComponent> _templates;


        public:        
            virtual std::string getPackageName() final;

            virtual std::shared_ptr<AComponentInitializer> createComponent() final;

            virtual std::vector<std::shared_ptr<Entity>> &getPrefabs() final;

            virtual std::vector<std::shared_ptr<Config::XmlComponent>> &getComponentTemplates() final;

            virtual void preUpdateInternalSystems(std::shared_ptr<Scene> &scene) final;
            
            virtual void updateInternalSystems(std::shared_ptr<Scene> &scene) final;
            
            virtual void postUpdateInternalSystems(std::shared_ptr<Scene> &scene) final;

    };
}