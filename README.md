# Drush zsh completion

Dursh autocomplete awesomeness for zsh.

## Demo

- [http://bit.ly/hSq1E7](http://bit.ly/hSq1E7)

## Installation (zsh)

- Clone _drush\_zsh\_completion_
        
        git clone https://github.com/webflo/drush_zsh_completion.git ~/.drush/drush_zsh

- Clone _zsh\_drush\_plugin_

        git clone https://github.com/webflo/zsh_drush_plugin.git ~/.zsh/drush

- Load _zsh\_drush\_plugin_ in your ~/.zshrc (or ~/.zshrc.local). Copy & pase the following snippet.  

        fpath=(~/.zsh/drush $fpath)
        autoload -U compinit
        compinit -i  

- Start / restart zsh
    
- Have fun!

## Installation (oh-my-zsh)

- Clone _drush\_zsh\_completion_

        git clone https://github.com/webflo/drush_zsh_completion.git ~/.drush/drush_zsh

- Clone _zsh\_drush\_plugin_

        git clone https://github.com/webflo/zsh_drush_plugin.git ~/.oh-my-zsh/plugins/drush

- Load _zsh\_drush\_plugin_ in your ~/.zshrc. Add 'drush' to plugins()

- Start / restart zsh
    
- Have fun!

## Requirements

- [Drush 4.0-rc3](http://drupal.org/project/drush)
- [zsh](http://www.zsh.org/)
- Optional: [oh-my-zsh](https://github.com/robbyrussell/oh-my-zsh)