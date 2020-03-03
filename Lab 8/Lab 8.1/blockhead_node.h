struct BLOCKHEAD_NODE
{
    int x,y; // position
    float dx,dy; // movement component
    long color;
    int size;
    struct BLOCKHEAD_NODE * next;
};
typedef struct BLOCKHEAD_NODE BLOCK;

void printBlock(struct BLOCKHEAD_NODE ** blockhead_list);

void addBlockHeadToList( struct BLOCKHEAD_NODE ** blockhead_list);
void addBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_list, int* x, int* y);
void removeBlockHeadFromList( struct BLOCKHEAD_NODE ** blockhead_list, int index);
void removeBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_list, int* x, int* y);
void renderBlockHead(struct BLOCKHEAD_NODE * blockhead, SDL_Surface *screenSurface);
void renderBlockHeadList( struct BLOCKHEAD_NODE * blockhead_list, SDL_Surface *screenSurface);
void moveBlockHead(struct BLOCKHEAD_NODE * blockhead);
void moveBlockHeadList( struct BLOCKHEAD_NODE * blockhead_list);

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 1000;
