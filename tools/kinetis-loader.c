#include <hidapi/hidapi.h>

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h> /* getopt */

static const char opts[] = ":hU:l";

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
"	-U <device>	usb hid device to communicate with\n"
"	-l		list usb hid devices\n"
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
	bool do_usb_list = false;

	while ((opt = getopt(argc, argv, opts)) != -1) {
		switch (opt) {
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case 'U':
			free(dev_path);
			dev_path = strdup(optarg);
			break;
		case 'l':
			do_usb_list = true;
			break;
		case ':':
		case '?':
		default:
			fprintf(stderr, "Error: unknown flag -%c\n", optopt);
			err++;
		}
	}

	if (!dev_path && !do_usb_list) {
		fprintf(stderr, "Error: a device (`-U <device>`) is required, use `-l` to list them\n");
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

	if (do_usb_list) {
		struct hid_device_info *di = hid_enumerate(0, 0);	
		if (!di) {
			fprintf(stderr, "Error: could not enumerate hid devices: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		
		struct hid_device_info *i = di;
		while (i) {
			printf("%s  [%04x:%04x sn=%ls release=%x manuf=%ls product_string=%ls ifnum=%d]\n",
					i->path, i->vendor_id, i->product_id, i->serial_number, i->release_number,
					i->manufacturer_string, i->product_string, i->interface_number);
			i = i->next;
		}

		hid_free_enumeration(di);
	}

	if (dev_path) {
		hid_device *dev = hid_open_path(dev_path);
		if (!dev) {
			fprintf(stderr, "Error: could not open hid device %s: %s\n", dev_path, strerror(errno));
			exit(EXIT_FAILURE);
		}

		/* TODO: do something */

		hid_close(dev);
	}

	r = hid_exit();
	if (r != 0)
		fprintf(stderr, "Warning: failed to cleanup hid library: %s\n", strerror(errno));

	free(dev_path);

	return 0;
}
