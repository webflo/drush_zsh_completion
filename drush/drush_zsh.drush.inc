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
  
  $items['zsh-features-list'] = array(
    'description' => 'Return all features',
    'hidden' => TRUE,
  );

  return $items;
}

/**
 * Drush zsh-commands callback.
 */
function drush_drush_zsh_zsh_commands() {
  $phases = _drush_bootstrap_phases();
  // For speed, only bootstrap up to DRUSH_BOOTSTRAP_DRUPAL_SITE+1.
  $phases = array_slice($phases, 0, DRUSH_BOOTSTRAP_DRUPAL_SITE+1);

  $printed_rows = $rows = array();
  $phase_index = DRUSH_BOOTSTRAP_DRUSH;

  foreach ($phases as $phase_index) {
    if (drush_bootstrap_validate($phase_index)) {
      if ($phase_index > drush_get_context('DRUSH_BOOTSTRAP_PHASE')) {
        drush_bootstrap($phase_index);
      }

      $commands = drush_get_commands();
      // Filter by command file if specified.
      if ($commandfile = drush_get_option('filter')) {
        foreach ($commands as $key => $candidate) {
          if ($candidate['commandfile'] != $commandfile) {
            unset($commands[$key]);
          }
        }
      }

      $rows = array();
      ksort($commands);
      foreach($commands as $key => $command) {
        if (!$command['hidden']) {
          if (!array_key_exists('is_alias', $command) || !$command['is_alias']) {
            if (!array_key_exists($key, $printed_rows)) {
              $name = $command['aliases'] ? $key . ' (' . implode(', ', $command['aliases']) . ')': $key;
              $rows[$key] = array($name, $command['description']);
              $command_completion[] = $key . ':' . $command['description'];
              foreach($command['aliases'] as $alias) {
                $command_completion[] = $alias . ':' . $command['description'];
              }
            }
          }
        }
      }

      $printed_rows = array_merge($printed_rows, $rows);
    }
    else {
      break;
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
    foreach(drush_get_global_options() as $option => $info) {
      if (is_array($info)) {
        switch ($option) {
          case 'root':
            $function = ':directory:_path_files -/';
            $option .= '=';
            break;
          default:
            $function = '';
        }
        
        if ($info['short-form']) {
          $completion[] = '(-' . $info['short-form'] . ')-' . $info['short-form'] . '['. $info['description'] . ']' . $function;
        }
        $completion[] = '(--' . $option . ')--'  . $option . '[' . $info['description'] . ']' . $function;
      } else {
        $completion[] = '(--' . $option .')--' . $option . '[' . $info . ']' . $function;
      }
    }
  }

  drush_print_pipe($completion);
}

function drush_zsh_extract_options($command) {
  $row = array();
  if (is_array($command['options'])) {
    foreach($command['options'] as $option => $description) {
      $aliases = explode(',' , $option);
      foreach($aliases as $alias) {
        $row[] = '(--' . trim($alias) .')--' . trim($alias). '['. $description .']';
      }
    }
  }
  return $row;
}

function drush_drush_zsh_zsh_features_list() {
  module_load_include('inc', 'features', 'features.export');
  
  $rows = array();
  foreach (features_get_features(NULL, TRUE) as $k => $m) {
    $rows[] = $m->name;
  }
  
  $rows = implode(',', $rows);
  drush_print_pipe($rows);
}