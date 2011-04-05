# Drush zsh completion

Drush autocomplete awesomeness for zsh.

## Demo

- [http://bit.ly/hSq1E7](http://bit.ly/hSq1E7)

## Installation (zsh)

- Clone _drush\_zsh_

        git clone --branch master http://git.drupal.org/sandbox/webflo/1113394.git ~/drush_zsh

- Load  _drush\_zsh_ in your drush folder.

        ln -s  ~/drush_zsh/drush/drush_zsh.drush.inc ~/.drush/drush_zsh.drush.inc

- Load _drush\_zsh_ in your ~/.zshrc (or ~/.zshrc.local). Copy & pase the following snippet.

        fpath=(~/drush_zsh/zsh $fpath)
        autoload -U compinit
        compinit -i

- Start / restart zsh

- Have fun!

## Installation (oh-my-zsh)

- Clone _drush\_zsh_

        git clone --branch master http://git.drupal.org/sandbox/webflo/1113394.git ~/drush_zsh

- Load  _drush\_zsh_ in your drush folder.

        ln -s  ~/drush_zsh/drush/drush_zsh.drush.inc ~/.drush/drush_zsh.drush.inc

- Load  _drush\_zsh_ in your oh-my-zsh plugins folder.

        ln -s ~/drush_zsh/zsh ~/.oh-my-zsh/plugins/drush

- Load  _drush\_zsh_ in your ~/.zshrc. Add 'drush' to plugins()

- Start / restart zsh

- Have fun!

## Updates

- Clone _drush\_zsh_ via git

        cd ~/drush_zsh && git pull origin master

## Requirements

- [Drush 4.x](http://drupal.org/project/drush)
- [zsh](http://www.zsh.org/)
- Optional: [oh-my-zsh](https://github.com/robbyrussell/oh-my-zsh)
