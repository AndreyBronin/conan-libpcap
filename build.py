"""This script build Conan.io package to multiple platforms."""
import platform
from copy import copy
from conan.packager import ConanMultiPackager


if __name__ == "__main__":
    builder = ConanMultiPackager()
    builder.add_common_builds(shared_option_name="libpcap:shared", pure_c=True)
    for settings, options, env_vars, build_requires, reference in reversed(builder.items):
        if platform.system() == "Linux":
            false_options = copy(options)
            false_options["libpcap:enable_usb"] = True
            false_options["libpcap:enable_bluetooth"] = True
            false_options["libpcap:enable_dbus"] = True
            false_options["libpcap:enable_packet_ring"] = True
            builder.builds.append([settings, false_options, env_vars, build_requires, reference])
    builder.run()
