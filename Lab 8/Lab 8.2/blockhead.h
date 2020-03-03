struct BLOCKHEAD_NODE
{
    int x,y; // position
    float dx,dy; // movement component
    long color;
    int size;
};
typedef struct BLOCKHEAD_NODE BLOCK;

void addBlockHeadToList(struct BLOCKHEAD_NODE ** blockhead_array, int number_of_blocks);
//void printlist( struct BLOCKHEAD_NODE *blockhead_array, int number_of_blocks);
void addBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_array, int* x, int* y, int number_of_blocks);
void removeBlockHeadFromList( struct BLOCKHEAD_NODE ** blockhead_array, int index, int number_of_blocks);
void removeBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_array, int* x, int* y, int *number_of_blocks);
//void freeBlockHeadList( struct BLOCKHEAD_NODE ** blockhead_array);
void renderBlockHead(struct BLOCKHEAD_NODE * blockhead, SDL_Surface *screenSurface);
void renderBlockHeadList( struct BLOCKHEAD_NODE ** blockhead_array, SDL_Surface *screenSurface, int number_of_blocks);
void moveBlockHead(struct BLOCKHEAD_NODE * blockhead);
void moveBlockHeadList( struct BLOCKHEAD_NODE * blockhead_array,int number_of_blocks);

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 1000;
