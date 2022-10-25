# plugin-template

This is a template for creating a new plugin for the [Polymorph Engine](https://github.com/PolymorphEngine/engine).

## Installation

1. FORK this repository and set its `NAME` to the new plugin name (e.g. `pluginname-type`).
2. Set the CMake project name in `CMakeLists.txt` to the new plugin name (e.g. `pluginname-type`).
3. Change the `plugin-template.pcf.cpt` to the new plugin name (e.g. `pluginname-type.pcf.plugin`).
4. Make sure to change the `name=plugin-template` attribute too.
5. To be used, you also have to create `NAMESPACE` directory in `IncludeExport`
6. Inside it try to have at least an include file named by your plugin name (e.g. `IncludeExport/NAMESPACE/pluginname-type.hpp`).

## Architecture Example
    '---render-2D'
    '   |'
    '   |---render-2D.pcf.plugin'
    '   |---IncludeExport'
    '   |   |'
    '   |   |---Polymorph'
    '   |   |   |'
    '   |   |   |---render-2D.hpp' (including SpriteRendererComponent.hpp, TextureModule.hpp and more)

## Scripts
- Please make sure to use the `PolymorphInterface` to generate new scripts
- Otherwise you have to create scripts manually and add them to the `Factory/include/ScriptFactory.hpp` file
- Also to create manually the script `Initailizer` in the `Factory/include/intializers/` directory

## Symbols
- In case you are developing a plugin that implements other plugins `Interfaces`
- Make sure to add a dev dependency to the `CMakelists.txt` file with a fetch content
- Also include the `Interfaces and the Symbols definitions`
- Then you just have to make a definition for those
- That's it !

## Modules (Serializable classes)
- Belong in the `Core` directory

## Internal Plugin updates
- Belong in the `Core` directory
- In the class `PluginCore`
