#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main() {
    setgid(0);
    setuid(0);

    uid_t real_uid = getuid();
    struct passwd *pw = getpwuid(real_uid);
    if (!pw) {
        fprintf(stderr, "Failed to get username for UID %d\n", real_uid);
        return 1;
    }

    char *username = pw->pw_name;

    execl("/usr/bin/python3", "python3", "/opt/secret/secret_script.py", username, (char *)NULL);

    perror("execl");
    return 1;
}
