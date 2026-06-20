#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <any>
#include <fstream>
#include <string_view>
#include <unordered_map>



namespace Minecraft {
namespace Utils {


    class FileParser {

        struct Value {

            enum Type {
                TEXT, NUMBER, DECIMAL
            };  

            Type type;
            std::any value;
        };

        using FileSchema = std::unordered_map<std::string_view, Value>;
    private:
        bool process(std::ifstream& stream, std::unordered_map<std::string_view, Value> output) {

            while(stream.good()) {
                char* character;
                stream.read(character, 1);
            }
            return true;
        }
    };
}
}
#endif