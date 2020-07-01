
files to edit:

libethereum/ExtVM.cpp --> call (definition at line 108) : create a Executive instance and invoke its call function --> go (line 113 -> definition at line 59) --> invoke Executive instance's go function agian.
libethereum/Executive.cpp--> go (definition at line 330) --> "calling VMFactory  create() function to create vm" (at line 340) --> "call vm exec(...) function" (at line 343, the function definition is at line 207 of libevm/LegacyVM.cpp)
libevm/VMFactory.cpp --> create (definition at line 159) --> "create a vm instance for g\_kind, g\_kind is defined at line 21, valued VMKind::Legacy" 
libevm/LegacyVM.h
libevm/LegacyVMOpt.cpp --> initEntry(line 180): which is the entry to a loop structure to execute all operations in 'libevm/LegacyVM.cpp--> exec (line 220)"
libevm/LegacyVM.cpp  --> exec (definition at line 207): execute all operations at line 220 - 223 by a loop structure.

