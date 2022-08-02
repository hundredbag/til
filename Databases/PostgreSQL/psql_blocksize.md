# PostgreSQL Blocksize

### How to get PostgreSQL block size

```mysql
test=# SELECT current_setting('block_size');
current_setting
-----------------
 8192
```



### How to set PostgreSQL block size

Block size is determined when PostgreSQL is compiled or when it is installed.

(Use `--with-blocksize` option when running the `configure` script.)

* **--with-blocksize=BLOCKSIZE**

  The default, 8 kilobytes, is suitable for most situations; but other values may be useful in special cases. The value must be a power of 2 between 1 and 32 (kilobytes).

<https://www.postgresql.org/docs/current/install-procedure.html>

> PostgreSQL server does not work if DB blocksize and configured blocksize are different