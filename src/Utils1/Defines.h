#pragma once

#define METHODS(FUNC) Local<Value> FUNC(Arguments const& args)

#define GetScriptClass(CLASS, VAL) EngineScope::currentEngine()->getNativeInstance<CLASS>(VAL)