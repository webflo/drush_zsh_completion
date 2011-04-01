# add drush completion function to path
fpath=($ZSH/plugins/drush $fpath)
autoload -U compinit
compinit -i
