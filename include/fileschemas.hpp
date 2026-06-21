#ifndef FILE_SCHEMA_H
#define FILE_SCHEMA_H


#define MAIN_SETTINGS_FILE_SCHEMA(entry)                                                    \
    entry(SETTINGS_HOSTNAME, "hostname", TEXT, "localhost"),                                \
    entry(SETTINGS_NETWORK_PORT, "port", NUMBER, 25565),                                    \
    entry(SETTINGS_SERVER_NAME, "name", TEXT, "Default Name"),                              \
    entry(SETTINGS_SERVER_MOTD, "motd", TEXT, "This server is ready for HIGH loads")


#endif
