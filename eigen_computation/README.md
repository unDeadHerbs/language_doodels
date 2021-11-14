Turtles of Computations
=======================

This is a continuation of some thoughts I've been working on related
to processor architecture.

In an abstract computer science sense, how do different language
features effect the abstractions built upon them?  For some features
in small cases this is easy to say; if, for example, a language is
garbage collected then any language built inside of it must rely on
the garbage collector to properly manage it's memory.  This isn't
explicitly true as via making a block structure of memory blobs and
emulating into those a level of control can be recaptured, but, in
essence, one can not regain that control.  But, with a language
feature like lazy evaluation, it is much harder to observe the
effects. And, in both cases, it is hard to understand the effects
after several layers of abstraction.

To Observe the side effects of different language features I will be
working in both Lisp and Brain-Fuck as small, easily extensible
languages.  The method of analyses I will be using is to have stacks
of interpreters written in each language to either parse its self of
the other.  This is to simulate computation, rather than as
computation on machinery, as an infinite stack of interpreters that
works in a "turtles all the way down" sense.

Stages
------

The first stage of this project is to write two interpreters that
provide useful statistics on the executions performed on them.  This
will become the basis of the metrics, how much load is removed from an
interpreter an arbitrarily large distance up the turtles.

The second stage will be to write a pair of base interpreters in each
of the two languages, one for each.  These will be used for simulating
the intermediate turtles.  It is important that these be some what
efficient so that the collected data is not ... I don't know that.

The third stage is to run some baseline tests on different towers to
approximate how much work needs doing at each depth. ("Hello, World"
and a small compiler are my current plan.)

The fourth stage is to write new versions of the interpreters with
different features that I want to test and see how they affect the
load experienced by the "base" layer.

Mathematical Justification
--------------------------

After an arbitrarily large number of layers the work to be done will
me mostly work for the act of running the interpreters rather than the
work of the actual task, at such a point the work performed by the
next layer will be a function of only the layer depth and time rather
than any details of the original task. (Assuming there are no
operations that can be present in the original task but are not
performed by the interpreters.)
