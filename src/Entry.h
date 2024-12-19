#pragma once
#include <endstone/plugin/plugin.h>

namespace jse {

class PluginDescriptionBuilderImpl : public endstone::detail::PluginDescriptionBuilder {
public:
    PluginDescriptionBuilderImpl() {
        description  = "JavaScript Engine";
        authors      = {"engsr6982"};
        contributors = {"engsr6982", "zimuya4153"}; // Github Username
        website      = "https://github.com/engsr6982/Js_Engine";
    }
};

class Entry : public endstone::Plugin {
public:
    static Entry* getInstance();

    void onLoad() override;

    void onEnable() override;

    void onDisable() override;

    endstone::PluginDescription const& getDescription() const override;

private:
    PluginDescriptionBuilderImpl builder;
    endstone::PluginDescription  description_ = builder.build("js_engine", "0.1.0");
};
} // namespace jse