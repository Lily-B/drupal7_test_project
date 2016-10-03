<?php

/**
 * Implement hook_views_data().
 *
 * Describe table "pets_owners_storage" so that it can be used by views
 */
function pets_owners_storage_views_data() {

  $data['pets_owners_storage']['table']['group'] = t('Pets Owners table');

  $data['pets_owners_storage']['table']['base'] = array(
    'field' => 'id', // This is the identifier field for the view.
    'title' => t('Pets Owners table'),
    'help' => t('Pets Owners table contains all the pets owners in the db.'),
    'weight' => -10,
  );

  $data['pets_owners_storage']['id'] = array(
    'title' => t('Pets owners ID'),
    'help' => t('Some example content that references a node.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['pets_owners_storage']['first_name'] = array(
    'title' => t('First Name'),
    'help' => t('Pets owners first name.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['pets_owners_storage']['last_name'] = array(
    'title' => t('Last Name'),
    'help' => t('Pets owners last name.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['pets_owners_storage']['email'] = array(
    'title' => t('Email'),
    'help' => t('Pets owners email.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}