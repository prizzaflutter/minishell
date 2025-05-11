#include "minishell.h"

void handle_ctrl_c(int sig)
{
    (void)sig;
    ctrlc_in_hrdoc = 1;
    write(1, "\n", 1);
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
    exit_status(1, 130);
}
