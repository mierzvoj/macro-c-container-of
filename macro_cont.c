#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define offset_of(st, m) \
((size_t)&(((st *)0)->m))

#define container_of(ptr, type, member)({ \
	const typeof (((type *)0)->member) *_mptr = (ptr); \
(type *)((char *)_mptr - offset_of(type, member));})


typedef struct api api_;

typedef void (*setit)(struct api*, int y);
typedef int (*getit)(struct api*);

struct api{
    setit set;
    getit get;
};


typedef struct {
    int some_other_data;
    int this_data;
    api_ api;
} container;

int get(api_ *x){
    container *y = container_of(x, container, api );
    return y->some_other_data;
}


void set(api_ *x, int y){
    container *z = container_of(x, container, api);
    z->some_other_data = y;

}

struct api *use_api(){
    container *mycontainer= (container*)malloc(sizeof(mycontainer));
    mycontainer->api.set = &set;
    mycontainer->api.get = &get;
    return (struct api *) &(mycontainer->api);
}

int main(void)
{
    struct api *data = use_api();
    data->set(data,10);
    printf("%d", data->get(data));
    return 0;
}
