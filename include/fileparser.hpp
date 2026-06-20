#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <fstream>
#include <string>
#include <string_view>
#include <utility>
#include <variant>

#include "utils.hpp"

#define FILE_SCHEMA_ENTRY_RESOLVER(name, type, value) {name, LineEntry::Type::type, value}

namespace Minecraft {
namespace Utils {

    struct LineEntry {

        enum Type {

            TEXT, NUMBER
        };  
        std::string_view name;
        Type type;
        std::variant<std::string_view, int> value; // also default value        
    };
    
    inline std::variant<std::string_view, int> ParseValue(std::string_view value, LineEntry::Type type) {

        int integerValue = -1;
            
        switch (type) {
            case LineEntry::NUMBER:
                std::from_chars(value.begin(), value.end(), integerValue);
                return integerValue;        
            case LineEntry::TEXT:
                return value;
            default:
              return "ERROR_TYPE";
        }
        std::unreachable();
    }


    class FileParser {

        using FileSchema = LineEntry[];

        FileParser() = delete;
        FileParser(FileParser&) = delete;

    public:
        static std::string SchemaToString(const FileSchema& schema, int schemaSize) {
            std::string text;

            text.reserve(schemaSize*20);

            for(auto i = 0; i < schemaSize; ++i) {
                text.append(schema[i].name);
                text.append("=");
    
                std::visit([&](const auto& v) {
                    using T = std::decay_t<decltype(v)>;

                    if constexpr (std::is_same_v<T, std::string_view>) {
                        text.append(v);
                    } else if constexpr (std::is_same_v<T, int>) {
                        text.append(std::to_string(v));
                    }
                }, schema[i].value);

                text.append("\n");
            }
            return text;
        }

        static void Process(std::ifstream& stream, FileSchema& schema, int schemaSize) {
    
            std::string line;
            while (std::getline(stream, line)) {

                std::string_view lineView(line);

                auto index = lineView.find_first_of('=');

                if(index == std::string::npos) {
                    LogMessage(LOG_TYPE_WARNING, std::format("Ignoring line: {}", lineView));
                    continue;
                }

                const auto key = lineView.substr(0, index);

                for(auto i = 0; i < schemaSize; ++i) {
                    if(key == schema[i].name) {
                        schema[i].value = std::move(ParseValue(key, schema[i].type));
                    }    
                }
            }
        }
    };
}
}
#endif