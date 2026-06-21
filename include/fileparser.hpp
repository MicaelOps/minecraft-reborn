#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <fstream>
#include <utility>
#include <variant>

#include "utils.hpp"

#define FILE_SCHEMA_ENTRY_RESOLVER(identifier, name, type, value) {name, LineEntry::Type::type, value}


#define FILE_SCHEMA_ENTRY_ERASER(identifier, name, type, value) identifier

#define FILE_SCHEMA_SCHEMA_COUNT(decl, prefix) decl, prefix##_SCHEMA_COUNT

#define FILE_SCHEMA_ENTRY_IDENTIFIER_SETUP(declarations, prefix) enum { declarations, prefix##_SCHEMA_COUNT};

namespace Minecraft {
namespace Utils {

struct LineEntry {

    enum Type {

        TEXT, NUMBER
    };  
    std::string_view name;
    Type type;
    std::variant<std::string, int> value; // also default value        
};

inline bool ParseValue(std::string_view value, LineEntry::Type type, std::variant<std::string, int>& entry) {

    int integerValue = -1;
            
    switch (type) {
        case LineEntry::NUMBER:
            std::from_chars(value.begin(), value.end(), integerValue);
            entry = integerValue;        
            return false;
        case LineEntry::TEXT:
            std::get<std::string>(entry).assign(value);
            return false;
        default:
          return true;
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
                if constexpr (std::is_same_v<T, std::string>) {
                    text.append(v);
                } else if constexpr (std::is_same_v<T, int>) {
                    text.append(std::to_string(v));
                }
            }, schema[i].value);
            text.append("\n");
        }
        return text;
    }

    static bool Process(std::ifstream& stream, FileSchema& schema, int schemaSize) {
    
        std::string line;
        int count = 0;

        while (std::getline(stream, line)) {

            const std::string_view lineView(line);

            const auto index = lineView.find_first_of('=');

            RETURN_IF_MESSAGE(index == std::string::npos, std::format("Unable to parse line: {}", lineView));

            const auto key = lineView.subview(0, index);

            for(auto i = 0; i < schemaSize; ++i) {
                if(key == schema[i].name) {
                    RETURN_IF_MESSAGE(ParseValue(lineView.subview(index+1), schema[i].type, schema[i].value), "Unable to parse value");
                    ++count;  
                }  
            }
        }

        // Checking if we parsed all the lines we expected
        RETURN_IF_MESSAGE(count!=schemaSize, "Unable to parse all values");

        return false; // function did not fail
    }
};
}
}
#endif