#ifndef FILE_SCHEMA_H
#define FILE_SCHEMA_H


#define MAIN_SETTINGS_FILE_SCHEMA(entry) \
    entry("hostname", TEXT, "localhost") \
    entry("port", NUMBER, 25565) \
    entry("name", TEXT, "Default Name") \
    entry("motd", TEXT, "This server is ready for HIGH loads")


#endif
