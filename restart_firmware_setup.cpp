#include <cstdlib>

int main() {
    // Execute the command to restart and enter firmware setup
    system("shutdown /r /fw /t 0");

    return 0;
}

/*

The `shutdown` command with the parameters `/r /fw /t 0` is used to restart the computer and enter the firmware setup (UEFI/BIOS).

- `/r`: Instructs the system to restart.
- `/fw`: Initiates a restart and enters the firmware setup (UEFI/BIOS) on the next boot.
- `/t 0`: Sets the time delay before restarting to 0 seconds. The restart will happen immediately.

So, the command `shutdown /r /fw /t 0` will restart the computer and, on the next boot, enter the firmware setup without any delay.

*/