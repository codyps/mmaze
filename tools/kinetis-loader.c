#include <hidapi/hidapi.h>

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> /* getopt */

static const char opts[] = ":D:";


int main(int argc, char *argv[])
{
	int r;
	int opt;

	while ((opt = getopt(argc, argv, opts)) != -1) {

	}

	r = hid_init();
	if (r != 0) {
		fprintf(stderr, "Error: could not initialize hid library: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	

	r = hid_exit();
	if (r != 0)
		fprintf(stderr, "Warning: failed to cleanup hid library: %s\n", strerror(errno));
}
