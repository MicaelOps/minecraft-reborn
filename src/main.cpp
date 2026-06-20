
#include <fstream>
#include <ios>

#include "utils.hpp"


constexpr std::string_view settingsConfig = "name=asda\naplspa";

int main(int argc, char* argv[]) {
    
    using namespace Minecraft::Utils;

    std::ifstream configFile("settings.config", std::ios_base::in);

    if(!configFile) {
        
        LogMessage(LOG_TYPE_WARNING, "Settings file not found! Creating new one...");

        
        // create file
        std::ofstream outputFile("settings.config");
        outputFile.write(settingsConfig.data(), settingsConfig.size());
        outputFile.close();

        LogMessage(LOG_TYPE_INFO, "Default settings have been written. Please change them as appropriate. For more information, visit the github page ");
        return -1;
    }

    

    std::cout << "Initiating the server...." << std::endl;
    return 0;
}
