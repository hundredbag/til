# Directory exist check

### Directory exist?

```bash
#!/bin/sh
if [ -d "$DIRECTORY" ]; then
     echo "$DIRECTORY exists."
fi
```



### Directory not exist?

```bash
#!/bin/sh
if [ ! -d "$DIRECTORY" ]; then
    echo "$DIRECTORY doesn't exists." 
fi
```



### Directory is symbolic link?

```bash
#!/bin/sh
if [ -L "$DIRECTORY" ]; then
    echo "$DIRECTORY symbolic link" 
fi
```

