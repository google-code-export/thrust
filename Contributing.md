Here's an incomplete list of the ways you can help make Thrust better.

# Bug Reports #

# Feedback #

# Feature Requests #

# Documentation #

We strive to make Thrust's [Documentation](Documentation.md) as accurate and informative as possible.  However, if you find the documentation incomplete or misleading in a certain area, please let us know.  Either report an [issue](http://code.google.com/p/thrust/issues/list) or send a message to [thrust-users](http://groups.google.com/group/thrust-users).

# Source Code #

Last, but not least, you can contribute source code to Thrust.  Some ideas you might consider are listed in our [Roadmap](Roadmap.md), but feel free to suggest others.  In either case, please let us know your intentions by posting to [thrust-users](http://groups.google.com/group/thrust-users) so we can determine a plan of action.

## Developing with Mercurial ##

Begin by [creating a personal "clone" of the Thrust repository](http://code.google.com/p/thrust/source/createClone).  This creates a copy of the mainstream Thrust repository but hosts it under a different name. The clone will serve as an external repository to host changes before they are ready to be integrated back into the mainstream Thrust repository.

You can clone your clone to your development machine like so:

```
$ hg clone https://developername-clonename.googlecode.com/hg thrust-clonename
```

Develop in your local clone:

```
$ cd thrust-clonename
<<<hack hack hack>>>
```

Commit changes locally, and push them back to your personal repository:

```
$ hg commit -u <developername>
$ hg push
```

Periodically integrate changes from the mainstream Thrust repository to ensure your clone doesn't fall too far out of sync:

```
$ hg pull https://thrust.googlecode.com/hg
$ hg up
$ hg push
```

When you are ready to propose your change, request a code review by sending a message to thrust-users.

Finally, a developer with commit access to the mainstream Thrust repository will commit your changes:

```
$ hg clone https://thrust.googlecode.com/hg thrust-merge-contribution
$ cd thrust-merge-contribution
$ hg pull https://developername-clonename.googlecode.com/hg
$ hg up
$ hg commit -u <committername>
$ hg push
```