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

    // # SIGINT = ctrl + c (int 2)
    // # displays a new prompt on a new line
	if (sigaction(SIGINT, &sa, NULL) == -1)
		write(1, "Error setting SIGINT handler", 28);
    
    // # SIGQUIT = ctrl + '\' (int 3)
    // # should do nothing
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		write(1, "Error setting SIGQUIT handler", 28);
}

void	sig_handler(int signal)
{
    if (signal == 2)
        printf("signal = %d\n", signal);
    else if (signal == 3)
        printf("signal = %d\n", signal);
    exit (0);
}

// # ctrl + d sends an EOF (End-Of-File) marker to the process reading from the terminal
// # if (readline == NULL) exit the shell and free everything

int main(void)
{
    config_signal();

    while (1)
        ;
}