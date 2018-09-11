<!-- MarkdownTOC -->

- [Installation](#installation)
  - [via curl](#via-curl)
  - [via wget](#via-wget)
  - [For non-sudoer, only change a specific user](#for-non-sudoer-only-change-a-specific-user)
- [Plugins](#plugins)
  - [Git](#git)

<!-- /MarkdownTOC -->

[oh-my-zsh](https://github.com/robbyrussell/oh-my-zsh) is a framework for managing your zsh configuration. 

Includes 200+ optional plugins, over 140 themes to spice up your morning, and an auto-update tool.

# Installation

### via curl

```
sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
```

### via wget

```
sh -c "$(wget https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"
```

### For non-sudoer, only change a specific user

```
export SHELL=/usr/bin/zsh
exec /usr/bin/zsh --login
```

# Plugins

```
plugins=(
  git
)
```

### Git
