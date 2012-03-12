#ifndef MAZE_MAP_H_
#define MAZE_MAP_H_

typedef uint8_t maze_sq_ix;

enum maze_edge {
	ME_UNK = 0,
	ME_WALL = 1,
	ME_OPEN = 2
};

/* The stored representation of a single square in a maze.
 * @down, @right: assigned on of enum maze_edge. */
struct maze_sq_store {
	uint8_t down, right;
} __attribute__((__aligned__(2)));

/* A whole maze */
struct maze {
	struct maze_sq_store sqs[MAX_MAZE_LEN][MAX_MAZE_WIDTH];
};
extern struct maze g_maze;

/* A representation of the information in the maze map. */
struct maze_sq {
	uint8_t up, down, left, right;
};

/* FIXME: Is this function too big to inline? */
static inline struct maze_sq maze_get_sq(maze_sq_ix x, maze_sq_ix y)
{
	return (struct maze_sq){
		.down  = g_maze[x][y].down,
		.right = g_maze[x][y].right,
		.up    = g_maze[x][y-1].down,
		.left  = g_maze[x-1][y].right
	};
}

#endif
