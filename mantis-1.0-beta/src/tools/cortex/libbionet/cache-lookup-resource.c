

#include <string.h>

#include <glib.h>

#include "bionet.h"


bionet_resource_t *bionet_cache_lookup_resource(const char *hab_type, const char *hab_id, const char *node_id, const char *resource_id) {
    bionet_node_t *node;

    node = bionet_cache_lookup_node(hab_type, hab_id, node_id);
    if (node == NULL) {
        return NULL;
    }

    return bionet_node_get_resource_by_id(node, resource_id);
}


