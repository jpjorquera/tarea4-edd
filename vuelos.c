#include <stdlib.h>
typedef struct vertex {
    unsigned long ciudad;
    struct vertex *adyacente;
} vertex;

typedef struct {
    vertex *head;
} tGrafo;


int maint(){
    return 1;
}