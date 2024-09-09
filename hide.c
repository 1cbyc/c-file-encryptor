#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    while (1) {
        // Add all changes
        system("git add .");

        // Commit the changes with a generic message
        system("git commit -m 'testing out my theory'");

        // Push the changes to the remote repository
        system("git push");

        // Wait for 8 seconds before the next commit
        sleep(8);
    }

    return 0;
}
