#pragma once

typedef struct {
	unsigned char magic[4];
	unsigned short width;
	unsigned short height;
	unsigned int   length;
	unsigned char  alpha;
} DukeHeader_t;
