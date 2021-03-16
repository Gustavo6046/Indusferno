# Indusferno C Reference

This section of the Indusferno documentation website describes internal
details about the Indusferno source code.

Note that this only applies to the C source code in `src/`. This is the
code that is compiled into ACS objects and that handles high-level
details about the game, like industries, companies and stations. The
actual in-game objects are written in ZDCode and compiled to DECORATE.

If you don't know what all that means, then you should probably get
acquainted with the basics of ZDoom modding before even considering
looking at the internal documentation of Indusferno. See the ZDoom wiki
pages on:

 * [DECORATE](https://zdoom.org/wiki/DECORATE)
 * [ACS](https://zdoom.org/wiki/ACS)

It is only possible to compile C into ACS bytecode thanks to the
[gdcc](https://github.com/DavidPH/GDCC) project. Many kudos to them.

Instead of writing plain DECORATE, our own
[ZDCode](https://github.com/zeta-group/ZDCode) project is used to
abstract away the more tedious parts of writing in DECORATE. More info
in the above-linked GitHub repository's README section.

## Table of Content

* [High Level](md_docs_doxygen_high.html)
* [Internals](md_docs_doxygen_internals.html)
* [Error Handling](m__error_8h.html)
* [Misc. Utilities](m__util_8h.html)
