# Building the application under Windows by using mingw. Make sure
# you have installed and configured mingw to your PATH.
#
# By using the powershell script make sure to enable to run
# powershell scripts on your system.
#
# author:		ITWorks4U
# created:		July 17th, 2025

param (
	[string]$Action = ""
)

# variables for the script itself
$compiler = "gcc.exe"
$flags = "-g3 -Wall -Iinclude"
$source = "source\\n_queen_problem.c source\\main.c"
$target = "n_queen_problem.exe"

function print_help {
	$script_name = $MyInvocation.MyCommand.Name
	$summary = @"
	Usage: .\$script_name [build | clean]

	commands:
	build <=> compile the application
	clean <=> remove the compiled exceutable, if existing
"@

	Write-Host $summary
}

function building_app {
	Write-Host "start to build the application..."
	$command = "$compiler $flags $source -o $target"
	Write-Host "running command: $command"
	Invoke-Expression $command

	if ($LASTEXITCODE -eq 0) {
		Write-Host "application has been built."
	} else {
		Write-Host "building failed..."
	}
}

function clean_up {
	Write-Host "clean up the mess..."
	if (Test-Path ".\$target") {
		Remove-Item ".\$target"
	} else {
		Write-Host "nothing to clean up..."
	}
}

switch ($Action.ToLower()) {
	"build" { building_app }
	"clean" { clean_up }
	default { print_help }
}