#include <hidapi/hidapi.h>

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> /* getopt */

static const char opts[] = ":hD:";

#define PRGMNAME (argc?argv[0]:"kinetis-loader")
#define usage(e) usage_(PRGMNAME, e)
static void usage_(const char *prgmname, int e)
{
	FILE *f;
	if (e == EXIT_SUCCESS)
		f = stdout;
	else
		f = stderr;

	fprintf(f,
"Usage: %s [options]\n"
"Options: [%s]\n"
"	-D <device>	device to communicate with\n"
"	-h		show this help\n",

	prgmname, opts);

	exit(e);
}

int main(int argc, char *argv[])
{
	int r;
	int opt;
	int err = 0;
	char *dev_path = NULL;

	while ((opt = getopt(argc, argv, opts)) != -1) {
		switch (opt) {
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case 'D':
			free(dev_path);
			dev_path = strdup(optarg);
			break;
		case ':':
		case '?':
		default:
			fprintf(stderr, "Error: unknown flag -%c\n", optopt);
			err++;
		}
	}

	if (!dev_path) {
		fprintf(stderr, "Error: a device (-D) is required\n");
		err++;
	}

	if (err) {
		fprintf(stderr, "Exiting due to previous errors, try `-h` for usage\n");
		exit(EXIT_FAILURE);
	}

	r = hid_init();
	if (r != 0) {
		fprintf(stderr, "Error: could not initialize hid library: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* TODO: do something */
	hid_device *dev = hid_open_path(dev_path);
	if (!dev) {
		fprintf(stderr, "Error: could not open hid device %s: %s\n", dev_path, strerror(errno));
		exit(EXIT_FAILURE);
	}

	r = hid_exit();
	if (r != 0)
		fprintf(stderr, "Warning: failed to cleanup hid library: %s\n", strerror(errno));

	return 0;
}
