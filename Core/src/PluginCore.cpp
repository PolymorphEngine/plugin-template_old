#include "PluginCore.hpp"

#include <utility>
#include "polymorph/Debug.hpp"
#include "../../Factory/include/ScriptFactory.hpp"
#include "../../Factory/include/ObjectFactory.hpp"
#include "Plugins/AssetManager.hpp"
#include "Plugins/PluginManager.hpp"
#include "ScriptingAPI/ASerializableObject.hpp"

namespace polymorph::engine 
{
    std::string PluginCore::getPackageName()
    {
        return _packageName;
    }

    PluginCore::PluginCore(PluginCore::XmlNode &data, Engine &game, std::string PluginsPath) 
    : _data(data), _game(game), _pluginsPath(std::move(PluginsPath)), assetManager(game.getAssetManager()), pluginManager(game.getPluginManager())
    {
        _initializePlugin();
    }

    std::shared_ptr<IComponentInitializer>
    PluginCore::createComponent(std::string &type, Config::XmlComponent &data,
    GameObject entity)
    {
        return _factory->create(type, data, entity);
    }

    bool PluginCore::hasComponent(std::string &type)
    {
        return _factory->hasType(type);
    }


    std::vector<Config::XmlComponent> &
    PluginCore::getComponentTemplates()
    {
        return _templates;
    }

    void PluginCore::preUpdateInternalSystems(std::shared_ptr<Scene> &scene)
    {

    }

    void PluginCore::updateInternalSystems(std::shared_ptr<Scene> &scene)
    {
        
    }

    void PluginCore::postUpdateInternalSystems(std::shared_ptr<Scene> &scene)
    {

    }

    void PluginCore::_loadPrefabs()
    {
        auto prefabs = _data.findChild("Prefabs");

        for (auto &t: *prefabs) {
            _prefabs.emplace_back(std::make_shared<Config::XmlEntity>(t, _game, _pluginsPath +"/"+ _packageName));
        }
            
    }

    void PluginCore::_loadTemplates()
    {
        auto templates = _data.findChild("Templates");
        
        for (auto &t: *templates)
            _templates.emplace_back(t);

    }

    bool PluginCore::hasPrefab(const std::string &id)
    {
        return std::find_if(_prefabs.begin(), _prefabs.end(), [&id](auto &p) {
            return p->getId() == id;
        }) != _prefabs.end();
    }

    std::shared_ptr<Config::XmlEntity> &PluginCore::getPrefabConf(
            const std::string &id)
    {
        auto r = std::find_if(_prefabs.begin(), _prefabs.end(), [&id](auto &p) {
            return p->getId() == id;
        });
        return *r;
    }

    bool PluginCore::isEnabled()
    {
        return _isEnabled;
    }

    void PluginCore::startScripts(std::shared_ptr<Scene> &scene)
    {

    }

    void PluginCore::endScripts(std::shared_ptr<Scene> &scene)
    {

    }

    void PluginCore::_initializePlugin()
    {
        Plugin = this;
        try {
            _packageName = _data.findAttribute("name")->getValue();
            _isEnabled = _data.findAttribute("enabled")->getValueBool();
        } catch (myxmlpp::AttributeNotFoundException &e) {
            throw ExceptionLogger("Plugin: Plugin corrupted, no name attribute found");
        }
        _factory = std::make_unique<ScriptFactory>();
        _objectFactory = std::make_unique<ObjectFactory>();
        if (!_isEnabled)
            return;
        _loadTemplates();
        _loadPrefabs();
    }

    std::shared_ptr<ASerializableObject>
    PluginCore::createSharedObject(std::string &type,
                                   Config::XmlComponent &data,
                                   std::shared_ptr<Config::XmlNode> &node,
                                   engine::PluginManager &Plugins)
    {
        return _objectFactory->createS(type, node, data, Plugins);
    }

    bool PluginCore::hasObject(std::string &type)
    {
        return _objectFactory->hasType(type);
    }

    std::shared_ptr<ASerializableObject>
    PluginCore::createEmptySharedObject(std::string &type,
                                        PluginManager &Plugins)
    {
        return _objectFactory->createEmpty(type, Plugins);
    }
}

extern "C"
{
    EXPORT_MODULE polymorph::engine::IPlugin *createPlugin(polymorph::engine::Config::XmlNode &data,
    polymorph::engine::Engine &game, std::string PluginsPath)
    {
        return new polymorph::engine::PluginCore(data, game, std::move(PluginsPath));
    }
}
