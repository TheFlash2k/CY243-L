## Question-6:

Building upon question-5, write a bash script called `looper.sh` that resides in `/usr/share` that does the following:

- Reads in 2 numbers from the command line arguments:
    - Loop Start
    - Loop End
- Checks for even and odd and print out all the numbers in the following format:

```bash
12:even
17:odd
19:odd
18:even
```

- Store the output to `/opt/data.log`

> NOTE: Loop End is not inclusive i.e. if loop start is 10 and loop end is 14, then the numbers will be 10,11,12 and 13.