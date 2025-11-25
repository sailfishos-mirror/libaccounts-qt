Accounts management library for Qt applications
=================================================

This project is a library for managing accounts which can be used from Qt
applications. It is part of the @accounts-sso project.


License
-------

SPDX-License-Identifier: LGPL-2.1-only

See COPYING file.


Build instructions
------------------

The project depends on [libaccounts-glib](https://gitlab.com/accounts-sso/libaccounts-glib).
It can build against either Qt 5 or Qt 6.

To build it, run:
```
qmake  # Or qmake-qt5 or qmake-qt6, depending on the distro
make
make install
```

Resources
---------

[API reference documentation](http://accounts-sso.gitlab.io/libaccounts-qt/)

[Official source code repository](https://gitlab.com/accounts-sso/libaccounts-qt)
