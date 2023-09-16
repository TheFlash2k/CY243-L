# Lab 1 - Introduction to Linux and Bash

---

## Instructions

- You are required to complete the provided tasks in the given order.
- You are required to submit a report containing the screenshots of the commands used to complete the tasks.
- You are required to submit the report in PDF format.
- Before starting your work, you must clean your command history using the following command:

```bash
history -c
```

- Along with the report, you must submit your command history using the following command:

```bash
history > cy243l-<batch>-<roll-number>.txt
## Example:
history > cy243l-f21-210125.txt
```

- PDF and TXT files must be named as `cy243l-<batch>-<roll-number>`.
Example:

```text
cy243l-f21-210125.pdf
```

- The final 2-files must be attached to the assignment submission.

```md
cy243l-<batch>-<roll-number>.pdf
cy243l-<batch>-<roll-number>.txt

## Example
cy243l-f21-210125.pdf
cy243l-f21-210125.txt
```

- It is recommended that you utilize [`Notion`](https://notion.so) for writing your report.
- You are required to submit your work before the deadline. Late submissions will lead to marks deduction.

---

## Task 1 - Creating files and folders

- Inside the `/tmp/` folder, create a new folder called `test <roll-number>` (replace `<roll-number>` with your roll number)
    Example:
        - If your roll number is `123456`, then the folder name should be `test 123456`
        *NOTE*: There is a space between `test` and `123456`

- Inside the `test <roll-number>` folder, create a new file called `test.txt` and write the following text in it:

```text
This is a test file
```

> It is highly encouraged that you use new ways to write contents into a file and even trying to create a file without using the `touch` command.

---

## Task 2 - Creating users and groups

- Create a new user called `kali-auto-user`, set its password to `test123`, and add it to the `sudo` group. Also, ensure that the home directory of this user is `/var/kali-auto-user`

- Create a new group called `kali-auto-group` and add the `kali-auto-user` user to this group.

---

## Task 3 - Installing packages

- Install the `git` package
- Install the `curl` package
- Using curl, download an image from the internet, add it's screenshot in the final report.
- Using git, clone the following repository: [https://github.com/theflash2k/CY243-L.git](https://github.com/theflash2k/CY243-L.git) and list the contents of the cloned repository (including hiddent files)

---

## Task 4 - Permission management

- Rename the `test <roll-number>` folder to `test-<roll-number>`
- Create a new file called `test2.txt` inside the `test <roll-number>` folder and write the following text in it:

```text
This file is created by <your-name>
```

- Change the owner of the `test-<roll-number>` folder to `kali-auto-user` and also the file (Hint: `-R`)
- Change the group of the file `test2.txt` to `kali-auto-group`
- Change the permissions as the following:

    **Owner: Read, Write, Execute**
  
    **Group: Read, Execute**
  
    **Others: None**
  
    > In the report, add both the numbers for this permission as well as the character-set for this permission.
- Try reading the file `test2.txt` using the `cat` command as the current user. Can you read it? If not, answer in report; why?
- Login as `kali-auto-user` and check if its part of the group
- Try reading the file `test2.txt` using the `cat` command as the `kali-auto-user`. Can you read it? If not, answer in report; why?, If yes, add the screenshot in the report and explain why.

<h2 style="text-align: center">
    <b>Good Luck!</b>
</h2>

---
