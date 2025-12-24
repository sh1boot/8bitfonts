 ▄█▀▀█▄ ▀██        ▀▀     ██      ▄█▀█▄                   ██    
 ▀█▄▄█▀  ██▀▀█▄   ▀██    ▀██▀▀   ▄██▄    ▄█▀▀█▄ ▀█▄▀▀█▄  ▀██▀▀  
 ██  ██  ██  ██    ██     ██ ▄▄   ██     ██  ██  ██  ██   ██ ▄▄ 
  ▀▀▀▀  ▀▀ ▀▀▀    ▀▀▀▀     ▀▀▀   ▀▀▀▀     ▀▀▀▀   ▀▀  ▀▀    ▀▀▀  

## 8-bit character generator ROM to TLF converter

Reads various ROM dumps of 8-bit bitmap fonts and writes out files
compatible with [toilet][] or [figlet][].

## Usage

You need a ROM dump and, generally, a [map file][] which is just one
line per character in the ROM stating what unicode codepoint each
character represents (Just the `U+xxxx` part, the rest is ignored).
The file needs as many lines as there are characters in the ROM, and
blank lines corresponding to characters with no Unicode mapping to keep
sync.

If the ROM is in ASCII order and you don't care about the bits around
the outside, the default behaviour with no map file is to assume the
first character read is space.  You can pass `-k <offset>` to skip over
whatever else is in the file leading up to that.

With those in place, run:
```sh
./8bitfont -i example.bin -m example.map -o example
```

(only the `-i` argument is essential if all the names are the same)

And you'll get a bunch of `example2.tlf`, `example4dot.tlf`, etc.,
files.  To use these, you'll need the `toilet` utility installed, and
then you can render some text with:

```sh
$ toilet -f example2dot "Hello world!"
⢸⣇⣸⡇⢀⡤⢤⡀⠀⢲⡆⠀⠀⢲⡆⠀⢀⡤⢤⡀⠀⠀⠀⠀⢠⡄⡀⣤⢀⡤⢤⡀⢠⡤⢤⡀⠀⢲⡆⠀⠀⣀⣰⡆⠀⢸⡇⠀
⠸⠇⠸⠇⠘⠯⠭⠁⠀⠼⠧⠀⠀⠼⠧⠀⠘⠧⠼⠃⠀⠀⠀⠀⠈⠿⠻⠏⠘⠧⠼⠃⠸⠇⠀⠀⠀⠼⠧⠀⠘⠧⠼⠇⠀⠠⠄⠀
```

## Compatibility

Whether or not you can see anything meaningful from the output of
`toilet` depends on your fonts.  `2dot` is widely supported because it
uses the Unicode Braille characters.  But this usually leaves an obvious
line through the middle.  `4wide` uses mostly [Block Elements][]
characters, which are widely supported, but it takes up a lot of screen
space.

The others dip into [Legacy Computing][] and [Legacy Computing
Supplement][] and get a bit messed up if the font doesn't support this.

So far the only font I've seen which supports all of these fonts is
[Iosevka][].

With the exception of the Braille output, most of these use Unicode's
[Figure Space][] for spacing.  I couldn't find anything better.  Regular
ASCII will be too narrow if the text is rendered outside of a monospaced
context.  Figure space seems to mostly work.  This interferes with the
"smushing" feature in `toilet` and `figlet` and I'm not sure I can do
much about that, except maybe to revert to ASCII space.

## Sources of fonts

I found a couple of repos with ROMS:
* <https://github.com/ivop/8x8-fonts/>
* <https://github.com/spacerace/romfont/>
which I added as git submodules, so you can fetch those with
`git submodule update`.

Some of these need the `-k` argument to skip some noise at the
beginning.  For example, .64c files have a two-byte load address,
requiring `-k2` to avoid.  Some ROMs might contain a whole kernel or
BASIC interpreter to skip over.

I also dumped a few pre-built outputs from this tool in [my toilet
fonts][] repo (and there are other toilet font collections out there if
you go digging).

## Extending

There's a `Patcher` class in the source code, and an example usage which
adds drop shadows to one of the output modes.  It takes a list of
patterns to match in the bitmap (where `' '` (space) must be zero,
`'@'` must be 1, and any other character (eg., `'.'`) can be any value),
and the character to place if the pattern matches.  This mode uses more
surrounding context than the generator it applies to, so it's able to
look for, for example, pixels which would cast a shadow on the current
cell.  I figure this should also be usable to distinguish between
diagonal lines and orthogonal corners, and to place better-shaped
characters to smooth out the diagonals.  If no patch matches then it
falls through to the default block map.


[map file]: <c64.map>
[toilet]: <https://github.com/cacalabs/toilet>
[toilet-insecure]: <http://caca.zoy.org/wiki/toilet>
[figlet]: <https://www.figlet.org/>
[Iosevka]: <https://typeof.net/Iosevka/>
[Block Elements]: <https://www.unicode.org/charts/PDF/U2580.pdf>
[Legacy Computing]: <https://www.unicode.org/charts/PDF/U1FB00.pdf>
[Legacy Computing Supplement]: <https://www.unicode.org/charts/PDF/U1CC00.pdf>
[Figure space]: <https://en.wikipedia.org/wiki/Figure_space>
[my toilet fonts]: <https://github.com/sh1boot/toilet-fonts>
