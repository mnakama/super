#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <sys/prctl.h>
#include <sys/capability.h>

// These are defined in the kernel, but not in /usr/include/linux/prctl.h
#define PR_CAP_AMBIENT 47
#define PR_CAP_AMBIENT_IS_SET 1
#define PR_CAP_AMBIENT_RAISE 2
#define PR_CAP_AMBIENT_LOWER 3
#define PR_CAP_AMBIENT_CLEAR_ALL 4

int main(int argc, char **argv) {
	int ret = 0;
	cap_t cap;
	cap_flag_value_t val = 0;
	cap_value_t dac = CAP_DAC_OVERRIDE;

	if (argc <= 1) {
		printf("usage: %s <command> [arguments]\n", argv[0]);
		return 1L;
	}

	cap = cap_get_proc();
	if (cap == NULL) err(1, "Could not get current thread capabilities");

	//printf("cap: %x\n", cap);

	/*printf("permitted\n");
	if (cap_get_flag(cap, CAP_DAC_OVERRIDE, CAP_PERMITTED, &val) == -1)
		err(1, "Could not query CAP_DAC_OVERRIDE");
	printf("CAP_DAC_OVERRIDE: %d\n", val);

	printf("\ninherit\n");
	if (cap_get_flag(cap, CAP_DAC_OVERRIDE, CAP_INHERITABLE, &val) == -1)
		err(1, "Could not query CAP_DAC_OVERRIDE");
	printf("CAP_DAC_OVERRIDE: %d\n", val);*/

	if (cap_set_flag(cap, CAP_INHERITABLE, 1, &dac, 1) == -1)
		err(1, "Could not set CAP_DAC_OVERRIDE flag");

	/*if (cap_get_flag(cap, CAP_DAC_OVERRIDE, CAP_INHERITABLE, &val) == -1)
		err(1, "Could not query CAP_DAC_OVERRIDE");
	printf("CAP_DAC_OVERRIDE: %d\n", val);


	printf("\neffective\n");
	if (cap_get_flag(cap, CAP_DAC_OVERRIDE, CAP_EFFECTIVE, &val) == -1)
		err(1, "Could not query CAP_DAC_OVERRIDE");
	printf("CAP_DAC_OVERRIDE: %d\n", val);

	// make sure secure bits aren't set
	ret = prctl(PR_GET_SECUREBITS, 0, 0, 0, 0);
	printf("\nsecurebits: %d\n", ret);
	if (ret < 0) err(1, "Could not get secbits");*/

	if (cap_set_proc(cap) == -1) err(1, "Could not set thread permissions");

	ret = prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_RAISE, CAP_DAC_OVERRIDE, 0, 0);
	if (ret < 0) err(1, "Could not raise ambient permission set");

	execvp(argv[1], argv+1);
	err(1, "Could not execute \"%s\"", argv[1]);
}
