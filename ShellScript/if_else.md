# if and else

Note: Each end of square brackets must be blank.

```bash
#!/bin/bash

if [ condition1 ]; then
	echo "condition 1"
elif [ condition2 ]; then
	echo "condition 2"
else
	echo "else"
fi
```



There are many different ways that an conditional statement can be used. These are summarized here:

| String Comparison | Description                               |
| ----------------- | ----------------------------------------- |
| Str1 = Str2       | Returns true if the strings are equal     |
| Str1 != Str2      | Returns true if the strings are not equal |
| -n Str1           | Returns true if the string is not null    |
| -z Str1           | Returns true if the string is null        |

| Numeric Comparison | Description                                             |
| ------------------ | ------------------------------------------------------- |
| expr1 -eq expr2    | Returns true if the expressions are equal               |
| expr1 -ne expr2    | Returns true if the expressions are not equal           |
| expr1 -gt expr2    | Returns true if expr1 is greater than expr2             |
| expr1 -ge expr2    | Returns true if expr1 is greater than or equal to expr2 |
| expr1 -lt expr2    | Returns true if expr1 is less than expr2                |
| expr1 -le expr2    | Returns true if expr1 is less than or equal to expr2    |
| ! expr1            | Negates the result of the expression                    |

| File Conditionals | Description            |
| ----------------- | ------------------------------------------------- |
| -d file           | True if the file is a directory                              |
| -e file           | True if the file exists (note that this is not particularly portable, thus -f is generally used) |
| -f file           | True if the provided string is a file                        |
| -g file           | True if the group id is set on a file                        |
| -r file           | True if the file is readable                                 |
| -s file           | True if the file has a non-zero size                         |
| -u                | True if the user id is set on a file                         |
| -w                | True if the file is writable                                 |
| -x                | True if the file is an executable                            |