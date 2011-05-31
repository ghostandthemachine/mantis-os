
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <netdb.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include <glib.h>

#include "bionet-util.h"




bionet_stream_t *bionet_stream_new(
    const char *id,
    bionet_stream_direction_t direction,
    const char *type,
    const char *host,
    uint16_t port
) {
    bionet_stream_t *stream;


    //
    // is the caller INSANE??!
    //

    if (id == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new: no id specified!");
        return NULL;
    }

    if (! bionet_is_valid_name_component(id)) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new: invalid id specified!");
        return NULL;
    }

    if (
        (direction != BIONET_STREAM_DIRECTION_PRODUCER) &&
        (direction != BIONET_STREAM_DIRECTION_CONSUMER)
    ) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new: invalid direction specified!");
        return NULL;
    }

    if (type == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new: no type specified!");
        return NULL;
    }

    // FIXME: make this its own function, is_valid_type()
    if (strcmp(type, "audio") != 0) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new: invalid type specified!");
        return NULL;
    }


    //
    //  caller is sane
    //  allocate stream
    //

    stream = (bionet_stream_t *)calloc(1, sizeof(bionet_stream_t));
    if (stream == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "out of memory!");
        goto cleanup;
    }


    //
    // throw caller's arguments in the stream
    //

    stream->id = strdup(id);
    if (stream->id == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "out of memory!");
        goto cleanup;
    }

    stream->direction = direction;

    stream->type = strdup(type);
    if (stream->type == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "out of memory!");
        goto cleanup;
    }

    if (host != NULL) {
        stream->host = strdup(host);
        if (stream->host == NULL) {
            g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "out of memory!");
            goto cleanup;
        }
    }

    stream->port = port;

    return stream;


cleanup:
    if (stream != NULL) {
        bionet_stream_free(stream);
    }
    return NULL;
}




bionet_stream_t *bionet_stream_new_from_strings(
    const char *id,
    const char *direction_str,
    const char *type,
    const char *host,
    const char *port_str
) {
    bionet_stream_direction_t direction;

    bionet_stream_t *stream;


    //
    // is the caller INSANE??!
    //

    if (id == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new_from_strings: no id specified!");
        return NULL;
    }

    if (! bionet_is_valid_name_component(id)) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new_from_strings: invalid id specified!");
        return NULL;
    }

    direction = bionet_stream_direction_from_string(direction_str);
    if (
        (direction != BIONET_STREAM_DIRECTION_PRODUCER) &&
        (direction != BIONET_STREAM_DIRECTION_CONSUMER)
    ) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new_from_strings: invalid direction specified!");
        return NULL;
    }

    if (type == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new_from_strings: no type specified!");
        return NULL;
    }

    // FIXME: make this its own function, is_valid_type()
    if (strcmp(type, "audio") != 0) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "bionet_stream_new_from_strings: invalid type specified!");
        return NULL;
    }


    //
    //  caller is sane
    //  allocate stream
    //

    stream = (bionet_stream_t *)calloc(1, sizeof(bionet_stream_t));
    if (stream == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "out of memory!");
        goto cleanup;
    }


    //
    // throw caller's arguments in the stream
    //

    stream->id = strdup(id);
    if (stream->id == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "out of memory!");
        goto cleanup;
    }

    stream->direction = direction;

    stream->type = strdup(type);
    if (stream->type == NULL) {
        g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "out of memory!");
        goto cleanup;
    }

    if (host != NULL) {
        stream->host = strdup(host);
        if (stream->host == NULL) {
            g_log(BIONET_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "out of memory!");
            goto cleanup;
        }
    }

    // FIXME: better error checking
    stream->port = atoi(port_str);

    return stream;


cleanup:
    if (stream != NULL) {
        bionet_stream_free(stream);
    }
    return NULL;
}

