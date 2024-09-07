#pragma once
#include "Extension.h"
#include<algorithm>

class ExtensionHandler{
private:
    static ExtensionHandler* extensionHandler;
    std::vector<std::string> nom_extensions;
    std::vector<Extension*>extensions;
    ExtensionHandler();
public:
    ExtensionHandler(ExtensionHandler&)=delete;
    void operator=(const ExtensionHandler&)=delete;

    static ExtensionHandler* GetInstance();

    void activeExtension(const std::string& nom);
    bool isActive(const std::string& nom);
    void desactiveExtension(const std::string& nom);
    std::vector<Extension*> getActiveExtensions();
    inline std::vector<Extension*> getAllExtension(){return extensions;};
    inline std::vector<std::string> getExtensionsNames(){return nom_extensions;};
    ~ExtensionHandler();
};
