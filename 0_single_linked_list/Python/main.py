#	linked list example by using python
#
#	author:		ITWorks4U
#	created:	July 14th, 2025
#

from signal import signal, SIGINT, SIGTERM

from linked_list import LinkedList
from signal_handling import handle_signal

END_OF_INPUT = "q"
INVALID_ID_USAGE = "ERROR: Your input did not match trough the regular expression filter ([0-9]+ only)"

def main() -> None:
	#	handling signals, like SIGINT, SIGTERM
	signal(SIGINT, handle_signal)
	signal(SIGTERM, handle_signal)

	linked_list = LinkedList()
	print(f"Enter {END_OF_INPUT} to stop adding elements into the list...")

	while True:
		content = input()
		linked_list.add_to_list(content)

		if content == END_OF_INPUT:
			break
		#end if
	#end while

	#	print the full list
	linked_list.print_separator("printing the full list")
	linked_list.print_list()

	#	looking for ID
	linked_list.print_separator("looking for ID")
	id_input = input(f"Enter ID to look for: ")

	if not linked_list.on_valid_input(id_input):
		print(INVALID_ID_USAGE)
	else:
		id_input = int(id_input)

		if not linked_list.on_existing_node(id_input):
			print(f"ERROR: ID ({id_input}) was not found")
		else:
			print(f"({id_input}) {linked_list.get_node_content(id_input)}")
		#end if
	#end if

	#	removing ID from list
	linked_list.print_separator("removing ID from list")
	id_input = input(f"Enter ID to remove from list: ")

	if not linked_list.on_valid_input(id_input):
		print(INVALID_ID_USAGE)
	else:
		id_input = int(id_input)

		if not linked_list.on_existing_node(id_input):
			print(f"ERROR: ID ({id_input}) was not found")
		else:
			linked_list.remove_from_list(id_input)
		#end if
	#end if

	#	reversing list
	linked_list.print_separator("reversing list")
	linked_list.reverse_list()
	linked_list.print_list()

	#	clean up the mess
	linked_list.print_separator("clean up")
	linked_list.clean_up()
#end main

if __name__ == '__main__':
	main()
#end entry point