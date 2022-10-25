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


        public:
            using XmlNode = myxmlpp::Node;
            PluginCore(XmlNode &data, Engine &game, std::string PluginsPath);
            ~PluginCore() = default;

            
        public:
            static inline std::shared_ptr<PluginManager> pluginManager = nullptr;
            static inline std::shared_ptr<AssetManager> assetManager = nullptr;

        private:
            std::string _packageName;
            bool _isEnabled = true;
            std::string _pluginsPath;
            XmlNode _data;
            std::vector<std::shared_ptr<Config::XmlEntity>> _prefabs;
            std::vector<Config::XmlComponent> _templates;
            std::unique_ptr<IScriptFactory> _factory;
            Engine &_game;
            
        public:
            /**
             * @brief Get the package name
             * @return The package name as a string
             */
            std::string getPackageName() final;

            /**
             * @brief Create a component from the plugin
             * @param type The type of the component to create (as a string)
             * @param data The data of the component to create (as a XmlComponent)
             * @param entity The entity to which the component will be attached
             * @return A shared pointer to the created component container
             */
            std::shared_ptr<IComponentInitializer> createComponent(std::string &type,
            Config::XmlComponent &data, GameObject entity) final;
            
            
            /**
             * @brief Check if the plugin is enabled
             * @return True if the plugin is enabled, false otherwise
             */
            bool isEnabled() override;
            
            /**
             * @brief Check if the plugin has a component of the given type
             * @param type The type of the component to check
             * @return True if the plugin has a component of the given type, false otherwise
             */
            bool hasComponent(std::string &type) final;

            /**
             * @brief Check if the plugin has a prefab of the given id
             * @param id The id of the prefab to check
             * @return True if the plugin has a prefab of the given id, false otherwise
             */
            bool hasPrefab(const std::string &id) final;


            /**
             * @brief Get the prefab configuration
             * @param id The id of the prefab
             * @return A shared pointer to the prefab configuration
             */
            std::shared_ptr<Config::XmlEntity> &getPrefabConf(
                    const std::string &id) final;


            /*
             * @brief Get the component templates
             * @return A vector of shared pointers to the component templates
             */
            std::vector<Config::XmlComponent> &getComponentTemplates() final;

            void startScripts(std::shared_ptr<Scene> &scene) override;

            void preUpdateInternalSystems(std::shared_ptr<Scene> &scene) final;

            void updateInternalSystems(std::shared_ptr<Scene> &scene) final;

            void postUpdateInternalSystems(std::shared_ptr<Scene> &scene) final;

            void endScripts(std::shared_ptr<Scene> &scene) override;
            
        private:
            void _loadPrefabs();
            void _loadTemplates();
            void _initializePlugin();

    };
}