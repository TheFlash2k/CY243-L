# Question - 2

Building upon question-1, I have already added user: `ashfaq` and set it's home directory to `/usr/share/ashfaq`

Write a simple bash script called `q2.sh` that resides in `/opt/` that does the following when invoked:

- Creates a group called `cats`
- Adds `ashfaq` to `cats` and `sudo`
- Creates another user called `bajwa`
- Add `bajwa` to `cats`
- Creates another group called `goats`
- Adds `ashfaq` to `goats`
- Creates a new file called `/opt/posted` and add your roll number (ONLY your roll number in the file.)
- Change the owner of this file to `bajwa` and group to `goats`

> **NOTE**:
All of this has to be done from the bash script, even if you do it manually, it won't work.
Also, you don't need to switch to another user, the `checker` will handle each case automatically