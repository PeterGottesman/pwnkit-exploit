## pwnkit (CVE-2021-4034) Privilege Escalation exploit sample

This repository contains an exploit of CVE-2021-4034, a local
privilege escalation in `pkexec`. This implementation is based on that
described in the [CVE
disclosure](https://marc.info/?l=oss-security&m=164313339424946&w=2), which you should read.

If this works on your machine, it means you are vulnerable. To address
this, either update polkit to a patched version, or disable the `setuid`
bit on `pkexec` with the following:

```
$ sudo chmod a-s $(which pkexec)
```

This exploit is dangerously easy to write based on the information in
the disclosure, so patch all of your machines ASAP.

### Using this repo 

To run this exploit, simply run `make` in the top level
directory. This will:
- compile `exploit.c`, which runs the exploit
- compile `gconv/badconv.c`, which contains the payload
- Run `./exploit`

If this drops you into a shell as root, your system is vulnerable. 

If you get the following output, you succesfully mitigated the bug
using the above `chmod` command:

```
Running exploit...
GLib: Cannot convert message: Could not open converter from “UTF-8” to “ZT”
pkexec must be setuid root
```

If you get the `pkexec` help message as the output, your system was
likely already patched.

This implementation _should_ work on any vulnerable systems, including
Fedora 34+ and some versions of OpenSUSE which seem to not be
vulnerable to some implementations. Specifically, this will work even
if your system has a version of polkit which disables GVFS ([added
here](https://gitlab.freedesktop.org/polkit/polkit/-/commit/daf3d5c2d15466a267221fcb099c59c870098e03)). That
being said, I have no formal experience with computer security and it
may report that your system is patched, even if it is still vulnerable
to this or other similar exploits. As such, you should make sure that
you keep your systems updated, listen to the people who know what they
are talking about, and always eat your vegetables.
