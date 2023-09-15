# Lab Task - 1

---

## Instructions

- You are required to complete the following tasks in the given order.
- You are required to submit a report containing the screenshots of the commands used to complete the tasks.
- You are required to submit the report in PDF format.
- Before starting your work, you must clean your command history using the following command:

```bash
history -c
```

- Along with the report, you must submit your command history using the following command:

```bash
history > <roll-number>.txt
```

- PDF and TXT files must be named as `cy204l-<batch>-<roll-number>`.
Example:

```text
cy204l-f21-210125.pdf
```

- It is recommended that you utilize [`Notion`](https://notion.so) for writing your report.
- You are required to submit your work before the deadline.

---

## Creating files and folders

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

## Creating users and groups

- Create a new user called `kali-auto-user`, set its password to `test123`, and add it to the `sudo` group. Also, ensure that the home directory of this user is `/var/kali-auto-user`

- Create a new group called `kali-auto-group` and add the `kali-auto-user` user to this group.

---

## Installing packages

- Install the `git` package
- Install the `curl` package

- Using curl, download an image from the internet, add it's screenshot in the final report.
- Using git, clone the following repository:
    [https://github.com/theflash2k/CY243-L.git](https://github.com/theflash2k/CY243-L.git)

---

<p text-align="center">
    <b>Good Luck!</b>
</p>
