# This file is configured by CMake automatically as DartConfiguration.tcl
# If you choose not to use CMake, this file may be hand configured, by
# filling in the required variables.


# Configuration directories and files
SourceDirectory: C:/workspace/libs/vxl-1.14.0
BuildDirectory: C:/workspace/libs/vxl-1.14.0/build

# Where to place the cost data store
CostDataFile: 

# Site is something like machine.domain, i.e. pragmatic.crd
Site: ANALYSEVIDÉO

# Build name is osname-revision-compiler, i.e. Linux-2.4.2-2smp-c++
BuildName: Win32-mingw32-make

# Submission information
IsCDash: TRUE
CDashVersion: 
QueryCDashVersion: 
DropSite: www.cdash.org
DropLocation: /CDash/submit.php?project=vxl
DropSiteUser: 
DropSitePassword: 
DropSiteMode: 
DropMethod: http
TriggerSite: 
ScpCommand: SCPCOMMAND-NOTFOUND

# Dashboard start time
NightlyStartTime: 22:00:00 EST

# Commands for the build/test/submit cycle
ConfigureCommand: "C:/Program Files (x86)/CMake/bin/cmake.exe" "C:/workspace/libs/vxl-1.14.0"
MakeCommand: C:/Program\ Files\ (x86)/CMake/bin/cmake.exe --build . --config "${CTEST_CONFIGURATION_TYPE}" -- -i
DefaultCTestConfigurationType: Release

# version control
UpdateVersionOnly: 

# CVS options
# Default is "-d -P -A"
CVSCommand: CVSCOMMAND-NOTFOUND
CVSUpdateOptions: -d -A -P

# Subversion options
SVNCommand: SVNCOMMAND-NOTFOUND
SVNOptions: 
SVNUpdateOptions: 

# Git options
GITCommand: GITCOMMAND-NOTFOUND
GITUpdateOptions: 
GITUpdateCustom: 

# Perforce options
P4Command: P4COMMAND-NOTFOUND
P4Client: 
P4Options: 
P4UpdateOptions: 
P4UpdateCustom: 

# Generic update command
UpdateCommand: 
UpdateOptions: 
UpdateType: 

# Compiler info
Compiler: C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/bin/g++.exe

# Dynamic analysis (MemCheck)
PurifyCommand: 
ValgrindCommand: 
ValgrindCommandOptions: 
MemoryCheckType: 
MemoryCheckSanitizerOptions: 
MemoryCheckCommand: MEMORYCHECK_COMMAND-NOTFOUND
MemoryCheckCommandOptions: 
MemoryCheckSuppressionFile: 

# Coverage
CoverageCommand: C:/mingw-w64/x86_64-4.9.2-posix-seh-rt_v3-rev1/mingw64/bin/gcov.exe
CoverageExtraFlags: -l

# Cluster commands
SlurmBatchCommand: SLURM_SBATCH_COMMAND-NOTFOUND
SlurmRunCommand: SLURM_SRUN_COMMAND-NOTFOUND

# Testing options
# TimeOut is the amount of time in seconds to wait for processes
# to complete during testing.  After TimeOut seconds, the
# process will be summarily terminated.
# Currently set to 25 minutes
TimeOut: 1500

UseLaunchers: 
CurlOptions: 
# warning, if you add new options here that have to do with submit,
# you have to update cmCTestSubmitCommand.cxx

# For CTest submissions that timeout, these options
# specify behavior for retrying the submission
CTestSubmitRetryDelay: 5
CTestSubmitRetryCount: 3
