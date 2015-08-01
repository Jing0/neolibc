# ini-reader
ini-reader is a simple .ini parser implemented in C

## Simple example in C ##

```
; ignore this comment
[DATA]
port=8080
backlog=10
buffersize=8192
[PATH]
root="./"
index=index.html
errPath=./_pages/
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

typedef struct serverConfig {
    int port;
    int backlog;
    char indexPage[MAX_URI];
    char errPath[MAX_URI];
} serverConfig;

serverConfig gConfig;

int initialize() {
    ini_t *config = ini_new(CONFIG_PATH);
    if (config == NULL) {
        fprintf(stderr, "%s\n",
                "Failed to read initialization file.\n"
                "Default configuration will be used");
        return -1;
    }
    ini_getInt(config, "DATA", "port", &gConfig.port);
    ini_getInt(config, "DATA", "backlog", &gConfig.backlog);
    ini_getString(config, "PATH", "index", gConfig.indexPage);
    ini_getString(config, "PATH", "errPath", gConfig.errPath);
    ini_free(config);
    return 0;
}

int main(int argc, char const *argv[]) {   
    initialize();
    return 0;
}
```

a snippet adapted from [TinyServer](https://github.com/Jing0/TinyServer)