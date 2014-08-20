TypeTime-old
============

C version of TypeTime.

Bluntly, you probably don't want to use this.  Unless you're averse to .NET or Mono, your best bet is the current [TypeTime](https://github.com/jcolag/TypeTime), written in C# and far more configurable and complete.

_This_ version of the program was my original prototype, issued from a morning shell script that fills in the current date.

It works.  It just lacks more than rudimentary bells and whistles and it's little more than a quick hack.

Usage
-----

Using _TypeTime_ is straightforward, because there are only two configuration options.  To use it directly, run as,

    ./typetime

This will only print results to the standard output.

The full invocation looks like this.

    ./typetime [-f output.csv] [-l length]

The options are:

 - _**`-f`** <`output.csv`>_:  _TypeTime_ prints the summary to the console, rather than the full log entry, and logs the full results to the specified CSV file.  Again, note that _TypeTime_ assumes that the date has been inserted into the file first.

 - _**`-l`** <number>_:  Sets the length of _TypeTime_'s target string.

_TypeTime_ defaults to no log file and a string length of five characters.

Output
------

The session will look something like the following.

First, after a random delay, _TypeTime_ displays the target string.

    kmukt - Repeat!

The user then repeats it.

    kmukt

Finally, assuming the user logs the specifics to a file, the summary report gives a quick idea of how well the user did.

    0 errors, 2 seconds

Errors are tallied based on the [Levenshtein Distance](https://en.wikipedia.org/wiki/Levenshtein_distance).  Time is rounded to the nearest second.

CSV output (to `stdout` if no file is specified, instead of the summary) looks something like the following.

    ,3,5,0,2.674929

These items are:

 - Date, not printed by _TypeTime_.

 - **Delay**:  The time (in seconds) before displaying the target string.

 - **Length**:  The length of the target string.

 - **Errors**:  The number of errors made by the user repeating the string.

 - **Time**:  The duration (in seconds, down to the microsecond) taken by the user in repeating the string.

Note that, if used, [uManage-reports](https://github.com/jcolag/uManage-reports) assumes that the date information is presented as _year_`,`_month_`,`_date_`,`_day of week_.
