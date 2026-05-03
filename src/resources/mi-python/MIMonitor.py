# SPDX-FileCopyrightText: 2026 Ernie Pasveer <epasveer@att.net>
#
# SPDX-License-Identifier: MIT

import re

#
# Python MI command to support gdb's "start" commands.
#

class MIMonitor(gdb.MICommand):
    """
    Send a command to gdb's monitor.

    -monitor-exec            Rin a command in gdb's monitor.

    See:
        https://sourceware.org/gdb/current/onlinedocs/gdb.html/Server.html
    """

    def __init__(self, name, mode):
        self._mode = mode
        super(MIMonitor, self).__init__(name)

    def invoke(self, argv):
        if self._mode == "exec":
            gdb.execute ("monitor " + " ".join(argv), to_string=True)
            return None
        else:
            raise gdb.GdbError("monitor: Invalid parameter: %s" % self._mode)

MIMonitor("-monitor-exec", "exec")

