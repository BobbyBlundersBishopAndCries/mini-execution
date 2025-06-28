#include "exec.h"


int main(int argc, char **argv)
{
    (void)argc;  // Unused parameter
    (void)argv;  // Unused parameter

    // Call your ft_env function with the environment variables
    int ret = ft_pwd();

    return ret;
}