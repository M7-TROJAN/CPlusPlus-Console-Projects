#include <cstdlib>

int main() {
    // Execute the command to restart and enter the boot menu
    system("shutdown /r /o /t 0");

    return 0;
}

/*

The `shutdown` command with the parameters `/r /o /t 0` is used to restart the computer and enter the boot menu.

- `/r`: Instructs the system to restart.
- `/o`: Initiates a restart and opens the advanced startup options menu, which includes the boot menu.
- `/t 0`: Sets the time delay before restarting to 0 seconds. The restart will happen immediately.

So, the command `shutdown /r /o /t 0` will restart the computer and, on the next boot, open the advanced startup options menu, allowing you to access the boot menu.

*/
