#include <stdio.h>
#include <string.h>

typedef struct {
    int w, h; // width, height
} Plane;

void print_plane(Plane *p) {
    printf("W %d, H %d\n", p->w, p->h);
}

typedef union {
    int i;
    char c[10];
    Plane p;
} Mix;

int main(){
    Mix m;
    m.p.h = 3;
    m.p.w = 5;
    printf("m.i=%d\n", m.i);
    print_plane(&m.p);
    strcpy(m.c, "Hello!\n");
    printf("%s", m.c); // %s - format for a string
}