#define BOARD_HEIGHT 100
#define BOARD_WIDTH 200

void next_generation(int board[BOARD_HEIGHT][BOARD_WIDTH]);
int next_state(int board[BOARD_HEIGHT][BOARD_WIDTH],int x,int y);
int num_neighbors(int board[BOARD_HEIGHT][BOARD_WIDTH],int x,int y);
void init_board( int board[BOARD_HEIGHT][BOARD_WIDTH], int num_alive);
void display_board( int board[BOARD_HEIGHT][BOARD_WIDTH], SDL_Window*window, SDL_Surface* screenSurface);
void add_random(int board[BOARD_HEIGHT][BOARD_WIDTH], int num_alive);
void kill_random(int board[BOARD_HEIGHT][BOARD_WIDTH], float chance);
