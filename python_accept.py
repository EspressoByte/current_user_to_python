import sys

if len(sys.argv) < 2:
    print("No username passed!")
    sys.exit(1)

username = sys.argv[1]
print(f"Running secret script as: {username}")
