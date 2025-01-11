#pragma once
#include <endstone/detail/plugin/plugin_description_builder.h>
#include <endstone/plugin/plugin.h>
#include <endstone/plugin/plugin_description.h>
#include <cstdint>

namespace jse {

class JsPluginDescriptionBuilder : public endstone::detail::PluginDescriptionBuilder {
public:
    JsPluginDescriptionBuilder() = default;
};

class JavaScriptPlugin : public endstone::Plugin {
public:
    JavaScriptPlugin(uint64_t engineId, endstone::PluginDescription description)
    : engineId_(engineId),
      description_(description) {}
    ~JavaScriptPlugin() override;

public:
    void onLoad() override;
    void onEnable() override;
    void onDisable() override;

    const endstone::PluginDescription& getDescription() const override;

    bool
    onCommand(endstone::CommandSender& sender, const endstone::Command& command, const std::vector<std::string>& args)
        override;

private:
    uint64_t                    engineId_;
    endstone::PluginDescription description_;
};


} // namespace jse
