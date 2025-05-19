#include "jsonify.h"
#include <stdio.h>

char* create_json(char* user_id, unsigned int distance){
        static char json_data[256];

        snprintf(json_data, sizeof(json_data),
                "{\"device-id\": \"%s\", \"distance\": %u}",
                user_id, distance);
        return json_data;
}
