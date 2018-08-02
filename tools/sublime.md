<!-- MarkdownTOC -->

- [Plugins](#plugins)
  - [Installation](#installation)
  - [Configuration](#configuration)
  - [Usage](#usage)
  - [Sublime: Package control popular](#sublime-package-control-popular)
  - [plugin-examples](#plugin-examples)
- [Index tree for git](#index-tree-for-git)

<!-- /MarkdownTOC -->
# Plugins
### Installation

Bring up the Command Palette (Command+Shift+p on OS X, Control+Shift+p on Linux/Windows).
Select "Package Control: Install Package" (it'll take a few seconds)
Select __expected package__ when the list appears.
* [Git](https://packagecontrol.io/packages/Git)
* [GitGutter](https://packagecontrol.io/packages/GitGutter)
* [MarkdownTOC](https://packagecontrol.io/packages/MarkdownTOC)
* 

### Configuration
* Pick: Sublime Text > Preferences > Package Settings > MarkdownTOC > Settings - User

```
{
  "defaults": {
    "autolink": true,
    "indent": "  "
  }
}
```

* Pick: Sublime Text > Preferences > Package Settings > Git > Settings - User

* ...


### Usage
* Git

`Command+Shift+p on OS X, then git`

* MarkdownTOC

`Command+Shift+p on OS X, then MarkdownTOC`

or

`Pick from menu: Tools > MarkdownTOC > Insert TOC`

### [Sublime: Package control popular](https://packagecontrol.io/browse/popular)

### [plugin-examples](http://www.sublimetext.com/docs/plugin-examples)



# Index tree for git
```
I wrote a small script that does the trick:

#!/bin/bash

#File: tree-md

tree=$(tree -tf --noreport -I '*~' --charset ascii $1 |
       sed -e 's/| \+/  /g' -e 's/[|`]-\+/ */g' -e 's:\(* \)\(\(.*/\)\([^/]\+\)\):\1[\4](\2):g')

printf "# Project tree\n\n${tree}"
Example:
Original tree command:
$ tree
.
├── dir1
│   ├── file11.ext
│   └── file12.ext
├── dir2
│   ├── file21.ext
│   ├── file22.ext
│   └── file23.ext
├── dir3
├── file_in_root.ext
└── README.md

3 directories, 7 files
Markdown tree command:
$ ./tree-md .
# Project tree

.
 * [tree-md](./tree-md)
 * [dir2](./dir2)
   * [file21.ext](./dir2/file21.ext)
   * [file22.ext](./dir2/file22.ext)
   * [file23.ext](./dir2/file23.ext)
 * [dir1](./dir1)
   * [file11.ext](./dir1/file11.ext)
   * [file12.ext](./dir1/file12.ext)
 * [file_in_root.ext](./file_in_root.ext)
 * [README.md](./README.md)
 * [dir3](./dir3)
```
