#include <unistd.h>
#include <stdio.h>
#include <err.h>

int main(int argc, char **argv) {
	if (argc <= 1) {
		printf("usage: %s <command> [arguments]\n", argv[0]);
		return 1L;
	}
	/*printf("uid: %d\n", getuid());
	printf("euid: %d\n", geteuid());*/

	setuid(0);

	/*printf("uid: %d\n", getuid());
	printf("euid: %d\n", geteuid());*/

	execvp(argv[1], argv+1);
	err(1, "Could not execute \"%s\"", argv[1]);
}
