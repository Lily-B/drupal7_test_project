<?php

/**
 * Implements hook_drush_command().
 */
function drush_unpublish_drush_command() {

  $items['drush-unpublish-command'] = array(
    'description' => 'Unpublishes 2 days and older nodes.',
    'aliases' => array('unpublish'),
    'arguments' => array(
      'type' => 'The type of node (article, product or news).',
    ),
    'examples' => array(
      'drush unpublish article' => 'Unpublish all articles older than 2 days.',
      'drush unpublish news' => 'Unpublish all news older than 2 days.',
    ),
  );

  return $items;
}

/**
 * Callback for the drush-unpublish-command command
 */
function drush_drush_unpublish_command($type = FALSE) {

  // Check for existence of argument
  if (!$type) {
    $options = array(
      'article' => dt('Article'),
      'news' => dt('News'),
      'product' => dt('Product'),
    );
    $type = drush_choice($options, dt('What kind of node you\'d like to unpublish?'));
  }

  // Check for correct argument
  $correct_args = array('article', 'news', 'product');
  if (!in_array($type, $correct_args)) {
    return drush_set_error(dt('"@type" is not a valid statement type. Please choose between "news" and "article".', array('@type' => $type)));
  }
  drush_unpublish($type);
}