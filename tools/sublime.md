<!-- MarkdownTOC -->

- [Plugins](#plugins)
  - [Installation](#installation)
  - [Markdown Preview](#markdown-preview)
  - [Compare Side-By-Side](#compare-side-by-side)
  - [packages for ReactJS on Sublime 3](#packages-for-reactjs-on-sublime-3)
  - [Configuration](#configuration)
  - [Usage](#usage)
  - [Sublime: Package control popular](#sublime-package-control-popular)
  - [plugin-examples](#plugin-examples)
  - [回到上一次光标编辑处](#%E5%9B%9E%E5%88%B0%E4%B8%8A%E4%B8%80%E6%AC%A1%E5%85%89%E6%A0%87%E7%BC%96%E8%BE%91%E5%A4%84)
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

### Markdown Preview

Preview and build your markdown files quickly in your web browser using Sublime Text 3.


[PackageControl](https://github.com/facelessuser/MarkdownPreview), which means you just have to

1. Open the command palette (`ctrl+shift+p`)
2. Search for: `Package Control: Install Package`
3. Search for: `MarkdownPreview`
4. hit <kbd>enter</kbd>

### Compare Side-By-Side
Side-by-side file comparison & difference tool for ST2/3

Installation Options
1. Search for and install using Package Control (ctrl+shift+P, “Install Package”)
2. Search for: `side-by-side`


* Usage Options
1. Right click on a tab and select “Compare with…”
2. Right click somewhere in the active view and select “Compare with…”
3. Right click on a tab and select “Compare with active tab”
4. Highlight text, right click -> “Mark selection for comparison”
5. Mark a second selection, then right click -> “Compare selections”
6. Create two selections by holding CTRL, then “Compare selections”
7. From the command line: see README_COMMANDS.md
8. Jump to next: Alt+N, Jump to previous: Alt+P

### packages for ReactJS on Sublime 3

* Babel: JSX/Babel Syntax Highlighting
* Babel Snippets: AutoComplete ReactJS
* Emmet: AutoComplete JSX/HTML
* SublimeLinter: A Linter, packages:
  * SublimeLinter
  * SublimeLinter-contrib-eslint
  * `npm install -g eslint`


https://medium.com/@adrianmcli/setting-up-sublime-text-3-for-reactjs-3bf6baceb73a

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


### 回到上一次光标编辑处

`windows下是alt+-, mac下是ctrl+-`


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
