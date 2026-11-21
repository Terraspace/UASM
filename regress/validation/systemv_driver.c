/* Optional Linux runtime driver for the self-checking System V fixtures.
 * Link one fixture at a time. The normal Go suite only assembles/compares.
 */
#include <stdio.h>
extern long long run_tests(void);
int main(void)
{
    long long result = run_tests();
    if (result != 0)
        fprintf(stderr, "System V ABI assertion failed: %lld\n", result);
    return result != 0;
}
