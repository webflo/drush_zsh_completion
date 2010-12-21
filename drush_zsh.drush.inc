<?php
// $Id:

/**
 * @file
 *   Some commands for zsh completion
 */

/**
 * Implementation of hook_drush_command().
 *
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing each command.
 */
function drush_zsh_drush_command() {
  $items = array();

  $items['zsh-commands'] = array(
    'description' => 'Return all drush commands.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, 
    'hidden' => TRUE,
  );
  
  $items['zsh-options'] = array(
    'description' => 'Return command options.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'hidden' => TRUE,
  );

  return $items;
}

/**
 * Drush zsh-commands callback.
 */
function drush_drush_zsh_zsh_commands() {
  $rows = array();
  $commands = drush_get_commands();
  // ksort($commands);
    
  foreach($commands as $key => $command) {
    if (!$command['hidden']) {
      if (!array_key_exists('is_alias', $command) || !$command['is_alias']) {
        $command_completion[] = $key . ':' . $command['description'];
        foreach($command['aliases'] as $alias) {
          $command_completion[] = $alias . ':' . $command['description'];
        }
      }
    }
  }  
  
  // Newline-delimited list for zsh completion. Set the --commands option.
  if (isset($command_completion)) {
    drush_print_pipe($command_completion);
  }
  
  return;
}

/**
 * Drush zsh-options callback.
 */
function drush_drush_zsh_zsh_options() {
  $command = func_get_args();  
  $completion = array();
  
  if (!empty($command)) {
    // Drush command. Get specific options
    $commandstring = array_shift($command);
  
    $commands = drush_get_commands();
    if (array_key_exists($commandstring, $commands)) {
      $command = $commands[$commandstring];
      $completion = drush_zsh_extract_options($command);
    }
  } else {
    // No drush command. Get global options
    
    // TODO: Fix global options.
    // $completion = drush_zsh_extract_options(array('options' => drush_get_global_options()));  
  }
  
  drush_print_pipe($completion);
}

function drush_zsh_extract_options($command) {
  $row = array();
  if (is_array($command['options'])) {
    foreach($command['options'] as $option => $description) {
      $aliases = explode(',' , $option);
      foreach($aliases as $alias) {
        $row[] = trim($alias) . '['. $description .']';
      }
    }
  }
  return $row;
}
