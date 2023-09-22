# Lab 2 - Bash Scripting and Automation

---

## Instructions

- You are required to complete the provided tasks in the given order.
- You are required to submit a report containing the screenshots of the commands used to complete the tasks as well as the code.
- You are required to submit the report in PDF format.

> You are not required to provide the history file as part of this lab task.

- PDF file must be named as `cy243l-<batch>-<roll-number>.pdf`.
Example:

```text
cy243l-f21-210125.pdf
```

- It is recommended that you utilize [`Notion`](https://notion.so) for writing your report.
- You are required to submit your work before the deadline. Late submissions will lead to marks deduction.

---

## Task 1

Write a bash script that takes a number as an argument and prints whether the number is even or odd. The output should be "True" or "False". Case matters. The file must be inside `/tmp/` directory and named as `even-odd.sh`.

### Task 2

Using a for loop in bash, try and ping the subnet "172.16.0.0/24" and print the IP addresses that are up.
Output should be like:
"172.16.0.0 = UP"

> Hint: Use `ping -c 1 <ip-address>` to ping the IP address once.
> Utilizing the `ip-extract.sh` that you created in your lab, you also are required to *chain* the ping command with the script you created before.

The file must be inside `/tmp/` directory and named as `ping.sh`.

### Task 3

Create a function called `create_user` that takes two arguments: username and password. The function should create a user with the given username and password. Also, write another function called `add_to_group` that takes two arguments: username and groupname. The function should add the user to the given group. The file must be inside `/tmp/` directory and named as `user.sh`. The username, password and groupname should be provided from the command line as arguments to the script.
Example usage would be:

```bash
/tmp/user.sh new_user "my-password" sudo
```

Also, add a check to see if the group exists or not.

---

## Submission

- Deadline: 11:59 PM, 28th September, 2023

---

<h2 style="text-align: center">
    <b>Good Luck!</b>
</h2>