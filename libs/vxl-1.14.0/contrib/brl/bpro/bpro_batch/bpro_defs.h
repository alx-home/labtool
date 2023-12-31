#ifndef BPRO_DEFS_H
#define BPRO_DEFS_H

#define py_funcs(name,process,arg,doc) {name,process,arg,doc}

py_funcs("init_process",init_process,METH_VARARGS,"init_process(s) create a new process instance by name"),
py_funcs("process_print_default_params",process_print_default_params,METH_VARARGS,"process_print_default_params(s,s) print the default values of the process by name"),
py_funcs("set_params_process",set_params_process,METH_VARARGS,"set_params_process(s) set the parameter values of the current process from the XML file"),
py_funcs("set_input_bool",set_input_bool,METH_VARARGS,"set_input_(i,b) set input i on current process to a bool value"),
py_funcs("set_input_string",set_input_string,METH_VARARGS,"set_input_(i,s) set input i on current process to a string value"),
py_funcs("set_input_int",set_input_int,METH_VARARGS,"set_input_(i,i) set input i on current process to an int value"),
py_funcs("set_input_unsigned",set_input_unsigned,METH_VARARGS,"set_input_(i,i) set input i on current process to an unsigned value"),
py_funcs("set_input_long",set_input_long,METH_VARARGS,"set_input_(i,l) set input i on current process to a long value"),
py_funcs("set_input_float",set_input_float,METH_VARARGS,"set_input_(i,f) set input i on current process to a float value"),
py_funcs("set_input_double",set_input_double,METH_VARARGS,"set_input_(i,d) set input i on current process to a double value"),
py_funcs("get_input_float",get_input_float,METH_VARARGS,"get_input_(i) return value of output i in the database"),
py_funcs("get_input_unsigned",get_input_unsigned,METH_VARARGS,"get_input_(i) return value of output i in the database"),
py_funcs("process_init",process_init,METH_VARARGS,"process_init() initialize the current process state before execution"),
py_funcs("run_process",run_process,METH_VARARGS,"run_process() run the current process"),
py_funcs("commit_output",commit_output,METH_VARARGS,"commit_output(i) put output i in the database"),
py_funcs("set_input_from_db",set_input_from_db,METH_VARARGS,"set_input_from_db(i, i) set input i of the current process to db id value"),
py_funcs("remove_data",remove_data,METH_VARARGS,"remove_data(i) remove data with id from db"),
py_funcs("remove_data_obj",remove_data_obj,METH_VARARGS,"remove_data_obj(i) remove data with obj.id from db"),
py_funcs("print_db",print_db,METH_VARARGS,"print_db() print the database"),
py_funcs("clear",clear,METH_VARARGS,"clear() clear the database tables"),

#undef py_funcs

#endif
