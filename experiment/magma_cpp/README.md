# Magma is main. Link C++ generator

In this test, magma is going to predeclare the interfaces for the Generators which it will use.
This means that compiling magma will *not* call out to the external c++ generator. Rather, this will be a separate link-time step.
