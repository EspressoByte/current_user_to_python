# Gatekeeper: Secure Python Script Wrapper

This repository contains two files:

- `gatekeeper.c`: A secure C wrapper that runs as a set-UID binary.
- `secret_script.py`: A Python script that is executed securely through the wrapper.

The goal is to allow standard Linux users to execute a protected Python script **without being able to read or modify its contents**, while still identifying who invoked the script.

---

## How It Works

### 1. `gatekeeper.c`
- When compiled and installed with `set-UID`, this C program runs with `root` privileges.
- It captures the actual username of the person who executed it using `getuid()` and `getpwuid()`.
- It then calls the protected Python script (`secret_script.py`), passing the username as an argument.
- The user never sees or has read access to the Python script.

### 2. `secret_script.py`
- A normal Python script that expects the invoking user's name as its first argument.
- It can log, display, or use the username in any custom logic.
- It should reside in a root-owned, restricted path like `/opt/secret/` with permissions set to `700`.

---

## Setup Instructions

### Compile the C Wrapper
```bash
gcc -o gatekeeper gatekeeper.c
sudo chown root:root gatekeeper
sudo chmod 4755 gatekeeper
sudo mv gatekeeper /usr/local/bin/
```

### Secure the Python Script
```bash
sudo mkdir -p /opt/secret
sudo mv secret_script.py /opt/secret/
sudo chown root:root /opt/secret/secret_script.py
sudo chmod 700 /opt/secret/secret_script.py
```

### Test It
```bash
gatekeeper
```

This will execute the Python script and pass in the current username as the first argument.

---

## Example Python Script Output
```bash
Welcome, Admin! Running protected logic now...
```

---

## Security Notes
- The Python script is unreadable by normal users.
- The C wrapper executes it with root privileges.
- The user identity is securely captured and passed to the script.

For extra security:
- Log activity inside the Python script.
- Audit access using `/var/log` or syslog.

---

## License
This code is released into the public domain. You may use, modify, distribute, and sell it freely without restriction or attribution.
