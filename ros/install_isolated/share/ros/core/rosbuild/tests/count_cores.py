#!/usr/bin/env python.exe

import os
print(os.sysconf(os.sysconf_names['SC_NPROCESSORS_ONLN']))
