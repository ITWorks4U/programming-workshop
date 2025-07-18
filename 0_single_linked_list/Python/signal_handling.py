#	Handling common incoming signals in python and terminate the application.
#
#	author:		ITWorks4U
#	created:	July 14th, 2025
#

import sys
from signal import Signals

def handle_signal(signal, frame) -> None:
	summary = f"""
incoming signal: {signal}
type: {Signals(signal)}
located: {frame}

The application is going to terminate..."""

	print(summary)
	sys.exit(0)
#end function