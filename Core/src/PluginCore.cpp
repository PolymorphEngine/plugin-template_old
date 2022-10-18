#include "PluginCore.hpp"
#include "Polymorph/Debug.hpp"
#include "ScriptFactory.hpp"

namespace Polymorph 
{
    std::string PluginCore::getPackageName()
    {
        return _packageName;
    }

    PluginCore::PluginCore(PluginCore::XmlNode &data, Engine &game) : _data(data), _game(game)
    {
        try {
            _packageName = _data.findAttribute("name")->getValue();
        } catch (myxmlpp::AttributeNotFoundException &e) {
            throw ExceptionLogger("Plugin: Plugin corrupted, no name attribute found");
        }
        _factory = std::make_unique<ScriptFactory>();
        _loadTemplates();
        _loadPrefabs();
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


    std::vector<std::shared_ptr<Config::XmlComponent>> &
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

            //TODO: determine directory where will be the plugin to set the work dir for configuration !!!!!!!!!!!!!
            //TODO: idea 1: the engine sends the plugin path from the global workdir ?
            _prefabs.emplace_back(std::make_shared<Config::XmlEntity>(t, _game, "" + _packageName));
            //TODO: VOUERY IMPOERTENTE
        }
            
    }

    void PluginCore::_loadTemplates()
    {
        auto templates = _data.findChild("Templates");
        
        for (auto &t: *templates)
            _templates.emplace_back(std::make_shared<Config::XmlComponent>(t));

    }

    bool PluginCore::hasPrefab(std::string &id)
    {
        return std::find_if(_prefabs.begin(), _prefabs.end(), [&id](auto &p) {
            return p->getId() == id;
        }) != _prefabs.end();
    }

    std::shared_ptr<Config::XmlEntity> &PluginCore::getPrefabConf(std::string &id)
    {
        auto r = std::find_if(_prefabs.begin(), _prefabs.end(), [&id](auto &p) {
            return p->getId() == id;
        });
        return *r;
    }
}