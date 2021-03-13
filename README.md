# Indusferno

----

**DISCLAIMER: Please note that this project is in an UNFINISHED STATE,**
**and still far from completion. It is not yet in a playable state,**
**or anywhere near that; thus, do not follow any of the instructions**
**for downloading or playing this project, at this current state of.**
**the project**.

Friendly disclaimer that this is a **Work in Progress**. Thus, keep in
mind that the remainder of this document is currently meant for an
actual, _finished_ state of this project in the near future, and read
further. You have been noticed.

----

_"If OpenTTD and Doom had a child, it would be Indusferno. And it would
be nasty."_

This is a partial conversion themed around the art of moving cargo
around, truly an industry in its own right. Capitalist Doomguy realizes
there is potential in Hell to make money, and much more than he could
have imagined; and now he wants to make the most out of his hellish
adventures as he can.

To this end, he will set up a transport network, funneling monsters
into death traps to harvest cargo from them, and moving cargo around
between industries to make more money and even new, processed kinds of
cargo!

Watch your empire rise, as the money keeps trickling in from all sides
of your enterprise; or be a moron, and fail absolutely at moving any
cargo, while your company is devoured by unpayable debts and ultimately
dissolved, and back into the ground whence it rose. The choice is
yours! [But you'll probably prefer the former! I'd bet!]

Who would know those weird types were so ingenious in the
industrialization of the underworld.

## Downloading

See the [Releases](https://github.com/Gustavo6046/Indusferno/releases)
section (of this project's GitHub repository), and download a pre-built
package of this mod.

The built package on its own is cross-platform,

You will most likely only need the "rel" build. The "dbg" build is for


## Running

First, make sure you have those requirements met before you can run
this mod on your computer.

* You **WILL** need a sufficiently non-ancient
ZDoom or derived source port. This does include somewhat legacy
versions, notably Zandronum 3.0 and above. Note that this entails the
hardware requirements of whichever source port is chosen to run this
mod; please consult the sourceport's respective website or
documentation for details on that.

* Generally, you will also need the Doom 2 game data file (`doom2.wad`),
but simply because this mod does not supply its own, and tries to match
the aesthetics of Doom 2, as well as assuming a standard Doom 2
bestiary. It might still technically work with Freedoom, but it is not
directly supported by Indusferno; there is no guarantee that the
experience will be seamless. Please refer to the ZDoom websites for
instructions on acquiring Doom 2 and obtaining the necessary doom2.wad
file from it.

Once that is done, it is finally time to run it:

* To run this mod on Windows, drag-and-drop the desired .pk3 files
"into" the ZDoom executable; that is to say, hold the left mouse button
in order to hold them, as if you were to drag them into another
directory; then, instead of moving them, drag them into the ZDoom
executable file, in the same folder as `doom2.wad`. If you know how
to use the Command Prompt, you may also use that. For instance, with
LZDoom, in a folder with `doom2.wad` in it:

```console
C:\> cd C:\LZDoom
C:\LZDoom\> lzdoom.exe -iwad doom2.wad -file Indusferno-rel-assets.pk3 -file Indusferno-rel-code.pk3
```

* To run this mod on **Linux**, the quickiest and most direct, way is
through the command line. But fret not! It is a very simple and short
command that has to be typed. Besides, this is how Doom used to be
invoked, in a crude, bare DOS prompt. So don't be surprised that
this appears here. Anyway, in order to do this, make sure you have a
source port installed, then invoke it through the command line, passing
the paths to `doom2.wad` and to the Indusferno PK3 files.

```console
# if you don't have a source port yet, install one, e.g. with LZDoom:
$ sudo apt install lzdoom # on Debian/Ubuntu
$ sudo dnf install lzdoom # on Fedora
$ sudo pacman -S lzdoom   # on Arch Linux, etc.

# to run the mod, invoke your source port of choice with your files, eg
$ lzdoom -iwad doom2.wad -file Indusferno-rel-assets.pk3 -file Indusferno-rel-code.pk3
```


## Building

This guide assumes you're using Linux. If you're on Windows, building
this mod can be a very arduous and futile process, if not nigh
dehumanizing... or something.

Needless to say, building on Windows is not supported, and if you
_really_ want to, you'll have to figure it out on your own. Nonetheless
if you do, we wish you best of luck. You could've just grabbed a
pre-built release and went from there, though; see the Downloading
section above on how to do that precisely!

To build the ACS part of Indusferno code, use Ninja. A build.ninja file
is provided to build the project.

```console
$ ninja

...

  # now the ACS objects are built, e.g.
$ file bin/dbg/infindus.o bin/rel/infindus.o
bin/dbg/infindus.o: GLS_BINARY_LSB_FIRST
bin/rel/infindus.o: GLS_BINARY_LSB_FIRST
```

Once that is done, all that is left is using
[ZDCode](https://github.com/Gustavo6046/ZDCode)'s Zake build system to
package the `content` folder and the ACS binaries produced in `bin`
into ZDoom-ready packages, which will be put into `pkg`.

**If** you don't have ZDCode yet, install it:

```console
# hint: use pyenv or venv to install packages in self-contained
  # python environments
$ python3 -m pip install zdcode
...
```

Now you only have to actually build the omd.

```console
$ python3 -m zdcode
...


### Documentation

To build documentation, simply use the provided Doxyfile, and build
with Doxygen:

```console
$ doxygen Doxyfile

...

  # now documentation is built, e.g.
$ file doc/html/index.html
doc/html/index.html: HTML document, ASCII text
```

## Contributing

When adding any source files, pleas update build.ninja correspondingly.

## License

This project is licensed under the terms of the MIT Software License.
For details, please see [LICENSE](LICENSE).
