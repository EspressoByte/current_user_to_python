#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main() {
    uid_t real_uid = getuid();  // 1. Capture real user ID BEFORE elevation

    setgid(0);  // 2. Then elevate
    setuid(0);

    struct passwd *pw = getpwuid(real_uid);
    if (!pw) {
        fprintf(stderr, "Failed to get username for UID %d\n", real_uid);
        return 1;
    }

    char *username = pw->pw_name;

    // 3. Call your protected script
    execl("/usr/bin/python3", "python3", "/opt/secret/secret_script.py", username, (char *)NULL);

    perror("execl");
    return 1;
}
