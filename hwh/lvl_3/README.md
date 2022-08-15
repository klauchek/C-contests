# Hashtable (Quads task)
## Task: 
<p> Find four strings a, b, c, d, such that a+b == c+d where concatenation is used as an addition (for example: "aabde" + "acb" == "aab" + "edacb") </p>

#
### *Input*:
stings' buffer size <br>
strings devided with `\n`
### *Output*:
number of quads

<br>

### *Example*:
#### 4
#### aabde
#### acb
#### aab
#### deacb

#
## To run this project
1. clone this repo using command
```
  $ git clone git@github.com:klauchek/C-contests.git
```
2. cd to the `hwh/lvl_3` and build project using command
```
  $ make
```
#### **NOTE**: *if you want to print all found quads, build using* 
```
  $ make CFLAGS+=-DPRINT_QUADS -f Makefile
```

3. run program
```
  $ ./hwh_lvl_3
```