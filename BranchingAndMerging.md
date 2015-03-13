These instructions were adapted from [here](http://blog.red-bean.com/sussman/?p=92).

## Step 1 ##

Make a branch for your experimental work:

```
$ svn copy https://thrust.googlecode.com/svn/trunk/  https://thrust.googlecode.com/svn/branches/YOUR_BRANCH_NAME
$ svn switch https://thrust.googlecode.com/svn/branches/YOUR_BRANCH_NAME
```

## Step 2 ##

Work on the branch for a while:

```
# ...edit files
$ svn commit
# ...edit files
$ svn commit
```

## Step 3 ##

Sync your branch with the trunk, so your branch doesn’t fall behind:

```
$ svn merge https://thrust.googlecode.com/svn/trunk/
--- Merging r3452 through r3580 into '.':
U button.c
U integer.c
...
$ svn commit
```

## Step 4 ##

Repeat the prior two steps until you’re done coding.

## Step 5 ##

Merge your branch back into the trunk:

```
$ svn switch https://thrust.googlecode.com/svn/trunk/
$ svn merge --reintegrate https://thrust.googlecode.com/svn/branches/YOUR_BRANCH_NAME
--- Merging differences between repository URLs into '.':
U button.c
U integer.c
...

$ svn commit
```

**Note**: once a `–reintegrate merge` is done from branch to trunk, the branch is no longer usable for further work. It’s not able to correctly absorb new trunk changes, nor can it be properly reintegrated to trunk again. Therefore, the branch should be deleted after a `-reintegrate merge` is performed. [further detail](http://blogs.open.collab.net/svn/2008/07/subversion-merg.html)