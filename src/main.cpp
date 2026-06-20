
#include <fstream>
#include <ios>

#include "fileschemas.hpp"
#include "fileparser.hpp"
#include "utils.hpp"




int main(int argc, char* argv[]) {
    
    using namespace Minecraft::Utils;

    // file config loads
    {
        std::ifstream configFile("settings.config", std::ios_base::in);

        LineEntry schema[] = {MAIN_SETTINGS_FILE_SCHEMA(FILE_SCHEMA_ENTRY_RESOLVER)};
     
        if(!configFile) {
            
            LogMessage(LOG_TYPE_WARNING, "Settings file not found! Creating new one...");
            
            // create file
            std::ofstream outputFile("settings.config");

            auto configData = FileParser::SchemaToString(schema, 4);
            outputFile.write(configData.data(), configData.size());
            outputFile.close();

            LogMessage(LOG_TYPE_INFO, "Default settings have been written. Please change them as appropriate. For more information, visit the github page ");
            return -1;
        }
   
    }

    LogMessage(LOG_TYPE_INFO, "Initiating the server...");
    std::cout << std::endl;
    return 0;
}
