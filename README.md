# NanoTekSpice
Digital Electronics  

./nanotekspice circuit_file.nts input_name=input_value
-------------------------------------------------------

NanoTekSpice is a logic simulator that builds a graph (the nodes of which will be simulated digital electronic
components, inputs or outputs) from a configuration file, and injects values into that graph to get results.  

The Configuration File :
------------------------

The first part starting with the “.chipsets:” statement is used to declare
and name components that will be used by the program.
Some components may need to be initialized with a value, which is provided after the name, between
parenthesis.  

The second part starting with the “.links:” statement is used to declare links between components.
Each link indicates which pin of which component are linked.  


The Components :
----------------

| Components | Description        |
| ---------: | -------------------|
| **C4001**  | Four NOR gates     |
| **C4008**  | 4 bits adder       |
| **C4011**  | Four NAND gates    |
| **C4013**  | DualFlipFlop       |
| **C4030**  | Four XOR gates     |
| **C4040**  | 12 bits counter    |
| **C4069**  | Six Inverter gates |
| **C4081**  | Four AND gates     |
| **C4071**  | Four OR gates      |


The Special Components :
------------------------

| Special Components | Description                                                                                      |
| -----------------: | ------------------------------------------------------------------------------------------------ |
| **input**          | a component with a single pin directly linked to the command line. This value must be 0 or 1     |
| **output**         | a component with a single pin that writes its state to the standard output after each simulation |
| **clock**          | a component that works like an input except its value is inverted after each simulation          |
| **true**           | a component with a single pin that is always TRUE                                                |
| **false**          | a component with a single pin that is always FALSE                                               |


Execution :
-----------

	• exit : closes the program.
	• display : prints the value of all outputs the standard output, sorted by name in ASCII order.
	• input=value : changes the value of an input. This does not apply to clocks.
	• simulate: runs the simulation.
	• loop : continuously runs the simulation without displaying a prompt, until SIGINT is received.
	• dump : calls the dump method of every component.


Creation of a new IComponent :
------------------------------

You must write a member function of a class relevant to your system
that will let you create new components in a generic manner.
This function must have the following prototype:

	• std:: unique_ptr <IComponent > createComponent(const  std:: string &name)