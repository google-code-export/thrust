# Introduction #

This page lists some instructions on how to build & run Thrust's tests.  The testers have
been built & tested on Windows, Ubuntu, and Mac OS X, but these instructions assume a Debian-based OS like Ubuntu.

# Prerequisites #

Thrust's build process depends on [Scons](http://www.scons.org).  If you are on a
Debian-based OS, you can install Scons with

`$ sudo apt-get install scons`

The testing infrastructure isn't included in the zip file on the
website, so you'll need to checkout the source tree from the
repository with [Mercurial](http://mercurial.selenic.com).  If you are on a Debian-based OS, you can install Mercurial with

`$ sudo apt-get install mercurial`

To checkout the current development version of Thrust use

`$ hg clone http://thrust.googlecode.com/hg thrust`

# Unit Tests #

You can build the unit tester simply by changing to the testing
directory and running scons:

`$ cd thrust/testing`

`$ scons`

To run all tests,

`$ ./tester`

You can also specify a list of tests to run by name as arguments to tester.  The test driver also provides a verbose mode which prints additional information:

`$ ./tester --verbose`

The list of available options is printed with the help option

```
$ ./tester --help
Example Usage:
  ./tester
  ./tester TestName1 [TestName2 ...] 
  ./tester PartialTestName1* [PartialTestName2* ...] 
  ./tester --device=1
  ./tester --sizes={tiny,small,medium,default,large,huge,epic,max}
  ./tester --verbose or --concise
  ./tester --list
  ./tester --help

Options:
  The sizes option determines which input sizes are tested.
    --sizes=tiny    tests sizes up to 32
    --sizes=small   tests sizes up to 256
    --sizes=medium  tests sizes up to 4096
    --sizes=default tests sizes up to 65536
    --sizes=large   tests sizes up to 1048576 (0.25 GB memory)
    --sizes=huge    tests sizes up to 16777216 (1.50 GB memory)
    --sizes=epic    tests sizes up to 67108864 (3.00 GB memory)
    --sizes=max     tests all available sizes
```

A custom subset of the unit tests can be run with the following steps.
```
#Save all test names to a file
$ ./tester --list > list.txt

#Edit the test list to suit
$ gvim list.txt

#Run test driver with specified list
$ ./tester --verbose  `tr '\n' ' ' < list.txt`
```

# Performance Tests #

To build the performance tests, change to the performance directory:

$ cd ../performance

To build all the performance test programs, simply run scons:

`$ scons`

You can also get a usage message from this build with

`$ scons -h`

You can run a performance test for any of the files in this directory
suffixed with ".test".  To run a performance test and output a report,
run scons with the test base name suffixed with ".xml".  For example,
to output radix\_sort's report, run:

`$ scons radix_sort.xml`

You can also output graphs of some of our performance tests.  To
create graphs for all .xml files in this directory, run the report.py
script:

`$ python report.py`

This will output .png files for any existing .xml files in this
directory that the report script recognizes.  The report script requires the [SciPy](http://www.scipy.org/) and [matplotlib](http://matplotlib.sourceforge.net/) Python libraries.  You install these packages with apt-get or a super package like [EPD](http://www.enthought.com/products/getepd.php) or the [MacOSX SuperPack](http://macinscience.org/?page_id=6).