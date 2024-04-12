# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void	sig_handler(int signal);

void	config_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_SIGINFO;

    // # SIGINT = ctrl + c
	if (sigaction(SIGINT, &sa, NULL) == -1)
		write(1, "Error setting SIGINT handler", 28);
    
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		write(1, "Error setting SIGUSR2 handler", 28);
}

void	sig_handler(int signal)
{
    if (signal == 2)
        printf("signal = %d\n", signal);
    exit (0);

}

int main(void)
{
    config_signal();

    while (1)
        ;
}