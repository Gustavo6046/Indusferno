# Indusferno Verbose Setup

This page describes very detailed instructions for downloading and
running Indusferno. It does not describe how to play the game. Only
use this as a detailed reference.

If you ~~are a dummy~~ only need the gist of it, please refer to the
[Indusferno Quickstart Guide](quickstart.md)


## Downloading

See the [Releases](https://github.com/Gustavo6046/Indusferno/releases)
section (of this project's GitHub repository), and download a pre-built
package of this mod.

You will most likely only need the "rel" build.

Each build will include both an "asset" and a "code" PK3 files. You will
need both of them to play Indusferno. This is so minor ZDCode changes
that don't affect other assets only require the "code" file to be
replaced with a newer version, without forcing players to download the
large "asset" file yet another time.

Using them is not complicated. Simply load both at the same time, as
instructed in the section below.


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
