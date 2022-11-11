#include <iostream>
#include <memory>
#include <vector>
#include <polymorph/Core.hpp>
#include <polymorph/Config.hpp>
#include <polymorph/Plugins.hpp>

namespace polymorph::engine
{
    class PluginCore : public IPlugin
    {
        public:


        public:
            using XmlNode = myxmlpp::Node;
            PluginCore(XmlNode &data, Engine &game, std::string PluginsPath);
            ~PluginCore() override = default;

        private:
            PluginCore(const PluginCore &copy): _data(copy._data), _game(copy._game), _pluginsPath(copy._pluginsPath), assetManager(copy.assetManager), pluginManager(copy.pluginManager) {
                
            }
            
        public:
            static inline const PluginCore* Plugin = nullptr;
            PluginManager &pluginManager;
            AssetManager &assetManager;

        private:

            std::string _packageName;
            bool _isEnabled = true;
            std::string _pluginsPath;
            XmlNode _data;
            std::vector<std::shared_ptr<Config::XmlEntity>> _prefabs;
            std::vector<Config::XmlComponent> _templates;
            std::unique_ptr<IScriptFactory> _factory;
            std::unique_ptr<ISerializableObjectFactory> _objectFactory;
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
         
            std::shared_ptr<ASerializableObject>
            createSharedObject(std::string &type, Config::XmlComponent &data,
                               std::shared_ptr<Config::XmlNode> &node,
                               engine::PluginManager &Plugins) override;

            std::shared_ptr<ASerializableObject>
            createEmptySharedObject(std::string &type,
                                    PluginManager &Plugins) override;

            bool hasObject(std::string &type) override;
            
        private:
            void _loadPrefabs();
            void _loadTemplates();
            void _initializePlugin();

    };
}