#include <stdio.h>
#include <stdlib.h>

#define offset_of(st, m) \
((size_t)&(((st *)0)->m))

#define container_of(ptr, type, member)({ \
	const typeof (((type *)0)->member) *_mptr = (ptr); \
(type *)((char *)_mptr - offset_of(type, member));})

typedef struct _api_t api_t;


typedef void (*api_set_fun_t)(api_t *api, int a);
typedef int(*api_read_fun_t)(api_t *api);

struct _api_t {
    api_read_fun_t read;
    api_set_fun_t set;
};

typedef struct{
    api_t api;
    int value;
} api_priv_t;


void set(api_t *api, int a){
    api_priv_t *priv_api = container_of(api, api_priv_t, api);
    priv_api->value = a;
}

int read(api_t *api){
     api_priv_t *priv_api = container_of(api, api_priv_t, api);
     return priv_api->value;
}


api_t *install_api(void){
    api_priv_t *api_priv = malloc(sizeof(api_priv_t));
    if(api_priv == NULL){
        return NULL;
    }
    api_priv->api.read = &read;
    api_priv->api.set = &set;
    return (api_t*) &(api_priv->api);
}

void uninstall_api(api_t *api){
    free(api);
}


int main(void)
{
    struct _api_t API;
    struct api_t *mycontainer= (struct api_t*)malloc(sizeof(api_t));
    struct API *mycontainer1= (struct API*)malloc(sizeof(API));
    printf("%d\n", &mycontainer);
    printf("%d\n", &mycontainer1);

    api_t *api = install_api();
    api->set(api, 9);
    printf("%d\n", api->read(api));
    uninstall_api(api);
    return 0;
}
